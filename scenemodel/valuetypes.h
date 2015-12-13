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
