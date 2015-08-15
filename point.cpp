//STL

//Qt

//Project
#include "point.h"
#include "cgt.h"

Point::Point(id_point pt)
    : m_ptId(pt)
{
    getPointData();
}

Point::~Point()
{
}

void Point::getPointData()
{
    m_dataType = cgt::ptGetDataType(m_ptId);
    m_index = cgt::ptGetIndex(m_ptId);
    m_info = QString::fromLocal8Bit(cgt::ptGetInfo(m_ptId));
    m_linkPoint = cgt::ptGetLinkPoint(m_ptId);
    m_name = QString::fromLocal8Bit(cgt::ptGetName(m_ptId));
    m_parent = cgt::ptGetParent(m_ptId);
    m_RLinkPoint = cgt::ptGetRLinkPoint(m_ptId);
    m_type = cgt::ptGetType(m_ptId);
    m_dpeName = QString::fromLocal8Bit(cgt::pt_dpeGetName(m_ptId));
}
