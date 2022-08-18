#include "mainWindow.h"

MainWindow::MainWindow(QWidget *parent) : BaseWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlags(windowFlags() | Qt::Tool);
    loadStyleSheet("mainWindow");
    initControl();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::initControl() {
    // 树获取焦点时不绘制边框
    ui->treeWidget->setStyle(new MainProxyStyle);
    setLevelPixmap(26);
    setAvatarPixmap(":/assets/avatar.bmp");
    setStatusMenuIcon(":/assets/StatusSucceeded.png");

    auto *appUpLayout = new QHBoxLayout;
    appUpLayout->setContentsMargins(0, 0, 0, 0);
    appUpLayout->addWidget(addOtherAppExtension(":/assets/app/app_7.png", "app_7"));
    appUpLayout->addWidget(addOtherAppExtension(":/assets/app/app_2.png", "app_2"));
    appUpLayout->addWidget(addOtherAppExtension(":/assets/app/app_3.png", "app_3"));
    appUpLayout->addWidget(addOtherAppExtension(":/assets/app/app_4.png", "app_4"));
    appUpLayout->addWidget(addOtherAppExtension(":/assets/app/app_5.png", "app_5"));
    appUpLayout->addWidget(addOtherAppExtension(":/assets/app/app_6.png", "app_6"));
    appUpLayout->addWidget(addOtherAppExtension(":/assets/app/skin.png", "app_skin"));
    appUpLayout->addStretch();
    appUpLayout->setSpacing(2);
    ui->appWidget->setLayout(appUpLayout);

    ui->bottomLayout_up->addWidget(addOtherAppExtension(":/assets/app/app_10.png", "app_10"));
    ui->bottomLayout_up->addWidget(addOtherAppExtension(":/assets/app/app_8.png", "app_8"));
    ui->bottomLayout_up->addWidget(addOtherAppExtension(":/assets/app/app_11.png", "app_11"));
    ui->bottomLayout_up->addWidget(addOtherAppExtension(":/assets/app/app_9.png", "app_9"));
    ui->bottomLayout_up->addStretch();
}

void MainWindow::setUsername(const QString &username) {

}

void MainWindow::setLevelPixmap(int level) {
    QPixmap pix(ui->levelBtn->size());
    pix.fill(Qt::transparent);

    QPainter painter(&pix);
    painter.drawPixmap(0, 4, QPixmap(":/assets/lv.png"));

    int unitNum = level % 10;   // 个位数
    int tenNum = level / 10;    // 十位数

    // 绘制图片的部分内容，十位数的等级
    painter.drawPixmap(10, 4, QPixmap(":/assets/levelvalue.png"), tenNum * 6, 0, 6, 7);
    // 个位数等级
    painter.drawPixmap(16, 4, QPixmap(":/assets/levelvalue.png"), unitNum * 6, 0, 6, 7);

    ui->levelBtn->setIcon(pix);
    ui->levelBtn->setIconSize(ui->levelBtn->size());
}

void MainWindow::setAvatarPixmap(const QString &avatar) {
    QPixmap pix;
    pix.load(":/assets/head_mask.png");
    ui->headLabel->setPixmap(getRoundImage(QPixmap(avatar), pix, ui->headLabel->size()));
}

void MainWindow::setStatusMenuIcon(const QString &statusPath) {
    QPixmap statusBtnPixmap(ui->statusBtn->size());
    statusBtnPixmap.fill(Qt::transparent);

    QPainter painter(&statusBtnPixmap);
    painter.drawPixmap(4, 4, QPixmap(statusPath));

    ui->statusBtn->setIcon(statusBtnPixmap);
    ui->statusBtn->setIconSize(ui->statusBtn->size());
}

QWidget *MainWindow::addOtherAppExtension(const QString &appPath, const QString &appName) {
    auto *btn = new QPushButton(this);
    btn->setFixedSize(20, 20);

    QPixmap pixmap(btn->size());
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    QPixmap appPixmap(appPath);

    painter.drawPixmap((btn->width() - appPixmap.width()) / 2, (btn->height() - appPixmap.height()) / 2, appPixmap);
    btn->setIcon(pixmap);
    btn->setIconSize(btn->size());
    btn->setObjectName(appName);
    btn->setProperty("hasBorder", true);

    connect(btn, &QPushButton::clicked, this, &MainWindow::onAppIconClicked);
    return btn;
}

void MainWindow::onAppIconClicked() {
    // 判断信号发送者的对象名是否是 皮肤修改图标
    if (sender()->objectName() == "app_skin") {
        Skin *skin = new Skin;
        skin->show();
    }
}
