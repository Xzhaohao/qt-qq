#include "TcpServer.h"

TcpServer::TcpServer(int port) {

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
