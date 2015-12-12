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
    Elements m_elements{};

public:
    Container(quintptr id, PElement parent);
    friend class SceneModel;

public:
    quintptr findElementByName(QString name);
    quintptr getId() const;
};
