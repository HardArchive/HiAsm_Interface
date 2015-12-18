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
    quintptr m_id{};
    DataTypes m_type = data_null;
    DataTypes m_arrayType = data_null;
    QVariant m_value;
    PProperty m_parent{};

public:
    explicit Value(quintptr id_value = 0, DataTypes type = data_null, const QVariant &value = QVariant(), PProperty parent = nullptr);

public:
    quintptr getId() const;
    DataTypes getType() const;
    DataTypes getDataType() const;
    QVariant getVariant() const;
    void setValue(QVariant v);
    void setType(DataTypes type);
    void setArrayType(DataTypes type);
    PProperty getParent() const;
    size_t getArraySize() const;
    DataTypes getArrayType() const;
    const SharedProperty getArrayItemByIndex(uint index) const;
    quintptr getArrayIdItemByIndex(uint index) const;
    QString getArrayItemName(uint index) const;

    SharedValueFont toFont() const;
    QString toString() const;
    int toInt() const;
    qreal toReal() const;

};

Q_DECLARE_METATYPE(Value)
Q_DECLARE_METATYPE(SharedValue)
