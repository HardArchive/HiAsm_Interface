//Project
#include "point.h"
#include "container.h"
#include "element.h"
#include "cgt/cgt.h"


//STL

//Qt

Point::Point(quintptr id_point, PSceneModel model, QObject *parent)
    : QObject(parent)
    , m_id(id_point)
    , m_model(model)
{
    collectingData();
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

quintptr Point::getId() const
{
    return m_id;
}

