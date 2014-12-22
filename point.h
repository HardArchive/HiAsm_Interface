#ifndef POINT_H
#define POINT_H

//STL

//Qt
#include <QDebug>

//Project
#include "CGTShare.h"
#include "cgtsharewrapper.h"

class Point {
private:
    PCodeGenTools m_cgt;
    id_point m_ptId;

    //ru Данные точки
    DataTypes m_dataType{};
    int m_index{};
    QString m_info{};
    id_point m_linkPoint{};
    QString m_name{};
    id_element m_parent{};
    id_point m_RLinkPoint{};
    QString m_dpeName{};

public:
    explicit Point(PCodeGenTools cgt, id_point pt);
    ~Point();

private:
    void receiptPointData();
};

#endif // POINT_H
