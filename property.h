#pragma once

//Project
#include "datatypes.h"

//STL

//Qt
#include <QDebug>

class Property
{
public:
    //ru Данные
    const id_prop m_id;
    QString m_name;
    DataTypes m_type{};
    int m_isTranslate{};

    //ru Указатели и ссылки
    PElement m_parent;

    //Список значений свойства
    PropValues m_propValues;

public:
    Property(id_prop propId, PElement parent);
    ~Property();

public:
    void collectingData();
    void getValues();

};
