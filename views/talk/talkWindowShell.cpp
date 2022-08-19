#include "talkWindowShell.h"

TalkWindowShell::TalkWindowShell(QWidget *parent) : BaseWindow(parent), ui(new Ui::TalkWindowShell) {
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    loadStyleSheet("talkWindow");
    initControl();
}

TalkWindowShell::~TalkWindowShell() {
    delete ui;
    delete mEmotionWindow;
    mEmotionWindow = nullptr;
}

void TalkWindowShell::initControl() {
    setWindowTitle("聊天窗口");

    mEmotionWindow = new EmotionWindow;
    mEmotionWindow->hide();

    QList<int> leftWidgetSize;
    leftWidgetSize << 154 << width() - 154;
    ui->splitter->setSizes(leftWidgetSize);

    ui->listWidget->setStyle(new CustomProxyStyle(this));

    connect(ui->listWidget, &QListWidget::itemClicked, this, &TalkWindowShell::onTalkWindowItemClicked);
    connect(mEmotionWindow, SIGNAL(signalEmotionItemClicked(int)), this, SLOT(onEmotionItemClicked(int)));
}

// 设置当前聊天窗口
void TalkWindowShell::setCurrentWidget(QWidget *widget) {
    ui->rightStackedWidget->setCurrentWidget(widget);
}

// 添加聊天窗口
void TalkWindowShell::addTalkWindow(TalkWindow *talkWindow, TalkWindowItem *talkWindowItem, GroupType groupType) {
    ui->rightStackedWidget->addWidget(talkWindow);
    connect(mEmotionWindow, SIGNAL(signalEmotionHide()), talkWindow, SLOT(onSetEmotionBtnStatus()));

    auto *aItem = new QListWidgetItem(ui->listWidget);
    mTalkWindowItemMap.insert(aItem, talkWindow);
    aItem->setSelected(true);
}

// 表情按钮被点击
void TalkWindowShell::onEmotionBtnClicked(bool) {
    mEmotionWindow->setVisible(!mEmotionWindow->isVisible());
    // 将当前控件的相对位置转换为屏幕的绝对位置
    QPoint emotionPoint = this->mapToGlobal(QPoint(0, 0));
    emotionPoint.setX(emotionPoint.x() + 170);
    emotionPoint.setY(emotionPoint.y() + 220);
    mEmotionWindow->move(emotionPoint);
}

// 左侧列表点击后执行的槽函数
void TalkWindowShell::onTalkWindowItemClicked(QListWidgetItem *item) {
    QWidget *talkWindowWidget = mTalkWindowItemMap.find(item).value();
    ui->rightStackedWidget->setCurrentWidget(talkWindowWidget);
}

// 表情被选中
void TalkWindowShell::onEmotionItemClicked(int emotionNum) {
    auto *curTalkWindow = dynamic_cast<TalkWindow *>(ui->rightStackedWidget->currentWidget());
    if (curTalkWindow) {
        curTalkWindow->addEmotionImage(emotionNum);
    }
}
