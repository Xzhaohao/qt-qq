#include "talkWindow.h"

TalkWindow::TalkWindow(QWidget *parent, const QString &uid) : QWidget(parent), ui(new Ui::TalkWindow), mTalkId(uid) {
    ui->setupUi(this);
    WindowManger::getInstance()->addWindowName(uid, this);
    setAttribute(Qt::WA_DeleteOnClose);
    initGroupTalkStatus();
    initControl();
}

TalkWindow::~TalkWindow() {
    delete ui;
    WindowManger::getInstance()->deleteWindowName(mTalkId);
}

void TalkWindow::addEmotionImage(int emotionNum) {

}

void TalkWindow::setWindowName(const QString &name) {

}

QString TalkWindow::getTalkId() {
    return QString();
}

void TalkWindow::initControl() {
    QList<int> rightWidgetSize;
    rightWidgetSize << 600 << 138;
    ui->bodySplitter->setSizes(rightWidgetSize);

    ui->textEdit->setFontPointSize(10);
    ui->textEdit->setFocus();

    connect(ui->sysMin, SIGNAL(clicked(bool)), parent(), SLOT(onShowMin(bool)));
    connect(ui->sysClose, SIGNAL(clicked(bool)), parent(), SLOT(onShowClose(bool)));
    connect(ui->closeBtn, SIGNAL(clicked(bool)), parent(), SLOT(onShowClose(bool)));
    connect(ui->faceBtn, SIGNAL(clicked(bool)), parent(), SLOT(onEmotionBtnClicked(bool)));
    connect(ui->sendBtn, SIGNAL(clicked(bool)), this, SLOT(onSendBtnClicded(bool)));
    connect(ui->treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem * , int)),
            this, SLOT(onItemDoubleClicked(QTreeWidgetItem * , int)));
    connect(ui->fileopenBtn, SIGNAL(clicked(bool)), this, SLOT(onFileOpenBtnClicked(bool)));

    if (mIsGroupTalk) {
        initTalkWindow();
    } else {
        initPtoPTalk();
    }
}

void TalkWindow::initGroupTalkStatus() {

}

int TalkWindow::getCompDepID() {
    return 0;
}
