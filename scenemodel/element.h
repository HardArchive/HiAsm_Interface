#pragma once

//Project
#include "types.h"
#include "property.h"
#include "cgt/CGTShare.h"

//STL

//Qt
#include <QObject>
#include <QString>

class Element: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Element)

private:
    const quintptr m_id;
    PSceneModel const m_model;

    quintptr m_linkMain{};
    quintptr m_userData{};
    QString m_className;
    QString m_codeName;
    ElementClass m_classIndex{};
    ElementFlgs m_flags{};
    int m_group{};
    QString m_interface;
    QString m_inherit;
    QString m_infSub;
    bool m_linkIs{};
    int m_propCount{};
    int m_ptCount{};
    int m_posX{};
    int m_posY{};
    int m_sizeW{};
    int m_sizeH{};

    //Массивы
    Containers m_containers;
    Points m_points;
    Properties m_properties;

public:
    explicit Element(quintptr id_element, PSceneModel model, QObject *parent);
    friend class SceneModel;

private:
    void collectingData();

public:
    quintptr getId() const;
    PSceneModel getModel() const;
    QString getClassName() const;
    ElementFlags getFlags() const;
    void setCodeName(const QString &name);
    QString getCodeName() const;
    quintptr getUserData() const;
    void setUserData(quintptr userData);
    ElementClass getClassIndex();
    PContainer getParent() const;
    int getCountProps() const;
    SharedProperty getPropertyByIndex(uint index) const;
    quintptr getIdPropertyByIndex(uint index) const;
    SharedProperty getPropertyById(quintptr id_prop) const;
    int getCountPoints() const;
    PPoint getPointByIndex(uint index) const;
    quintptr getIdPointByIndex(uint index) const;
    bool getLinkIs() const;
    int getPosX() const;
    int getPosY() const;
    int getSizeW() const;
    int getSizeH() const;
    PContainer getContainer() const;
    quintptr getIdContainer() const;
    PContainer getContainerByIndex(uint index);
    quintptr getIdContainerByIndex(uint index);
    int getCountContainers() const;
    QString getInterface() const;
    QString getInherit() const;
    PPoint getPointByName(const QString &name) const;
    quintptr getIdPointByName(const QString &name) const;
    const SharedProperty getPropertyByName(const QString &name) const;
    quintptr getIdPropertyByName(const QString &name) const;
};
