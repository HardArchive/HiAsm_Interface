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
        m_properties.append(new Property(propId, m_model, this));
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

PProperty Element::getPropertyByIndex(int index) const
{
    int size = m_properties.size();
    if ((index >= 0) && (index < size))
        return m_properties[index];
    else
        return nullptr;
}

quintptr Element::getIdPropertyByIndex(int index) const
{
    PProperty e = getPropertyByIndex(index);
    if (!e)
        return 0;

    return e->getId();
}

PProperty Element::getPropertyById(quintptr id_prop) const
{
    if (!id_prop)
        return nullptr;

    for (const PProperty p : m_properties) {
        if (p->getId() == id_prop) {
            return p;
        }
    }

    return nullptr;
}

int Element::getCountPoints() const
{
    return m_ptCount;
}

PPoint Element::getPointByIndex(int index) const
{
    int size = m_points.size();
    if ((index >= 0) && (index < size))
        return m_points[index];
    else
        return nullptr;
}

quintptr Element::getIdPointByIndex(int index) const
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
    if (!m_containers.isEmpty())
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
