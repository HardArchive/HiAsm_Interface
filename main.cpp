//STL

//Qt
#include <QDebug>
#include <QDateTime>

//Project
#include "maincontainer.h"
#include "element.h"
#include "global.h"
#include "CGTShare.h"

void myMessageOutput(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
    QTextStream cerr(stderr);
    QString DIV = "; ";
    QString LS = "\n";
    QString BEGIN = "====== %1 ======" + LS;
    QString dateTime = "DateTime: " + QDateTime::currentDateTime().toString("yyyy/MM/dd HH:mm:ss") + LS;
    QString file = "File: " + QString(context.file) + LS;
    QString function = "Function: " + QString(context.function) + LS;
    QString line = "Line: " + QString::number(context.line) + LS;
    QString message = "Message: " + msg + LS;

    QString formatedMessage = BEGIN + dateTime + file + line + function + message;

    auto makeMessage = [&](const QString& prefix) {
        cerr << formatedMessage.arg(prefix) << endl;
    };

    switch (type) {
    case QtDebugMsg:
        makeMessage("debug");
        break;
    case QtWarningMsg:
        makeMessage("warning");
        break;
    case QtCriticalMsg:
        makeMessage("critical");
        break;
    case QtFatalMsg:
        makeMessage("fatal");
        abort();
    }
}

DLLIMPORT int buildPrepareProc(TBuildPrepareRec* params)
{
    Q_UNUSED(params)

    return CG_SUCCESS;
}

DLLIMPORT int buildProcessProc(TBuildProcessRec* params)
{
    qInstallMessageHandler(myMessageOutput);
    setlocale(LC_ALL, "Russian");

    MainContainer mainContainer(params);

    return CG_SUCCESS;
}

DLLIMPORT int CheckVersionProc(THiAsmVersion* params)
{
    Q_UNUSED(params)

    return CG_SUCCESS;
}
