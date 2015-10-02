#pragma once

//Project
#include "CGTShare.h"
#include "global.h"

//STL
#include <memory>

//Qt


class DataCollector
{

private:
    Containers m_containers;

public:
    explicit DataCollector();
    ~DataCollector();

private:
    PContainer grabberSDK(id_sdk sdk, PElement parent = PElement());

};
