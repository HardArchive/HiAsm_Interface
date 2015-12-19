#pragma once

//Project
#include "types.h"
#include "value.h"
#include "valuetypes.h"
#include "cgt/CGTShare.h"

//STL

//Qt
#include <QObject>

class Property: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Property)

private:
    //Self
    const quintptr m_id;
    QString m_name;
    DataTypes m_type{};
    bool m_isDefProp{};

    //Model
    PSceneModel m_model{};

    //Value
    SharedValue m_value;

private:
    Q_PROPERTY(PSceneModel model READ getModel)

public:
    explicit Property(quintptr id_prop, QObject *parent);

private:
    void collectingData();

public:
    //Self
    quintptr getId() const;

    QString getName() const;
    DataTypes getType() const;
    bool getIsDefProp() const;

    void setName(const QString &name);
    void setType(DataTypes type);
    void setIsDefProp(bool value);

    //Value
    void setValue(const SharedValue &value);
    SharedValue getValue() const;
    uchar toByte() const;
    int toInt() const;
    qreal toReal() const;
    QString toString() const;
    const SharedLinkedElementInfo toLinkedElementInfo() const;

    //Model
    PSceneModel getModel();
};
