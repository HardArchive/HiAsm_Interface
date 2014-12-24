#ifndef PROPERTY_H
#define PROPERTY_H

//STL
#include <windows.h>

//Qt
#include <QDebug>

//Project
#include "CGTShare.h"
#include "cgtsharewrapper.h"

class Property;
typedef QSharedPointer<Property> PProperty;
typedef QVector<PProperty> ArrayPProperties;

class Property {
private:
    PCodeGenTools m_cgt{};
    id_proplist m_proplist{};
    id_element m_elId{};

    //ru Данные свойства
    id_prop m_propId{};
    id_element m_linkedElement{};
    id_element m_linkedElementInfo{};
    QString m_name{};
    DataTypes m_type{};
    void* m_value{};
    int m_isTranslate{};

public:
    Property(PCodeGenTools cgt, id_proplist proplist, id_element elementId);
    ~Property();

private:
    void getPropertyData();
    
};

#endif // PROPERTY_H
