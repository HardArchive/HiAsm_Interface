#pragma once

//Project
#include "types.h"
#include "value.h"
#include "cgt/CGTShare.h"

//STL

//Qt
#include <QObject>
#include <QSet>

class SceneModel: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(SceneModel)

private:
    bool m_isDebug{};
    TCgtParams m_cgtParams;
    Containers m_containers;
    MapContainers m_mapContainers;
    MapElements m_mapElements;
    MapPoints m_mapPoints;
    MapProperties m_mapProperties;
    MapValues m_mapValues;
    QSet<QString> m_resources;

public:
    explicit SceneModel(QObject *parent = 0);
    virtual ~SceneModel();
    static const char *strToPChar(const QString &str);

private:
    void collectingData(quintptr id_sdk);
    PContainer grabberSDK(quintptr id_sdk, QObject *parent);
    void initMapObjects();
    void deleteResources();

public:
    bool isDebug() const;
    void getCgtParam(CgtParams index, quintptr value) const;
    PContainer getContainerById(quintptr id_sdk) const;
    PElement getElementFromSDKByIndex(quintptr id_sdk, int index) const;
    quintptr getIdElementFromSDKByIndex(quintptr id_sdk, int index) const;
    uint getCountElementsInContainer(quintptr id_sdk) const;
    PElement getElementById(quintptr id_element) const;
    PPoint getPointById(quintptr id_point) const;
    PProperty getPropertyById(quintptr id_prop) const;
    SharedValue getValueById(quintptr id_value) const;
    void addValueToMap(SharedValue value);
    const char *addResByIdProp(quintptr id_prop);
    const char *addResFromString(const QString &str);
    int addResList(const QString &filePath);

};
