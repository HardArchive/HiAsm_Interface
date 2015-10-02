#pragma once

//Project
#include "point.h"
#include "property.h"
#include "CGTShare.h"
#include "cgt.h"
#include "global.h"

//STL

//Qt
#include <QString>

class Element
{
private:
    //ru Данные элемента
    const id_element m_id;
    id_element m_linkMain{};

    //Указатели и ссылки
    PContainer m_parent{};
    PElement m_linkMainPtr{};

    QString m_className{};
    QString m_codeName{};
    ElementClass m_classIndex{};
    ElementFlgs m_flags{};
    QString m_inherit{};
    int m_group{};
    QString m_interface{};
    QString m_infSub{};
    bool m_linkIs{};
    int m_propCount{};
    int m_ptCount{};

    int m_posX{};
    int m_posY{};
    int m_sizeW{};
    int m_sizeH{};

    //Массивы
    Containers m_containers;
    Points m_points;
    Properties m_properties;

public:
    explicit Element(id_element eId, PContainer parent);
    ~Element();

private:
    void collectingData();

public:
    friend class DataCollector;
    friend class Container;
    friend class Point;
    friend class Property;

};
