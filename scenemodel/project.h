#pragma once

#include <QObject>

class Project : public QObject {
    Q_OBJECT
public:
    explicit Project(const QString &filePath, QObject *parent = 0);

private:
    QStringList m_fileContent;
    QString m_filePath;
    QString m_package;

private:
    bool load();
    void parse();
};
