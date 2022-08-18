#ifndef __EMOTION_WINDOW_H
#define __EMOTION_WINDOW_H

#include <QStyleOption>
#include "ui_emotionWindow.h"
#include "emotionLabelItem.h"
#include "../../utils/commonUtils.h"

class EmotionWindow : public QWidget {
Q_OBJECT

public:
    explicit EmotionWindow(QWidget *parent = nullptr);

    ~EmotionWindow() override;

private:
    void initControl();

private slots:

    void addEmotion(int emotionNum);

signals:

    void signalEmotionHide();

    void signalEmotionItemClicked(int emotionNum);

private:
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::EmotionWindow *ui;
};

#endif // __EMOTION_WINDOW_H
