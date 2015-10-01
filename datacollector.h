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
    struct  {

    } m_params;

private:
    SContainer m_container;

public:
    explicit DataCollector();
    ~DataCollector();

private:
    SContainer grabberFromSDK(id_sdk sdk) const;
};
