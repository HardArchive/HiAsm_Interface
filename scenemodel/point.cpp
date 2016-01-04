//Project
#include "point.h"
#include "container.h"
#include "element.h"
#include "scenemodel.h"
#include "cgt/cgt.h"


//STL

//Qt

Point::Point(quintptr id_point, const SharedConfPoint &conf, QObject *parent)
    : QObject(parent)
    , m_id(id_point)
    , m_cgt(parent->property("cgt").value<PCodeGenTools>())
    , m_model(parent->property("model").value<PSceneModel>())
    , m_conf(conf)
{
    m_model->addPointToMap(this);
    collectingData();
}

void Point::collectingData()
{
    m_linkPoint = m_cgt->ptGetLinkPoint(m_id);
    m_RLinkPoint = m_cgt->ptGetRLinkPoint(m_id);
}

quintptr Point::getId() const
{
    return m_id;
}

PElement Point::getParent() const
{
    return qobject_cast<PElement>(parent());
}

PointType Point::getType() const
{
    return m_conf->pointType;
}

DataType Point::getDataType() const
{
    return m_conf->dataType;
}

QString Point::getName() const
{
    return m_conf->name;
}

void Point::setDpeName(const QString &dpeName)
{
    m_dpeName = dpeName;
}

QString Point::getDpeName() const
{
    return m_dpeName;
}

QString Point::getInfo() const
{
    return m_conf->desc;
}

void Point::setLinkPoint(quintptr linkPoint)
{
    m_linkPoint = linkPoint;
}

quintptr Point::getLinkPoint() const
{
    return m_linkPoint;
}

void Point::setRLinkPoint(quintptr RLinkPoint)
{
    m_RLinkPoint = RLinkPoint;
}

quintptr Point::getRLinkPoint() const
{
    return m_RLinkPoint;
}

PCodeGenTools Point::getCgt()
{
    return m_cgt;
}

PSceneModel Point::getModel()
{
    return m_model;
}
