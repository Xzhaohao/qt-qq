#include "rootContactItem.h"

RootContactItem::RootContactItem(bool hasArrow, QWidget *parent) : QLabel(parent), mRotation(0), mHasArrow(hasArrow) {
    // 设置固定高度
    setFixedHeight(32);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    mAnimation = new QPropertyAnimation(this, "rotation");
    mAnimation->setDuration(100);
    mAnimation->setEasingCurve(QEasingCurve::InQuad);
}

void RootContactItem::setText(const QString &title) {
    mTitleText = title;
    update();
}

void RootContactItem::setExpanded(bool expand) {
    if (expand) {
        mAnimation->setEndValue(90);
    } else {
        mAnimation->setEndValue(0);
    }
    mAnimation->start();
}

int RootContactItem::rotation() {
    return mRotation;
}

void RootContactItem::setRotation(int rotation) {
    mRotation = rotation;
    update();
}

void RootContactItem::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    // 文本反锯齿
    painter.setRenderHint(QPainter::TextAntialiasing, true);

    QFont font;
    font.setPointSize(10);
    painter.setFont(font);
    painter.drawText(24, 0, width() - 24, height(), Qt::AlignLeft | Qt::AlignVCenter, mTitleText);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.save();

    if (mHasArrow) {
        QPixmap pix;
        pix.load(":/assets/arrow.png");

        QPixmap tmpPix(pix.size());
        tmpPix.fill(Qt::transparent);

        QPainter p(&tmpPix);
        p.setRenderHint(QPainter::SmoothPixmapTransform, true);

        // 坐标系偏移，绘制箭头
        p.translate((qreal) pix.width() / 2, (qreal) pix.height() / 2);
        p.rotate(mRotation);
        p.drawPixmap(0 - pix.width() / 2, 0 - pix.height() / 2, pix);

        painter.drawPixmap(6, (height() - pix.height()) / 2, tmpPix);
        // 回复画家设置
        painter.restore();
    }

    QLabel::paintEvent(event);
}

RootContactItem::~RootContactItem() = default;
