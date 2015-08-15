//Project
#include "global.h"
#include "CGTShare.h"
#include "cgtsharewrapper.h"
#include "maincontainer.h"
#include "element.h"

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
const char RESULT_STR[] = "Result:";

//Типы функций
typedef int(*t_buildPrepareProc)(TBuildPrepareRec &params);
typedef int(*t_buildProcessProc)(TBuildProcessRec &params);
typedef int(*t_CheckVersionProc)(THiAsmVersion &params);
typedef void(*t_ConfToCode)(const char *Pack, const char *UName);
typedef void(*t_synReadFuncList)(TSynParams &params);
typedef void(*t_hintForElement)(THintParams &params);
typedef int(*t_isElementMaker)(PCodeGenTools cgt, id_element e);
typedef int(*t_MakeElement)(PCodeGenTools cgt, id_element e);
typedef bool(*t_isReadyForAdd)(PCodeGenTools cgt, const TRFD_Rec rfd, id_sdk sdk);

//Объявление функций проксируемого кодогенератора
static t_buildPrepareProc proxy_buildPrepareProc;
static t_buildProcessProc proxy_buildProcessProc;
static t_CheckVersionProc proxy_CheckVersionProc;
static t_ConfToCode proxy_ConfToCode;
static t_synReadFuncList proxy_synReadFuncList;
static t_hintForElement proxy_hintForElement;
static t_isElementMaker proxy_isElementMaker;
static t_MakeElement proxy_MakeElement;
static t_isReadyForAdd proxy_isReadyForAdd;

//Переопределение вывода отладочных сообщений
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    Q_UNUSED(context)

    QByteArray localMsg = msg.toLocal8Bit();
    switch(type) {
    case QtDebugMsg:
        std::cout << localMsg.constData() << std::endl;
        break;
    case QtInfoMsg:
        std::cout << localMsg.constData() << std::endl;
        break;
    case QtWarningMsg:
        std::cerr << localMsg.constData() << std::endl;
        break;
    case QtCriticalMsg:
        std::cerr << localMsg.constData() << std::endl;
        break;
    case QtFatalMsg:
        std::cerr << localMsg.constData() << std::endl;
        abort();
    }
}

//Служебные переменные
static HMODULE m_codegen = nullptr;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
    Q_UNUSED(hModule)
    Q_UNUSED(lpReserved)

    switch(reason) {
    case DLL_PROCESS_ATTACH: {
        qInstallMessageHandler(myMessageOutput);

        qDebug() << "CODEGEN_PROCESS_ATTACH";

        //Загружаем оригинальную DLL в память
        m_codegen = LoadLibraryW(L"D:/MyProgs/HiAsm_AltBuild/Elements/delphi/CodeGen_orig.dll");

        //Определение функций проксируемого кодогенератора
        proxy_buildPrepareProc = (t_buildPrepareProc)GetProcAddress(m_codegen, "buildPrepareProc");
        proxy_buildProcessProc = (t_buildProcessProc)GetProcAddress(m_codegen, "buildProcessProc");
        proxy_CheckVersionProc = (t_CheckVersionProc)GetProcAddress(m_codegen, "CheckVersionProc");
        proxy_ConfToCode = (t_ConfToCode)GetProcAddress(m_codegen, "ConfToCode");
        proxy_synReadFuncList = (t_synReadFuncList)GetProcAddress(m_codegen, "synReadFuncList");
        proxy_hintForElement = (t_hintForElement)GetProcAddress(m_codegen, "hintForElement");
        proxy_isElementMaker = (t_isElementMaker)GetProcAddress(m_codegen, "isElementMaker");
        proxy_MakeElement = (t_MakeElement)GetProcAddress(m_codegen, "MakeElement");
        proxy_isReadyForAdd = (t_isReadyForAdd)GetProcAddress(m_codegen, "isReadyForAdd");

        break;
    }

    case DLL_PROCESS_DETACH: {
        qDebug() << "CODEGEN_PROCESS_DETACH";

        FreeLibrary(m_codegen);

        break;
    }
    }

    return(TRUE);
}

//Экспортируемые функции
DLLEXPORT int buildPrepareProc(TBuildPrepareRec &params)
{
    PRINT_FUNC_INFO
    int res = proxy_buildPrepareProc(params);
    qDebug() << RESULT_STR << res;

    return res;
}

DLLEXPORT int buildProcessProc(TBuildProcessRec &params)
{
    PRINT_FUNC_INFO

    cgt::saveOriginalCgt(params.cgt);
    params.cgt = cgt::getProxyCgt();

//#define MAINCONTAINER
#ifdef MAINCONTAINER
    MainContainer mainContainer(params);
    return CG_SUCCESS;
#else
    int res = proxy_buildProcessProc(params);
    qDebug() << RESULT_STR << res;
    return res;
#endif
}

DLLEXPORT int CheckVersionProc(THiAsmVersion &params)
{
    PRINT_FUNC_INFO
    int res = proxy_CheckVersionProc(params);
    qDebug() << RESULT_STR << res;

    return res;
}

DLLEXPORT void ConfToCode(const char *Pack, const char *UName)
{
    PRINT_FUNC_INFO
    proxy_ConfToCode(Pack, UName);
}

DLLEXPORT void synReadFuncList(TSynParams &params)
{
    PRINT_FUNC_INFO
    proxy_synReadFuncList(params);
}

DLLEXPORT void hintForElement(THintParams &params)
{
    PRINT_FUNC_INFO
    proxy_hintForElement(params);
}

DLLEXPORT int isElementMaker(PCodeGenTools cgt, id_element e)
{
    PRINT_FUNC_INFO
    int res = proxy_isElementMaker(cgt, e);
    qDebug() << RESULT_STR << res;

    return res;
}

DLLEXPORT int MakeElement(PCodeGenTools cgt, id_element e)
{
    PRINT_FUNC_INFO
    int res = proxy_MakeElement(cgt, e);
    qDebug() << RESULT_STR << res;

    return res;
}

DLLEXPORT bool isReadyForAdd(PCodeGenTools cgt, const TRFD_Rec rfd, id_sdk sdk)
{
    Q_UNUSED(cgt)
    Q_UNUSED(rfd)
    Q_UNUSED(sdk)

    //PRINT_FUNC_INFO
    //bool res =  proxy_isReadyForAdd(cgt, rfd, sdk);
    //qDebug() << RESULT_STR << res;

    return 1;
}

