//Project
#include "point.h"
#include "container.h"
#include "element.h"
#include "scenemodel.h"
#include "cgt/cgt.h"


//STL

//Qt

Point::Point(quintptr id_point, QObject *parent)
    : QObject(parent)
    , m_id(id_point)
    , m_model(parent->property("model").value<PSceneModel>())
{
    m_model->addPointToMap(this);
    collectingData();
}

void Point::collectingData()
{
    m_type = cgt::ptGetType(m_id);
    m_dataType = cgt::ptGetDataType(m_id);
    m_index = cgt::ptGetIndex(m_id);
    m_name = QString::fromLocal8Bit(cgt::ptGetName(m_id));
    m_dpeName = QString::fromLocal8Bit(cgt::pt_dpeGetName(m_id));
    m_info = QString::fromLocal8Bit(cgt::ptGetInfo(m_id));
    m_linkPoint = cgt::ptGetLinkPoint(m_id);
    m_RLinkPoint = cgt::ptGetRLinkPoint(m_id);
}

quintptr Point::getId() const
{
    return m_id;
}

PElement Point::getParent() const
{
    return qobject_cast<PElement>(parent());
}

PointTypes Point::getType() const
{
    return m_type;
}

DataTypes Point::getDataType() const
{
    return m_dataType;
}

uint Point::getIndex() const
{
    return m_index;
}

QString Point::getName() const
{
    return m_name;
}

QString Point::getDpeName() const
{
    return m_dpeName;
}

QString Point::getInfo() const
{
    return m_info;
}

quintptr Point::getLinkPoint() const
{
    return m_linkPoint;
}

quintptr Point::getRLinkPoint() const
{
    return m_RLinkPoint;
}


void Point::setType(const PointTypes &type)
{
    m_type = type;
}

void Point::setDataType(const DataTypes &dataType)
{
    m_dataType = dataType;
}

void Point::setIndex(const uint &index)
{
    m_index = index;
}

void Point::setName(const QString &name)
{
    m_name = name;
}

void Point::setDpeName(const QString &dpeName)
{
    m_dpeName = dpeName;
}

void Point::setInfo(const QString &info)
{
    m_info = info;
}

void Point::setLinkPoint(const quintptr &linkPoint)
{
    m_linkPoint = linkPoint;
}

void Point::setRLinkPoint(const quintptr &RLinkPoint)
{
    m_RLinkPoint = RLinkPoint;
}


PSceneModel Point::getModel()
{
    return m_model;
}
