#ifndef __TITLE_BAR_H
#define __TITLE_BAR_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QPainter>
#include <QMouseEvent>
#include "buttonType.h"

/**
 * 自定义标题栏
 */
class TitleBar : public QWidget {
Q_OBJECT

public:
    explicit TitleBar(QWidget *parent = nullptr);

    ~TitleBar() override;

    // 设置标题栏图标 ICOn
    void setTitleIcon(const QString &filePath);

    // 设置标题栏内容
    void setTitle(const QString &title);

    // 设置标题栏宽度
    void setTitleWidth(int width);

    // 设置标题栏按钮类型
    void setButtonType(ButtonType buttonType);

    // 保存窗口最大化前窗口的位置及大小
    void saveRestoreInfo(const QPoint &point, const QSize &size);

    // 获取窗口最大化前窗口的位置及大小
    void getRestoreInfo(QPoint &point, QSize &size);

private:
    // 绘图事件
    void paintEvent(QPaintEvent *event) override;

    // 鼠标双击事件
    void mouseDoubleClickEvent(QMouseEvent *event) override;

    // 鼠标按下事件
    void mousePressEvent(QMouseEvent *event) override;

    // 鼠标移动事件
    void mouseMoveEvent(QMouseEvent *event) override;

    // 鼠标松开事件
    void mouseReleaseEvent(QMouseEvent *event) override;


    // 初始化控件
    void initControl();

    // 初始化信号与槽的连接
    void initConnections();

    // 加载样式表
    void loadStyleSheet(const QString &styleName);


// 信号
signals:

    // 最小化按钮被点击时触发的信号
    void signalButtonMinClicked();

    // 最大化还原按钮被点击时触发的信号
    void signalButtonRestoreClicked();

    // 最大化按钮被点击时触发的信号
    void signalButtonMaxClicked();

    // 关闭按钮被点击时触发的信号
    void signalButtonCloseClicked();


// 槽
private slots:

    void onButtonMinClicked();

    void onButtonRestoreClicked();

    void onButtonMaxClicked();

    void onButtonCloseClicked();

private:

    QLabel *mIcon{};      // 标题栏图标
    QLabel *mTitle{};     // 标题栏内容

    QPushButton *mButtonMin{};        // 最小化按钮
    QPushButton *mButtonRestore{};    // 最大化还原按钮
    QPushButton *mButtonMax{};        // 最大化按钮
    QPushButton *mButtonClose{};      // 关闭按钮

    // 最大化还原按钮变量（用于保存窗体位置及大小）
    QPoint mRestorePos;
    QSize mRestoreSize;

    // 移动窗口的变量
    bool mIsPressed;
    QPoint mStartMovePos;

    QString mTitleContent;      // 标题栏内容
    ButtonType mButtonType;     // 标题栏按钮类型
};

#endif // __TITLE_BAR_H
