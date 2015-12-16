#pragma once
//Project
#include "cgt/CGTShare.h"

//STL

//Qt
#include <QObject>
#include <QVariant>
#include <QSharedPointer>

struct LinkedElementInfo {
    quintptr id{};
    QString interface;
};
typedef QSharedPointer<LinkedElementInfo> SharedLinkedElementInfo;
Q_DECLARE_METATYPE(SharedLinkedElementInfo)

struct ValueFont {
    QString name;
    uint size{};
    uchar style{};
    uint color{};
    uchar charset{};
};
typedef QSharedPointer<ValueFont> SharedValueFont;
Q_DECLARE_METATYPE(SharedValueFont)

struct ArrayValue {
    QString name;
    DataTypes type{};
    QVariant data;
};
typedef QSharedPointer<ArrayValue> SharedArrayValue;
Q_DECLARE_METATYPE(SharedArrayValue)
typedef QVector<SharedArrayValue> ArrayValues;
Q_DECLARE_METATYPE(ArrayValues)
