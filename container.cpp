#include "container.h"
#include "cgt.h"

Container::Container(id_sdk id, PElement parent)
    : m_id(id)
    , m_parent(parent)
{

}

void Container::addElement(PElement element)
{
    m_elements.append(element);
}
