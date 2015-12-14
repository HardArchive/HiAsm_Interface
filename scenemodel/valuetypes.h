#pragma once
//Project

//STL

//Qt
#include <QObject>

struct Font {
    QString name;
    uint size{};
    uchar style{};
    uint color{};
    uchar charset{};
};
typedef QSharedPointer<Font> SharedFont;
Q_DECLARE_METATYPE(SharedFont)

typedef QVector<int> ArrayInteger;
Q_DECLARE_METATYPE(ArrayInteger)

typedef QVector<qreal> ArrayReal;
Q_DECLARE_METATYPE(ArrayReal)
