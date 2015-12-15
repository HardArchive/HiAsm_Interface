//Project
#include "cgt/cgt.h"
#include "cgt/proxycgt.h"
#include "cgt/emulatecgt.h"
#include "scenemodel/scenemodel.h"
#include "scenemodel/element.h"
#include "logger.h"

//NATIVE
#include <windows.h>

//STL
#include <iostream>

//Qt
#include <QDebug>
#include <QDateTime>

//Дефайны
#define DLLEXPORT extern "C" __cdecl
#define PRINT_FUNC_INFO qDebug("Call: %s", Q_FUNC_INFO);
#define PRINT_RESULT(X) qDebug().noquote() << "Return:" << X;

//Константы
static const char NOT_FOUND_FUNCTION[] = "Called function is not found: %s";

//Типы функций
typedef int(*t_buildPrepareProc)(TBuildPrepareRec &params);
typedef int(*t_buildProcessProc)(TBuildProcessRec &params);
typedef int(*t_CheckVersionProc)(THiAsmVersion &params);
typedef void(*t_ConfToCode)(const char *Pack, const char *UName);
typedef void(*t_synReadFuncList)(TSynParams &params);
typedef void(*t_hintForElement)(THintParams &params);
typedef int(*t_isElementMaker)(PCodeGenTools cgt, quintptr e);
typedef int(*t_MakeElement)(PCodeGenTools cgt, quintptr e);
typedef bool(*t_isReadyForAdd)(PCodeGenTools cgt, const TRFD_Rec rfd, quintptr sdk);

//Объявление функций проксируемого кодогенератора
static t_buildPrepareProc original_buildPrepareProc;
static t_buildProcessProc original_buildProcessProc;
static t_CheckVersionProc original_CheckVersionProc;
static t_ConfToCode original_ConfToCode;
static t_synReadFuncList original_synReadFuncList;
static t_hintForElement original_hintForElement;
static t_isElementMaker original_isElementMaker;
static t_MakeElement original_MakeElement;
static t_isReadyForAdd original_isReadyForAdd;


//Переопределение вывода отладочных сообщений
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    Q_UNUSED(context)

    switch(type) {
    case QtDebugMsg:
        LOG(DEBUG) << msg;
        break;
    case QtInfoMsg:
        LOG(INFO) << msg;
        break;
    case QtWarningMsg:
        LOG(WARNING) << msg;
        break;
    case QtCriticalMsg:
        LOG(ERROR) << msg;
        break;
    case QtFatalMsg:
        LOG(FATAL) << msg;
        abort();
    }
}

//Служебные переменные
static HMODULE m_codegen = nullptr;

INITIALIZE_EASYLOGGINGPP

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
    Q_UNUSED(hModule)
    Q_UNUSED(lpReserved)

    switch (reason) {
    case DLL_PROCESS_ATTACH: {
        //Инициализация логгера
        QDir makeLogDir;
        makeLogDir.mkdir("logs");
        el::Configurations conf;
        conf.setGlobally(el::ConfigurationType::Filename, "logs/%datetime.log");
        conf.setGlobally(el::ConfigurationType::Format, "%datetime{%h:%m:%s.%z}: %msg");
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

        qDebug() << "CODEGEN_PROCESS_ATTACH";

        //ru Вычисляем путь к оригинальному кодогенератору относительно текущего модуля (hModule)
        const uint max_path = 2048;
        char tmpCurrentModulePath[max_path];
        GetModuleFileNameA(hModule, tmpCurrentModulePath, max_path);
        QFileInfo currentModulePath(QString::fromLocal8Bit(tmpCurrentModulePath));
        QString nameOriginal = "CodeGen_original.dll";
        QString pathOriginal = currentModulePath.absolutePath() + QDir::separator() + nameOriginal;
        pathOriginal = QDir::toNativeSeparators(pathOriginal);

        //ru Загружаем оригинальную DLL в память
        if (!QFile::exists(pathOriginal)) {
            MessageBoxW(0, QString("Библиотека %1 не найдена!").arg(nameOriginal).toStdWString().data(),
                        L"Ошибка!", MB_ICONERROR);
            exit(0);
        }
        m_codegen = LoadLibraryW(pathOriginal.toStdWString().data());
        if (m_codegen)
            qDebug("%s successfully loaded.", qPrintable(nameOriginal));
        else
            qCritical("%s is not loaded.", qPrintable(nameOriginal));

        //ru Определение прототипов функций проксируемого кодогенератора
        original_buildPrepareProc = reinterpret_cast<t_buildPrepareProc>(GetProcAddress(m_codegen, "buildPrepareProc"));
        original_buildProcessProc = reinterpret_cast<t_buildProcessProc>(GetProcAddress(m_codegen, "buildProcessProc"));
        original_CheckVersionProc = reinterpret_cast<t_CheckVersionProc>(GetProcAddress(m_codegen, "CheckVersionProc"));
        original_ConfToCode = reinterpret_cast<t_ConfToCode>(GetProcAddress(m_codegen, "ConfToCode"));
        original_synReadFuncList = reinterpret_cast<t_synReadFuncList>(GetProcAddress(m_codegen, "synReadFuncList"));
        original_hintForElement = reinterpret_cast<t_hintForElement>(GetProcAddress(m_codegen, "hintForElement"));
        original_isElementMaker = reinterpret_cast<t_isElementMaker>(GetProcAddress(m_codegen, "isElementMaker"));
        original_MakeElement = reinterpret_cast<t_MakeElement>(GetProcAddress(m_codegen, "MakeElement"));
        original_isReadyForAdd = reinterpret_cast<t_isReadyForAdd>(GetProcAddress(m_codegen, "isReadyForAdd"));

        break;
    }

    case DLL_PROCESS_DETACH: {
        qDebug() << "CODEGEN_PROCESS_DETACH";
        FreeLibrary(m_codegen);
        break;
    }
    }

    return TRUE;
}

//Экспортируемые функции
DLLEXPORT int buildPrepareProc(TBuildPrepareRec &params)
{
    if (!original_buildPrepareProc) {
        qDebug(NOT_FOUND_FUNCTION, Q_FUNC_INFO);
        return 1;
    }

    PRINT_FUNC_INFO
    int res = original_buildPrepareProc(params);
    PRINT_RESULT(res);
    return res;
}

DLLEXPORT int buildProcessProc(TBuildProcessRec &params)
{
    PRINT_FUNC_INFO
    cgt::init(params);

#ifdef PROXYCGT
    //ProxyCgt::setProxiedCgt(params.cgt);
    //cgt::setProxyCgt(ProxyCgt::getCgt());
#endif

#ifdef SCENEMODEL
    SceneModel sceneModel;
    EmulateCgt::setSceneModel(sceneModel);
    ProxyCgt::setProxiedCgt(EmulateCgt::getCgt());
#else
    ProxyCgt::setProxiedCgt(params.cgt);
#endif

#ifdef PROXYCGT
    cgt::setProxyCgt(ProxyCgt::getCgt());
#endif

    int res = original_buildProcessProc(params);
    PRINT_RESULT(CgResult(res));
    return res;
}

DLLEXPORT int CheckVersionProc(THiAsmVersion &params)
{
    if (!original_CheckVersionProc) {
        qDebug(NOT_FOUND_FUNCTION, Q_FUNC_INFO);
        return 0;
    }


    PRINT_FUNC_INFO
    qDebug("Arg1: %d.%d.%d", params.major, params.minor, params.build);
    int res = original_CheckVersionProc(params);
    PRINT_RESULT(res);
    return res;
}

DLLEXPORT void ConfToCode(const char *pack, const char *name)
{
    if (!original_ConfToCode) {
        qDebug(NOT_FOUND_FUNCTION, Q_FUNC_INFO);
        return;
    }

    PRINT_FUNC_INFO
    qDebug("Arg1: \"%s\"", pack);
    qDebug("Arg2: \"%s\"", name);
    original_ConfToCode(pack, name);
}

DLLEXPORT void synReadFuncList(TSynParams &params)
{
    if (!original_synReadFuncList) {
        qDebug(NOT_FOUND_FUNCTION, Q_FUNC_INFO);
        return;
    }

    PRINT_FUNC_INFO
    original_synReadFuncList(params);
}

DLLEXPORT void hintForElement(THintParams &params)
{
    if (!original_hintForElement) {
        qDebug(NOT_FOUND_FUNCTION, Q_FUNC_INFO);
        return;
    }

    PRINT_FUNC_INFO
    original_hintForElement(params);
}

DLLEXPORT int isElementMaker(PCodeGenTools cgt, quintptr id_element)
{
    if (!original_isElementMaker) {
        qDebug(NOT_FOUND_FUNCTION, Q_FUNC_INFO);
        return 0;
    }


    PRINT_FUNC_INFO
    int res = original_isElementMaker(cgt, id_element);
    PRINT_RESULT(res);
    return res;
}

DLLEXPORT int MakeElement(PCodeGenTools cgt, quintptr id_element)
{
    if (!original_MakeElement) {
        qDebug(NOT_FOUND_FUNCTION, Q_FUNC_INFO);
        return 0;
    }

    PRINT_FUNC_INFO
    int res = original_MakeElement(cgt, id_element);
    PRINT_RESULT(res);
    return res;
}

DLLEXPORT bool isReadyForAdd(PCodeGenTools cgt, const TRFD_Rec rfd, quintptr id_sdk)
{
    if (!original_isReadyForAdd) {
        qDebug(NOT_FOUND_FUNCTION, Q_FUNC_INFO);
        return true;
    }

    PRINT_FUNC_INFO
    bool res =  original_isReadyForAdd(cgt, rfd, id_sdk);
    PRINT_RESULT(res);
    return res;
}

