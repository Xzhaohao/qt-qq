#include "commonUtils.h"

CommonUtils::CommonUtils() = default;

QPixmap CommonUtils::getRoundImage(const QPixmap &src, QPixmap &mask, QSize maskSize) {
    if (maskSize == QSize(0, 0)) {
        maskSize = mask.size();
    } else {
        mask = mask.scaled(maskSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }
    QImage resultImage(maskSize, QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&resultImage);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(resultImage.rect(), Qt::transparent);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawPixmap(0, 0, mask);
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.drawPixmap(0, 0, src.scaled(maskSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    painter.end();

    return QPixmap::fromImage(resultImage);
}

void CommonUtils::loadStyleSheet(QWidget *widget, const QString &sheetName) {
    QFile file(":/styles/" + sheetName + ".qss");
    file.open(QFile::ReadOnly);
    if (file.isOpen()) {
        widget->setStyleSheet("");
        QString qsStyleSheet = QLatin1String(file.readAll());
        widget->setStyleSheet(qsStyleSheet);
    }
    file.close();
}

void CommonUtils::setDefaultSkinColor(const QColor &color) {
    const QString &&path = QApplication::applicationDirPath() + "/" + QString("tradePrintInfo.ini");
    QSettings settings(path, QSettings::IniFormat);
    settings.setValue("DefaultSkin/red", color.red());
    settings.setValue("DefaultSkin/green", color.green());
    settings.setValue("DefaultSkin/blue", color.blue());
}

QColor CommonUtils::getDefaultSkinColor() {
    QColor color;
    const QString &&path = QApplication::applicationDirPath() + "/" + QString("tradePrintInfo.ini");
    if (!QFile::exists(path)) {
        setDefaultSkinColor(QColor(22, 154, 218));
    }
    QSettings settings(path, QSettings::IniFormat);
    color.setRed(settings.value("DefaultSkin/red").toInt());
    color.setGreen(settings.value("DefaultSkin/green").toInt());
    color.setBlue(settings.value("DefaultSkin/blue").toInt());

    return color;
}
