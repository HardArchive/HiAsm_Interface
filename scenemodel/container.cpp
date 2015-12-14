//Project
#include "container.h"
#include "element.h"
#include "cgt/cgt.h"

//STL

//Qt


Container::Container(quintptr id_sdk, PSceneModel model, QObject *parent)
    : QObject(parent)
    , m_id(id_sdk)
    , m_model(model)
{

}

PElement Container::getElementByName(const QString &name) const
{
    for (PElement e : m_elements) {
        if (e->getClassName() == name) {
            return e;
        }
    }

    return 0;
}

quintptr Container::getIdElementByName(const QString &name) const
{
    PElement e = getElementByName(name);
    if (e)
        return e->getId();

    return 0;
}

quintptr Container::getId() const
{
    return m_id;
}

PElement Container::getElementByIndex(quintptr index) const
{
    if (index < m_elements.size())
        return m_elements[index];
    else
        return nullptr;
}

quintptr Container::getIdElementByIndex(quintptr index) const
{
    if (index < m_elements.size())
        return m_elements[index]->getId();
    else
        return 0;
}

PElement Container::getParent() const
{
    return qobject_cast<PElement>(parent());
}
