//Project
#include "element.h"

//STL

//Qt

Element::Element(id_element eId, PContainer parent)
    : m_id(eId)
    , m_parent(parent)
{
    collectingData();
}

Element::~Element()
{
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
    for(int i = 0; i < m_ptCount; ++i) {
        id_prop pointId = cgt::elGetPt(m_id, i);
        m_points.append(new Point(pointId, this));
    }

    //ru Получаем информацию о свойствах
    for(int i = 0; i < m_propCount; ++i) {
        id_prop propId = cgt::elGetProperty(m_id, i);
        m_properties.append(new Property(propId, this));
    }
}
