#pragma once

//Project

//STL

//Qt
#include <QList>
#include <QSharedPointer>

//Дефайны
#define DLLEXPORT extern "C" __cdecl
#define PRINT_FUNC_INFO qDebug() << CALL_STR << Q_FUNC_INFO;

// Типы данных
class Property;
typedef QSharedPointer<Property> SProperty;
typedef QList<SProperty> Properties;

class Point;
typedef QSharedPointer<Point> SPoint;
typedef QList<SPoint> Points;

class Element;
typedef QSharedPointer<Element> SElement;
typedef QList<SElement> Elements;

class Container;
typedef QSharedPointer<Container> SContainer;
typedef QList<SContainer> Containers;
