QT       += core gui sql xml network webenginewidgets webchannel

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

SOURCES += \
    main.cpp \
    views/main/mainWindow.cpp \
    views/base/baseWindow.cpp \
    components/titleBar/titleBar.cpp \
    manger/notifyManger.cpp \
    utils/commonUtils.cpp \
    views/login/login.cpp

HEADERS += \
    views/main/mainWindow.h \
    views/base/baseWindow.h \
    components/titleBar/titleBar.h \
    components/titleBar/buttonType.h \
    manger/notifyManger.h \
    utils/commonUtils.h \
    utils/customProxyStyle.h \
    views/login/login.h \
    views/main/mainProxyStyle.h

FORMS += \
    views/main/mainWindow.ui \
    views/login/login.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

msvc {
    QMAKE_CFLAGS += /utf-8
    QMAKE_CXXFLAGS += /utf-8
}

RESOURCES += \
    res.qrc
