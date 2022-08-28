#include "baseWindow.h"

extern QString gLoginEmployeeID;

BaseWindow::BaseWindow(QWidget *parent) : QDialog(parent) {
    mColorBackground = CommonUtils::getDefaultSkinColor();
    // 无边框窗口
    setWindowFlags(Qt::FramelessWindowHint);
    // 透明效果
    setAttribute(Qt::WA_TranslucentBackground, true);
    connect(NotifyManger::getInstance(), SIGNAL(signalSkinChanged(const QColor&)),
            this, SLOT(onSignalSkinChanged(const QColor&)));
}

BaseWindow::~BaseWindow() = default;

// 皮肤被修改
void BaseWindow::onSignalSkinChanged(const QColor &color) {
    mColorBackground = color;
    loadStyleSheet(mStyleName);
}

void BaseWindow::setTitleBarTitle(const QString &title, const QString &icon) {
    titleBar->setTitleIcon(icon);
    titleBar->setTitle(title);
}

void BaseWindow::initTitleBar(ButtonType buttonType) {
    titleBar = new TitleBar(this);
    titleBar->setButtonType(buttonType);
    titleBar->move(0, 0);

    connect(titleBar, SIGNAL(signalButtonMinClicked()), this, SLOT(onButtonMinClicked()));
    connect(titleBar, SIGNAL(signalButtonRestoreClicked()), this, SLOT(onButtonRestoreClicked()));
    connect(titleBar, SIGNAL(signalButtonMaxClicked()), this, SLOT(onButtonMaxClicked()));
    connect(titleBar, SIGNAL(signalButtonCloseClicked()), this, SLOT(onButtonCloseClicked()));
}

void BaseWindow::loadStyleSheet(const QString &styleName) {
    mStyleName = styleName;
    QFile file(":/styles/" + styleName + ".qss");
    file.open(QFile::ReadOnly);
    if (file.isOpen()) {
        setStyleSheet("");

        // 获取用户当前的皮肤RGB值
        QString r = QString::number(mColorBackground.red());
        QString g = QString::number(mColorBackground.green());
        QString b = QString::number(mColorBackground.blue());

        QString qsStyleSheet = QString("QWidget[titleSkin=true] {"
                                       "background-color: rgb(%1, %2, %3);"
                                       "border-top-left-radius: 4px;}"
                                       "QWidget[bottomSkin=true] {"
                                       "border-top: 1px solid rgba(%1, %2, %3, 100);"
                                       "background-color: rgba(%1, %2, %3, 50);"
                                       "border-bottom-left-radius: 4px;"
                                       "border-bottom-right-radius: 4px;}").arg(r).arg(g).arg(b);

        qsStyleSheet += QLatin1String(file.readAll());

        setStyleSheet(qsStyleSheet);
    }

    file.close();
}

// 子类化部件时，需要重写绘图事件设置背景图
void BaseWindow::paintEvent(QPaintEvent *event) {
    // Q_UNUSED(event);
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QDialog::paintEvent(event);
}

QPixmap BaseWindow::getRoundImage(const QPixmap &src, QPixmap &mask, QSize maskSize) {
    if (maskSize == QSize(0, 0)) {
        maskSize = mask.size();
    } else {
        // 缩放给定头像
        mask = mask.scaled(maskSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }

    // 保存转换后的图像
    QImage resultImage(maskSize, QImage::Format_A2BGR30_Premultiplied);
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

void BaseWindow::onShowClose(bool) {
    close();
}

void BaseWindow::onShowMin(bool) {
    showMinimized();
}

void BaseWindow::onShowHide(bool) {
    hide();
}

void BaseWindow::onShowNormal(bool) {
    show();
    activateWindow();
}

void BaseWindow::onShowQuit(bool) {
    // 更改数据库登录状态为离线
    QString strSqlStatus = QString("UPDATE tab_employees SET `online` =1 WHERE employeeID=%1").arg(gLoginEmployeeID);
    QSqlQuery sqlStatus(strSqlStatus);
    sqlStatus.exec();

    QApplication::quit();
}

void BaseWindow::mouseMoveEvent(QMouseEvent *event) {
    if (mMousePressed && (event->buttons() && Qt::LeftButton)) {
        move(event->globalPos() - mMousePoint);
        event->accept();
    }
}

void BaseWindow::mousePressEvent(QMouseEvent *event) {
    if (event->buttons() == Qt::LeftButton) {
        mMousePressed = true;
        mMousePoint = event->globalPos() - pos();
        event->accept();
    }
}

void BaseWindow::mouseReleaseEvent(QMouseEvent *) {
    mMousePressed = false;
}

void BaseWindow::onButtonMinClicked() {
    if (Qt::Tool == (windowFlags() & Qt::Tool)) {
        hide();
    } else {
        showMinimized();
    }
}

void BaseWindow::onButtonRestoreClicked() {
    QPoint windowPos;
    QSize windowSize;
    titleBar->getRestoreInfo(windowPos, windowSize);
    setGeometry(QRect(windowPos, windowSize));
}

void BaseWindow::onButtonMaxClicked() {
    titleBar->saveRestoreInfo(pos(), QSize(width(), height()));
    QRect desktopRect = QApplication::desktop()->availableGeometry();
    QRect factRect = QRect(desktopRect.x() - 3, desktopRect.y() - 3, desktopRect.width() + 6, desktopRect.height() + 6);
    setGeometry(factRect);
}

void BaseWindow::onButtonCloseClicked() {
    close();
}
