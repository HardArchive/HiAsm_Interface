#include "project.h"
#include <QFile>

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
    }
}
