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
    DataTypes m_dataType = m_cgt->ptGetDataType(m_ptId);
    int m_index = m_cgt->ptGetIndex(m_ptId);
    QString m_info = m_cgt->ptGetInfo(m_ptId);
    id_point m_linkPoint = m_cgt->ptGetLinkPoint(m_ptId);
    QString m_name = m_cgt->ptGetName(m_ptId);
    id_element m_parent = m_cgt->ptGetParent(m_ptId);
    id_point m_RLinkPoint = m_cgt->ptGetRLinkPoint(m_ptId);
    QString m_dpeName = m_cgt->pt_dpeGetName(m_ptId);

public:
    explicit Point(PCodeGenTools cgt, id_point pt);
    ~Point();

private:
    void receiptPointData();
};

#endif // POINT_H
