#include "property.h"

Property::Property(PCodeGenTools cgt, id_proplist proplist, id_element elementId)
    : m_cgt(cgt)
    , m_proplist(proplist)
    , m_elId(elementId)
{
    getPropertyData();
}

Property::~Property()
{
}

void Property::getPropertyData()
{
    m_propId = m_cgt->plGetProperty(m_proplist);
    
    m_name = m_cgt->propGetName(m_propId);
    m_type = m_cgt->propGetType(m_propId);
    m_value = m_cgt->propGetValue(m_propId);
}
