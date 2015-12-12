#pragma once

//Project
#include "CGTShare.h"
#include "global.h"

//STL

//Qt

class Container
{
public:

    //Данные контейнера
    const id_sdk m_id;

    //Указатели и ссылки
    PElement m_parent;

    //Массив элементов
    Elements m_elements;

public:
    Container(id_sdk id, PElement parent);

public:
    id_element findElementByName(QString name);

};
