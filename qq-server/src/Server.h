#ifndef QQ_SERVER_H
#define QQ_SERVER_H

#include <QDialog>
#include "ui_Server.h"
#include "TcpServer.h"

class Server : public QDialog {
Q_OBJECT

public:
    explicit Server(QWidget *parent = nullptr);

    ~Server() override;

private:
    void initTopSocket();

private slots:

    void onUDPBroadMsg(QByteArray &btData);

private:
    Ui::ServerClass *ui;

    TcpServer *mTcpServer{};
};

#endif // QQ_SERVER_H
