#include "Server.h"

const int tcpPort = 8888;

Server::Server(QWidget *parent) : QDialog(parent), ui(new Ui::ServerClass) {
    ui->setupUi(this);

    initTopSocket();
}

Server::~Server() {
    delete ui;
}

void Server::initTopSocket() {
    mTcpServer = new TcpServer(tcpPort);
    mTcpServer->run();

    // 收到TCP客户端发来的信息后进行UDP广播
    connect(mTcpServer, &TcpServer::signalTcpMsgComes, this, &Server::onUDPBroadMsg);
}

void Server::onUDPBroadMsg(QByteArray &btData) {

}
