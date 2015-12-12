#pragma once

//Project

//STL

//Qt
#include <QVector>
#include <QMap>

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

typedef QMap<quintptr, quintptr> MapObjects;

class SceneModel;
