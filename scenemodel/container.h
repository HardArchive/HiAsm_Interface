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
    QString m_name;
    Elements m_elements;

private:
    Q_PROPERTY(PSceneModel model READ getModel)

public:
    explicit Container(quintptr id_sdk, QObject *parent);

private:
    void collectingData();

public:
    PElement getElementByName(const QString &name) const;
    quintptr getIdElementByName(const QString &name) const;
    quintptr getId() const;
    PElement getElementByIndex(int index) const;
    quintptr getIdElementByIndex(int index) const;
    PElement getParent() const;
    QString getName() const;
    void setName(const QString &name);
    PSceneModel getModel() const;
    size_t getCountElements() const;
};
