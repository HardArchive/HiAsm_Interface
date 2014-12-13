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
    
public:
    explicit Element(PCodeGenTools cgt, id_element eId);
    
    //ru Добавляем в элемент указатель на контейнер
    void append(PContainer container);
    
};

#endif // ELEMENT_H
