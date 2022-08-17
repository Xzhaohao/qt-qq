#include "titleBar.h"

#define BUTTON_HEIGHT 27    // 按钮高度 27px
#define BUTTON_WIDTH 27     // 按钮宽度
#define TITLE_HEIGHT 27     // 标题宽度

TitleBar::TitleBar(QWidget *parent) : QWidget(parent), mIsPressed(false), mButtonType(MIN_MAX_BUTTON) {
    initControl();
    initConnections();
    loadStyleSheet("title");
}

TitleBar::~TitleBar() = default;

// 初始化控件
void TitleBar::initControl() {
    mIcon = new QLabel(this);
    mTitle = new QLabel(this);

    mButtonMin = new QPushButton(this);
    mButtonRestore = new QPushButton(this);
    mButtonMax = new QPushButton(this);
    mButtonClose = new QPushButton(this);

    // 按钮固定大小
    mButtonMin->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));
    mButtonRestore->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));
    mButtonMax->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));
    mButtonClose->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));

    // 设置对象名
    mTitle->setObjectName("title");
    mButtonMin->setObjectName("buttonMin");
    mButtonRestore->setObjectName("buttonRestore");
    mButtonMax->setObjectName("buttonMax");
    mButtonClose->setObjectName("buttonClose");

    // 设置布局
    auto *mLayout = new QHBoxLayout(this);
    mLayout->addWidget(mIcon);
    mLayout->addWidget(mTitle);
    mLayout->addWidget(mButtonMin);
    mLayout->addWidget(mButtonRestore);
    mLayout->addWidget(mButtonMax);

    // 设置间隙
    mLayout->setContentsMargins(5, 0, 0, 0);
    mLayout->setSpacing(0);

    // 标题栏左右伸缩，垂直固定
    mTitle->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    // 标题栏高度永远保持 27
    setFixedHeight(TITLE_HEIGHT);
    // 无边框窗体风格
    setWindowFlags(Qt::FramelessWindowHint);
}

// 初始化信号与槽的连接
void TitleBar::initConnections() {
    connect(mButtonMin, SIGNAL(clicked()), this, SLOT(onButtonMinClicked()));
    connect(mButtonRestore, SIGNAL(clicked()), this, SLOT(onButtonRestoreClicked()));
    connect(mButtonMax, SIGNAL(clicked()), this, SLOT(onButtonMaxClicked()));
    connect(mButtonClose, SIGNAL(clicked()), this, SLOT(onButtonCloseClicked()));
}

// 设置标题栏图标
void TitleBar::setTitleIcon(const QString &filePath) {
    QPixmap titleIcon(filePath);
    mIcon->setFixedSize(titleIcon.size());
    mIcon->setPixmap(titleIcon);
}

// 设置标题栏内容
void TitleBar::setTitle(const QString &title) {
    mTitle->setText(title);
    mTitleContent = title;
}

// 设置标题栏宽度
void TitleBar::setTitleWidth(int width) {
    setFixedWidth(width);
}

// 设置标题栏中按钮的类型
void TitleBar::setButtonType(ButtonType buttonType) {
    mButtonType = buttonType;

    switch (buttonType) {
        case MIN_BUTTON: {
            mButtonRestore->setVisible(false);
            mButtonMax->setVisible(false);
            break;
        }
        case MIN_MAX_BUTTON:
            mButtonRestore->setVisible(false);
            break;
        case ONLY_CLOSE_BUTTON: {
            mButtonRestore->setVisible(false);
            mButtonMax->setVisible(false);
            mButtonMin->setVisible(false);
            break;
        }
        default:
            break;
    }
}

// 保存窗口最大化前的位置及大小
void TitleBar::saveRestoreInfo(const QPoint &point, const QSize &size) {
    mRestorePos = point;
    mRestoreSize = size;
}

// 获取窗口最大化前的位置及大小
void TitleBar::getRestoreInfo(QPoint &point, QSize &size) {
    point = mRestorePos;
    size = mRestoreSize;
}

// 绘制标题栏
void TitleBar::paintEvent(QPaintEvent *event) {
    // 设置背景色
    QPainter painter(this);
    QPainterPath pathBack;
    // 设置填充规则
    pathBack.setFillRule(Qt::WindingFill);
    // 添加圆角矩形到绘图路径
    pathBack.addRoundRect(QRect(0, 0, width(), height()), 3, 3);
    // 平滑转换
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

    // 当窗口最大化或还原后，窗口长度改变，标题栏相应作出改变
    if (width() != parentWidget()->width()) {
        setFixedWidth(parentWidget()->width());
    }

    QWidget::paintEvent(event);
}

// 鼠标双击事件，主要实现双击标题栏实现最大化、还原的操作
void TitleBar::mouseDoubleClickEvent(QMouseEvent *event) {
    // 只有存在最大化、最小化按钮才有效
    if (mButtonType == MIN_MAX_BUTTON) {
        if (mButtonMax->isVisible()) {
            onButtonMaxClicked();
        } else {
            onButtonRestoreClicked();
        }
    }

    return QWidget::mouseDoubleClickEvent(event);
}

// 通过鼠标按下、鼠标移动、鼠标释放事件实现拖动标题栏打到移动窗口效果
void TitleBar::mousePressEvent(QMouseEvent *event) {
    // todo 优化
    if (mButtonType == MIN_MAX_BUTTON && mButtonMax->isVisible()) {
        // 在窗口最大化时，禁止拖动
        mIsPressed = false;
        // globalPos()返回事件发生时鼠标坐标的全局位置
        mStartMovePos = event->globalPos();
    } else {
        mIsPressed = true;
        mStartMovePos = event->globalPos();
    }

    return QWidget::mousePressEvent(event);
}

// 鼠标移动事件
void TitleBar::mouseMoveEvent(QMouseEvent *event) {
    if (mIsPressed) {
        QPoint movePoint = event->globalPos() - mStartMovePos;
        QPoint widgetPos = parentWidget()->pos();
        mStartMovePos = event->globalPos();
        parentWidget()->move(widgetPos.x() + movePoint.x(), widgetPos.y() + movePoint.y());
    }

    return QWidget::mouseMoveEvent(event);
}

// 鼠标松开事件
void TitleBar::mouseReleaseEvent(QMouseEvent *event) {
    mIsPressed = false;
    return QWidget::mouseReleaseEvent(event);
}

// 加载样式表
void TitleBar::loadStyleSheet(const QString &styleName) {
    QFile file(":/styles/" + styleName + ".qss");
    file.open(QFile::ReadOnly);
    if (file.isOpen()) {
        QString styleSheet = this->styleSheet();
        styleSheet += QLatin1String(file.readAll());
        setStyleSheet(styleSheet);
    }
}

// 最小化
void TitleBar::onButtonMinClicked() {
    emit signalButtonMinClicked();
}

// 还原
void TitleBar::onButtonRestoreClicked() {
    mButtonRestore->setVisible(false);
    mButtonMax->setVisible(true);
    emit signalButtonRestoreClicked();
}

// 最大化
void TitleBar::onButtonMaxClicked() {
    mButtonRestore->setVisible(true);
    mButtonMax->setVisible(false);
    emit signalButtonMaxClicked();
}

// 关闭
void TitleBar::onButtonCloseClicked() {
    emit signalButtonCloseClicked();
}
