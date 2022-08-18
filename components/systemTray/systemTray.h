#ifndef __SYSTEM_TRAY_H
#define __SYSTEM_TRAY_H

#include <QSystemTrayIcon>
#include <QWidget>
#include "customMenu.h"

/**
 * 系统托盘
 */
class SystemTray : public QSystemTrayIcon {
Q_OBJECT

public:
    explicit SystemTray(QWidget *parent);

    ~SystemTray() override;

public slots:

    void onIconActivated(QSystemTrayIcon::ActivationReason reason);

private:
    void initSystemTray();

    void addSystemMenu();

private:
    QWidget *mParent;
};

#endif // __SYSTEM_TRAY_H
