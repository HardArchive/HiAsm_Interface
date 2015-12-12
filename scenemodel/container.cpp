//Project
#include "container.h"
#include "element.h"
#include "cgt/cgt.h"

//STL

//Qt

Container::Container(quintptr id, PElement parent)
    : m_id(id)
    , m_parent(parent)
{

}

quintptr Container::findElementByName(QString name)
{
    /*
    for (PElement e : m_elements) {
        if (e->m_className == name) {
            return reinterpret_cast<id_element>(e);
        }
    }
    */
    return 0;
}

quintptr Container::getId() const
{
    return m_id;
}
