#pragma once
//Project
#include "scenemodel.h"

//STL

//Qt
#include <QObject>
#include <QVector>
#include <QSharedPointer>
#include <QVariantMap>
#include <QVariantList>
#include <QStack>
#include <QJsonDocument>

class SHALoader : public QObject
{
    Q_OBJECT

public:
    enum LineType {
        Null,
        Undefined,
        Ignore,
        Make,
        Ver,
        Add,
        OpenBlock,
        CloseBlock,
        Link,
        Point,
        HideProp,
        Prop,
        BEGIN_SDK,
        END_SDK,
        Empty
    };
    Q_ENUM(LineType)

    enum ParseType {
        BeginToEnd,
        EndToBegin
    };
    Q_ENUM(ParseType)

private:
    QStringList m_content;
    QString m_filePath;
    SceneModel *m_model;

public:
    explicit SHALoader(const QString &filePath, SceneModel *model, QObject *parent = 0);
    explicit SHALoader(SceneModel *model, QObject *parent = 0);

public:
    bool loadSha();
    bool parse();
    QString getFilePath() const;
    void setFilePath(const QString &filePath);

private:
    static QString findBlock(const QString &line, const QString &beginTok,
                             const QString &endTok);
    static QStringList findMultiBlock(QString &str, const QString &beginTok,
                                      const QString &endTok,
                                      bool cutBlock = false,
                                      bool removeTok = false);
    static QPair<QString, QString> splitSLine(const QString &sline, const QChar &del, ParseType type = BeginToEnd);
    static QVariantMap linkToVariantMap(const QString &sline);
    static QVariantMap propToVariantMap(const QString &sline);

    static LineType getLineType(const QString &sline);
    static LineType getLineType(const QStringList &content, int idx);
    bool parseHeader();
    QVariantList parseElements(int begin = 0, int _size = 0, int *prev = 0);
};
