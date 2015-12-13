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
    bool m_isDefault{};

    //ru Указатели и ссылки
    PElement m_parent;

    //Данные свойства
    PropValues m_propValues;

public:
    Property(quintptr propId, PElement parent);
    friend class SceneModel;

private:
    void collectingData();

public:
    quintptr getId() const;
    DataTypes getType() const;
    bool getIsDefault() const;
    void setIsDefault(bool value);
    int getValueInt() const;
    QString getValueString() const;
    float getValueFloat() const;
    uchar getValueByte() const;
    QString getName() const;
};
