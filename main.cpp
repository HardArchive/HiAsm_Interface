//Project
#include "global.h"
#include "CGTShare.h"
#include "cgt.h"
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
const char RESULT_STR[] = "Return:";

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
        original_buildPrepareProc = (t_buildPrepareProc)GetProcAddress(m_codegen, "buildPrepareProc");
        original_buildProcessProc = (t_buildProcessProc)GetProcAddress(m_codegen, "buildProcessProc");
        original_CheckVersionProc = (t_CheckVersionProc)GetProcAddress(m_codegen, "CheckVersionProc");
        original_ConfToCode = (t_ConfToCode)GetProcAddress(m_codegen, "ConfToCode");
        original_synReadFuncList = (t_synReadFuncList)GetProcAddress(m_codegen, "synReadFuncList");
        original_hintForElement = (t_hintForElement)GetProcAddress(m_codegen, "hintForElement");
        original_isElementMaker = (t_isElementMaker)GetProcAddress(m_codegen, "isElementMaker");
        original_MakeElement = (t_MakeElement)GetProcAddress(m_codegen, "MakeElement");
        original_isReadyForAdd = (t_isReadyForAdd)GetProcAddress(m_codegen, "isReadyForAdd");

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
    int res = original_buildPrepareProc(params);
    qDebug() << RESULT_STR << res;

    return res;
}

DLLEXPORT int buildProcessProc(TBuildProcessRec &params)
{
    PRINT_FUNC_INFO

    cgt::setParams(params);

#define MAINCONTAINER
#ifdef MAINCONTAINER
    MainContainer mainContainer;
    return CG_SUCCESS;
#else
    int res = original_buildProcessProc(params);
    qDebug() << RESULT_STR << res;
    return res;
#endif
}

DLLEXPORT int CheckVersionProc(THiAsmVersion &params)
{
    PRINT_FUNC_INFO
    int res = original_CheckVersionProc(params);
    qDebug() << RESULT_STR << res;

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

DLLEXPORT int isElementMaker(PCodeGenTools cgt, id_element e)
{
    PRINT_FUNC_INFO
    int res = original_isElementMaker(cgt, e);
    qDebug() << RESULT_STR << res;

    return res;
}

DLLEXPORT int MakeElement(PCodeGenTools cgt, id_element e)
{
    PRINT_FUNC_INFO
    int res = original_MakeElement(cgt, e);
    qDebug() << RESULT_STR << res;

    return res;
}

DLLEXPORT bool isReadyForAdd(PCodeGenTools cgt, const TRFD_Rec rfd, id_sdk sdk)
{
    Q_UNUSED(cgt)
    Q_UNUSED(rfd)
    Q_UNUSED(sdk)

    //PRINT_FUNC_INFO
    //bool res =  original_isReadyForAdd(cgt, rfd, sdk);
    //qDebug() << RESULT_STR << res;

    return 1;
}

