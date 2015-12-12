//Project
#include "container.h"
#include "cgt.h"
#include "element.h"

//STL

//Qt

Container::Container(id_sdk id, PElement parent)
    : m_id(id)
    , m_parent(parent)
{

}

id_element Container::findElementByName(QString name)
{
    for (PElement e : m_elements) {
        if (e->m_className == name) {
            return reinterpret_cast<id_element>(e);
        }
    }

    return 0;
}
