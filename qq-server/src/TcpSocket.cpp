#include "TcpSocket.h"

TcpSocket::TcpSocket() = default;

TcpSocket::~TcpSocket() = default;

void TcpSocket::run() {
    // 设置描述符
    mDescriptor = this->socketDescriptor();

    connect(this, SIGNAL(readyRead()), this, SLOT(onReceiveData()));
    connect(this, SIGNAL(disconnected()), this, SLOT(onClientDisConnect()));
}

void TcpSocket::onReceiveData() {
    QByteArray buffer = this->readAll();
    if (!buffer.isEmpty()) {
        // QString strData = QString(buffer);
        // 发射信号（接收到了客户端数据）
        emit signalGetDataFromClient(buffer, mDescriptor);
    }
}

void TcpSocket::onClientDisConnect() {
    emit signalClientDisConnect(mDescriptor);
}
