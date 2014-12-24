#ifndef PROPERTY_H
#define PROPERTY_H

//STL
#include <windows.h>

//Qt
#include <QDebug>

//Project
#include "CGTShare.h"
#include "cgtsharewrapper.h"

class Property {
private:
    const PCodeGenTools m_cgt;
    const id_point m_propId;
    const id_element m_elId;

    //ru Данные свойства
    id_element m_linkedElement{};
    id_element m_linkedElementInfo{};
    QString m_name{};
    int m_type{};
    void* m_value{};
    int m_isTranslate{};

public:
    Property(PCodeGenTools cgt, id_prop propId, id_element elementId);
    ~Property();

private:
    void getPropertyData();
    
};

#endif // PROPERTY_H
