#ifndef ELEMENT_H
#define ELEMENT_H

//STL
#include "memory"

//Qt
#include <QString>
#include <QVector>
#include <QSharedPointer>

//Project
#include "CGTShare.h"

using namespace std;

class Element;
typedef QSharedPointer<Element> PElement;
typedef QVector<PElement> Container;
typedef QSharedPointer<Container> PContainer;
typedef QVector<PContainer> ArrayPContainers; 
typedef QSharedPointer<ArrayPContainers> PArrayPContainers; 

class Element
{
private:
    PCodeGenTools m_cgt{};
    id_element m_eId{};
    PArrayPContainers m_arrayContainers;
    
    //ru Данные элемента
    QString m_className{};
    ElementClasses m_classIndex{};
    ElementFlgs m_flags{};
    QString m_inherit{};
    int m_SDKCount{};
    int m_group;
    QString m_interface{};
    QString m_infSub{};
    int m_propCount{};
    int m_propertyListCount{};
    int m_ptCount{};
    bool m_linkIs{};
    id_element m_linkMain{};
    int m_posX{};
    int m_posY{};
    int m_sizeW{};
    int m_sizeH{};
    
public:
    explicit Element(PCodeGenTools cgt, id_element eId);
            ~Element();
    //ru Добавляем в элемент указатель на контейнер
    void append(PContainer container);

private:
    void receiptElementData();
    
};

#endif // ELEMENT_H
