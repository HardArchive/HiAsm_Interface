#pragma once

//Project
#include "CGTShare.h"
#include "cgtsharewrapper.h"

//STL
#include <windows.h>

//Qt
#include <QDebug>
#include <QSharedPointer>

class Property;
typedef QSharedPointer<Property> PProperty;
typedef QVector<PProperty> ArrayPProperties;

typedef QPair<QVariant, DataTypes> PropValue;
typedef QList<PropValue> ListPropValue;

class Property {
private:
    const PCodeGenTools m_cgt{};
    const id_prop m_propId{};
    const id_element m_elId{};

    //ru Данные свойства
    ListPropValue m_listPropValue;
    QString m_name;
    DataTypes m_type{};
    int m_isTranslate{};

public:
    Property(PCodeGenTools cgt, id_prop propId, id_element elementId);
    ~Property();

private:
    void getPropertyData();
    void getValues();
};
