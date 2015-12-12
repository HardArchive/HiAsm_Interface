#pragma once
//Project
#include "cgt.h"
#include "global.h"

//STL

//Qt
#include <QObject>
#include <QVariant>

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
