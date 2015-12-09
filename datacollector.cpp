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
    : m_sdk(cgt::getMainSDK())
{
    //ru Собираем данные о среде
    collectingData();

    //ru Получаем контейнер c элементами из SDK
    grabberSDK(m_sdk);

    //ru Исправляем указатели
    fixedPtr();

    //qDebug() << 12;
}

DataCollector::~DataCollector()
{

}

void DataCollector::collectingData()
{
    m_isDebug = cgt::isDebug(m_sdk);

    id_element eId = cgt::sdkGetElement(m_sdk, 0);

    int iBuf{};
    QByteArray buf("", 512);

    buf.fill('\0');
    reinterpret_cast<quintptr *>(buf.data())[0] = eId;
    cgt::GetParam(PARAM_CODE_PATH, buf.data());
    m_cgtParams.PARAM_CODE_PATH = QString::fromLocal8Bit(buf);

    cgt::GetParam(PARAM_DEBUG_MODE, &iBuf);
    m_cgtParams.PARAM_DEBUG_MODE = iBuf;

    cgt::GetParam(PARAM_DEBUG_SERVER_PORT, &iBuf);
    m_cgtParams.PARAM_DEBUG_SERVER_PORT = iBuf;

    cgt::GetParam(PARAM_DEBUG_CLIENT_PORT, &iBuf);
    m_cgtParams.PARAM_DEBUG_CLIENT_PORT = iBuf;

    buf.fill('\0');
    reinterpret_cast<quintptr *>(buf.data())[0] = eId;
    cgt::GetParam(PARAM_PROJECT_PATH, buf.data());
    m_cgtParams.PARAM_PROJECT_PATH = QString::fromLocal8Bit(buf);

    const char f[] = "%mj.%mn.%bl";
    char *tmpBuf = new char[strlen(f) + 1];
    strcpy(tmpBuf, f);
    cgt::GetParam(PARAM_HIASM_VERSION, tmpBuf);
    m_cgtParams.PARAM_HIASM_VERSION = QString::fromLatin1(tmpBuf);
    delete tmpBuf;

    buf.fill('\0');
    cgt::GetParam(PARAM_USER_NAME, buf.data());
    m_cgtParams.PARAM_USER_NAME = QString::fromLocal8Bit(buf);

    buf.fill('\0');
    cgt::GetParam(PARAM_USER_MAIL, buf.data());
    m_cgtParams.PARAM_USER_MAIL = QString::fromLocal8Bit(buf);

    buf.fill('\0');
    reinterpret_cast<quintptr *>(buf.data())[0] = eId;
    cgt::GetParam(PARAM_PROJECT_NAME, buf.data());
    m_cgtParams.PARAM_PROJECT_NAME = QString::fromLocal8Bit(buf);

    uint tmpW[1] = {reinterpret_cast<uint>(eId)};
    cgt::GetParam(PARAM_SDE_WIDTH, tmpW);
    m_cgtParams.PARAM_SDE_WIDTH = tmpW[0];

    uint tmpH[1] = {reinterpret_cast<uint>(eId)};
    cgt::GetParam(PARAM_SDE_HEIGHT, tmpH);
    m_cgtParams.PARAM_SDE_HEIGHT = tmpH[0];

    buf.fill('\0');
    reinterpret_cast<quintptr *>(buf.data())[0] = eId;
    cgt::GetParam(PARAM_COMPILER, buf.data());
    m_cgtParams.PARAM_COMPILER = QString::fromLocal8Bit(buf);
}

PContainer DataCollector::grabberSDK(id_sdk sdk, PElement parent)
{
    PContainer container = new Container(sdk, parent);
    m_containers.append(container);

    int countElements = cgt::sdkGetCount(sdk);
    for (int i = 0; i < countElements; ++i) {
        id_element eId = cgt::sdkGetElement(sdk, i);

        //ru Создаём элемент
        PElement element = new Element(eId, container);

        if (fcgt::isLink(element->m_flags)) {
            container->m_elements << element;
            continue;
        }

        //ru Элемент содержит контейнер(ы)
        if (fcgt::isMulti(element->m_flags)) {
            //ru Элемен содержит полиморфный контейнер
            if (fcgt::isPolyMulti(element->m_classIndex)) {
                //ru Получаем к-во контейнеров, которое содержит элемент
                int countContainers = cgt::elGetSDKCount(eId);

                for (int i = 0; i < countContainers; ++i) {
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
    for (PContainer c : m_containers) {
        for (PElement e : c->m_elements) {
            for (PPoint p : e->m_points) {
                p->fixedPtr();
            }
        }
    }
}
