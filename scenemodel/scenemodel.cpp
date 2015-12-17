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

SceneModel::SceneModel(QObject *parent):
    QObject(parent)
{
    //ru Собираем данные о среде
    collectingData(cgt::getMainSDK());

    //ru Получаем контейнер c элементами из SDK
    grabberSDK(cgt::getMainSDK(), this);

    //ru Инициализация карты объектов
    initMapObjects();
}

SceneModel::~SceneModel()
{
    deleteResources();
}

const char *SceneModel::strToPChar(const QString &str)
{
    char *buf = new char[uint(str.size() + 1)];
    strcpy(buf, str.toStdString().c_str());
    return buf;
}

void SceneModel::collectingData(quintptr id_sdk)
{
    m_isDebug = cgt::isDebug(id_sdk);

    quintptr eId = cgt::sdkGetElement(id_sdk, 0);

    int iBuf{};
    QByteArray buf("", 512);

    buf.fill('\0');
    reinterpret_cast<quintptr *>(buf.data())[0] = eId;
    cgt::GetParam(PARAM_CODE_PATH, buf.data());
    m_cgtParams.CODE_PATH = QString::fromLocal8Bit(buf);

    cgt::GetParam(PARAM_DEBUG_MODE, &iBuf);
    m_cgtParams.DEBUG_MODE = iBuf;

    cgt::GetParam(PARAM_DEBUG_SERVER_PORT, &iBuf);
    m_cgtParams.DEBUG_SERVER_PORT = iBuf;

    cgt::GetParam(PARAM_DEBUG_CLIENT_PORT, &iBuf);
    m_cgtParams.DEBUG_CLIENT_PORT = iBuf;

    buf.fill('\0');
    reinterpret_cast<quintptr *>(buf.data())[0] = eId;
    cgt::GetParam(PARAM_PROJECT_PATH, buf.data());
    m_cgtParams.PROJECT_PATH = QString::fromLocal8Bit(buf);

    const char f[] = "%mj.%mn.%bl";
    char *tmpBuf = new char[strlen(f) + 1];
    strcpy(tmpBuf, f);
    cgt::GetParam(PARAM_HIASM_VERSION, tmpBuf);
    m_cgtParams.HIASM_VERSION = QString::fromLatin1(tmpBuf);
    delete[] tmpBuf;

    buf.fill('\0');
    cgt::GetParam(PARAM_USER_NAME, buf.data());
    m_cgtParams.USER_NAME = QString::fromLocal8Bit(buf);

    buf.fill('\0');
    cgt::GetParam(PARAM_USER_MAIL, buf.data());
    m_cgtParams.USER_MAIL = QString::fromLocal8Bit(buf);

    buf.fill('\0');
    reinterpret_cast<quintptr *>(buf.data())[0] = eId;
    cgt::GetParam(PARAM_PROJECT_NAME, buf.data());
    m_cgtParams.PROJECT_NAME = QString::fromLocal8Bit(buf);

    uint tmpW[1] = {reinterpret_cast<uint>(eId)};
    cgt::GetParam(PARAM_SDE_WIDTH, tmpW);
    m_cgtParams.SDE_WIDTH = tmpW[0];

    uint tmpH[1] = {reinterpret_cast<uint>(eId)};
    cgt::GetParam(PARAM_SDE_HEIGHT, tmpH);
    m_cgtParams.SDE_HEIGHT = tmpH[0];

    buf.fill('\0');
    reinterpret_cast<quintptr *>(buf.data())[0] = eId;
    cgt::GetParam(PARAM_COMPILER, buf.data());
    m_cgtParams.COMPILER = QString::fromLocal8Bit(buf);
}

PContainer SceneModel::grabberSDK(quintptr id_sdk, QObject *parent)
{
    PContainer container = new Container(id_sdk, this, parent);
    m_containers.append(container);

    int countElements = cgt::sdkGetCount(id_sdk);
    for (int i = 0; i < countElements; ++i) {
        quintptr eId = cgt::sdkGetElement(id_sdk, i);

        PElement element = new Element(eId, this, container);

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

            for (SharedProperty p : e->m_properties) {
                m_mapProperties.insert(p->m_id, p);
            }
        }
    }
}

void SceneModel::deleteResources()
{
    for (const QString &filePath : m_resources) {
        QFile::remove(filePath);
    }
    m_resources.clear();
}

bool SceneModel::isDebug() const
{
    return m_isDebug;
}

void SceneModel::getCgtParam(CgtParams index, quintptr value) const
{
    switch (index) {
    case PARAM_CODE_PATH :
        strcpy(reinterpret_cast<char *>(value), m_cgtParams.CODE_PATH.toStdString().c_str());
        break;
    case PARAM_DEBUG_MODE:
        *reinterpret_cast<int *>(value) = m_cgtParams.DEBUG_MODE;
        break;
    case PARAM_DEBUG_SERVER_PORT:
        *reinterpret_cast<int *>(value) = m_cgtParams.DEBUG_SERVER_PORT;
        break;
    case PARAM_DEBUG_CLIENT_PORT:
        *reinterpret_cast<int *>(value) = m_cgtParams.DEBUG_CLIENT_PORT;
        break;
    case PARAM_PROJECT_PATH:
        strcpy(reinterpret_cast<char *>(value), m_cgtParams.PROJECT_PATH.toStdString().c_str());
        break;
    case PARAM_HIASM_VERSION:
        strcpy(reinterpret_cast<char *>(value), m_cgtParams.HIASM_VERSION.toStdString().c_str());
        break;
    case PARAM_USER_NAME:
        strcpy(reinterpret_cast<char *>(value), m_cgtParams.USER_NAME.toStdString().c_str());
        break;
    case PARAM_USER_MAIL:
        strcpy(reinterpret_cast<char *>(value), m_cgtParams.USER_MAIL.toStdString().c_str());
        break;
    case PARAM_PROJECT_NAME:
        strcpy(reinterpret_cast<char *>(value), m_cgtParams.PROJECT_NAME.toStdString().c_str());
        break;
    case PARAM_SDE_WIDTH:
        *reinterpret_cast<int *>(value) = m_cgtParams.SDE_WIDTH;
        break;
    case PARAM_SDE_HEIGHT:
        *reinterpret_cast<int *>(value) = m_cgtParams.SDE_HEIGHT;
        break;
    case PARAM_COMPILER:
        strcpy(reinterpret_cast<char *>(value), m_cgtParams.COMPILER.toStdString().c_str());
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

PPoint SceneModel::getPointById(quintptr id_point) const
{
    return m_mapPoints[id_point];
}

SharedProperty SceneModel::getPropertyById(quintptr id_prop) const
{
    return m_mapProperties[id_prop];
}

SharedValue SceneModel::getValueById(quintptr id_value) const
{
    return m_mapValues[id_value];
}

void SceneModel::addValueToMap(SharedValue value)
{
    if (value)
        m_mapValues.insert(value->getId(), value);
}

void SceneModel::addPropertyToMap(SharedProperty prop)
{
    if (prop)
        m_mapProperties.insert(prop->getId(), prop);
}

const char *SceneModel::addResByIdProp(quintptr id_prop)
{
    const SharedProperty p = getPropertyById(id_prop);
    if (!p)
        return nullptr;

    const SharedValue v = p->getValue();
    if (!v)
        return nullptr;

    const QByteArray byteArray = v->getVariant().toByteArray();
    static const QString nameDir = "compiler";
    static const QString name = "STREAM";
    QString suffix = QString::number(m_resources.size());
    QString fileName = name + suffix;

    QString resFilePath = QDir::toNativeSeparators(
                              QDir::currentPath() + QDir::separator() +
                              nameDir + QDir::separator() + fileName
                          );
    QFile file(resFilePath);
    if (!file.open(QIODevice::WriteOnly))
        return nullptr;

    file.write(byteArray);
    file.close();
    m_resources.insert(resFilePath);

    return strToPChar(fileName);
}

const char *SceneModel::addResFromString(const QString &str)
{
    if (str.isEmpty())
        return nullptr;

    static const QString nameDir = "compiler";
    static const QString name = "STREAM";
    QString suffix = QString::number(m_resources.size());
    QString fileName = name + suffix;
    QString resFilePath = QDir::toNativeSeparators(
                              QDir::currentPath() + QDir::separator() +
                              nameDir + QDir::separator() + fileName
                          );
    QFile file(resFilePath);
    if (!file.open(QIODevice::WriteOnly))
        return nullptr;

    file.write(str.toLocal8Bit());
    file.close();
    m_resources.insert(resFilePath);

    return strToPChar(fileName);
}

int SceneModel::addResList(const QString &filePath)
{
    m_resources.insert(filePath);
    return 0;
}
