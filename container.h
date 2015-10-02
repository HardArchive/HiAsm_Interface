#pragma once

//Project
#include "CGTShare.h"
#include "global.h"


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
    friend class DataCollector;
};
