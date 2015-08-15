//Project
#include "maincontainer.h"
#include "CGTShare.h"
#include "element.h"
#include "cgt.h"

//STL

//Qt
#include <QDebug>
#include <QFile>

MainContainer::MainContainer()
{
    //ru Получаеим контейнер c элементами из SDK
    m_container = getContainerFromSDK(cgt::getMainSDK());
}

MainContainer::~MainContainer()
{
}

void MainContainer::saveToFile() const
{
    QString buf;
    QTextStream out(&buf);

    for(const PElement e : *m_container) {
        out << e->getDataText() << endl;
    }

    qDebug() << buf;
}

PContainer MainContainer::getContainerFromSDK(id_sdk sdk) const
{
    int countElements = cgt::sdkGetCount(sdk);
    PContainer container = PContainer::create();

    for(int i = 0; i < countElements; ++i) {
        id_element eId = cgt::sdkGetElement(sdk, i);
        ClassesElements eClass = cgt::elGetClassIndex(eId);
        ElementFlgs eFlags = cgt::elGetFlag(eId);

        //ru Создаём элемент
        PElement element = PElement::create(eId);

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
                    element->append(getContainerFromSDK(SDKContiner));
                }
            } else { //ru Элемент содержит обычный контейнер

                //ru Получаем контейнер редактора
                id_sdk SDKContiner = cgt::elGetSDK(eId);

                //ru Добавляем в элемент указатель на контейнер
                element->append(getContainerFromSDK(SDKContiner));
            }
        }

        //ru Добавляем элемент в контейнер
        container->append(element);
    }

    return container;
}
