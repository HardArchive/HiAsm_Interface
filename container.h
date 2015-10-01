#pragma once

//Project
#include "global.h"

//STL

//Qt

class Container
{
private:
    Elements m_elements;

public:
    Container();

public:
    void addElement(const SElement &element);
};
