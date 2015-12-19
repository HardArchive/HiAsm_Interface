//Project
#include "property.h"
#include "element.h"
#include "valuetypes.h"
#include "scenemodel.h"
#include "cgt/cgt.h"

//STL

//Qt
#include <QFont>
#include <QTemporaryFile>
#include <QDebug>
#include <QUuid>

Property::Property(quintptr id_prop, QObject *parent)
    : QObject(parent)
    , m_id(id_prop)
    , m_model(parent->property("model").value<PSceneModel>())
{
    m_model->addPropertyToMap(this);
    collectingData();
}

void Property::collectingData()
{
    m_name = QString::fromLocal8Bit(cgt::propGetName(m_id));
    m_type = cgt::propGetType(m_id);
    quintptr id_value = cgt::propGetValue(m_id);

    auto setValue = [this, &id_value](const QVariant & value, DataTypes type = data_null, DataTypes arrType = data_null, const QString &name = QString()) {
        m_value = SharedValue::create(id_value, type, name, value, this);
        m_value->setArrayType(arrType);
        m_model->addValueToMap(m_value);
    };

    switch (m_type) {
    case data_int:
    case data_color:
    case data_flags: {
        setValue(cgt::propToInteger(m_id), m_type);
        break;
    }
    case data_real: {
        setValue(cgt::propToReal(m_id), m_type);
        break;
    }
    case data_str:
    case data_comboEx:
    case data_list:
    case data_script:
    case data_code: {
        setValue(QString::fromLocal8Bit(cgt::propToString(m_id)), m_type);
        break;
    }
    case data_data: {
        const DataTypes dataType = cgt::dtType(id_value);
        switch (dataType) {
        case data_int:
            setValue(cgt::dtInt(id_value), m_type);
            break;
        case data_str:
            setValue(QString::fromLocal8Bit(cgt::dtStr(id_value)), m_type);
            break;
        case data_real:
            setValue(cgt::dtReal(id_value), m_type);
            break;
        default:
            setValue(QVariant(), m_type);
            break;
        }
        break;
    }
    case data_combo: {
        setValue(cgt::propToByte(m_id), m_type);
        break;
    }
    case data_icon: {
        if (!strcmp(cgt::resAddIcon(m_id), "ASMA")) {
            break;
        }
    }
    case data_stream:
    case data_bitmap:
    case data_jpeg:
    case data_wave: {
        static QString nameRandom = QUuid::createUuid().toString() + ".wtf";
        static QString filePath = QDir::toNativeSeparators(QDir::tempPath() + QDir::separator() + nameRandom);

        cgt::propSaveToFile(m_id, filePath.toStdString().data());
        QFile file(filePath);
        if (file.size()) {
            file.open(QIODevice::ReadOnly);
            setValue(file.readAll(), m_type);
            file.close();
        }
        file.remove();

        break;
    }
    case data_array: {
        int arrCount = cgt::arrCount(id_value);
        DataTypes arrItemType = cgt::arrType(id_value);
        Values values;

        for (int i = 0; i < arrCount; ++i) {
            const quintptr id_prop = cgt::arrGetItem(id_value, i);

            QString name = QString::fromLocal8Bit(cgt::arrItemName(id_value, i));
            QVariant data;
            switch (arrItemType) {
            case data_int:
                data = cgt::propToInteger(id_prop);
                break;
            case data_str:
                data = QString::fromLocal8Bit(cgt::propToString(id_prop));
                break;
            case data_real:
                data = cgt::propToReal(id_prop);
                break;
            default: break;
            }

            values.append(SharedValue::create(0, arrItemType, name, data));
        }

        setValue(QVariant::fromValue(values), m_type, arrItemType);
        break;
    }
    case data_font: {
        SharedValueFont font = SharedValueFont::create();
        font->name = QString::fromLocal8Bit(cgt::fntName(id_value));
        font->size = cgt::fntSize(id_value);
        font->style = cgt::fntStyle(id_value);
        font->color = cgt::fntColor(id_value);
        font->charset = cgt::fntCharSet(id_value);

        setValue(QVariant::fromValue(font));
        break;
    }
    case data_element: {
        const PElement e = qobject_cast<PElement>(parent());
        if (!e)
            return;

        char buf[PATH_MAX];
        quintptr linkedElement = cgt::propGetLinkedElementInfo(e->getId(), m_id, buf);

        if (linkedElement) {
            SharedLinkedElementInfo elementInfo = SharedLinkedElementInfo::create();
            elementInfo->id = linkedElement;
            elementInfo->interface = QString::fromLocal8Bit(buf);
            setValue(QVariant::fromValue(elementInfo));
        }
        break;
    }
    default: break;
    }
}

quintptr Property::getId() const
{
    return m_id;
}

QString Property::getName() const
{
    return m_name;
}

DataTypes Property::getType() const
{
    return m_type;
}

bool Property::getIsDefProp() const
{
    return m_isDefProp;
}

void Property::setName(const QString &name)
{
    m_name = name;
}

void Property::setType(DataTypes type)
{
    m_type = type;
}

void Property::setIsDefProp(bool value)
{
    m_isDefProp = value;
}

void Property::setValue(const SharedValue &value)
{
    m_value = value;
}

SharedValue Property::getValue() const
{
    return m_value;
}

uchar Property::toByte() const
{
    if (!m_value)
        return 0;

    return m_value->toByte();
}

int Property::toInt() const
{
    if (!m_value)
        return 0;

    return m_value->toInt();
}

qreal Property::toReal() const
{
    if (!m_value)
        return 0.0;

    return m_value->toReal();
}

QString Property::toString() const
{
    if (!m_value)
        return QString();

    return m_value->toString();
}

const SharedLinkedElementInfo Property::toLinkedElementInfo() const
{
    if (!m_value)
        return SharedLinkedElementInfo();

    return m_value->toLinkedElementInfo();
}

PSceneModel Property::getModel()
{
    return m_model;
}
