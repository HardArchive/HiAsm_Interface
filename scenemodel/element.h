#pragma once

//Project
#include "types.h"
#include "cgt/CGTShare.h"

//STL

//Qt
#include <QString>

class Element
{
private:
    const quintptr m_id;
    quintptr m_linkMain{};

    PContainer m_parent{};
    PElement m_linkMainPtr{};

    quintptr m_userData{};
    QString m_className;
    QString m_codeName;
    ElementClass m_classIndex{};
    ElementFlgs m_flags{};
    QString m_inherit;
    int m_group{};
    QString m_interface;
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
    explicit Element(quintptr eId, PContainer parent);
    friend class SceneModel;

private:
    void collectingData();

public:
    quintptr getId() const;
    QString getClassName() const;
    ElementFlags getFlags() const;
    void setCodeName(const QString &name);
    QString getCodeName() const;
    quintptr getUserData() const;
    void setUserData(quintptr userData);
    ElementClass getClassIndex();
    PContainer getParent() const;
    int getPropCount() const;
    PProperty getProperty(int index) const;
    quintptr getIdProperty(int index) const;
};
