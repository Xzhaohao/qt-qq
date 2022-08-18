#ifndef __MAIN_WINDOW_H
#define __MAIN_WINDOW_H

#include <QTimer>
#include "ui_mainWindow.h"
#include "mainProxyStyle.h"
#include "../base/baseWindow.h"
#include "../skin/skin.h"
#include "../../components/systemTray/systemTray.h"

class MainWindow : public BaseWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

public:
    void initTimer();

    void initControl();

    void setUsername(const QString &username);

    void setLevelPixmap(int level);

    void setAvatarPixmap(const QString &avatar);

    // 设置在线状态
    void setStatusMenuIcon(const QString &statusPath);

    // 添加应用部件
    QWidget *addOtherAppExtension(const QString &appPath, const QString &appName);

private:
    void resizeEvent(QResizeEvent *event) override;

    bool eventFilter(QObject *obj, QEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

private slots:

    void onAppIconClicked();

private:
    Ui::MainWindow *ui;
};

#endif // __MAIN_WINDOW_H
