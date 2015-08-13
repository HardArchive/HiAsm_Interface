#pragma once

//Project
#include "CGTShare.h"
#include "point.h"
#include "property.h"
#include "cgtsharewrapper.h"
#include "global.h"

//STL

//Qt
#include <QString>

class Element {
private:
    const PCodeGenTools m_cgt{};
    const id_element m_eId{};

    ArrayPContainers m_arrayContainers;
    ArrayPPoints m_arrayPoints;
    ArrayPProperties m_arrayProperties;
    
    //ru Данные элемента
    QString m_className{};
    ClassesElements m_classIndex{};
    ElementFlgs m_flags{};
    QString m_inherit{};
    int m_SDKCount{};
    int m_group{};
    QString m_interface{};
    QString m_infSub{};
    int m_propCount{};
    int m_propertyListCount{};
    int m_ptCount{};
    bool m_linkIs{};
    id_element m_linkMain{};
    int m_posX{};
    int m_posY{};
    int m_sizeW{};
    int m_sizeH{};

public:
    explicit Element(PCodeGenTools cgt, id_element eId);
    ~Element();

    //ru Добавляем в элемент указатель на контейнер
    void append(PContainer container);

    //ru Возвращаем данные элемента в текстовом формате (для тестов).
    QString getDataText(uchar inc = 0) const;

private:
    void getElementData();
};
