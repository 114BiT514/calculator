QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# Disable pre-Qt6 deprecated APIs (we're using Qt 6)
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    calculatorengine.cpp \
    financedialog.cpp

HEADERS += \
    mainwindow.h \
    calculatorengine.h \
    financedialog.h

FORMS += \
    mainwindow.ui \
    financedialog.ui

RESOURCES += \
    resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
