#include "project.h"
#include <QFile>
#include <QDebug>
#include <QRegExp>

Project::Project(const QString &filePath, QObject *parent)
    : QObject(parent)
    , m_filePath(filePath)
{
    load();
    parse();
}

bool Project::load()
{
    QFile file(m_filePath);
    if (!file.open(QIODevice::ReadOnly))
        return false;

    m_fileContent = QString(file.readAll()).split("\r\n");
    return true;
}

void Project::parse()
{
    for (const QString &s : m_fileContent) {
        qInfo() << getLineType(s);
    }
}

Project::LineType Project::getLineType(const QString &str)
{
    QString Make = "*Make(*)";
    QString Ver = "*ver(*)";
    QString Add = "*Add(*)";
    QString OpenBlock = "*{*";
    QString CloseBlock = "*}*";
    QString Link = "*link(*)";
    QString Prop = "*=*";
    QString Point = "*Point(*)";
    QString Hint = "*@Hint=*";
    QString BEGIN_SDK = "*BEGIN_SDK";
    QString END_SDK = "*END_SDK";

    QString temp;
    bool skipSpace = false;

    auto checkPattern = [&](const QString &pattern) {
        QRegExp regExp(pattern, Qt::CaseSensitive, QRegExp::Wildcard);
        return regExp.exactMatch(str);
    };

    if (checkPattern(Make))
        return LineType::Make;
    if (checkPattern(Ver))
        return LineType::Ver;
    if (checkPattern(Add))
        return LineType::Add;
    if (checkPattern(OpenBlock))
        return LineType::OpenBlock;
    if (checkPattern(CloseBlock))
        return LineType::CloseBlock;
    if (checkPattern(Link))
        return LineType::Link;
    if (checkPattern(Prop))
        return LineType::Prop;
    if (checkPattern(Point))
        return LineType::Point;
    if (checkPattern(Hint))
        return LineType::Hint;
    if (checkPattern(BEGIN_SDK))
        return LineType::BEGIN_SDK;
    if (checkPattern(END_SDK))
        return LineType::END_SDK;

    return LineType::Undefined;
}
