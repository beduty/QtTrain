QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
#CONFIG += c++11
DEFINES += QT_DEPRECATED_WARNINGS
SOURCES += \
    ../91_QWx_BoostAsioREST_Client/asioclient.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ../91_QWx_BoostAsioREST_Client/asioclient.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

INCLUDEPATH += C:\local\boost_1_73_0
LIBS += -LC:\local\boost_1_73_0\lib32-msvc-14.1 -lboost_thread-vc141-mt-gd-x32-1_73

#INCLUDEPATH += $$PWD/../../../../../../local/boost_1_73_0/lib32-msvc-14.1
#DEPENDPATH += $$PWD/../../../../../../local/boost_1_73_0/lib32-msvc-14.1
#LIBS += -LC:\local\boost_1_73_0\lib32-msvc-14.1
#LIBS += C:\local\boost_1_73_0\lib32-msvc-14.1\boost_thread-vc141-mt-gd-x32-1_73.dll
#LIBS += C:\local\boost_1_73_0\lib32-msvc-14.1\boost_thread-vc141-mt-gd-x32-1_73.lib

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#win32:{}

#macx:{
#    INCLUDEPATH +=
#    LIBS+=
#}
#win32:{

#}

