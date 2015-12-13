//Project
#include "property.h"
#include "element.h"
#include "valuetypes.h"
#include "scenemodel.h"
#include "cgt/cgt.h"

//STL

//Qt
#include <QFont>

Property::Property(quintptr propId, PElement parent)
    : m_id(propId)
    , m_parent(parent)
{
    collectingData();
}

void Property::collectingData()
{

    m_name = QString::fromLocal8Bit(cgt::propGetName(m_id));
    m_type = cgt::propGetType(m_id);
    quintptr id_value = cgt::propGetValue(m_id);

    const PSceneModel model = m_parent->getModel();
    auto addValue = [this, &model, &id_value](QVariant value) {
        PValue newValue = new Value(id_value, m_type, value, this);
        model->addValueToMap(newValue);
        m_values.append(newValue);
    };

    switch (m_type) {
    case data_int: {
        addValue(cgt::propToInteger(m_id));
        break;
    }
    case data_str: {
        addValue(QString::fromLocal8Bit(cgt::propToString(m_id)));
        break;
    }
    case data_data: {
        addValue(cgt::propToInteger(m_id));
        break;
    }
    case data_combo: {
        addValue(cgt::propToInteger(m_id));
        break;
    }
    case data_list: {
        addValue(QString::fromLocal8Bit(cgt::propToString(m_id)));
        break;
    }
    case data_icon: {
        addValue(cgt::propToInteger(m_id));
        break;
    }
    case data_real: {
        addValue(cgt::propToReal(m_id));
        break;
    }
    case data_color: {
        addValue(cgt::propToInteger(m_id));
        break;
    }
    case data_script: {
        addValue(QString::fromLocal8Bit(cgt::propToString(m_id)));
        break;
    }
    case data_stream: {
        addValue(cgt::propToInteger(m_id));
        break;
    }
    case data_bitmap: {

        addValue(cgt::propToInteger(m_id));
        break;
    }
    case data_wave: {
        addValue(cgt::propToInteger(m_id));
        break;
    }
    case data_array: {
        addValue(cgt::propToInteger(m_id));
        break;
    }
    case data_comboEx: {
        addValue(QString::fromLocal8Bit(cgt::propToString(m_id)));
        break;
    }
    case data_font: {
        Font font;
        font.name = QString::fromLocal8Bit(cgt::fntName(id_value));
        font.size = cgt::fntSize(id_value);
        font.style = cgt::fntStyle(id_value);
        font.color = cgt::fntColor(id_value);
        font.charset = cgt::fntCharSet(id_value);

        addValue(QVariant::fromValue(font));
        break;
    }
    case data_matr: {
        addValue(cgt::propToInteger(m_id));
        break;
    }
    case data_jpeg: {
        addValue(cgt::propToInteger(m_id));
    }
    case data_menu: {
        addValue(cgt::propToInteger(m_id));
        break;
    }
    case data_code: {
        addValue(cgt::propToInteger(m_id));
        break;
    }
    case data_element: {
        quintptr linkedElement = cgt::propGetLinkedElement(m_parent->getId(), m_name.toStdString().c_str());
        if (linkedElement)
            addValue(linkedElement);

        break;
    }
    case data_flags: {
        addValue(cgt::propToInteger(m_id));
        break;
    }
    case data_object: {
        addValue(cgt::propToInteger(m_id));
        break;
    }
    default: break;
    }

    /*
    case data_data: {
        quintptr id_data = cgt::propGetValue(m_id);
        DataTypes type = cgt::dtType(id_data);
        switch (type) {
        case data_int:
            value = new Value(id_value, type, cgt::dtInt(id_data), this);
            model->addValueToMap(value);
            m_values << value;
            break;
        case data_str:
            value = new Value(id_value, type, QString::fromLocal8Bit(cgt::dtStr(id_data)), this);
            model->addValueToMap(value);
            m_values << value;
            break;
        case data_real:
            value = new Value(id_value, type, cgt::dtReal(id_data), this);
            model->addValueToMap(value);
            m_values << value;
        default:
            break;
        }
        break;
    }

    case data_array: {
        quintptr array = static_cast<quintptr>(cgt::propGetValue(m_id));
        DataTypes subType = cgt::arrType(array);
        for (int i = 0; i < cgt::arrCount(array); ++i) {
            switch (subType) {
            case data_int:
                value->setValue(cgt::propToInteger(m_id));
                model->addValueToMap(value);
                m_values << cgt::propToInteger(cgt::arrGetItem(array, i)),
                         subType);
                break;
            case data_str:
                    value->setValue(cgt::propToInteger(m_id));
                    model->addValueToMap(value);
                    m_values << QString::fromLocal8Bit(cgt::propToString(cgt::arrGetItem(array, i))),
                             subType);
                    break;
                case data_real:
                        value->setValue(cgt::propToInteger(m_id));
                        model->addValueToMap(value);
                        m_values << cgt::propToReal(cgt::arrGetItem(array, i)),
                                 subType);
                        break;
                    default:
                            value->setValue(cgt::propToInteger(m_id));
                            model->addValueToMap(value);

                            break;
                        }
        }
        break;
    }
    case data_element: {
        value->setValue(cgt::propToInteger(m_id));
        model->addValueToMap(value);
        quintptr linkedElement = cgt::propGetLinkedElement(m_parent->getId(), m_name.toStdString().c_str());
        if (linkedElement)
            m_values << linkedElement, data_element);
            break;
        }
    case data_bitmap: {
        value->setValue(cgt::propToInteger(m_id));
        model->addValueToMap(value);
        m_values << QString::fromLocal8Bit(cgt::resAddBitmap(m_id)),
                 data_bitmap);
        break;
    }
    case data_stream: {
        value->setValue(cgt::propToInteger(m_id));
        model->addValueToMap(value);
        m_values << QString::fromLocal8Bit(cgt::resAddStream(m_id)),
                 data_stream);
        break;
    }
    case data_icon: {
        value->setValue(cgt::propToInteger(m_id));
        model->addValueToMap(value);
        m_values << QString::fromLocal8Bit(cgt::resAddIcon(m_id)),
                 data_icon);
        break;
    }
    case data_wave: {
        value->setValue(cgt::propToInteger(m_id));
        model->addValueToMap(value);
        m_values << QString::fromLocal8Bit(cgt::resAddWave(m_id)),
                 data_wave);
        break;
    }
    case data_menu: {
        value->setValue(cgt::propToInteger(m_id));
        model->addValueToMap(value);
        m_values << QString::fromLocal8Bit(cgt::resAddMenu(m_id)),
                 data_menu);
        break;
    }
    case data_font: {
        value->setValue(cgt::propToInteger(m_id));
        model->addValueToMap(value);

        PFont font = new Font;

        m_name = QString::fromLocal8Bit(cgt::fntName(id_value));
        m_size = cgt::fntSize(id_value);
        m_style = cgt::fntStyle(id_value);
        m_color = cgt::fntColor(id_value);
        m_charset = cgt::fntCharSet(id_value);

        m_values << Value(QVariant::fromValue(font), data_font);
        break;
    }
    */

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
