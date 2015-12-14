#pragma once

//Project
#include "types.h"

//STL

//Qt
#include <QObject>

class Container: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Container)

private:
    const quintptr m_id;
    PSceneModel const m_model;
    Elements m_elements;

public:
    explicit Container(quintptr id_sdk, PSceneModel model, QObject *parent);
    friend class SceneModel;

public:
    PElement getElementByName(const QString &name) const;
    quintptr getIdElementByName(const QString &name) const;
    quintptr getId() const;
    PElement getElementByIndex(quintptr index) const;
    quintptr getIdElementByIndex(quintptr index) const;
    PElement getParent() const;
};
