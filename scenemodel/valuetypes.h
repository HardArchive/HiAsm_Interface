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
typedef Font *PFont;
Q_DECLARE_METATYPE(Font)
Q_DECLARE_METATYPE(PFont)

typedef QVector<int> ArrayInteger;
Q_DECLARE_METATYPE(ArrayInteger)

typedef QVector<qreal> ArrayReal;
Q_DECLARE_METATYPE(ArrayReal)
