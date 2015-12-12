#pragma once

//Project
#include "types.h"
#include "cgt/CGTShare.h"

//STL

//Qt

class SceneModel
{
private:
    const quintptr m_sdk;
    bool m_isDebug{};
    TCgtParams m_cgtParams{};

    //Контейнеры
    Containers m_containers;
    MapContainers m_mapContainers;
    MapElements m_mapElements;
    MapPoints m_mapPoints;
    MapProperties m_mapProperties;

public:
    explicit SceneModel();

private:
    void collectingData();
    PContainer grabberSDK(quintptr id_sdk, PElement parent = nullptr);
    void initMapObjects();
    void fixedPtr();

public:
    bool isDebug() const;
    void getCgtParam(CgtParams index, quintptr value) const;
    PContainer getContainerById(quintptr id_sdk) const;
    PElement getElementFromSDKByIndex(quintptr id_sdk, int index) const;
    quintptr getIdElementFromSDKByIndex(quintptr id_sdk, int index) const;
    uint getCountElementsInContainer(quintptr id_sdk) const;

};
