QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    asioclient.cpp \
    main.cpp \
    widget.cpp

HEADERS += \
    asioclient.h \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += C:\local\boost_1_73_0
LIBS += -LC:\local\boost_1_73_0\lib32-msvc-14.1 -lboost_thread-vc141-mt-gd-x32-1_73
