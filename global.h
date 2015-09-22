#pragma once

//Project

//STL
#include <memory>
#include <vector>

//Qt

//Дефайны
#define DLLEXPORT extern "C" __cdecl
#define PRINT_FUNC_INFO qDebug() << CALL_STR << Q_FUNC_INFO;

// Типы данных
class Element;
typedef std::shared_ptr<Element> PElement;
typedef std::vector<PElement> Container;
typedef std::shared_ptr<Container> PContainer;
typedef std::vector<PContainer> ArrayPContainers;
