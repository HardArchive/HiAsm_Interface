//Project
#include "point.h"
#include "container.h"
#include "element.h"

#include "cgt.h"


//STL

//Qt

Point::Point(id_point pt, PElement parent)
    : m_id(pt)
    , m_parent(parent)
{
    collectingData();
}

Point::~Point()
{
}

void Point::collectingData()
{
    m_dataType = cgt::ptGetDataType(m_id);
    m_index = cgt::ptGetIndex(m_id);
    m_info = QString::fromLocal8Bit(cgt::ptGetInfo(m_id));
    m_name = QString::fromLocal8Bit(cgt::ptGetName(m_id));
    m_linkPoint = cgt::ptGetLinkPoint(m_id);
    m_RLinkPoint = cgt::ptGetRLinkPoint(m_id);
    m_type = cgt::ptGetType(m_id);
    m_dpeName = QString::fromLocal8Bit(cgt::pt_dpeGetName(m_id));
}

void Point::fixedPtr()
{
    if (!(m_linkPoint || m_RLinkPoint))
        return;

    if (m_linkPointPtr && m_RLinkPointPtr)
        return;

    for (PElement e : m_parent->m_parent->m_elements) {
        for (PPoint p : e->m_points) {
            if (p->m_id == m_id)
                continue;

            if (p->m_id == m_linkPoint) {
                m_linkPointPtr = p;

                if (m_RLinkPointPtr)
                    return;
            }
            if (p->m_id == m_RLinkPoint) {
                m_RLinkPointPtr = p;

                if (m_linkPointPtr)
                    return;
            }
        }
    }
}
