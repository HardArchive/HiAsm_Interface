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

    quintptr m_linkPoint{};
    quintptr m_RLinkPoint{};
    DataTypes m_dataType{};
    int m_index{};
    PointTypes m_type{};
    QString m_info;
    QString m_name;
    QString m_dpeName;
    PPoint m_linkPointPtr{};
    PPoint m_RLinkPointPtr{};

public:
    explicit Point(quintptr id_point, PSceneModel model, QObject *parent);
    friend class SceneModel;

private:
    void collectingData();
    quintptr getId() const;

};
