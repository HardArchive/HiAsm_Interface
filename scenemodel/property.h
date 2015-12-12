#pragma once

//Project
#include "types.h"
#include "proptypes.h"

//STL

//Qt
#include <QDebug>

class Property
{
private:
    //ru Данные
    const quintptr m_id;
    QString m_name;
    DataTypes m_type{};
    int m_isTranslate{};

    //ru Указатели и ссылки
    PElement m_parent;

    //Список значений свойства
    PropValues m_propValues;

public:
    Property(quintptr propId, PElement parent);
    friend class SceneModel;

private:
    void collectingData();

public:
    quintptr getId() const;

};
