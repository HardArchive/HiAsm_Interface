#pragma once

//Project
#include "types.h"
#include "cgt/CGTShare.h"

//STL

//Qt
#include <QObject>
#include <QDebug>

class Point: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Point)

private:
    const quintptr m_id;
    PSceneModel const m_model;

    QString m_info;
    QString m_name;
    QString m_dpeName;
    quintptr m_linkPoint{};
    quintptr m_RLinkPoint{};
    DataTypes m_dataType{};
    PointTypes m_type{};
    int m_index{};

public:
    explicit Point(quintptr id_point, PSceneModel model, QObject *parent);
    friend class SceneModel;

private:
    void collectingData();

public:
    quintptr getId() const;
    QString getInfo() const;
    QString getName() const;
    QString getDpeName() const;
    quintptr getLinkPoint() const;
    quintptr getRLinkPoint() const;
    DataTypes getDataType() const;
    PointTypes getType() const;
    int getIndex() const;
};
