#ifndef __MAIN_WINDOW_H
#define __MAIN_WINDOW_H

#include <QTimer>
#include "ui_mainWindow.h"
#include "mainProxyStyle.h"
#include "rootContactItem.h"
#include "../base/baseWindow.h"
#include "../skin/skin.h"
#include "../../components/systemTray/systemTray.h"
#include "../../components/contactItem/contactItem.h"

class MainWindow : public BaseWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

public:
    void setUsername(const QString &username);

    void setLevelPixmap(int level);

    void setAvatarPixmap(const QString &avatar);

    // 设置在线状态
    void setStatusMenuIcon(const QString &statusPath);

    // 添加应用部件
    QWidget *addOtherAppExtension(const QString &appPath, const QString &appName);

private:
    void resizeEvent(QResizeEvent *event) override;

    // 事件过滤器
    bool eventFilter(QObject *obj, QEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

private:
    void initControl();

    // 初始化计时器
    void initTimer();

    // 更新搜索框样式
    void updateSearchStyle();

    // 初始化联系人
    void initContactTree();

    // 添加部门
    void addCompanyDeps(QTreeWidgetItem *pRootGroupItem, const QString &deps);

private slots:

    void onAppIconClicked();

    void onItemClicked(QTreeWidgetItem *item, int column);

    void onItemExpanded(QTreeWidgetItem *item);

    void onItemCollapsed(QTreeWidgetItem *item);

    void onItemDoubleClicked(QTreeWidgetItem *item, int column);

private:
    Ui::MainWindow *ui;
};

#endif // __MAIN_WINDOW_H
