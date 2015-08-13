#ifndef CONTAINER_H
#define CONTAINER_H

//STL

//Qt

//Project
#include "CGTShare.h"
#include "element.h"

class MainContainer {

private:
    PCodeGenTools m_cgt{};
    id_sdk m_sdk{};
    PContainer m_container{};

public:
    explicit MainContainer(TBuildProcessRec &params);
    ~MainContainer();

    void saveToFile() const;

private:
    PContainer getContainerFromSDK(id_sdk sdk) const;
};

#endif // CONTAINER_H
