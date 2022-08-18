#ifndef __CLICK_LABEL_H
#define __CLICK_LABEL_H

#include <QLabel>
#include <QMouseEvent>

class ClickLabel : public QLabel {
Q_OBJECT

public:
    explicit ClickLabel(QWidget *parent = nullptr);

    ~ClickLabel() override;

protected:
    void mousePressEvent(QMouseEvent *event) override;

signals:

    void clicked();
};


#endif // __CLICK_LABEL_H
