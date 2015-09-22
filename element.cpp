//STL

//Qt
#include <QTextStream>
#include <QDebug>

//Project
#include "element.h"

Element::Element(id_element eId)
    : m_eId(eId)
{
    getElementData();
}

Element::~Element()
{
}

void Element::append(PContainer container)
{
    m_arrayContainers.push_back(container);
}

QString Element::getDataText(uchar inc) const
{
    Q_UNUSED(inc)
    /*
    QString space;
    space.fill(' ', inc * 5);

    ++inc;

    QString buff;
    QTextStream stream(&buff);

    stream << space << "m_className: " << m_className << endl;
    stream << space << "m_classIndex: " << m_classIndex << endl;
    stream << space << "m_flags: " << m_flags << endl;
    stream << space << "m_inherit: " << m_inherit << endl;
    stream << space << "m_SDKCount: " << m_SDKCount << endl;
    stream << space << "m_group: " << m_group << endl;
    stream << space << "m_interface: " << m_interface << endl;
    stream << space << "m_infSub: " << m_infSub << endl;
    stream << space << "m_propCount: " << m_propCount << endl;
    stream << space << "m_propertyListCount: " << m_propertyListCount << endl;
    stream << space << "m_ptCount: " << m_ptCount << endl;
    stream << space << "m_linkIs: " << m_linkIs << endl;
    stream << space << "m_linkMain: " << m_linkMain << endl;
    stream << space << "m_posX: " << m_posX << endl;
    stream << space << "m_posY: " << m_posY << endl;
    stream << space << "m_sizeW: " << m_sizeW << endl;
    stream << space << "m_sizeH: " << m_sizeH << endl;
    
    for (const PContainer c : m_arrayContainers) {
        for (const PElement e : *c) {
            stream << e->getDataText(inc);
        }
    }
    return buff;
    */

    return QString();
}

void Element::getElementData()
{
    m_className = QString::fromLocal8Bit(cgt::elGetClassName(m_eId));
    m_classIndex = cgt::elGetClassIndex(m_eId);
    m_flags = cgt::elGetFlag(m_eId);
    m_inherit = QString::fromLocal8Bit(cgt::elGetInherit(m_eId));
    m_SDKCount = cgt::elGetSDKCount(m_eId);
    m_group = cgt::elGetGroup(m_eId);
    m_interface = QString::fromLocal8Bit(cgt::elGetInterface(m_eId));
    m_infSub = QString::fromLocal8Bit(cgt::elGetInfSub(m_eId));
    m_propCount = cgt::elGetPropCount(m_eId);
    m_propertyListCount = cgt::elGetPropertyListCount(m_eId);
    m_ptCount = cgt::elGetPtCount(m_eId);
    m_linkIs = cgt::elLinkIs(m_eId);
    m_linkMain = cgt::elLinkMain(m_eId);

    cgt::elGetPos(m_eId, m_posX, m_posY);
    cgt::elGetSize(m_eId, m_sizeW, m_sizeH);

    //ru Получаем информацию о точках
    for(int i = 0; i < m_ptCount; ++i) {
        m_arrayPoints.push_back(std::make_shared<Point>(cgt::elGetPt(m_eId, i)));
    }

    //ru Получаем информацию о свойствах
    for(int i = 0; i < m_propCount; ++i) {
        id_prop propId = cgt::elGetProperty(m_eId, i);
        m_arrayProperties.push_back(std::make_shared<Property>(propId, m_eId));
    }
}
