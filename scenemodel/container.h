#pragma once

//Project
#include "types.h"

//STL

//Qt

class Container
{
private:
    const quintptr m_id;
    PElement m_parent{};
    Elements m_elements;

public:
    Container(quintptr id, PElement parent);
    friend class SceneModel;

public:
    PElement getElementByName(const QString &name) const;
    quintptr getIdElementByName(const QString &name) const;
    quintptr getId() const;
    PElement getElementByIndex(quintptr index) const;
    quintptr getIdElementByIndex(quintptr index) const;
    PElement getParent() const;
};
