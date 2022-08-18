#include "talkWindowShell.h"

TalkWindowShell::TalkWindowShell(QWidget *parent) : BaseWindow(parent), ui(new Ui::TalkWindowShell) {
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    initControl();
}

TalkWindowShell::~TalkWindowShell() {
    delete ui;
}

void TalkWindowShell::initControl() {
    loadStyleSheet("talkWindow");
    setWindowTitle("聊天窗口");
}