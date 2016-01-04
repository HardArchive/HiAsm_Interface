#pragma once

//Project
#include "types.h"
#include "cgt/CGTShare.h"
#include "package/types.h"

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
    quintptr m_id{};
    quintptr m_linkPoint{};
    quintptr m_RLinkPoint{};
    QString m_dpeName;

    //CGT
    PCodeGenTools m_cgt{};

    //Model
    PSceneModel m_model{};

    //Conf
    const SharedConfPoint m_conf;

private:
    Q_PROPERTY(PSceneModel model READ getModel)
    Q_PROPERTY(PCodeGenTools cgt READ getCgt)

public:
    explicit Point(quintptr id_point, const SharedConfPoint &conf, QObject *parent);

private:
    void collectingData();

public:
    //Self
    quintptr getId() const;
    PElement getParent() const;

    PointType getType() const;

    void setDataType(DataType dataType);
    DataType getDataType() const;

    QString getName() const;

    void setDpeName(const QString &dpeName);
    QString getDpeName() const;

    QString getInfo() const;

    void setLinkPoint(quintptr linkPoint);
    quintptr getLinkPoint() const;

    void setRLinkPoint(quintptr RLinkPoint);
    quintptr getRLinkPoint() const;

    //CGT
    PCodeGenTools getCgt();

    //Model
    PSceneModel getModel();
};
