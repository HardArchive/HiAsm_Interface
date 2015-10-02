#pragma once

//Project

//STL

//Qt
#include <QVector>

//Дефайны
#define DLLEXPORT extern "C" __cdecl
#define PRINT_FUNC_INFO qDebug() << CALL_STR << Q_FUNC_INFO;

// Типы данных
class Property;
typedef Property *PProperty;
typedef QVector<PProperty> Properties;

class Point;
typedef Point *PPoint;
typedef QVector<PPoint> Points;

class Element;
typedef Element *PElement;
typedef QVector<PElement> Elements;

class Container;
typedef Container *PContainer;
typedef QVector<PContainer> Containers;

class DataCollector;
