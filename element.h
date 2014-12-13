#ifndef ELEMENT_H
#define ELEMENT_H

//STL
#include "memory"

//Qt
#include <QString>
#include <QVector>

//Project
#include "CGTShare.h"

using namespace std;

class Element;
typedef shared_ptr<Element> PElement;
typedef QVector<PElement> Container;
typedef shared_ptr<Container> PContainer;
typedef QVector<PContainer> ArrayPContainers; 
typedef shared_ptr<ArrayPContainers> PArrayPContainers; 

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
