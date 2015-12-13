#pragma once

//Project

//STL

//Qt
#include <QVector>
#include <QMap>
#include <QMetaType>

// Типы данных
class Value;
typedef Value *PValue;
typedef QVector<PValue> Values;
typedef QMap<quintptr, PValue> MapValues;

class Property;
typedef Property *PProperty;
typedef QVector<PProperty> Properties;
typedef QMap<quintptr, PProperty> MapProperties;

class Point;
typedef Point *PPoint;
typedef QVector<PPoint> Points;
typedef QMap<quintptr, PPoint> MapPoints;

class Element;
typedef Element *PElement;
typedef QVector<PElement> Elements;
typedef QMap<quintptr, PElement> MapElements;

class Container;
typedef Container *PContainer;
typedef QVector<PContainer> Containers;
typedef QMap<quintptr, PContainer> MapContainers;

class SceneModel;
typedef SceneModel *PSceneModel;
