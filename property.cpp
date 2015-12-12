//Project
#include "property.h"
#include "element.h"

//STL

//Qt
#include <QFont>


Property::Property(id_prop propId, PElement parent)
    : m_id(propId)
    , m_parent(parent)
{
    collectingData();
}

Property::~Property()
{
}

void Property::collectingData()
{
    m_name = QString::fromLocal8Bit(cgt::propGetName(m_id));
    m_type = cgt::propGetType(m_id);

    getValues();
}

void Property::getValues()
{
    switch (m_type) {
    case data_int: {
        m_propValues << PropValue(cgt::propToInteger(m_id), data_int);
        break;
    }
    case data_flags: {
        m_propValues << PropValue(cgt::propToInteger(m_id), data_flags);
        break;
    }
    case data_color: {
        m_propValues << PropValue(cgt::propToInteger(m_id), data_color);
        break;
    }
    case data_combo: {
        m_propValues << PropValue(cgt::propToByte(m_id), data_combo);
        break;
    }
    case data_str: {
        m_propValues << PropValue(QString::fromLocal8Bit(cgt::propToString(m_id)),
                                  data_str);
        break;
    }
    case data_real: {
        m_propValues << PropValue(cgt::propToReal(m_id), data_real);
        break;
    }
    case data_comboEx: {
        m_propValues << PropValue(QString::fromLocal8Bit(cgt::propToString(m_id)),
                                  data_comboEx);
        break;
    }
    case data_data: {
        id_data data = static_cast<id_data>(cgt::propGetValue(m_id));
        switch (cgt::dtType(data)) {
        case data_int:
            m_propValues << PropValue(cgt::dtInt(data), data_int);
            break;
        case data_str:
            m_propValues << PropValue(QString::fromLocal8Bit(cgt::dtStr(data)),
                                      data_str);
            break;
        case data_real:
            m_propValues << PropValue(cgt::dtReal(data), data_real);
            break;
        default:
            m_propValues << PropValue(data_null, data_null);
        }
        break;
    }
    case data_list: {
        m_propValues << PropValue(QString::fromLocal8Bit(cgt::propToString(m_id)),
                                  data_list);
        break;
    }
    case data_array: {
        id_array array = static_cast<id_array>(cgt::propGetValue(m_id));
        DataTypes subType = cgt::arrType(array);
        for (int i = 0; i < cgt::arrCount(array); ++i) {
            switch (subType) {
            case data_int:
                m_propValues << PropValue(cgt::propToInteger(cgt::arrGetItem(array, i)),
                                          subType);
                break;
            case data_str:
                m_propValues << PropValue(QString::fromLocal8Bit(cgt::propToString(cgt::arrGetItem(array, i))),
                                          subType);
                break;
            case data_real:
                m_propValues << PropValue(cgt::propToReal(cgt::arrGetItem(array, i)),
                                          subType);
                break;
            default:
                break;
            }
        }
        break;
    }
    case data_element: {
        quintptr linkedElement = reinterpret_cast<quintptr>(cgt::propGetLinkedElement(m_parent->m_id, m_name.toStdString().c_str()));
        if (linkedElement)
            m_propValues << PropValue(linkedElement, data_element);
        break;
    }
    case data_bitmap: {
        m_propValues << PropValue(QString::fromLocal8Bit(cgt::resAddBitmap(m_id)),
                                  data_bitmap);
        break;
    }
    case data_stream: {
        m_propValues << PropValue(QString::fromLocal8Bit(cgt::resAddStream(m_id)),
                                  data_stream);
        break;
    }
    case data_icon: {
        m_propValues << PropValue(QString::fromLocal8Bit(cgt::resAddIcon(m_id)),
                                  data_icon);
        break;
    }
    case data_wave: {
        m_propValues << PropValue(QString::fromLocal8Bit(cgt::resAddWave(m_id)),
                                  data_wave);
        break;
    }
    case data_menu: {
        m_propValues << PropValue(QString::fromLocal8Bit(cgt::resAddMenu(m_id)),
                                  data_menu);
        break;
    }
    case data_font: {
        DFont font;
        quintptr fontPtr = cgt::propGetValue(m_id);
        font.name = QString::fromLocal8Bit(cgt::fntName(fontPtr));
        font.size = cgt::fntSize(fontPtr);
        font.style = cgt::fntStyle(fontPtr);
        font.color = cgt::fntColor(fontPtr);
        font.charset = cgt::fntCharSet(fontPtr);

        m_propValues << PropValue(QVariant::fromValue(font), data_font);
        break;
    }
    default:
        break;
    }
}
