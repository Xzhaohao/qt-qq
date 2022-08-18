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