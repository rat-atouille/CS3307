QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    layer.cpp \
    layerManager.cpp \
    layergroup.cpp \
    main.cpp \
    application.cpp \
    project.cpp

HEADERS += \
    Brush.h \
    application.h \
    brushFactory.h \
    eraser.h \
    layer.h \
    layerComponent.h \
    layerManager.h \
    layergroup.h \
    pen.h \
    project.h

FORMS += \
    application.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
