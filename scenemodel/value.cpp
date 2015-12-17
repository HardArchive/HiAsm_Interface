//Project
#include "value.h"

//STL

//Qt

Value::Value(quintptr id_value, DataTypes type, const QVariant &value, PProperty parent):
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

QVariant Value::getVariant() const
{
    return m_value;
}

SharedValueFont Value::toFont() const
{
    return m_value.value<SharedValueFont>();
}

void Value::setValue(QVariant v)
{
    m_value = v;
}

void Value::setType(DataTypes type)
{
    m_type = type;
}

void Value::setArrayType(DataTypes type)
{
    m_arrayType = type;
}

PProperty Value::getParent() const
{
    return m_parent;
}

size_t Value::getArraySize() const
{
    if (!m_value.canConvert<Properties>())
        return 0;

    return m_value.value<Properties>().size();
}

DataTypes Value::getArrayType() const
{
    return m_arrayType;
}

const SharedProperty Value::getArrayItemByIndex(uint index) const
{
    if (!m_value.canConvert<Properties>())
        return SharedProperty();

    const Properties arrayValues = m_value.value<Properties>();
    if (index < uint(arrayValues.size()))
        return arrayValues[index];

    return SharedProperty();
}

quintptr Value::getArrayIdItemByIndex(uint index) const
{
    const SharedProperty arrItem = getArrayItemByIndex(index);
    if (!arrItem)
        return 0;

    return arrItem->getId();
}

QString Value::getArrayItemName(uint index) const
{
    const SharedProperty arrItem = getArrayItemByIndex(index);
    if (!arrItem)
        return QString();

    return arrItem->getName();
}

