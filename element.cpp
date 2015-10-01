//STL

//Qt
#include <QTextStream>
#include <QDebug>

//Project
#include "element.h"

Element::Element(id_element eId)
    : m_eId(eId)
{
    getElementData();
}

Element::~Element()
{
}

void Element::addContainer(const SContainer &container)
{
    m_containers.append(container);
}

void Element::getElementData()
{
    m_className = QString::fromLocal8Bit(cgt::elGetClassName(m_eId));
    m_classIndex = cgt::elGetClassIndex(m_eId);
    m_flags = cgt::elGetFlag(m_eId);
    m_inherit = QString::fromLocal8Bit(cgt::elGetInherit(m_eId));
    m_SDKCount = cgt::elGetSDKCount(m_eId);
    m_group = cgt::elGetGroup(m_eId);
    m_interface = QString::fromLocal8Bit(cgt::elGetInterface(m_eId));
    m_infSub = QString::fromLocal8Bit(cgt::elGetInfSub(m_eId));
    m_propCount = cgt::elGetPropCount(m_eId);
    m_propertyListCount = cgt::elGetPropertyListCount(m_eId);
    m_ptCount = cgt::elGetPtCount(m_eId);
    m_linkIs = cgt::elLinkIs(m_eId);
    m_linkMain = cgt::elLinkMain(m_eId);

    cgt::elGetPos(m_eId, m_posX, m_posY);
    cgt::elGetSize(m_eId, m_sizeW, m_sizeH);

    //ru Получаем информацию о точках
    for(int i = 0; i < m_ptCount; ++i) {
        m_points.append(SPoint::create(cgt::elGetPt(m_eId, i)));
    }

    //ru Получаем информацию о свойствах
    for(int i = 0; i < m_propCount; ++i) {
        id_prop propId = cgt::elGetProperty(m_eId, i);
        m_properties.append(SProperty::create(propId, m_eId));
    }
}
