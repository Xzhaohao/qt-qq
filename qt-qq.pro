QT       += core gui sql xml network webenginewidgets webchannel webengine

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

RC_ICONS += logo.ico

SOURCES += \
    main.cpp \
    views/main/mainWindow.cpp \
    views/base/baseWindow.cpp \
    components/titleBar/titleBar.cpp \
    manger/notifyManger.cpp \
    manger/windowManger.cpp \
    utils/commonUtils.cpp \
    views/login/login.cpp \
    views/skin/skin.cpp \
    components/clickLabel/clickLabel.cpp \
    components/systemTray/systemTray.cpp \
    components/systemTray/customMenu.cpp \
    components/contactItem/contactItem.cpp \
    components/msgEdit/QMsgTextEdit.cpp \
    components/msgView/msgWebView.cpp \
    views/sendFile/sendFile.cpp \
    views/main/rootContactItem.cpp \
    views/talk/talkWindow.cpp \
    views/talk/talkWindowShell.cpp \
    views/emotion/emotionWindow.cpp \
    views/emotion/emotionLabelItem.cpp \
    views/receiveFile/receiveFile.cpp \
    views/talk/talkWindowItem.cpp

HEADERS += \
    views/main/mainWindow.h \
    views/base/baseWindow.h \
    components/titleBar/titleBar.h \
    components/titleBar/buttonType.h \
    manger/notifyManger.h \
    manger/windowManger.h \
    utils/commonUtils.h \
    utils/customProxyStyle.h \
    views/login/login.h \
    views/main/mainProxyStyle.h \
    views/skin/skin.h \
    components/clickLabel/clickLabel.h \
    components/systemTray/systemTray.h \
    components/systemTray/customMenu.h \
    components/contactItem/contactItem.h \
    components/msgEdit/QMsgTextEdit.h \
    components/msgView/msgWebView.h \
    views/sendFile/sendFile.h \
    views/main/rootContactItem.h \
    views/talk/talkWindow.h \
    views/talk/talkWindowShell.h \
    views/emotion/emotionWindow.h \
    views/emotion/emotionLabelItem.h \
    views/receiveFile/receiveFile.h \
    views/talk/talkWindowItem.h

FORMS += \
    views/main/mainWindow.ui \
    views/login/login.ui \
    views/skin/skin.ui \
    views/talk/talkWindowShell.ui \
    views/talk/talkWindow.ui \
    views/emotion/emotionWindow.ui \
    views/talk/talkWindowItem.ui \
    components/contactItem/contactItem.ui \
    views/receiveFile/receiveFile.ui \
    views/sendFile/sendFile.ui

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
