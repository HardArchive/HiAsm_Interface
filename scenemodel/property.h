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
    //Serialize
    QVariantMap serialize();

    //Self
    quintptr getId() const;

    void setName(const QString &name);
    QString getName() const;

    void setType(DataTypes type);
    DataTypes getType() const;

    void setIsDefProp(bool value);
    bool getIsDefProp() const;

    //Value
    SharedValue setValue(quintptr id = 0,
                         DataTypes type = data_null,
                         const QVariant &data = QVariant(),
                         const QString &name = QString(),
                         DataTypes arrayType = data_null);
    SharedValue setValue(const SharedValue &value);
    SharedValue getValue() const;
    uchar toByte() const;
    int toInt() const;
    qreal toReal() const;
    QString toString() const;
    const SharedLinkedElementInfo toLinkedElementInfo() const;

    //Model
    PSceneModel getModel();
};
