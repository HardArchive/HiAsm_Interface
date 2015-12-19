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
    m_container = new Container(cgt::getMainSDK(), this);
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

    return c->getCountElements();
}

PElement SceneModel::getElementById(quintptr id_element) const
{
    return m_mapElements[id_element];
}

PPoint SceneModel::getPointById(quintptr id_point) const
{
    return m_mapPoints[id_point];
}

PProperty SceneModel::getPropertyById(quintptr id_prop) const
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

const char *SceneModel::addResByIdProp(quintptr id_prop)
{
    PProperty p = getPropertyById(id_prop);
    if (!p)
        return nullptr;

    const SharedValue v = p->getValue();
    if (!v) {
        if (p->getType() == data_icon)
            return strToPChar(QString("ASMA"));

        return nullptr;
    }

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

bool SceneModel::resIsEmpty() const
{
    return m_resources.isEmpty();
}

void SceneModel::setPropArrayValue(const SharedValue &value)
{
    m_propArrayValue = value;
}

const SharedValue SceneModel::getPropArrayValue()
{
    return m_propArrayValue;
}

void SceneModel::addContainerToMap(PContainer id_sdk)
{
    if (id_sdk)
        m_mapContainers.insert(id_sdk->getId(), id_sdk);
}

void SceneModel::addElementToMap(PElement id_element)
{
    if (id_element)
        m_mapElements.insert(id_element->getId(), id_element);
}

void SceneModel::addPropertyToMap(PProperty id_prop)
{
    if (id_prop)
        m_mapProperties.insert(id_prop->getId(), id_prop);
}

void SceneModel::addPointToMap(PPoint id_point)
{
    if (id_point)
        m_mapPoints.insert(id_point->getId(), id_point);
}

PSceneModel SceneModel::getModel()
{
    return this;
}
