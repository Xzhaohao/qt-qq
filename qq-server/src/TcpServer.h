#ifndef QQ_TCP_SERVER_H
#define QQ_TCP_SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include "TcpSocket.h"

class TcpServer : public QTcpServer {
Q_OBJECT

public:
    explicit TcpServer(int port);

    ~TcpServer() override;

public:
    // 监听
    bool run();

protected:
    // 当客户端有新的连接时触发
    void incomingConnection(qintptr socketDescriptor) override;

private slots:

    // 处理数据
    void socketDataProcessing(QByteArray &sendData, int descriptor);

    // 断开连接处理
    void socketDisConnected(int descriptor);

signals:

    void signalTcpMsgComes(QByteArray &);

private:
    // 端口号
    int mPort{};

    QList<QTcpSocket *> mTcpSocketConnectList;
};


#endif // QQ_TCP_SERVER_H
