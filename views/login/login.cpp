#include "login.h"

Login::Login(QWidget *parent) : BaseWindow(parent), ui(new Ui::Login) {
    ui->setupUi(this);
    // setAttribute(Qt::WA_DeleteOnClose);
    initTitleBar();
    setTitleBarTitle("", ":/assets/qqlogoclassic.png");
    loadStyleSheet("login");
    initControl();
}

Login::~Login() {
    delete ui;
}

void Login::initControl() {
    auto *headLabel = new QLabel(this);
    headLabel->setFixedSize(68, 68);

    QPixmap pix(":/assets/head_mask.png");
    headLabel->setPixmap(getRoundImage(QPixmap(":/assets/avatar.bmp"), pix, headLabel->size()));
    headLabel->move(width() / 2 - 34, ui->titleWidget->height() - 34);

    connect(ui->loginBtn, &QPushButton::clicked, this, &Login::onLoginBtnClicked);
}

void Login::onLoginBtnClicked() {
    close();
    auto *mainWindow = new MainWindow;
    mainWindow->show();
};
