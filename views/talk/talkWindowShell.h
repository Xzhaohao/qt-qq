#ifndef QQ_TALK_WINDOW_SHELL_H
#define QQ_TALK_WINDOW_SHELL_H

#include "ui_talkWindowShell.h"
#include "talkWindow.h"
#include "../base/baseWindow.h"

class TalkWindowShell : public BaseWindow {
Q_OBJECT

public:
    explicit TalkWindowShell(QWidget *parent = nullptr);

    ~TalkWindowShell() override;

public:
    // 添加聊天窗口
    // void addTalkWindow(TalkWindow *talkWindow, TalkWindowItem *talkWindowItem, GroupType groupType);

    // 设置当前聊天窗口
    void setCurrentWidget(QWidget *widget);

private:
    void initControl();

public slots:

    //void onEmotionBtnClicked(bool);         // 表情按钮被点击
    //void updateSendTcpMsg(QString &strData, int &msgType, QString fileName = "");

private slots:

    //void onTalkWindowItemClicked(QListWidgetItem *item);        // 左侧列表点击后执行的槽函数
    //void onEmotionItemClicked(int emotionNum);                  // 表情被选中
    //void onProcessTcpData();

private:
    Ui::TalkWindowShell *ui;

    QMap<QListWidgetItem *, QWidget *> m_talkWindowItemMap;
};

#endif //QQ_TALK_WINDOW_SHELL_H
