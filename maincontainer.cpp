//STL

//Qt
#include <QDebug>

//Project
#include "maincontainer.h"
#include "element.h"
#include "cgtsharewrapper.h"
#include "CGTShare.h"

using namespace std;

MainContainer::MainContainer(TBuildProcessRec *params)
{
    m_cgt = params->cgt;
    m_sdk = params->sdk;

    //ru Получаеим контейнер c элементами из SDK
    m_container = getContainerFromSDK(m_sdk);
}

MainContainer::~MainContainer()
{
    
}

PContainer MainContainer::getContainerFromSDK(id_sdk sdk)
{
    int countElements = m_cgt->sdkGetCount(sdk);
    PContainer container = PContainer::create();

    for(int i = 0; i < countElements; ++i)
    {
        id_element eId = m_cgt->sdkGetElement(sdk, i);
        ElementClasses eClass = m_cgt->elGetClassIndex(eId);
        ElementFlgs eFlags = m_cgt->elGetFlag(eId);
        
        //ru Создаём элемент
        PElement element = PElement::create(m_cgt, eId);
        
        //ru Элемент содержит контейнер(ы)
        if( cgt::isMulti(eFlags) )
        {
            //ru Элемен содержит полиморфный контейнер
            if( cgt::isPolyMulti(eClass) )
            {
                //ru Получаем к-во контейнеров, которое содержит элемент
                int countSDKContiners = m_cgt->elGetSDKCount(eId);
                
                for(int i = 0; i < countSDKContiners; ++i)
                {
                    //ru Получаем контейнер
                    id_sdk SDKContiner = m_cgt->elGetSDKByIndex(eId, i);
                    
                    //ru Добавляем контейнер в элемент
                    element->append( getContainerFromSDK(SDKContiner) );
                }
            }
            else //ru Элемент содержит обычный контейнер
            {
                //ru Получаем контейнер редактора
                id_sdk SDKContiner = m_cgt->elGetSDK(eId);
                
                //ru Добавляем в элемент указатель на контейнер
                element->append( getContainerFromSDK(SDKContiner) );
            }
                     
        }
        
        //ru Добавляем элемент в контейнер
        container->append( element );        
    }
    
    return container;
}
