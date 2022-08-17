#ifndef COMMON_UTILS_H
#define COMMON_UTILS_H

#include <QPixmap>
#include <QSize>
#include <QPainter>
#include <QFile>
#include <qwidget.h>
#include <qapplication.h>
#include <qsettings.h>

class CommonUtils {
public:
    CommonUtils();

public:
    static QPixmap getRoundImage(const QPixmap &src, QPixmap &mask, QSize maskSize = QSize(0, 0));

    static void loadStyleSheet(QWidget *widget, const QString &sheetName);

    static void setDefaultSkinColor(const QColor &color);

    static QColor getDefaultSkinColor();
};

#endif // COMMON_UTILS_H
