#ifndef CONTAINER_H
#define CONTAINER_H

//STL

//Qt

//Project
#include "CGTShare.h"
#include "element.h"


class MainContainer
{
    
private:
    PCodeGenTools m_cgt{};
    id_sdk m_sdk{};
    int m_countElements{};
    PContainer m_container;
    
public:
    MainContainer(TBuildProcessRec *params);
    ~MainContainer();
    
private:
    PContainer getContainerFromSDK(id_sdk sdk);
    
};

#endif // CONTAINER_H
