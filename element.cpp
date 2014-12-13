//STL

//Qt

//Project
#include "element.h"

Element::Element(PCodeGenTools cgt, id_element eId) :
    m_cgt(cgt),
    m_eId(eId)
{
    m_className = m_cgt->elGetClassName(eId);
    m_classIndex = m_cgt->elGetClassIndex(eId);
    
    
}

void Element::append(PContainer container)
{
    if( m_arrayContainers == nullptr )
        m_arrayContainers = make_shared<ArrayPContainers>();
    
    m_arrayContainers->append( container );
}
