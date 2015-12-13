#pragma once
//Project
#include "types.h"
#include "cgt/CGTShare.h"

//STL

//Qt
#include <QObject>
#include <QVariant>
#include <QPair>

struct DFont {
    QString name;
    uint size{};
    uchar style{};
    uint color{};
    uchar charset{};
};
Q_DECLARE_METATYPE(DFont)

typedef QPair<QVariant, DataTypes> PropValue;
typedef QList<PropValue> PropValues;
