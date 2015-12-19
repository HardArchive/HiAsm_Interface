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
    QString m_name;
    QVariant m_value;
    PProperty m_parent{};
    DataTypes m_arrayType = data_null;

public:
    explicit Value(quintptr id_value = 0,
                   DataTypes type = data_null,
                   const QString &name = QString(),
                   const QVariant &value = QVariant(),
                   PProperty parent = nullptr);

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
    SharedValue getArrayItemByIndex(uint index) const;
    QString getArrayValueName(uint index) const;
    SharedValueFont toFont() const;
    QString toString() const;
    int toInt() const;
    qreal toReal() const;
    uchar toByte() const;
    const SharedLinkedElementInfo toLinkedElementInfo() const;
    QString getName() const;
};

Q_DECLARE_METATYPE(SharedValue)
Q_DECLARE_METATYPE(Values)
