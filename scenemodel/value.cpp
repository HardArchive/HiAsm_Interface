//Project
#include "value.h"

//STL

//Qt

Value::Value(quintptr id_value, DataTypes type, QVariant value, PProperty parent):
    m_id(id_value),
    m_type(type),
    m_value(value),
    m_parent(parent)
{

}

quintptr Value::getId() const
{
    return m_id;
}

DataTypes Value::getType() const
{
    return m_type;
}

QVariant Value::getValue() const
{
    return m_value;
}

SharedValueFont Value::toFont() const
{
    return qvariant_cast<SharedValueFont>(m_value);
}

void Value::setValue(QVariant v)
{
    m_value = v;
}

PProperty Value::getParent() const
{
    return m_parent;
}

size_t Value::getArraySize() const
{
    /*
    if (m_value.canConvert<ArrayInteger>()) {
        return qobject_cast<ArrayInteger>(m_value).size();
    } else if (m_value.canConvert<ArrayReal>()) {
        return qobject_cast<ArrayReal>(m_value).size();
    } else if (m_value.canConvert<QStringList>()) {
        return qobject_cast<QStringList>(m_value).size();
    }
    */
    return 0;

}

DataTypes Value::getArrayType() const
{
    /*
    if (m_value.canConvert<ArrayInteger>()) {
        return data_int;
    } else if (m_value.canConvert<ArrayReal>()) {
        return data_real;
    } else if (m_value.canConvert<QStringList>()) {
        return data_str;
    }
    */

    return data_null;
}
