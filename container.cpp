#include "container.h"

Container::Container()
{

}

void Container::addElement(const SElement &element)
{
    m_elements.append(element);
}
