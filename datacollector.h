#pragma once

//Project
#include "CGTShare.h"
#include "global.h"

//STL

//Qt


class DataCollector
{
private:
    const id_sdk m_sdk;
    bool m_isDebug{};
    TCgtParams m_cgtParams = TCgtParams();

    //Массив контейнеров
    Containers m_containers;

public:
    explicit DataCollector();
    ~DataCollector();

private:
    void collectingData();
    PContainer grabberSDK(id_sdk sdk, PElement parent = PElement());
    void fixedPtr();

};
