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
    //Self
    const quintptr m_id;
    void *m_userData{};
    ElementClass m_classIndex{};
    ElementFlgs m_flags{};
    int m_group{};
    bool m_linkIs{};
    quintptr m_linkMain{};
    int m_posX{};
    int m_posY{};
    int m_sizeW{};
    int m_sizeH{};
    QString m_className;
    QString m_codeName;
    QString m_interface;
    QString m_inherit;
    QString m_infSub;

    //Model
    PSceneModel const m_model;

    //Container
    Containers m_containers;

    //Point
    Points m_points;

    //Property
    Properties m_properties;

private:
    Q_PROPERTY(PSceneModel model READ getModel)

public:
    explicit Element(quintptr id_element, QObject *parent);

private:
    void collectingData();

public:
    //Self
    quintptr getId() const;
    PContainer getParent() const;

    void *getUserData() const;
    ElementClass getClassIndex();
    ElementFlags getFlags() const;
    int getGroup() const;
    bool getLinkIs() const;
    quintptr getLinkMain() const;
    int getPosX() const;
    int getPosY() const;
    int getSizeW() const;
    int getSizeH() const;
    QString getClassName() const;
    QString getCodeName() const;
    QString getInterface() const;
    QString getInherit() const;
    QString getInfSub() const;

    void setUserData(void *userData);
    void setClassIndex(const ElementClass &classIndex);
    void setFlags(const ElementFlgs &flags);
    void setGroup(int group);
    void setLinkIs(bool linkIs);
    void setLinkMain(const quintptr &linkMain);
    void setPosX(int posX);
    void setPosY(int posY);
    void setSizeW(int sizeW);
    void setSizeH(int sizeH);
    void setClassName(const QString &className);
    void setCodeName(const QString &name);
    void setInterface(const QString &interface);
    void setInherit(const QString &inherit);
    void setInfSub(const QString &infSub);

    //Model
    PSceneModel getModel();

    //Container
    size_t getCountContainers() const;
    PContainer getContainer() const;
    quintptr getIdContainer() const;
    PContainer getContainerByIndex(uint index);
    quintptr getIdContainerByIndex(uint index);
    PContainer addContainer(PContainer container);
    void removeContainer(uint index);

    //Point
    size_t getCountPoints() const;
    PPoint getPointByIndex(uint index) const;
    quintptr getIdPointByIndex(uint index) const;
    PPoint getPointByName(const QString &name) const;
    quintptr getIdPointByName(const QString &name) const;
    PPoint addPoint(PPoint point);
    void removePoint(uint index);

    //Property
    size_t getCountProps() const;
    PProperty getPropertyByIndex(uint index) const;
    quintptr getIdPropertyByIndex(uint index) const;
    PProperty getPropertyById(quintptr id_prop) const;
    PProperty getPropertyByName(const QString &name) const;
    quintptr getIdPropertyByName(const QString &name) const;
    PProperty addProperty(PProperty property);
    void removeProperty(uint index);
};
