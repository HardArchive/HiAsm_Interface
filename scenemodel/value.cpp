//Project
#include "value.h"

//STL

//Qt


Value::Value(quintptr id_value, DataTypes type, const QVariant &value, const QString &name, DataTypes arrayType):
    m_id(id_value),
    m_type(type),
    m_value(value),
    m_name(name),
    m_arrayType(arrayType)
{

}

QVariantMap Value::serialize()
{
    QVariantMap data;
    data.insert("id", m_id);
    data.insert("name", m_name);
    data.insert("type", m_type);
    data.insert("arrayType", m_arrayType);

    switch (m_type) {
    case data_stream:
    case data_bitmap:
    case data_jpeg:
    case data_wave: {
        break;
    }
    case data_array: {
        QVariantList array;
        for (const SharedValue &v : m_value.value<Values>()) {
            array.append(v->serialize());;
        }

        data.insert("ArrayValues", array);
        break;
    }
    case data_font: {
        const SharedValueFont font = m_value.value<SharedValueFont>();
        QVariantMap fontMap;
        fontMap.insert("name", font->name);
        fontMap.insert("size", font->size);
        fontMap.insert("style", font->style);
        fontMap.insert("color", font->color);
        fontMap.insert("charset", font->charset);

        data.insert("value", fontMap);
        break;
    }
    case data_element: {
        const SharedLinkedElementInfo info = m_value.value<SharedLinkedElementInfo>();
        QVariantMap infoMap;
        infoMap.insert("id", info->id);
        infoMap.insert("interface", info->interface);

        data.insert("value", infoMap);
        break;
    }
    default: {
        data.insert("value", m_value);
    }
    }

    return data;
}

void Value::setId(quintptr id)
{
    m_id = id;
}

quintptr Value::getId() const
{
    return m_id;
}

void Value::setType(DataTypes type)
{
    m_type = type;
}

DataTypes Value::getType() const
{
    return m_type;
}

void Value::setName(const QString &name)
{
    m_name = name;
}

QString Value::getName() const
{
    return m_name;
}

void Value::setValue(const QVariant &value)
{
    m_value = value;
}

QVariant Value::getValue() const
{
    return m_value;
}

uchar Value::toByte() const
{
    if (!m_value.canConvert<uchar>())
        return uchar();

    return m_value.value<uchar>();
}

int Value::toInt() const
{
    if (!m_value.canConvert<int>())
        return int();

    return m_value.value<int>();
}

qreal Value::toReal() const
{
    if (!m_value.canConvert<qreal>())
        return qreal();

    return m_value.value<qreal>();
}

QString Value::toString() const
{
    if (!m_value.canConvert<QString>())
        return QString();

    return m_value.value<QString>();
}

DataTypes Value::getDataType() const
{
    switch (m_value.type()) {
    case QMetaType::Int:
        return data_int;
    case QMetaType::QString:
        return data_str;
    case QMetaType::QReal:
        return data_real;
    default:
        return data_null;
    }
}

size_t Value::getArraySize() const
{
    if (!m_value.canConvert<Values>())
        return 0;

    return m_value.value<Values>().size();
}

void Value::setArrayType(DataTypes type)
{
    m_arrayType = type;
}

DataTypes Value::getArrayType() const
{
    return m_arrayType;
}

SharedValue Value::getArrayItemByIndex(uint index) const
{
    if (!m_value.canConvert<Values>())
        return SharedValue();

    const Values arrayValues = m_value.value<Values>();
    if (index < uint(arrayValues.size()))
        return arrayValues[index];

    return SharedValue();
}

QString Value::getArrayItemName(uint index) const
{
    const SharedValue arrValue = getArrayItemByIndex(index);
    if (!arrValue)
        return QString();

    return arrValue->getName();
}

SharedValueFont Value::toFont() const
{
    if (!m_value.canConvert<SharedValueFont>())
        return SharedValueFont();

    return m_value.value<SharedValueFont>();
}

const SharedLinkedElementInfo Value::toLinkedElementInfo() const
{
    if (!m_value.canConvert<SharedLinkedElementInfo>())
        return SharedLinkedElementInfo();

    return m_value.value<SharedLinkedElementInfo>();
}
