#include "contactItem.h"

ContactItem::ContactItem(QWidget *parent) : QWidget(parent), ui(new Ui::ContactItem) {
    ui->setupUi(this);
}

ContactItem::~ContactItem() {
    delete ui;
}

void ContactItem::setUserName(const QString &username) {
    ui->userName->setText(username);
}

void ContactItem::setSignName(const QString &signName) {
    ui->signName->setText(signName);
}

void ContactItem::setAvatarPixmap(const QPixmap &avatarPix) {
    ui->avatarWrap->setPixmap(avatarPix);
}

QString ContactItem::getUserName() const {
    return ui->userName->text();
}

QSize ContactItem::getAvatarSize() const {
    return ui->avatarWrap->size();
}
