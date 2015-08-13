#include "property.h"

Property::Property(PCodeGenTools cgt, id_prop propId, id_element elementId)
    : m_cgt(cgt)
    , m_propId(propId)
    , m_elId(elementId)
{
    getPropertyData();
}

Property::~Property()
{
}

void Property::getPropertyData()
{
    m_name = QString::fromLocal8Bit(m_cgt->propGetName(m_propId));
    m_type = m_cgt->propGetType(m_propId);

    getValues();
}

void Property::getValues()
{
    switch (m_type) {
    case data_int: {
        m_listPropValue << PropValue(m_cgt->propToInteger(m_propId), data_int);
        break;
    }
    case data_flags: {
        m_listPropValue << PropValue(m_cgt->propToInteger(m_propId), data_flags);
        break;
    }
    case data_color: {
        m_listPropValue << PropValue(m_cgt->propToInteger(m_propId), data_color);
        break;
    }
    case data_combo: {
        m_listPropValue << PropValue(m_cgt->propToByte(m_propId), data_combo);
        break;
    }
    case data_str: {
        m_listPropValue << PropValue(QString::fromLocal8Bit(m_cgt->propToString(m_propId)),
                                     data_str);
        break;
    }
    case data_real: {
        m_listPropValue << PropValue(m_cgt->propToReal(m_propId), data_real);
        break;
    }
    case data_comboEx: {
        m_listPropValue << PropValue(QString::fromLocal8Bit(m_cgt->propToString(m_propId)),
                                     data_comboEx);
        break;
    }
    case data_data: {
        id_data data = static_cast<id_data>(m_cgt->propGetValue(m_propId));
        switch (m_cgt->dtType(data)) {
        case data_int:
            m_listPropValue << PropValue(m_cgt->dtInt(data), data_int);
            break;
        case data_str:
            m_listPropValue << PropValue(QString::fromLocal8Bit(m_cgt->dtStr(data)),
                                         data_str);
            break;
        case data_real:
            m_listPropValue << PropValue(m_cgt->dtReal(data), data_real);
            break;
        default:
            m_listPropValue << PropValue(data_null, data_null);
        }
        break;
    }
    case data_list: {
        m_listPropValue << PropValue(QString::fromLocal8Bit(m_cgt->propToString(m_propId)),
                                     data_list);
        break;
    }
    case data_array: {
        id_array array = static_cast<id_array>(m_cgt->propGetValue(m_propId));
        DataTypes subType = m_cgt->arrType(array);
        for (int i = 0; i < m_cgt->arrCount(array); ++i) {
            switch (subType) {
            case data_int:
                m_listPropValue << PropValue(m_cgt->propToInteger(m_cgt->arrGetItem(array, i)),
                                             subType);
                break;
            case data_str:
                m_listPropValue << PropValue(QString::fromLocal8Bit(m_cgt->propToString(m_cgt->arrGetItem(array, i))),
                                             subType);
                break;
            case data_real:
                m_listPropValue << PropValue(m_cgt->propToReal(m_cgt->arrGetItem(array, i)),
                                             subType);
                break;
            default:
                break;
            }
        }
        break;
    }
    case data_element: {
        quintptr linkedElement = reinterpret_cast<quintptr>(m_cgt->propGetLinkedElement(m_elId, m_name.toStdString().c_str()));
        m_listPropValue << PropValue(linkedElement, data_element);
        break;
    }
    case data_bitmap: {
        m_listPropValue << PropValue(QString::fromLocal8Bit(m_cgt->resAddBitmap(m_propId)),
                                     data_bitmap);
        break;
    }
    case data_stream: {
        m_listPropValue << PropValue(QString::fromLocal8Bit(m_cgt->resAddStream(m_propId)),
                                     data_stream);
        break;
    }
    case data_icon: {
        m_listPropValue << PropValue(QString::fromLocal8Bit(m_cgt->resAddIcon(m_propId)),
                                     data_icon);
        break;
    }
    case data_wave: {
        m_listPropValue << PropValue(QString::fromLocal8Bit(m_cgt->resAddWave(m_propId)),
                                     data_wave);
        break;
    }
    case data_menu: {
        m_listPropValue << PropValue(QString::fromLocal8Bit(m_cgt->resAddMenu(m_propId)),
                                     data_menu);
        break;
    }
    default:
        break;
    }
}
