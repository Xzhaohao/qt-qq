#include "clickLabel.h"

ClickLabel::ClickLabel(QWidget *parent) : QLabel(parent) {

}

ClickLabel::~ClickLabel() = default;

void ClickLabel::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        emit clicked();
    }
    QLabel::mousePressEvent(event);
}
