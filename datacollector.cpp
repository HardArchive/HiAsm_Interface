//Project
#include "datacollector.h"
#include "CGTShare.h"
#include "element.h"
#include "container.h"
#include "cgt.h"

//STL

//Qt
#include <QDebug>
#include <QFile>

DataCollector::DataCollector()
{
    //ru Получаеим контейнер c элементами из SDK
    grabberSDK(cgt::getMainSDK());

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
        ElementClass eClass = element->getClassIndex();
        ElementFlgs eFlags = element->getFlags();

        //ru Элемент содержит контейнер(ы)
        if(fcgt::isMulti(eFlags)) {
            //ru Элемен содержит полиморфный контейнер
            if(fcgt::isPolyMulti(eClass)) {
                //ru Получаем к-во контейнеров, которое содержит элемент
                int countContainers = cgt::elGetSDKCount(eId);

                for(int i = 0; i < countContainers; ++i) {
                    //ru Получаем контейнер
                    id_sdk idSDK = cgt::elGetSDKByIndex(eId, i);

                    //ru Добавляем контейнер в элемент
                    element->addContainer(grabberSDK(idSDK, element));
                }
            } else { //ru Элемент содержит обычный контейнер

                //ru Получаем ID контейнера элемента
                id_sdk idSDK = cgt::elGetSDK(eId);

                //ru Добавляем контейнер в элемент
                element->addContainer(grabberSDK(idSDK, element));
            }
        }

        //ru Добавляем элемент в контейнер
        container->addElement(element);
    }

    return container;
}
