#pragma once

//Project
#include "CGTShare.h"
#include "global.h"

//STL

//Qt


class MainContainer
{

private:
    struct  {

    } m_params;

private:
    PContainer m_container{};

public:
    explicit MainContainer();
    ~MainContainer();

    void saveToFile() const;

private:
    PContainer getContainerFromSDK(id_sdk sdk) const;
};
