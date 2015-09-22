#pragma once

//Project
#include "CGTShare.h"
#include "cgt.h"

//STL
#include <windows.h>
#include <memory>

//Qt
#include <QDebug>

class Property;
typedef std::shared_ptr<Property> PProperty;
typedef std::vector<PProperty> ArrayPProperties;

typedef std::pair<QVariant, DataTypes> PropValue;
typedef QList<PropValue> ListPropValue;

class Property {
private:
    const id_prop m_propId{};
    const id_element m_elId{};

    //ru Данные свойства
    ListPropValue m_listPropValue;
    QString m_name;
    DataTypes m_type{};
    int m_isTranslate{};

public:
    Property(id_prop propId, id_element elementId);
    ~Property();

private:
    void getPropertyData();
    void getValues();
};
