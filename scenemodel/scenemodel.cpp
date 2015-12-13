//Project
#include "scenemodel.h"
#include "container.h"
#include "element.h"
#include "point.h"
#include "property.h"
#include "cgt/cgt.h"

//STL

//Qt
#include <QDebug>

SceneModel::SceneModel()
    : m_sdk(cgt::getMainSDK())
{
    //ru Собираем данные о среде
    collectingData();

    //ru Получаем контейнер c элементами из SDK
    grabberSDK(m_sdk);

    //ru Инициализация карты объектов
    initMapObjects();

    //ru Корректировка указателей
    fixedPtr();
}

void SceneModel::collectingData()
{
    m_isDebug = cgt::isDebug(m_sdk);

    quintptr eId = cgt::sdkGetElement(m_sdk, 0);

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

PContainer SceneModel::grabberSDK(quintptr id_sdk, PElement parent)
{
    PContainer container = new Container(id_sdk, parent);
    m_containers.append(container);

    int countElements = cgt::sdkGetCount(id_sdk);
    for (int i = 0; i < countElements; ++i) {
        quintptr eId = cgt::sdkGetElement(id_sdk, i);

        PElement element = new Element(eId, container, this);

        if (!fcgt::isLink(element->m_flags)) {
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
                    quintptr idSDK = cgt::elGetSDKByIndex(eId, i);

                    //ru Добавляем контейнер в элемент
                    element->m_containers << grabberSDK(idSDK, element);
                }
            } else { //ru Элемент содержит обычный контейнер

                //ru Получаем ID контейнера элемента
                quintptr idSDK = cgt::elGetSDK(eId);

                //ru Добавляем контейнер в элемент
                element->m_containers << grabberSDK(idSDK, element);
            }
        }

        //ru Добавляем элемент в контейнер
        container->m_elements << element;
    }

    return container;
}

void SceneModel::initMapObjects()
{
    for (PContainer c : m_containers) {
        m_mapContainers.insert(c->m_id, c);

        for (PElement e : c->m_elements) {
            m_mapElements.insert(e->m_id, e);

            for (PPoint p : e->m_points) {
                m_mapPoints.insert(p->m_id, p);
            }

            for (PProperty p : e->m_properties) {
                m_mapProperties.insert(p->m_id, p);
            }
        }
    }
}

void SceneModel::fixedPtr()
{
    for (PContainer c : m_containers) {
        for (PElement e : c->m_elements) {
            if (e->m_linkMain != e->m_id)
                e->m_linkMainPtr = m_mapElements[e->m_linkMain];

            for (PPoint p : e->m_points) {
                p->m_RLinkPointPtr = m_mapPoints[p->m_RLinkPoint];
                p->m_linkPointPtr = m_mapPoints[p->m_RLinkPoint];
            }
        }
    }
}

bool SceneModel::isDebug() const
{
    return m_isDebug;
}

void SceneModel::getCgtParam(CgtParams index, quintptr value) const
{
    switch (index) {
    case PARAM_CODE_PATH :
        strcpy(reinterpret_cast<char *>(value), m_cgtParams.PARAM_CODE_PATH.toStdString().c_str());
        break;
    case PARAM_DEBUG_MODE:
        *reinterpret_cast<int *>(value) = m_cgtParams.PARAM_DEBUG_MODE;
        break;
    case PARAM_DEBUG_SERVER_PORT:
        *reinterpret_cast<int *>(value) = m_cgtParams.PARAM_DEBUG_SERVER_PORT;
        break;
    case PARAM_DEBUG_CLIENT_PORT:
        *reinterpret_cast<int *>(value) = m_cgtParams.PARAM_DEBUG_CLIENT_PORT;
        break;
    case PARAM_PROJECT_PATH:
        strcpy(reinterpret_cast<char *>(value), m_cgtParams.PARAM_PROJECT_PATH.toStdString().c_str());
        break;
    case PARAM_HIASM_VERSION:
        strcpy(reinterpret_cast<char *>(value), m_cgtParams.PARAM_HIASM_VERSION.toStdString().c_str());
        break;
    case PARAM_USER_NAME:
        strcpy(reinterpret_cast<char *>(value), m_cgtParams.PARAM_USER_NAME.toStdString().c_str());
        break;
    case PARAM_USER_MAIL:
        strcpy(reinterpret_cast<char *>(value), m_cgtParams.PARAM_USER_MAIL.toStdString().c_str());
        break;
    case PARAM_PROJECT_NAME:
        strcpy(reinterpret_cast<char *>(value), m_cgtParams.PARAM_PROJECT_NAME.toStdString().c_str());
        break;
    case PARAM_SDE_WIDTH:
        *reinterpret_cast<int *>(value) = m_cgtParams.PARAM_SDE_WIDTH;
        break;
    case PARAM_SDE_HEIGHT:
        *reinterpret_cast<int *>(value) = m_cgtParams.PARAM_SDE_HEIGHT;
        break;
    case PARAM_COMPILER:
        strcpy(reinterpret_cast<char *>(value), m_cgtParams.PARAM_COMPILER.toStdString().c_str());
        break;
    }
}

PContainer SceneModel::getContainerById(quintptr id_sdk) const
{
    return m_mapContainers[id_sdk];
}

PElement SceneModel::getElementFromSDKByIndex(quintptr id_sdk, int index) const
{
    const PContainer c = getContainerById(id_sdk);
    if (!c)
        return nullptr;
    return c->getElementByIndex(index);
}

quintptr SceneModel::getIdElementFromSDKByIndex(quintptr id_sdk, int index) const
{
    const PContainer c = getContainerById(id_sdk);
    if (!c)
        return 0;
    return c->getIdElementByIndex(index);
}

uint SceneModel::getCountElementsInContainer(quintptr id_sdk) const
{
    const PContainer c = getContainerById(id_sdk);
    if (!c)
        return 0;

    return c->m_elements.size();
}

PElement SceneModel::getElementById(quintptr id_element) const
{
    return m_mapElements[id_element];
}

PProperty SceneModel::getPropertyById(quintptr id_prop) const
{
    return m_mapProperties[id_prop];
}

PValue SceneModel::getValueById(quintptr id_value) const
{
    return m_mapValues[id_value];
}

void SceneModel::addValueToMap(PValue value)
{
    if (value)
        m_mapValues.insert(value->getId(), value);
}
