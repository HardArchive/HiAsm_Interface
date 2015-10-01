#pragma once

//Project
#include "CGTShare.h"
#include "point.h"
#include "property.h"
#include "cgt.h"
#include "global.h"

//STL

//Qt
#include <QString>

class Element
{
private:
    const id_element m_eId {};

    Containers m_containers;
    Points m_points;
    Properties m_properties;
    
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
    explicit Element(id_element eId);
    ~Element();

private:
    void getElementData();

public:
    //ru Добавляем контейнер в список контейнеров элемента
    void addContainer(const SContainer &container);

};
