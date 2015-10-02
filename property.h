#pragma once

//Project
#include "CGTShare.h"
#include "cgt.h"
#include "global.h"

//STL

//Qt
#include <QDebug>

typedef QPair<QVariant, DataTypes> PropValue;
typedef QList<PropValue> PropValues;

class Property
{
private:

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

private:
    void collectingData();
    void getValues();

public:
    friend class DataCollector;

};
