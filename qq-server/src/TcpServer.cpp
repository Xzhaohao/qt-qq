#include "TcpServer.h"

TcpServer::TcpServer(int port) : mPort(port) {

}

TcpServer::~TcpServer() = default;

bool TcpServer::run() {
    if (this->listen(QHostAddress::AnyIPv4, mPort)) {
        qDebug() << QString("服务端监听 %1 端口成功！").arg(mPort);
        return true;
    } else {
        qDebug() << QString("服务端监听 %1 端口失败！").arg(mPort);
        return false;
    }
}

void TcpServer::incomingConnection(qintptr socketDescriptor) {
    qDebug() << "新的连接：" << socketDescriptor << endl;

    auto *tcpSocket = new TcpSocket();
    tcpSocket->setSocketDescriptor(socketDescriptor);
    tcpSocket->run();

    // 收到客户端数据的处理
    connect(tcpSocket, SIGNAL(signalGetDataFromClient(QByteArray & , int)),
            this, SLOT(socketDataProcessing(QByteArray & , int)));
    // 收到客户端断开连接的处理
    connect(tcpSocket, SIGNAL(signalClientDisConnect(int)),
            this, SLOT(socketDisConnected(int)));

    // 将socket添加到链表中
    mTcpSocketConnectList.append(tcpSocket);
}

void TcpServer::socketDataProcessing(QByteArray &sendData, int descriptor) {
    for (int i = 0; i < mTcpSocketConnectList.count(); ++i) {
        QTcpSocket *item = mTcpSocketConnectList.at(i);
        if (item->socketDescriptor() == descriptor) {
            qDebug() << "来自IP：" << item->peerAddress().toString() << "发来的数据：" << QString(sendData);
            emit signalTcpMsgComes(sendData);
        }
    }
}

// 断开连接
void TcpServer::socketDisConnected(int descriptor) {
    for (int i = 0; i < mTcpSocketConnectList.count(); ++i) {
        QTcpSocket *item = mTcpSocketConnectList.at(i);
        int itemDescriptor = item->socketDescriptor();

        // 查找断开连接的socket
        if (itemDescriptor == descriptor || itemDescriptor == -1) {
            // 将断开连接的socket从链表中移除
            mTcpSocketConnectList.removeAt(i);
            // 回收资源
            item->deleteLater();
            qDebug() << "TcpSocket断开连接：" << descriptor << endl;
        }
    }
}
