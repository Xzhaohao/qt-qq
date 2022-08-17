#include "login.h"

Login::Login(QWidget *parent) : BaseWindow(parent), ui(new Ui::Login) {
    ui->setupUi(this);
    initTitleBar();
    setTitleBarTitle("", ":/assets/qqlogoclassic.png");
    loadStyleSheet("login");
}

Login::~Login() {
    delete ui;
};
