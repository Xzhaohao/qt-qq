#include "systemTray.h"

SystemTray::SystemTray(QWidget *parent) : mParent(parent), QSystemTrayIcon(parent) {
    initSystemTray();
    show();
}

SystemTray::~SystemTray() = default;

void SystemTray::initSystemTray() {
    setToolTip(QString::fromUtf8("假QQ"));
    setIcon(QIcon(":/assets/app/logo.ico"));
    connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(onIconActivated(QSystemTrayIcon::ActivationReason)));
}

void SystemTray::onIconActivated(QSystemTrayIcon::ActivationReason reason) {
    if (reason == QSystemTrayIcon::Trigger) {
        mParent->show();
        mParent->activateWindow();
    } else if (reason == QSystemTrayIcon::Context) {
        addSystemMenu();
    }
}

void SystemTray::addSystemMenu() {
    auto *customMenu = new CustomMenu(mParent);
    customMenu->addCustomMenu("onShow", ":/assets/app/logo.ico", QString::fromUtf8("显示"));
    customMenu->addCustomMenu("onQuit", ":/assets/app/page_close_btn_hover.png", QString::fromUtf8("退出"));

    connect(customMenu->getAction("onShow"), SIGNAL(triggered(bool)), mParent, SLOT(onShowNormal(bool)));
    connect(customMenu->getAction("onQuit"), SIGNAL(triggered(bool)), mParent, SLOT(onShowQuit(bool)));

    // 让CustomMenu进入事件循环
    customMenu->exec(QCursor::pos());
    delete customMenu;
    customMenu = nullptr;
}
