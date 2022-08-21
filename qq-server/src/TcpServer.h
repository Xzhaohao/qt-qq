#ifndef QQ_TCP_SERVER_H
#define QQ_TCP_SERVER_H

#include <QTcpServer>
#include <QDebug>

class TcpServer : public QTcpServer {
Q_OBJECT

public:
    explicit TcpServer(int port);

    ~TcpServer() override;

public:
    bool run();

private:
    // 端口号
    int mPort{};
};


#endif // QQ_TCP_SERVER_H
