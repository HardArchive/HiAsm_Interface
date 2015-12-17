#pragma once

//Project
#include "types.h"
#include "value.h"
#include "valuetypes.h"
#include "cgt/CGTShare.h"

//STL

//Qt

class Property
{

private:
    //ru Данные о свойстве
    quintptr m_id;
    PSceneModel m_model{};
    QString m_name;
    DataTypes m_type{};
    int m_isTranslate{};
    bool m_isDefault{};
    PElement m_parent{};

    //Данные свойства
    SharedValue m_value;

public:
    explicit Property();
    explicit Property(quintptr id_prop, PSceneModel model, const PElement parent);
    explicit Property(quintptr id_prop, const QString &name, DataTypes type, const SharedValue &value);
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
    int getIsTranslate() const;
    const SharedLinkedElementInfo getLinkedElementInfo() const;
};

Q_DECLARE_METATYPE(Properties)
Q_DECLARE_METATYPE(SharedProperty)
