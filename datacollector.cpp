//Project
#include "datacollector.h"
#include "container.h"
#include "element.h"
#include "point.h"
#include "property.h"

#include "cgt.h"

//STL

//Qt
#include <QDebug>

DataCollector::DataCollector()
{
    //ru Получаем контейнер c элементами из SDK
    grabberSDK(cgt::getMainSDK());

    fixedPtr();
    qDebug() << 12;
}

DataCollector::~DataCollector()
{

}

PContainer DataCollector::grabberSDK(id_sdk sdk, PElement parent)
{
    PContainer container = new Container(sdk, parent);
    m_containers.append(container);

    int countElements = cgt::sdkGetCount(sdk);
    for(int i = 0; i < countElements; ++i) {
        id_element eId = cgt::sdkGetElement(sdk, i);

        //ru Создаём элемент
        PElement element = new Element(eId, container);

        //ru Элемент содержит контейнер(ы)
        if(fcgt::isMulti(element->m_flags)) {
            //ru Элемен содержит полиморфный контейнер
            if(fcgt::isPolyMulti(element->m_classIndex)) {
                //ru Получаем к-во контейнеров, которое содержит элемент
                int countContainers = cgt::elGetSDKCount(eId);

                for(int i = 0; i < countContainers; ++i) {
                    //ru Получаем контейнер
                    id_sdk idSDK = cgt::elGetSDKByIndex(eId, i);

                    //ru Добавляем контейнер в элемент
                    element->m_containers << grabberSDK(idSDK, element);
                }
            } else { //ru Элемент содержит обычный контейнер

                //ru Получаем ID контейнера элемента
                id_sdk idSDK = cgt::elGetSDK(eId);

                //ru Добавляем контейнер в элемент
                element->m_containers << grabberSDK(idSDK, element);
            }
        }

        //ru Добавляем элемент в контейнер
        container->m_elements << element;
    }

    return container;
}

void DataCollector::fixedPtr()
{
    for(PContainer c : m_containers) {
        for(PElement e : c->m_elements) {
            for(PPoint p : e->m_points) {
                p->fixedPtr();
            }
        }
    }
}
