#include "talkWindowShell.h"

TalkWindowShell::TalkWindowShell(QWidget *parent) : BaseWindow(parent), ui(new Ui::TalkWindowShell) {
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    loadStyleSheet("talkWindow");
    initControl();
    initTcpSocket();
}

TalkWindowShell::~TalkWindowShell() {
    delete ui;
    delete mEmotionWindow;
    mEmotionWindow = nullptr;
}

const QMap<QListWidgetItem *, QWidget *> &TalkWindowShell::getTalkWindowItemMap() const {
    return mTalkWindowItemMap;
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
void TalkWindowShell::addTalkWindow(TalkWindow *talkWindow, TalkWindowItem *talkWindowItem, const QString &uid) {
    ui->rightStackedWidget->addWidget(talkWindow);
    connect(mEmotionWindow, SIGNAL(signalEmotionHide()), talkWindow, SLOT(onSetEmotionBtnStatus()));

    auto *aItem = new QListWidgetItem(ui->listWidget);
    mTalkWindowItemMap.insert(aItem, talkWindow);
    aItem->setSelected(true);

    // 判断群聊还是单聊
    QSqlQueryModel sqlDepModel;
    QString strQuery = QString("select picture from tab_department where departmentID = %1").arg(uid);
    sqlDepModel.setQuery(strQuery);
    int rows = sqlDepModel.rowCount();
    if (rows == 0) { // 单聊
        strQuery = QString("SELECT picture FROM tab_employees WHERE employeeID = %1").arg(uid);
        sqlDepModel.setQuery(strQuery);
    }
    QModelIndex index = sqlDepModel.index(0, 0);
    QImage img;
    img.load(sqlDepModel.data(index).toString());

    talkWindowItem->setAvatarPixmap(QPixmap::fromImage(img));
    ui->listWidget->addItem(aItem);
    ui->listWidget->setItemWidget(aItem, talkWindowItem);

    onTalkWindowItemClicked(aItem);

    connect(talkWindowItem, &TalkWindowItem::signalCloseClocked, [talkWindowItem, talkWindow, aItem, this]() {
        mTalkWindowItemMap.remove(aItem);
        talkWindow->close();
        ui->listWidget->takeItem(ui->listWidget->row(aItem));
        delete talkWindowItem;
        ui->rightStackedWidget->removeWidget(talkWindow);

        // 如果聊天列表关闭完了，则关闭整个窗口
        if (ui->rightStackedWidget->count() < 1) {
            close();
        }
    });
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

void TalkWindowShell::initTcpSocket() {
    mTcpClientSocket = new QTcpSocket(this);
    mTcpClientSocket->connectToHost("127.0.0.1", TCP_PORT);
}

void TalkWindowShell::updateSendTcpMsg(QString &strData, int &msgType, const QString& fileName) {

}
