#include "talkWindowItem.h"

TalkWindowItem::TalkWindowItem(QWidget *parent) : QWidget(parent), ui(new Ui::TalkWindowItem) {
    ui->setupUi(this);
    initControl();
}

TalkWindowItem::~TalkWindowItem() {
    delete ui;
}

void TalkWindowItem::initControl() {
    ui->tCloseBtn->setVisible(false);
    connect(ui->tCloseBtn, SIGNAL(clicked(bool)), this, SIGNAL(signalCloseClocked()));
}

void TalkWindowItem::setAvatarPixmap(const QPixmap &avatar) {
    QPixmap mask = QPixmap(":/assets/head_mask.png");
    const QPixmap &avatarPix = CommonUtils::getRoundImage(avatar, mask, ui->avatarLabel->size());
    ui->avatarLabel->setPixmap(avatarPix);
}

void TalkWindowItem::setMsgLabelContent(const QString &msg) {
    ui->msgLabel->setText(msg);
}

QString TalkWindowItem::getMsgLabelText() {
    return ui->msgLabel->text();
}

void TalkWindowItem::enterEvent(QEvent *event) {
    ui->tCloseBtn->setVisible(true);
    QWidget::enterEvent(event);
}

void TalkWindowItem::leaveEvent(QEvent *event) {
    ui->tCloseBtn->setVisible(false);
    QWidget::leaveEvent(event);
}

void TalkWindowItem::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
}
