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
    MapObjects m_mapContainers;
    MapObjects m_mapElements;
    MapObjects m_mapPoints;
    MapObjects m_mapProperties;

public:
    explicit SceneModel();

private:
    void collectingData();
    PContainer grabberSDK(quintptr sdk, PElement parent = PElement());
    void initMapObjects();
    void fixedPtr();

public:
    bool isDebug() const;
    void getCgtParam(CgtParams index, void *value) const;
};
