#pragma once
//Project
#include "property.h"
#include "valuetypes.h"
#include "cgt/CGTShare.h"

//STL

//Qt
#include <QObject>
#include <QVariant>

class Value
{

private:
    //Self
    const quintptr m_id;
    DataTypes m_type = data_null;
    QVariant m_value;
    QString m_name;
    DataTypes m_arrayType = data_null;

public:
    explicit Value(quintptr id_value = 0,
                   DataTypes type = data_null,
                   const QVariant &value = QVariant(),
                   const QString &name = QString(),
                   DataTypes arrayType = data_null);

public:
    //Serialize
    QVariantMap serialize();

    //Self
    quintptr getId() const;
    void setType(DataTypes type);
    DataTypes getType() const;
    void setName(const QString &name);
    QString getName() const;

    //Value
    void setValue(const QVariant &value);
    QVariant getValue() const;

    //Byte
    uchar toByte() const;

    //Int
    int toInt() const;

    //Real
    qreal toReal() const;

    //String
    QString toString() const;

    //Data
    DataTypes getDataType() const;

    //Array
    size_t getArraySize() const;
    void setArrayType(DataTypes type);
    DataTypes getArrayType() const;
    SharedValue getArrayItemByIndex(uint index) const;
    QString getArrayItemName(uint index) const;

    //Font
    SharedValueFont toFont() const;

    //LinkedElementInfo
    const SharedLinkedElementInfo toLinkedElementInfo() const;
};

Q_DECLARE_METATYPE(SharedValue)
Q_DECLARE_METATYPE(Values)
