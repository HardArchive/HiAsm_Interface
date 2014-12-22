//STL

//Qt
#include <QTextStream>
#include <QDebug>

//Project
#include "element.h"
#include "point.h"
#include "cgtsharewrapper.h"

Element::Element(PCodeGenTools cgt, id_element eId)
    : m_cgt(cgt)
    , m_eId(eId)
{
    receiptElementData();
}

Element::~Element()
{
}

void Element::append(PContainer container)
{
    if (m_arrayContainers == nullptr)
        m_arrayContainers = PArrayPContainers::create();

    m_arrayContainers->append(container);
}

QString Element::getDataText(uchar inc) const
{
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

    if (m_arrayContainers != nullptr) {
        for (const PContainer c : *m_arrayContainers) {
            for (const PElement e : *c) {
                stream << e->getDataText(inc);
            }
        }
    }

    return buff;
}

void Element::receiptElementData()
{
    m_className = m_cgt->elGetClassName(m_eId);
    m_classIndex = m_cgt->elGetClassIndex(m_eId);
    m_flags = m_cgt->elGetFlag(m_eId);
    m_inherit = m_cgt->elGetInherit(m_eId);
    m_SDKCount = m_cgt->elGetSDKCount(m_eId);
    m_group = m_cgt->elGetGroup(m_eId);
    m_interface = m_cgt->elGetInterface(m_eId);
    m_infSub = m_cgt->elGetInfSub(m_eId);
    m_propCount = m_cgt->elGetPropCount(m_eId);
    m_propertyListCount = m_cgt->elGetPropertyListCount(m_eId);
    m_ptCount = m_cgt->elGetPtCount(m_eId);
    m_linkIs = m_cgt->elLinkIs(m_eId);
    m_linkMain = m_cgt->elLinkMain(m_eId);

    m_cgt->elGetPos(m_eId, m_posX, m_posY);
    m_cgt->elGetSize(m_eId, m_sizeW, m_sizeH);

    for (int i = 0; i < m_ptCount; ++i) {
        Point pt(m_cgt, m_cgt->elGetPt(m_eId, i));
    }
}
