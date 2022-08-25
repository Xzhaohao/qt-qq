#ifndef QQ_SERVER_H
#define QQ_SERVER_H

#include <QDialog>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QTimer>
#include "ui_Server.h"
#include "TcpServer.h"

class Server : public QDialog {
Q_OBJECT

public:
    explicit Server(QWidget *parent = nullptr);

    ~Server() override;

private:
    void initTopSocket();

    bool connectMySql();

    // 获取公司群QQ号
    int getComDepId();

    void setDepNameMap();

    void setStatusMap();

    void setOnlineMap();

    void updateData(int depID = 0, int empID = 0);

private slots:

    void onUDPBroadMsg(QByteArray &btData);

    void onRefresh();

private:
    Ui::ServerClass *ui;

    // 员工信息模型
    QSqlQueryModel mQueryInfoModel;
    // 定时刷新数据
    QTimer *m_timer;
    // 公司群QQ号
    int mComDepId;
    // 部门QQ号
    int mDepID;
    // 员工QQ号
    int mEmployeeID;
    // 头像路径
    QString mPixPath;
    // 状态
    QMap<QString, QString> mStatusMap;
    // 部门名称
    QMap<QString, QString> mDepNameMap;
    // 在线状态
    QMap<QString, QString> mOnlineMap;

    TcpServer *mTcpServer{};
};

#endif // QQ_SERVER_H
