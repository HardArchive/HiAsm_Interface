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

Property::Property(quintptr id_prop, PSceneModel model, QObject *parent)
    : QObject(parent)
    , m_id(id_prop)
    , m_model(model)
{
    collectingData();
}

void Property::collectingData()
{
    m_name = QString::fromLocal8Bit(cgt::propGetName(m_id));
    m_type = cgt::propGetType(m_id);
    quintptr id_value = cgt::propGetValue(m_id);

    auto setValue = [this, &id_value](QVariant value) {
        m_value = SharedValue::create(id_value, m_type, value, this);
        m_model->addValueToMap(m_value);
    };

    switch (m_type) {
    case data_int:
    case data_color:
    case data_flags: {
        setValue(cgt::propToInteger(m_id));
        break;
    }
    case data_real: {
        setValue(cgt::propToReal(m_id));
        break;
    }
    case data_str:
    case data_comboEx:
    case data_list:
    case data_script:
    case data_code: {
        setValue(QString::fromLocal8Bit(cgt::propToString(m_id)));
        break;
    }
    case data_data: {
        switch (cgt::dtType(id_value)) {
        case data_int:
            setValue(cgt::dtInt(id_value));
            break;
        case data_str:
            setValue(QString::fromLocal8Bit(cgt::dtStr(id_value)));
            break;
        case data_real:
            setValue(cgt::dtReal(id_value));
        default:
            break;
        }
        break;
    }
    case data_combo: {
        setValue(cgt::propToByte(m_id));
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
            setValue(file.readAll());
            file.close();
        }
        file.remove();

        break;
    }
    case data_array: {
        int arrCount = cgt::arrCount(id_value);
        switch (cgt::arrType(id_value)) {
        case data_int: {
            ArrayInteger arr;
            for (int i = 0; i < arrCount; ++i) {
                arr.append(cgt::propToInteger(cgt::arrGetItem(id_value, i)));
            }
            setValue(QVariant::fromValue(arr));
            break;
        }
        case data_str: {
            QStringList list;
            for (int i = 0; i < arrCount; ++i) {
                list.append(QString::fromLocal8Bit(cgt::propToString(cgt::arrGetItem(id_value, i))));
            }
            setValue(list);
            break;
        }
        case data_real: {
            ArrayReal arr;
            for (int i = 0; i < arrCount; ++i) {
                arr.append(cgt::propToReal(cgt::arrGetItem(id_value, i)));
            }
            setValue(QVariant::fromValue(arr));
            break;
        }
        default:
            break;
        }

        break;
    }
    case data_font: {
        SharedFont font = SharedFont::create();
        font->name = QString::fromLocal8Bit(cgt::fntName(id_value));
        font->size = cgt::fntSize(id_value);
        font->style = cgt::fntStyle(id_value);
        font->color = cgt::fntColor(id_value);
        font->charset = cgt::fntCharSet(id_value);

        setValue(QVariant::fromValue(font));
        break;
    }
    case data_element: {
        PElement e = qobject_cast<PElement>(parent());
        char buf[PATH_MAX];
        quintptr linkedElement = cgt::propGetLinkedElementInfo(e->getId(), m_id, buf);

        if (linkedElement) {
            SharedLinkedElementInfo le = SharedLinkedElementInfo::create();
            le->id = linkedElement;
            le->interface = QString::fromLocal8Bit(buf);
            setValue(QVariant::fromValue(le));
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

DataTypes Property::getType() const
{
    return m_type;
}

bool Property::getIsDefault() const
{
    return m_isDefault;
}

void Property::setIsDefault(bool value)
{
    m_isDefault = value;
}

QString Property::getName() const
{
    return m_name;
}

SharedValue Property::getValue() const
{
    return m_value;
}

int Property::getValueInt() const
{
    if (!m_value)
        return 0;

    return m_value->getValue().toInt();
}

qreal Property::getValueReal() const
{
    if (!m_value)
        return 0.0;

    return m_value->getValue().toReal();
}

QString Property::getValueString() const
{
    if (!m_value)
        return QString();

    return m_value->getValue().toString();
}

int Property::getIsTranslate() const
{
    return m_isTranslate;
}

SharedLinkedElementInfo Property::getLinkedElementInfo() const
{
    if(!m_value)
        return SharedLinkedElementInfo();

    return qvariant_cast<SharedLinkedElementInfo>(m_value->getValue());
}
