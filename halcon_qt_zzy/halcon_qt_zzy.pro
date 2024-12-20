QT       += core gui multimedia network

RC_ICONS = camera.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION,5): QT += core5compat

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += $$PWD/include
INCLUDEPATH += $$PWD/include/halconcpp

DEPENDPATH += $$PWD/include
DEPENDPATH += $$PWD/include/halconcpp

LIBS += -L$$PWD/lib -lhalcon
LIBS += -L$$PWD/lib -lhalconcpp

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
