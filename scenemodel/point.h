#pragma once

//Project
#include "types.h"
#include "cgt/CGTShare.h"

//STL

//Qt
#include <QDebug>

class Point
{
    Q_DISABLE_COPY(Point)

private:
    const quintptr m_id;
    quintptr m_linkPoint{};
    quintptr m_RLinkPoint{};

    DataTypes m_dataType{};
    int m_index{};
    PointTypes m_type{};
    QString m_info{};
    QString m_name{};
    QString m_dpeName{};

    PElement m_parent;
    PPoint m_linkPointPtr{};
    PPoint m_RLinkPointPtr{};

public:
    explicit Point(quintptr pt, PElement parent);
    friend class SceneModel;

private:
    void collectingData();
    quintptr getId() const;

};
