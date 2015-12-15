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
    Q_DISABLE_COPY(Value)

private:
    const quintptr m_id;
    DataTypes m_type{};
    QVariant m_value;
    PProperty m_parent{};

public:
    explicit Value(quintptr id_value, DataTypes type, QVariant value = QVariant(), PProperty parent = nullptr);

public:
    quintptr getId() const;
    DataTypes getType() const;
    QVariant getValue() const;
    SharedFont toFont() const;
    void setValue(QVariant v);
    PProperty getParent() const;
};
