#ifndef __TALK_WINDOW_SHELL_H
#define __TALK_WINDOW_SHELL_H

#include "ui_talkWindowShell.h"
#include "talkWindow.h"
#include "groupType.h"
#include "../base/baseWindow.h"
#include "../emotion/emotionWindow.h"
#include "../../utils/customProxyStyle.h"

class TalkWindowShell : public BaseWindow {
Q_OBJECT

public:
    explicit TalkWindowShell(QWidget *parent = nullptr);

    ~TalkWindowShell() override;

public:
    // 添加聊天窗口
    void addTalkWindow(TalkWindow *talkWindow, TalkWindowItem *talkWindowItem, GroupType groupType);

    // 设置当前聊天窗口
    void setCurrentWidget(QWidget *widget);

private:
    void initControl();

public slots:

    // 表情按钮被点击
    void onEmotionBtnClicked(bool);
    // void updateSendTcpMsg(QString &strData, int &msgType, QString fileName = "");

private slots:

    // 左侧列表点击后执行的槽函数
    void onTalkWindowItemClicked(QListWidgetItem *item);
    // 表情被选中
    void onEmotionItemClicked(int emotionNum);
    // void onProcessTcpData();

private:
    Ui::TalkWindowShell *ui;

    // 打开的聊天窗口
    QMap<QListWidgetItem *, QWidget *> mTalkWindowItemMap;

    // 表情窗口
    EmotionWindow *mEmotionWindow{};
};

#endif // __TALK_WINDOW_SHELL_H
