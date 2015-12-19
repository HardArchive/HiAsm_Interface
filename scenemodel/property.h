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
    //ru Данные о свойстве
    quintptr m_id;
    PSceneModel m_model{};
    QString m_name;
    DataTypes m_type{};
    bool m_isDefault{};

    //Данные свойства
    SharedValue m_value;

public:
    explicit Property(quintptr id_prop, PSceneModel model, QObject *parent);
    friend class SceneModel;

private:
    void collectingData();

public:
    quintptr getId() const;
    DataTypes getType() const;
    bool getIsDefault() const;
    void setIsDefault(bool value);
    QString getName() const;
    SharedValue getValue() const;
    uchar getValueByte() const;
    int getValueInt() const;
    qreal getValueReal() const;
    QString getValueString() const;
    const SharedLinkedElementInfo getLinkedElementInfo() const;
};

Q_DECLARE_METATYPE(Properties)
