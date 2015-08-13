#pragma once

//Project
#include "CGTShare.h"
#include "element.h"

//STL

//Qt

class MainContainer {

private:
    const PCodeGenTools m_cgt{};
    const id_sdk m_sdk{};
    const PContainer m_container{};

public:
    explicit MainContainer(TBuildProcessRec &params);
    ~MainContainer();

    void saveToFile() const;

private:
    PContainer getContainerFromSDK(id_sdk sdk) const;
};
