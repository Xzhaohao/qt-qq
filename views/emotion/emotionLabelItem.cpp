#include "emotionLabelItem.h"

EmotionLabelItem::EmotionLabelItem(QWidget *parent) : ClickLabel(parent) {
    initControl();

    connect(this, &ClickLabel::clicked, [this] {
        emit emotionClicked(mEmotionName);
    });
}

void EmotionLabelItem::initControl() {
    setAlignment(Qt::AlignCenter);
    setObjectName("emotionLabelItem");
    setFixedSize(32, 32);
}

void EmotionLabelItem::setEmotionName(int emotionName) {
    mEmotionName = emotionName;
    // 设置动图
    QString imageName = QString(":/assets/emotion/%1.png").arg(emotionName);
    mApngMovie = new QMovie(imageName, "apng", this);
    mApngMovie->start();
    mApngMovie->stop();
    setMovie(mApngMovie);
}

EmotionLabelItem::~EmotionLabelItem() = default;
