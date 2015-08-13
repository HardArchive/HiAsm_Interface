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
    const PCodeGenTools m_cgt {};
    const id_sdk m_sdk{};
    PContainer m_container{};

public:
    explicit MainContainer(TBuildProcessRec &params);
    ~MainContainer();

    void saveToFile() const;

private:
    PContainer getContainerFromSDK(id_sdk sdk) const;
};
