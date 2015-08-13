#pragma once

//Project

//STL

//Qt
#include <QVector>
#include <QSharedPointer>

//Дефайны
#define DLLEXPORT extern "C" __cdecl
#define PRINT_FUNC_INFO qDebug() << CALL_STR << Q_FUNC_INFO;

// Типы данных
class Element;
typedef QSharedPointer<Element> PElement;
typedef QVector<PElement> Container;
typedef QSharedPointer<Container> PContainer;
typedef QVector<PContainer> ArrayPContainers;
