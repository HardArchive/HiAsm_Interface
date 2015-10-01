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
    m_container = grabberFromSDK(cgt::getMainSDK());

    qDebug() << "test";
}

DataCollector::~DataCollector()
{

}

SContainer DataCollector::grabberFromSDK(id_sdk sdk) const
{
    int countElements = cgt::sdkGetCount(sdk);
    SContainer container = SContainer::create();

    qDebug() << fcgt::isCore(cgt::elGetFlag(sdk));

    for(int i = 0; i < countElements; ++i) {
        id_element eId = cgt::sdkGetElement(sdk, i);
        ClassesElements eClass = cgt::elGetClassIndex(eId);
        ElementFlgs eFlags = cgt::elGetFlag(eId);

        //ru Создаём элемент
        SElement element = SElement::create(eId);

        //ru Элемент содержит контейнер(ы)
        if(fcgt::isMulti(eFlags)) {
            //ru Элемен содержит полиморфный контейнер
            if(fcgt::isPolyMulti(eClass)) {
                //ru Получаем к-во контейнеров, которое содержит элемент
                int countSDKContiners = cgt::elGetSDKCount(eId);

                for(int i = 0; i < countSDKContiners; ++i) {
                    //ru Получаем контейнер
                    id_sdk SDKContiner = cgt::elGetSDKByIndex(eId, i);

                    //ru Добавляем контейнер в элемент
                    element->addContainer(grabberFromSDK(SDKContiner));
                }
            } else { //ru Элемент содержит обычный контейнер

                //ru Получаем контейнер редактора
                id_sdk SDKContiner = cgt::elGetSDK(eId);

                //ru Добавляем в элемент указатель на контейнер
                element->addContainer(grabberFromSDK(SDKContiner));
            }
        }

        //ru Добавляем элемент в контейнер
        container->addElement(element);
    }

    return container;
}
