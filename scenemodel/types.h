#pragma once

//Project

//STL

//Qt
#include <QVector>
#include <QMap>
#include <QMetaType>

// Типы данных
class Property;
typedef Property *PProperty;
typedef QSharedPointer<Property> SharedProperty;
typedef QMap<quintptr, SharedProperty> MapProperties;
typedef QVector<SharedProperty> Properties;

class Value;
typedef QSharedPointer<Value> SharedValue;
typedef QMap<quintptr, SharedValue> MapValues;

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
