#ifndef __TALK_WINDOW_H
#define __TALK_WINDOW_H

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QToolTip>
#include "ui_talkWindow.h"
#include "../../components/contactItem/contactItem.h"
#include "../main/rootContactItem.h"

class TalkWindow : public QWidget {
Q_OBJECT

public:
    explicit TalkWindow(QWidget *parent, const QString &uid);

    ~TalkWindow() override;

public:
    void addEmotionImage(int emotionNum);

    void setWindowName(const QString &name);

    QString getTalkId();

private:
    void initControl();

    void initGroupTalkStatus();

    int getCompDepID();

    // 初始化单聊
    void initTalkWindow();

    // 初始化单聊
    void initPtoPTalk();

    void addPeoInfo(QTreeWidgetItem *pRootGroupItem, int employeeID);

private slots:

    void onSendBtnClicked(bool);

    void onItemDoubleClicked(QTreeWidgetItem *, int);

    // void onSetEmotionBtnStatus();

    // void onFileOpenBtnClicked(bool);

private:
    Ui::TalkWindow *ui;

    QString mTalkId;
    // 是否为群聊
    bool mIsGroupTalk;
    QMap<QTreeWidgetItem *, QString> mGroupPeopleMap;

    friend class TalkWindowShell;
};

#endif // __TALK_WINDOW_H
