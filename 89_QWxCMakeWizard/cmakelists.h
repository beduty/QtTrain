#ifndef CMAKELISTS_H
#define CMAKELISTS_H
#include <QString>
#include <QMap>
#include <QList>

class CMakeLists
{
public:
    CMakeLists();

public:
    void setProjectName(const QString&);
    void addCMakeFlags(const QString&,const QString&);
    void addDefine(const QString&);
    void addIncludeDirectory(const QString &);
    void addSource(const QString &,const QString &);

public:
    QString GenerateCMakeLists();

private:
    QString projectName;
    QMap<QString, QString> cmakeFlags;
    QList<QString> defines;
    QList<QString> includeDirectories;
    QMap<QString, QString> sources;
};

#endif // CMAKELISTS_H
