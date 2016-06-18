#pragma once

//Project
#include "types.h"
#include "value.h"
#include "valuetypes.h"
#include "cgt/CGTShare.h"
#include "package/types.h"

//STL

//Qt
#include <QObject>

class Property: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Property)

private:
    //Self
    quintptr m_id{};

    //CGT
    PCodeGenTools m_cgt{};

    //Model
    PSceneModel m_model{};

    //Conf
    SharedConfProp m_conf;

    //Value
    Value m_value;

private:
    Q_PROPERTY(PSceneModel model READ getModel)
    Q_PROPERTY(PCodeGenTools cgt READ getCgt)

public:
    explicit Property(quintptr id_prop, const SharedConfProp &conf, QObject *parent);
    explicit Property(quintptr id = 0,
                      DataType type = data_null,
                      const QVariant &data = QVariant(),
                      const QString &name = QString());

private:
    void collectingData();
    void loadConf(const SharedConfProp &conf);

public:
    //Self
    quintptr getId() const;

    void setName(const QString &name);
    QString getName() const;

    DataType getType() const;

    //Value
    void setValue(quintptr id = 0,
                  DataType type = data_null,
                  const QVariant &data = QVariant(),
                  const QString &name = QString(),
                  DataType arrayType = data_null);

    PValue getValue();
    bool getIsDefProp();
    uchar toByte() const;
    int toInt() const;
    qreal toReal() const;
    QString toString() const;
    const SharedLinkedElementInfo toLinkedElementInfo() const;

    //CGT
    PCodeGenTools getCgt();

    //Model
    PSceneModel getModel();
};
