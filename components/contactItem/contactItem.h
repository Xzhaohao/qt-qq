#ifndef __CONTACT_ITEM_H
#define __CONTACT_ITEM_H

#include <QWidget>
#include "ui_contactItem.h"

class ContactItem : public QWidget {
Q_OBJECT

public:
    explicit ContactItem(QWidget *parent = nullptr);

    ~ContactItem() override;

public:
    void setUserName(const QString &username);

    void setSignName(const QString &signName);

    void setAvatarPixmap(const QPixmap &avatarPix);

    QString getUserName() const;

    QSize getAvatarSize() const;

private:
    Ui::ContactItem *ui;

};

#endif // __CONTACT_ITEM_H
