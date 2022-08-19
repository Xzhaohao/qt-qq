#ifndef __WINDOW_MANGER_H
#define __WINDOW_MANGER_H

#include <QObject>
#include "../views/talk/talkWindowShell.h"

class WindowManger : public QObject {
Q_OBJECT

public:
    explicit WindowManger();

    ~WindowManger() override;

public:
    QWidget *findWindowName(const QString &qsWindowName);

    void deleteWindowName(const QString &qsWindowName);

    void addWindowName(const QString &qsWindowName, QWidget *qWidget);

    static WindowManger *getInstance();

    TalkWindowShell *getTalkWindowShell();

    QString getCreatingTalkId();

    void addNewTalkWindow(const QString &uid);

private:
    TalkWindowShell *mTalkWindowShell;
    QMap<QString, QWidget *> mWindowMap;
    QString mStrCreatingTalkId = "";
};

#endif // __WINDOW_MANGER_H
