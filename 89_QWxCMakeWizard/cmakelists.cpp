#include "cmakelists.h"
#include <QTextStream>
CMakeLists::CMakeLists()
{

}

void CMakeLists::setProjectName(const QString &name)
{
    projectName = name;
}

void CMakeLists::addCMakeFlags(const QString &key, const QString &value)
{
    cmakeFlags.insert(key, value);
}

void CMakeLists::addDefine(const QString &value)
{
    defines.append(value);
}

void CMakeLists::addIncludeDirectory(const QString &dir)
{
    includeDirectories.append(dir);
}

void CMakeLists::addSource(const QString &key, const QString &value)
{
    sources.insert(key, value);
}

QString CMakeLists::GenerateCMakeLists()
{
    QString outpurString;
    QTextStream ots(&outpurString); // QString 뿐 아니라, File핸들을 넣어주면 파일에 데이터가 쓰여진다!
    //ots<<"test"<< endl;
    //ots<<QString("xxx %1, %2").arg(1).arg("sd")<<endl;

    ots<<"cmake_minimum_required(VERSION 3.10)"<<endl;
    ots<<QString("project(%1)").arg(projectName)<<endl;

    for(const auto& e: cmakeFlags.keys()){
        ots<<QString("set(%1 %2)").arg(e, cmakeFlags.value(e))<<endl;
    }

    if(defines.size()>0){
        QString def = "";
        for(const auto& e : defines){
            def += "-D" + e + " ";
        }
        ots<<QString("add_definitions(%1)").arg(def)<<endl;
    }

    for(const auto& e : includeDirectories){
        ots<<QString("include_directories(%1)").arg(e)<<endl;
    }

    for(const auto& e: sources.keys()){
        ots<<QString("add_executable(%1 %2)").arg(e, sources.value(e))<<endl;
    }

    return outpurString;
}













