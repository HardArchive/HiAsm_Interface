//Project
#include "element.h"
#include "container.h"
#include "point.h"
#include "property.h"
#include "cgt/cgt.h"

//STL

//Qt


Element::Element(quintptr id_element, PSceneModel model, QObject *parent)
    : QObject(parent)
    , m_id(id_element)
    , m_model(model)
{
    collectingData();
}

void Element::collectingData()
{
    m_className = QString::fromLocal8Bit(cgt::elGetClassName(m_id));
    m_codeName = QString::fromLocal8Bit(cgt::elGetCodeName(m_id));
    m_classIndex = cgt::elGetClassIndex(m_id);
    m_flags = cgt::elGetFlag(m_id);
    m_inherit = QString::fromLocal8Bit(cgt::elGetInherit(m_id));
    m_group = cgt::elGetGroup(m_id);
    m_interface = QString::fromLocal8Bit(cgt::elGetInterface(m_id));
    m_infSub = QString::fromLocal8Bit(cgt::elGetInfSub(m_id));
    m_linkIs = cgt::elLinkIs(m_id);
    m_linkMain = cgt::elLinkMain(m_id);
    m_propCount = cgt::elGetPropCount(m_id);
    m_ptCount = cgt::elGetPtCount(m_id);

    cgt::elGetPos(m_id, m_posX, m_posY);
    cgt::elGetSize(m_id, m_sizeW, m_sizeH);

    //ru Получаем информацию о точках
    for (int i = 0; i < m_ptCount; ++i) {
        quintptr pointId = cgt::elGetPt(m_id, i);
        m_points.append(new Point(pointId, m_model, this));
    }

    //ru Получаем информацию о свойствах
    for (int i = 0; i < m_propCount; ++i) {
        quintptr propId = cgt::elGetProperty(m_id, i);
        m_properties.append(SharedProperty::create(propId, m_model, this));
    }

    //ru Помечаем свойства, значения которых совпадают со стандартным из INI.
    for (int i = 0; i < m_propCount; ++i) {
        bool def = cgt::elIsDefProp(m_id, i);
        m_properties[i]->setIsDefault(def);
    }

}

quintptr Element::getId() const
{
    return m_id;
}

PSceneModel Element::getModel() const
{
    return m_model;
}

QString Element::getClassName() const
{
    return m_className;
}

ElementFlags Element::getFlags() const
{
    return ElementFlags(int(m_flags));
}

void Element::setCodeName(const QString &name)
{
    m_codeName = name;
}

QString Element::getCodeName() const
{
    return m_codeName;
}

quintptr Element::getUserData() const
{
    return m_userData;
}

void Element::setUserData(quintptr userData)
{
    m_userData = userData;
}

ElementClass Element::getClassIndex()
{
    return m_classIndex;
}

PContainer Element::getParent() const
{
    return qobject_cast<PContainer>(parent());
}

int Element::getCountProps() const
{
    return m_propCount;
}

SharedProperty Element::getPropertyByIndex(uint index) const
{
    if (index < m_properties.size())
        return m_properties[index];
    else
        return SharedProperty();
}

quintptr Element::getIdPropertyByIndex(uint index) const
{
    const SharedProperty e = getPropertyByIndex(index);
    if (!e)
        return 0;

    return e->getId();
}

SharedProperty Element::getPropertyById(quintptr id_prop) const
{
    if (!id_prop)
        return SharedProperty();

    for (SharedProperty p : m_properties) {
        if (p->getId() == id_prop) {
            return p;
        }
    }

    return SharedProperty();
}

int Element::getCountPoints() const
{
    return m_ptCount;
}

PPoint Element::getPointByIndex(uint index) const
{
    if (index < m_points.size())
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

bool Element::getLinkIs() const
{
    return m_linkIs;
}

int Element::getPosX() const
{
    return m_posX;
}

int Element::getPosY() const
{
    return m_posY;
}

int Element::getSizeW() const
{
    return m_sizeW;
}

int Element::getSizeH() const
{
    return m_sizeH;
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

int Element::getCountContainers() const
{
    return m_containers.size();
}

QString Element::getInterface() const
{
    return m_interface;
}

QString Element::getInherit() const
{
    return m_inherit;
}

PPoint Element::getPointByName(const QString &name) const
{
    for (const PPoint p : m_points) {
        if (p->getName() == name) {
            return p;
        }
    }

    return nullptr;
}

quintptr Element::getIdPointByName(const QString &name) const
{
    const PPoint p = getPointByName(name);
    if(!p)
        return 0;

    return p->getId();
}
