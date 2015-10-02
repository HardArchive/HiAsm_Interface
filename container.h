#pragma once

//Project
#include "global.h"
#include "CGTShare.h"

//STL

//Qt

class Container
{
private:

    //Данные контейнера
    const id_sdk m_id;

    //Указатели и ссылки
    PElement m_parent;

    //Массив элементов
    Elements m_elements;

public:
    Container(id_sdk id, PElement parent);

private:
    void collectingData();

public:
    void addElement(PElement element);
    Elements &getElements()
    {
        return m_elements;
    }
};
