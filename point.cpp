//STL

//Qt

//Project
#include "point.h"

Point::Point(PCodeGenTools cgt, id_point pt)
    : m_cgt(cgt)
    , m_ptId(pt)
{
    getPointData();
}

Point::~Point()
{
}

void Point::getPointData()
{
    m_dataType = m_cgt->ptGetDataType(m_ptId);
    m_index = m_cgt->ptGetIndex(m_ptId);
    m_info = QString::fromLocal8Bit(m_cgt->ptGetInfo(m_ptId));
    m_linkPoint = m_cgt->ptGetLinkPoint(m_ptId);
    m_name = QString::fromLocal8Bit(m_cgt->ptGetName(m_ptId));
    m_parent = m_cgt->ptGetParent(m_ptId);
    m_RLinkPoint = m_cgt->ptGetRLinkPoint(m_ptId);
    m_type = m_cgt->ptGetType(m_ptId);
    m_dpeName = QString::fromLocal8Bit(m_cgt->pt_dpeGetName(m_ptId));
}
