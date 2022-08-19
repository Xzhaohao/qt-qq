#include "QMsgTextEdit.h"

QMsgTextEdit::QMsgTextEdit(QWidget *parent) : QTextEdit(parent) {
}

QMsgTextEdit::~QMsgTextEdit() {
    deleteAllEmotionImage();
}

void QMsgTextEdit::onEmotionImageFrameChange(int) {
    auto *movie = qobject_cast<QMovie *>(sender());
    document()->addResource(QTextDocument::ImageResource, QUrl(mEmotionMap.value(movie)), movie->currentPixmap());
}

void QMsgTextEdit::addEmotionUrl(int emotionNum) {
    const QString &imageName = QString("qrc:/assets/emotion/%1.png").arg(emotionNum);
    const QString &flagName = QString("%1").arg(imageName);
    insertHtml(QString("<img src='%1'/>").arg(flagName));
    if (mListEmotionUrl.contains(imageName)) {
        return;
    } else {
        mListEmotionUrl.append(imageName);
    }
    auto *apngMovie = new QMovie(imageName, "apng", this);
    mEmotionMap.insert(apngMovie, flagName);

    connect(apngMovie, SIGNAL(frameChange(int)), this, SLOT(onEmotionImageFrameChange(int)));
    apngMovie->start();
    updateGeometry();
}

void QMsgTextEdit::deleteAllEmotionImage() {
    for (auto itor = mEmotionMap.constBegin(); itor != mEmotionMap.constEnd(); itor++) {
        delete itor.key();
    }
    mEmotionMap.clear();
}