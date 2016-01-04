#pragma once

//Project
#include "package.h"

//STL

//Native

//Qt
#include <QtCore>

class PackageManager : public QObject
{
    Q_OBJECT

private:
    QString m_packagesDir;
    QString m_packagesPath;
    Packages m_packages;
    bool m_sucess = true;

public:
    explicit PackageManager(const QString &packagesDir = QString("packages"), QObject *parent = 0);

public:
    PPackage getPackage(const QString &namePack);

};
