//Project
#include "cgt/cgt.h"
#include "cgt/proxycgt.h"
#include "cgt/emulatecgt.h"
#include "scenemodel/scenemodel.h"
#include "scenemodel/element.h"
#include "logger.h"

//NATIVE

//STL

//Qt
#include <QDebug>
#include <QLibrary>
#include <QCoreApplication>

//Дефайны
#define DLLEXPORT extern "C" __cdecl
#define PRINT_FUNC_INFO qInfo("Call: %s", Q_FUNC_INFO);
#define PRINT_RESULT(X) qInfo().noquote() << "Return:" << X;

//Переопределение вывода отладочных сообщений
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    Q_UNUSED(context)

    QByteArray message = msg.toLocal8Bit();
    switch (type) {
    case QtDebugMsg:
        LOG(DEBUG) << message.constData();
        break;
    case QtInfoMsg:
        LOG(INFO) << message.constData();
        break;
    case QtWarningMsg:
        LOG(WARNING) << message.constData();
        break;
    case QtCriticalMsg:
        LOG(ERROR) << message.constData();
        break;
    case QtFatalMsg:
        LOG(FATAL) << message.constData();
        abort();
    }
}

INITIALIZE_EASYLOGGINGPP
void initLogger()
{
    QDir makeLogDir;
    makeLogDir.mkdir("logs");
    el::Configurations conf;
    conf.setGlobally(el::ConfigurationType::Filename, "logs/%datetime.log");
    //conf.setGlobally(el::ConfigurationType::Format, "%datetime{%h:%m:%s.%z}:%levshort: %msg");
    conf.setGlobally(el::ConfigurationType::Format, "%msg");
    el::Logger *defaultLogger = el::Loggers::getLogger("default");
    defaultLogger->configure(conf);
    el::Loggers::removeFlag(el::LoggingFlag::NewLineForContainer);
    el::Loggers::addFlag(el::LoggingFlag::ColoredTerminalOutput);
    el::Loggers::addFlag(el::LoggingFlag::LogDetailedCrashReason);
    el::Loggers::addFlag(el::LoggingFlag::DisableApplicationAbortOnFatalLog);
    el::Loggers::addFlag(el::LoggingFlag::DisablePerformanceTrackingCheckpointComparison);
    el::Loggers::addFlag(el::LoggingFlag::DisableVModules);
    el::Loggers::addFlag(el::LoggingFlag::DisableVModulesExtensions);
    qInstallMessageHandler(myMessageOutput);
}

//Служебные переменные
static QLibrary codegen;
static SceneModel *sceneModel = nullptr;
static SceneModel *sceneModel2 = nullptr;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
    Q_UNUSED(lpReserved)

    switch (reason) {
    case DLL_PROCESS_ATTACH: {
        //ru Инициализация логгера
        initLogger();
        qInfo() << "CODEGEN_PROCESS_ATTACH";

        //ru Вычисляем путь к оригинальному кодогенератору относительно текущего модуля (hModule)
        const uint max_path = 2048;
        char tmpCurrentModulePath[max_path];
        GetModuleFileNameA(hModule, tmpCurrentModulePath, max_path);
        QFileInfo currentModulePath(QString::fromLocal8Bit(tmpCurrentModulePath));
        const QString nameOriginal = "CodeGen_original.dll";
        QString pathOriginal = currentModulePath.absolutePath() + QDir::separator() + nameOriginal;
        pathOriginal = QDir::toNativeSeparators(pathOriginal);

        //ru Загружаем оригинальную DLL в память
        if (!QFile::exists(pathOriginal)) {
            qCritical("«%s» library not found!", qPrintable(nameOriginal));
            exit(0);
        }
        codegen.setFileName(pathOriginal);
        if (codegen.load())
            qInfo("%s library successfully loaded.", qUtf8Printable(nameOriginal));
        else
            qCritical("%s library is not loaded.", qUtf8Printable(nameOriginal));

        //ru Определение прототипов функций проксируемого кодогенератора
        buildPrepareProcLib = reinterpret_cast<t_buildPrepareProc>(codegen.resolve("buildPrepareProc"));
        buildProcessProcLib = reinterpret_cast<t_buildProcessProc>(codegen.resolve("buildProcessProc"));
        checkVersionProcLib = reinterpret_cast<t_checkVersionProc>(codegen.resolve("CheckVersionProc"));
        break;
    }

    case DLL_PROCESS_DETACH: {
        qInfo() << "CODEGEN_PROCESS_DETACH";

        delete sceneModel;
        delete sceneModel2;
        codegen.unload();
        break;
    }
    }

    return TRUE;
}

//Экспортируемые функции
DLLEXPORT int buildPrepareProc(void *params)
{
    Q_UNUSED(params)
    return buildPrepareProcLib(params);
}

DLLEXPORT int buildProcessProc(TBuildProcessRec &params)
{
    PRINT_FUNC_INFO

#ifdef MODEL
    sceneModel = new SceneModel;
    sceneModel->initFromCgt(params.cgt, params.sdk);

    EmulateCgt::setSceneModel(sceneModel);
    params.cgt = EmulateCgt::getCgt();
#endif

#ifdef PROXY_MODEL
    ProxyCgt::setProxiedCgt(EmulateCgt::getCgt());
    params.cgt = ProxyCgt::getCgt();
#endif

#ifdef PROXY_ORIGINAL
    ProxyCgt::setProxiedCgt(params.cgt);
    params.cgt = ProxyCgt::getCgt();
#endif

    int res = buildProcessProcLib(params);
    PRINT_RESULT(CgResultMap[res]);

    return res;
}

DLLEXPORT int CheckVersionProc(const THiAsmVersion &params)
{
    PRINT_FUNC_INFO
    qInfo("Arg1: %d.%d.%d", params.major, params.minor, params.build);
    int res = checkVersionProcLib(params);
    PRINT_RESULT(res);
    return res;
}
