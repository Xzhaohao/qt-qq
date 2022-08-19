#ifndef __Q_MSG_TEXT_EDIT_H
#define __Q_MSG_TEXT_EDIT_H

#include <QTextEdit>
#include <QMovie>

class QMsgTextEdit : public QTextEdit {
Q_OBJECT

public:
    explicit QMsgTextEdit(QWidget *parent = nullptr);

    ~QMsgTextEdit() override;

private slots:

    // 动画改变时响应的槽函数
    void onEmotionImageFrameChange(int frame);

public:
    void addEmotionUrl(int emotionNum);

    void deleteAllEmotionImage();

private:
    QList<QString> mListEmotionUrl;
    QMap<QMovie *, QString> mEmotionMap;
};

#endif // __Q_MSG_TEXT_EDIT_H
