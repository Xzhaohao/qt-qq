#ifndef QQ_TCP_SOCKET_H
#define QQ_TCP_SOCKET_H

#include <QTcpSocket>

class TcpSocket : public QTcpSocket {
Q_OBJECT

public:
    TcpSocket();

    ~TcpSocket() override;

    void run();

signals:

    // 从客户端收到数据后发射信号处理数据
    void signalGetDataFromClient(QByteArray &, int);

    // 告诉Server有客户端断开连接
    void signalClientDisConnect(int);

private slots:

    // 处理 readyRead信号读取的数据
    void onReceiveData();

    // 处理客户端断开连接
    void onClientDisConnect();

private:
    // 描述符，用于唯一标识
    int mDescriptor{};
};

#endif // QQ_TCP_SOCKET_H
