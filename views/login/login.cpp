#include "login.h"

// 登录用户的ID
QString gLoginEmployeeID;

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

    if (!connectMySql()) {
        QMessageBox::information(nullptr, "提示", "数据库连接失败！");
        close();
        exit(0);
    }
}

void Login::onLoginBtnClicked() {
    if (!verifyAccount()) {
        QMessageBox::warning(nullptr, "提示", "账号或密码错误，请重新输入！");
        ui->editPassword->setText("");
        return;
    }
    close();
    auto *mainWindow = new MainWindow;
    mainWindow->show();
}

bool Login::connectMySql() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("qt-qq");
    db.setUserName("root");
    db.setPassword("123456");

    return db.open();
}

bool Login::verifyAccount() {
    QString accountText = ui->editUserAccount->text();
    QString passwordText = ui->editPassword->text();

    QString sql = QString("select code from tab_accounts where employeeID = %1").arg(accountText);
    QSqlQuery query(sql);
    query.exec();

    if (query.first()) {
        QString dbPassword = query.value(0).toString();
        if (passwordText == dbPassword) {
            gLoginEmployeeID = accountText;
            return true;
        } else {
            return false;
        }
    }
    return false;
};
