#ifndef __TALK_WINDOW_SHELL_H
#define __TALK_WINDOW_SHELL_H

#include <QTcpSocket>
#include "ui_talkWindowShell.h"
#include "talkWindow.h"
#include "talkWindowItem.h"
#include "../base/baseWindow.h"
#include "../emotion/emotionWindow.h"
#include "../../utils/customProxyStyle.h"

#define TCP_PORT 10086

class TalkWindowShell : public BaseWindow {
Q_OBJECT

public:
    explicit TalkWindowShell(QWidget *parent = nullptr);

    ~TalkWindowShell() override;

public:
    // 添加聊天窗口
    void addTalkWindow(TalkWindow *talkWindow, TalkWindowItem *talkWindowItem, const QString &uid);

    // 设置当前聊天窗口
    void setCurrentWidget(QWidget *widget);

    const QMap<QListWidgetItem *, QWidget *> &getTalkWindowItemMap() const;

private:
    void initControl();

    // 初始化TCP
    void initTcpSocket();

public slots:

    // 表情按钮被点击
    void onEmotionBtnClicked(bool);

    // 客户端发送Tcp数据
    void updateSendTcpMsg(QString &strData, int &msgType, const QString &fileName = "");

private slots:

    // 左侧列表点击后执行的槽函数
    void onTalkWindowItemClicked(QListWidgetItem *item);

    // 表情被选中
    void onEmotionItemClicked(int emotionNum);

    // 处理收到的数据
    // void onProcessTcpData();

private:
    Ui::TalkWindowShell *ui;

    // 打开的聊天窗口
    QMap<QListWidgetItem *, QWidget *> mTalkWindowItemMap;

    // 表情窗口
    EmotionWindow *mEmotionWindow{};

    // Tcp客户端
    QTcpSocket *mTcpClientSocket;
};

#endif // __TALK_WINDOW_SHELL_H
