#include "Server.h"

Server::Server(QWidget *parent) : QDialog(parent), ui(new Ui::ServerClass) {
    ui->setupUi(this);
}

Server::~Server() {
    delete ui;
}

void Server::initTopSocket() {

}
