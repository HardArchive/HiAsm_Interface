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

//Константы
const char CALL_STR[] = "Call:";
const char ARG_STR[] = "Arg";
const char RESULT_STR[] = "Return:";

//Дефайны
#define DLLEXPORT extern "C" __cdecl
#define PRINT_FUNC_INFO LOG(INFO) << CALL_STR << Q_FUNC_INFO;

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

//Служебные переменные
static HMODULE m_codegen = nullptr;

INITIALIZE_EASYLOGGINGPP

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
    Q_UNUSED(hModule)
    Q_UNUSED(lpReserved)

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

    switch (reason) {
    case DLL_PROCESS_ATTACH: {
        LOG(INFO) << "CODEGEN_PROCESS_ATTACH";

        //Загружаем оригинальную DLL в память
        QString codegen = QString("%1/CodeGen_original.dll").arg(HIASM_PACKAGE);
        if(!QFile::exists(codegen)){
            MessageBoxW(0, L"Библиотека CodeGen_original.dll не найдена!", L"Ошибка!", MB_ICONERROR);
            exit(0);
        }
        m_codegen = LoadLibraryW(&codegen.toStdWString()[0]);

        //Определение функций проксируемого кодогенератора
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
        LOG(INFO) << "CODEGEN_PROCESS_DETACH";
        FreeLibrary(m_codegen);
        break;
    }
    }

    return (TRUE);
}

//Экспортируемые функции
DLLEXPORT int buildPrepareProc(TBuildPrepareRec &params)
{
    PRINT_FUNC_INFO
    int res = original_buildPrepareProc(params);
    LOG(INFO) << RESULT_STR << res;

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

    int res = original_buildProcessProc(params);  //CG_SUCCESS
    LOG(INFO) << RESULT_STR << res;
    return res;
}

DLLEXPORT int CheckVersionProc(THiAsmVersion &params)
{
    PRINT_FUNC_INFO
    int res = original_CheckVersionProc(params);
    LOG(INFO) << RESULT_STR << res;

    return res;
}

DLLEXPORT void ConfToCode(const char *Pack, const char *UName)
{
    PRINT_FUNC_INFO
    original_ConfToCode(Pack, UName);
}

DLLEXPORT void synReadFuncList(TSynParams &params)
{
    PRINT_FUNC_INFO
    original_synReadFuncList(params);
}

DLLEXPORT void hintForElement(THintParams &params)
{
    PRINT_FUNC_INFO
    original_hintForElement(params);
}

DLLEXPORT int isElementMaker(PCodeGenTools cgt, quintptr e)
{
    PRINT_FUNC_INFO
    int res = original_isElementMaker(cgt, e);
    LOG(INFO) << RESULT_STR << res;

    return res;
}

DLLEXPORT int MakeElement(PCodeGenTools cgt, quintptr e)
{
    PRINT_FUNC_INFO
    int res = original_MakeElement(cgt, e);
    LOG(INFO) << RESULT_STR << res;

    return res;
}

DLLEXPORT bool isReadyForAdd(PCodeGenTools cgt, const TRFD_Rec rfd, quintptr sdk)
{
    Q_UNUSED(cgt)
    Q_UNUSED(rfd)
    Q_UNUSED(sdk)

    //PRINT_FUNC_INFO
    bool res =  original_isReadyForAdd(cgt, rfd, sdk);
    //LOG(INFO) << RESULT_STR << res;

    return res;
}

