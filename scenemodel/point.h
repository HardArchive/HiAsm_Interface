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
    //Self
    const quintptr m_id;
    PointTypes m_type{};
    DataTypes m_dataType{};
    uint m_index{};
    QString m_name;
    QString m_dpeName;
    QString m_info;
    quintptr m_linkPoint{};
    quintptr m_RLinkPoint{};

    //Model
    PSceneModel const m_model;

private:
    Q_PROPERTY(PSceneModel model READ getModel)

public:
    explicit Point(quintptr id_point, QObject *parent);

private:
    void collectingData();

public:
    //Self
    quintptr getId() const;
    PElement getParent() const;

    PointTypes getType() const;
    DataTypes getDataType() const;
    uint getIndex() const;
    QString getName() const;
    QString getDpeName() const;
    QString getInfo() const;
    quintptr getLinkPoint() const;
    quintptr getRLinkPoint() const;

    void setType(const PointTypes &type);
    void setDataType(const DataTypes &dataType);
    void setIndex(const uint &index);
    void setName(const QString &name);
    void setDpeName(const QString &dpeName);
    void setInfo(const QString &info);
    void setLinkPoint(const quintptr &linkPoint);
    void setRLinkPoint(const quintptr &RLinkPoint);

    //Model
    PSceneModel getModel();
};
