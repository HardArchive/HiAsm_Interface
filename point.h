#pragma once

//Project
#include "CGTShare.h"
#include "global.h"

//STL

//Qt
#include <QDebug>

class Point
{
private:
    //ru Данные
    const id_point m_id;
    id_point m_linkPoint{};
    id_point m_RLinkPoint{};

    DataTypes m_dataType{};
    int m_index{};
    PointTypes m_type{};
    QString m_info{};
    QString m_name{};
    QString m_dpeName{};

    //ru Указатели и ссылки
    PElement m_parent;
    PPoint m_linkPointPtr{};
    PPoint m_RLinkPointPtr{};

public:
    explicit Point(id_point pt, PElement parent);
    ~Point();

private:
    void collectingData();

};
