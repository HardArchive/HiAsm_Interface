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

void Value::setValue(QVariant v)
{
    m_value = v;
}

PProperty Value::getParent() const
{
    return m_parent;
}
