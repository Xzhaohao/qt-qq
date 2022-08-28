#ifndef QQ_SERVER_H
#define QQ_SERVER_H

#include <QDialog>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QTimer>
#include <QFileDialog>
#include <QUdpSocket>
#include "ui_Server.h"
#include "TcpServer.h"

class Server : public QDialog {
Q_OBJECT

public:
    explicit Server(QWidget *parent = nullptr);

    ~Server() override;

private:
    // 初始化TCP
    void initTopSocket();

    // 初始化UDP
    void initUdpSocket();

    // 初始化组合框的数据
    void initComboBoxData();

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

    // 点击信号与槽函数自动连接，根据QQ号查询员工
    void on_queryDepartmentBtn_clicked();

    // 根据员工QQ号筛选
    void on_queryIDBtn_clicked();

    // 注销员工QQ号
    void on_logoutBtn_clicked();

    // 选择图片按钮（员工的寸照）
    void on_selectPictureBtn_clicked();

    // 新增员工
    void on_addBtn_clicked();

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

    // tcp服务端
    TcpServer *mTcpServer{};
    // udp广播
    QUdpSocket *mUdpSender{};
};

#endif // QQ_SERVER_H
