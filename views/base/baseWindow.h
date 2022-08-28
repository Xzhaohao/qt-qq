#ifndef __BASE_WINDOW_H
#define __BASE_WINDOW_H

#include <QDialog>
#include <QStyleOption>
#include <QApplication>
#include <QDesktopWidget>
#include <QSqlQuery>
#include "../../components/titleBar/titleBar.h"
#include "../../manger/notifyManger.h"

class BaseWindow : public QDialog {
Q_OBJECT

public:
    explicit BaseWindow(QWidget *parent = nullptr);

    ~BaseWindow() override;

public:
    // 加载样式表
    void loadStyleSheet(const QString &styleName);

    // 获取圆头像
    QPixmap getRoundImage(const QPixmap &src, QPixmap &mask, QSize maskSize = QSize(0, 0));

protected:
    void paintEvent(QPaintEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

protected:
    void initTitleBar(ButtonType buttonType = MIN_BUTTON);

    void setTitleBarTitle(const QString &title, const QString &icon = "");

public slots:

    void onShowClose(bool);

    void onShowMin(bool);

    void onShowHide(bool);

    void onShowNormal(bool);

    void onShowQuit(bool);

    void onSignalSkinChanged(const QColor &color);      // 皮肤被修改

    void onButtonMinClicked();

    void onButtonRestoreClicked();

    void onButtonMaxClicked();

    void onButtonCloseClicked();

protected:
    QPoint mMousePoint;          // 鼠标位置
    bool mMousePressed{};        // 鼠标是否按下
    QColor mColorBackground;     // 背景色
    QString mStyleName;          // 样式文件名称
    TitleBar *titleBar{};        // 标题栏
};

#endif // __BASE_WINDOW_H
