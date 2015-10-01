#pragma once

//Project
#include "CGTShare.h"
#include "global.h"

//STL

//Qt


class DataCollector
{

private:
    struct  {

    } m_params;

private:
    PContainer m_container{};

public:
    explicit DataCollector();
    ~DataCollector();

    void saveToFile() const;

private:
    PContainer getContainerFromSDK(id_sdk sdk) const;
};
