#ifndef __TALK_WINDOW_ITEM_H
#define __TALK_WINDOW_ITEM_H

#include <QWidget>
#include "ui_talkWindowItem.h"
#include "../../utils/commonUtils.h"

class TalkWindowItem : public QWidget {
Q_OBJECT

public:
    explicit TalkWindowItem(QWidget *parent = nullptr);

    ~TalkWindowItem() override;

public:
    void setAvatarPixmap(const QPixmap &pixmap);

    void setMsgLabelContent(const QString &msg);

    QString getMsgLabelText();

private:
    void enterEvent(QEvent *event) override;

    void leaveEvent(QEvent *event) override;

    void resizeEvent(QResizeEvent *event) override;

private:
    void initControl();

signals:

    void signalCloseClocked();

private:
    Ui::TalkWindowItem *ui;
};

#endif // __TALK_WINDOW_ITEM_H
