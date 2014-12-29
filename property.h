#ifndef PROPERTY_H
#define PROPERTY_H

//STL
#include <windows.h>

//Qt
#include <QDebug>
#include <QSharedPointer>

//Project
#include "CGTShare.h"
#include "cgtsharewrapper.h"

class Property;
typedef QList<Property> ListProperties;

typedef QPair<QVariant, DataTypes> PropValue;
typedef QList<PropValue> ListPropValue;

class Property {
private:
    PCodeGenTools m_cgt{};
    id_proplist m_proplist{};
    id_element m_elId{};

    //ru Данные свойства
    ListPropValue m_listPropValue;
    id_prop m_propId{};
    QString m_name;
    DataTypes m_type{};
    int m_isTranslate{};

public:
    Property(PCodeGenTools cgt, id_proplist proplist, id_element elementId);
    ~Property();

private:
    void getPropertyData();
    void getValues();
};

#endif // PROPERTY_H
