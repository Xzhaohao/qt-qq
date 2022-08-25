#include "Server.h"

const int tcpPort = 8888;

Server::Server(QWidget *parent) : QDialog(parent), ui(new Ui::ServerClass) {
    ui->setupUi(this);

    if (!connectMySql()) {
        QMessageBox::warning(nullptr, "提示", "数据库连接失败！");
        close();
    }

    setDepNameMap();
    setStatusMap();
    setOnlineMap();

    mQueryInfoModel.setQuery("select * from tab_employees");
    // 只读
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // 初始化查询公司群所有员工信息
    mEmployeeID = 0;
    mDepID = getComDepId();
    mComDepId = mDepID;

    updateData();

    //定时刷新数据
    m_timer = new QTimer(this);
    m_timer->setInterval(200);
    m_timer->start();
    connect(m_timer, &QTimer::timeout, this, &Server::onRefresh);

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

bool Server::connectMySql() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("qt-qq");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("123456");
    db.setPort(3306);
    return db.open();
}

void Server::updateData(int depID, int empID) {
    ui->tableWidget->clear();
    if (depID && depID != mComDepId) { // 查询部门
        mQueryInfoModel.setQuery(QString("SELECT * FROM tab_employees WHERE departmentID =%1").arg(depID));
    } else if (empID) { // 精确查找
        mQueryInfoModel.setQuery(QString("SELECT * FROM tab_employees WHERE employeeID =%1").arg(empID));
    } else { // 公司群
        mQueryInfoModel.setQuery("SELECT * FROM tab_employees");
    }

    // 总行数（总记录数）
    int rows = mQueryInfoModel.rowCount();
    // 总列数
    int columns = mQueryInfoModel.columnCount();

    // 模型索引
    QModelIndex index;

    // 设置表格的行数、列数
    ui->tableWidget->setRowCount(rows);
    ui->tableWidget->setColumnCount(columns);

    //设置表头
    QStringList headers;
    headers << QStringLiteral("部门")
            << QStringLiteral("工号")
            << QStringLiteral("员工姓名")
            << QStringLiteral("员工签名")
            << QStringLiteral("员工状态")
            << QStringLiteral("员工头像")
            << QStringLiteral("在线状态");
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    // 设置列等宽
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            // 行，列
            index = mQueryInfoModel.index(i, j);
            // 获取i行j列的值
            QString strData = mQueryInfoModel.data(index).toString();

            // 获取字段名称
            QSqlRecord record = mQueryInfoModel.record(i);
            QString strRecordName = record.fieldName(j);

            if (strRecordName == QLatin1String("departmentID")) {
                ui->tableWidget->setItem(i, j, new QTableWidgetItem(mDepNameMap.value(strData)));
                continue;
            } else if (strRecordName == QLatin1String("status")) {
                ui->tableWidget->setItem(i, j, new QTableWidgetItem(mStatusMap.value(strData)));
                continue;
            } else if (strRecordName == QLatin1String("online")) {
                ui->tableWidget->setItem(i, j, new QTableWidgetItem(mOnlineMap.value(strData)));
                continue;
            }

            ui->tableWidget->setItem(i, j, new QTableWidgetItem(strData));
        }
    }
}

int Server::getComDepId() {
    QSqlQuery queryCompDepID(QString("SELECT departmentID FROM tab_department WHERE department_name = '%1'")
                                     .arg("公司群"));
    queryCompDepID.exec();
    queryCompDepID.next();

    int comDepID = queryCompDepID.value(0).toInt();
    return comDepID;
}

void Server::setDepNameMap() {
    mDepNameMap.insert(QStringLiteral("2001"), QStringLiteral("人事部"));
    mDepNameMap.insert(QStringLiteral("2002"), QStringLiteral("研发部"));
    mDepNameMap.insert(QStringLiteral("2003"), QStringLiteral("市场部"));
}

void Server::setStatusMap() {
    mStatusMap.insert(QStringLiteral("1"), QStringLiteral("有效"));
    mStatusMap.insert(QStringLiteral("0"), QStringLiteral("已注销"));
}

void Server::setOnlineMap() {
    mOnlineMap.insert(QStringLiteral("1"), QStringLiteral("离线"));
    mOnlineMap.insert(QStringLiteral("2"), QStringLiteral("在线"));
    mOnlineMap.insert(QStringLiteral("3"), QStringLiteral("隐身"));
}

void Server::onRefresh() {
    updateData(mDepID, mEmployeeID);
}
