//Project
#include "element.h"
#include "container.h"
#include "point.h"
#include "property.h"
#include "scenemodel.h"
#include "cgt/cgt.h"

//STL

//Qt


Element::Element(quintptr id_element, const SharedConfElement &conf, QObject *parent)
    : QObject(parent)
    , m_id(id_element)
    , m_cgt(parent->property("cgt").value<PCodeGenTools>())
    , m_model(parent->property("model").value<PSceneModel>())
    , m_conf(conf)
{
    m_model->addElementToMap(this);
    collectingData();
}

void Element::collectingData()
{
    m_flags = m_cgt->elGetFlag(m_id);
    m_linkIs = m_cgt->elLinkIs(m_id);
    m_linkMain = m_cgt->elLinkMain(m_id);
    m_codeName = QString::fromLocal8Bit(m_cgt->elGetCodeName(m_id));

    //ru Получаем информацию о точках
    int countPoints = m_conf->getCountPoints();
    for (int i = 0; i < countPoints; ++i) {
        quintptr pointId = m_cgt->elGetPt(m_id, i);

        const SharedConfPoint conf = m_conf->getPointByIndex(i);
        addPoint(new Point(pointId, conf, this));
    }

    /*
    if (fcgt::isLink(m_flags))
        return;

    //ru Элемент содержит контейнер(ы)
    if (fcgt::isMulti(m_flags)) {
        //ru Элемен содержит полиморфный контейнер
        if (fcgt::isPolyMulti(getClassIndex())) {
            //ru Получаем к-во контейнеров, которое содержит текущий элемент
            int countContainers = m_cgt->elGetSDKCount(m_id);

            for (int i = 0; i < countContainers; ++i) {
                //ru Получаем ID контейнера
                quintptr id_sdk = m_cgt->elGetSDKByIndex(m_id, i);
                QString name = QString::fromLocal8Bit(m_cgt->elGetSDKName(id_sdk, i));

                //ru Добавляем контейнер в элемент
                addContainer(new Container(id_sdk, this))->setName(name);
            }
        } else { //ru Элемент содержит обычный контейнер

            //ru Получаем ID контейнера элемента
            quintptr id_sdk = m_cgt->elGetSDK(m_id);

            //ru Добавляем контейнер в элемент
            addContainer(new Container(id_sdk, this));
        }
    }
    */
}

quintptr Element::getId() const
{
    return m_id;
}

PContainer Element::getParent() const
{
    return qobject_cast<PContainer>(parent());
}

QString Element::getName() const
{
    return m_conf->getName();
}

void Element::setUserData(quintptr userData)
{
    m_userData = userData;
}

quintptr Element::getUserData() const
{
    return m_userData;
}

ElementClass Element::getClassIndex()
{
    return ElementIndexMap[m_conf->getClassName()];
}

void Element::setFlags(const ElementFlgs &flags)
{
    m_flags = flags;
}

ElementFlags Element::getFlags() const
{
    return ElementFlags(int(m_flags));
}

void Element::setLinkIs(bool linkIs)
{
    m_linkIs = linkIs;
}

bool Element::getLinkIs() const
{
    return m_linkIs;
}

void Element::setLinkMain(quintptr linkMain)
{
    m_linkMain = linkMain;
}

quintptr Element::getLinkMain() const
{
    return m_linkMain;
}

void Element::setPosX(int posX)
{
    m_posX = posX;
}

int Element::getPosX() const
{
    return m_posX;
}

void Element::setPosY(int posY)
{
    m_posY = posY;
}

int Element::getPosY() const
{
    return m_posY;
}

void Element::setSizeW(int sizeW)
{
    m_sizeW = sizeW;
}

int Element::getSizeW() const
{
    return m_sizeW;
}

void Element::setSizeH(int sizeH)
{
    m_sizeH = sizeH;
}

int Element::getSizeH() const
{
    return m_sizeH;
}

QString Element::getClassName() const
{
    return m_conf->getClassName();
}

void Element::setCodeName(const QString &name)
{
    m_codeName = name;
}

QString Element::getCodeName() const
{
    return m_codeName;
}

QString Element::getInterface() const
{
    return m_conf->getInterface();
}

QString Element::getInherit() const
{
    return m_conf->getInherit().join(',');
}

QString Element::getInfSub() const
{
    return m_conf->getSub();
}

PCodeGenTools Element::getCgt()
{
    return m_cgt;
}

PSceneModel Element::getModel()
{
    return m_model;
}

int Element::getCountContainers() const
{
    return m_containers.size();
}

PContainer Element::getContainer() const
{
    if (m_containers.isEmpty())
        return nullptr;

    return m_containers[0];
}

quintptr Element::getIdContainer() const
{
    const PContainer c = getContainer();
    if (!c)
        return 0;

    return c->getId();
}

PContainer Element::getContainerByIndex(uint index)
{
    if (index < uint(m_containers.size()))
        return m_containers[index];
    else
        return nullptr;
}

quintptr Element::getIdContainerByIndex(uint index)
{
    const PContainer c = getContainerByIndex(index);
    if (!c)
        return 0;

    return c->getId();
}

PContainer Element::addContainer(PContainer container)
{
    m_containers.append(container);
    return container;
}

void Element::removeContainer(uint index)
{
    m_containers.remove(index);
}

int Element::getIndexPointById(quintptr id_point) const
{
    int size = m_points.size();
    for (int i = 0; i < size; ++i) {
        if (m_points[i]->getId() == id_point) {
            return i;
        }
    }

    return -1;
}

int Element::getCountPoints() const
{
    return m_points.size();
}

PPoint Element::getPointByIndex(uint index) const
{
    if (index < uint(m_points.size()))
        return m_points[index];
    else
        return nullptr;
}

quintptr Element::getIdPointByIndex(uint index) const
{
    const PPoint p = getPointByIndex(index);
    if (!p)
        return 0;

    return p->getId();
}

PPoint Element::getPointByName(const QString &name) const
{
    for (const PPoint p : m_points) {
        if (QString::compare(p->getName(), name, Qt::CaseInsensitive) == 0) {
            return p;
        }
    }

    return nullptr;
}

quintptr Element::getIdPointByName(const QString &name) const
{
    const PPoint p = getPointByName(name);
    if (!p)
        return 0;

    return p->getId();
}

PPoint Element::addPoint(PPoint point)
{
    m_points.append(point);
    return point;
}

void Element::removePoint(uint index)
{
    m_points.remove(index);
}

int Element::getCountProps() const
{
    return m_properties.size();
}

PProperty Element::getPropertyByIndex(uint index) const
{
    if (index < uint(m_properties.size()))
        return m_properties[index];
    else
        return PProperty();
}

quintptr Element::getIdPropertyByIndex(uint index) const
{
    const PProperty e = getPropertyByIndex(index);
    if (!e)
        return 0;

    return e->getId();
}

PProperty Element::getPropertyById(quintptr id_prop) const
{
    if (!id_prop)
        return PProperty();

    for (PProperty p : m_properties) {
        if (p->getId() == id_prop) {
            return p;
        }
    }

    return PProperty();
}

PProperty Element::getPropertyByName(const QString &name) const
{
    for (PProperty p : m_properties) {
        if (QString::compare(p->getName(), name, Qt::CaseInsensitive) == 0) {
            return p;
        }
    }

    return PProperty();
}

quintptr Element::getIdPropertyByName(const QString &name) const
{
    PProperty p = getPropertyByName(name);
    if (!p)
        return 0;

    return p->getId();
}

PProperty Element::addProperty(PProperty property)
{
    m_properties.append(property);
    return property;
}

bool Element::getIsDefPropByIndex(uint index)
{
    return false; //TODO закончить реализацию getIsDefPropByIndex
}
