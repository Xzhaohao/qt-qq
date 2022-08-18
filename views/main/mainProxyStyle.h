#ifndef __MAIN_PROXY_STYLE_H
#define __MAIN_PROXY_STYLE_H

#include <QProxyStyle>

class MainProxyStyle : public QProxyStyle {

public:
    virtual void drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter,
                               const QWidget *widget = nullptr) const {
        if (element == PE_FrameFocusRect) {
            return;
        } else {
            QProxyStyle::drawPrimitive(element, option, painter, widget);
        }
    }

};

#endif // __MAIN_PROXY_STYLE_H
