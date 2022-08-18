#ifndef __ROOT_CONTACT_ITEM_H
#define __ROOT_CONTACT_ITEM_H

#include <QLabel>
#include <QPropertyAnimation>
#include <QPainter>

class RootContactItem : public QLabel {
Q_OBJECT

    // 箭头角度
    Q_PROPERTY(int rotation READ rotation WRITE setRotation)

public:
    explicit RootContactItem(bool hasArrow = true, QWidget *parent = nullptr);

    ~RootContactItem() override;

public:
    void setText(const QString &title);

    void setExpanded(bool expand);

private:
    int rotation();

    void setRotation(int rotation);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPropertyAnimation *mAnimation;
    QString mTitleText;     // 显示的文本
    int mRotation;          // 箭头角度
    bool mHasArrow;         // 是否有箭头
};

#endif // __ROOT_CONTACT_ITEM_H
