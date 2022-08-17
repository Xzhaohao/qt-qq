#ifndef CUSTOM_PROXY_STYLE_H
#define CUSTOM_PROXY_STYLE_H

#include <QProxyStyle>

// 改变系统默认的控件风格
class CustomProxyStyle : public QProxyStyle {
public:
    explicit CustomProxyStyle(QObject *parent) {
        setParent(parent);
    }

    virtual void drawPrimitive(PrimitiveElement element, const QStyleOption *option,
                               QPainter *painter, const QWidget *widget = nullptr) const override {
        if (PE_FrameFocusRect == element) {
            // 去掉Windows中控件默认的边框或虚线，控件获取焦点时直接放回，不进行绘制
            return;
        } else {
            QProxyStyle::drawPrimitive(element, option, painter, widget);
        }
    }

private:

};

#endif // CUSTOM_PROXY_STYLE_H
