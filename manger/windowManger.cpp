#include "windowManger.h"

// 单例模式，创建全局静态对象
Q_GLOBAL_STATIC(WindowManger, theInstance)

WindowManger::WindowManger() : QObject(nullptr), mTalkWindowShell(nullptr) {
}

WindowManger::~WindowManger() = default;

QWidget *WindowManger::findWindowName(const QString &qsWindowName) {
    if (!mWindowMap.contains(qsWindowName)) return nullptr;
    return mWindowMap.value(qsWindowName);
}

void WindowManger::deleteWindowName(const QString &qsWindowName) {
    mWindowMap.remove(qsWindowName);
}

void WindowManger::addWindowName(const QString &qsWindowName, QWidget *qWidget) {
    if (!mWindowMap.contains(qsWindowName)) mWindowMap.insert(qsWindowName, qWidget);
}

WindowManger *WindowManger::getInstance() {
    return theInstance;
}

TalkWindowShell *WindowManger::getTalkWindowShell() {
    return mTalkWindowShell;
}

QString WindowManger::getCreatingTalkId() {
    return mStrCreatingTalkId;
}

void WindowManger::addNewTalkWindow(const QString &uid) {
    if (mTalkWindowShell == nullptr) {
        mTalkWindowShell = new TalkWindowShell;
        connect(mTalkWindowShell, &TalkWindowShell::destroyed, [this](QObject *obj) {
            mTalkWindowShell = nullptr;
        });
    }

    QWidget *widget = findWindowName(uid);
    if (!widget) {
        auto *talkWindow = new TalkWindow(mTalkWindowShell, uid);
        auto *talkWindowItem = new TalkWindowItem(talkWindow);
    } else {
        mTalkWindowShell->setCurrentWidget(widget);
    }

    mTalkWindowShell->show();
    mTalkWindowShell->activateWindow();
}
