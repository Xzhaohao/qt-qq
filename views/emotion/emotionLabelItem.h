#ifndef __EMOTION_LABEL_ITEM_H
#define __EMOTION_LABEL_ITEM_H

#include <QMovie>
#include "../../components/clickLabel/clickLabel.h"

class EmotionLabelItem : public ClickLabel {
Q_OBJECT

public:
    explicit EmotionLabelItem(QWidget *parent = nullptr);

    ~EmotionLabelItem() override;

    void setEmotionName(int emotionName);

private:
    void initControl();

signals:

    void emotionClicked(int emotionNum);

private:
    int mEmotionName{};
    QMovie *mApngMovie{};
};


#endif // __EMOTION_LABEL_ITEM_H
