#include "Server.h"

const int tcpPort = 8888;
const int gUdpPort = 6666;

Server::Server(QWidget *parent) : QDialog(parent), ui(new Ui::ServerClass) {
    ui->setupUi(this);

    if (!connectMySql()) {
        QMessageBox::warning(nullptr, "提示", "数据库连接失败！");
        close();
    }

    setDepNameMap();
    setStatusMap();
    setOnlineMap();

    initComboBoxData();

    mQueryInfoModel.setQuery("select * from tab_employees");
    // 只读
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // 初始化查询公司群所有员工信息
    mEmployeeID = 0;
    mDepID = getComDepId();
    mComDepId = mDepID;

    updateData();

    // 定时刷新数据
    m_timer = new QTimer(this);
    m_timer->setInterval(200);
    m_timer->start();
    connect(m_timer, &QTimer::timeout, this, &Server::onRefresh);

    initTopSocket();
    initUdpSocket();
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
    for (quint16 port = gUdpPort; port < gUdpPort + 200; ++port) {
        mUdpSender->writeDatagram(btData, btData.size(), QHostAddress::Broadcast, port);
    }
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
    QSqlQuery queryCompDepID(QString("select departmentID from tab_department where department_name = '%1'")
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

void Server::on_queryDepartmentBtn_clicked() {
    ui->queryIDLineEdit->clear();
    mEmployeeID = 0;
    mDepID = ui->departmentBox->currentData().toInt();
    updateData(mDepID);
}

void Server::on_queryIDBtn_clicked() {
    ui->departmentBox->setCurrentIndex(0);
    mDepID = mComDepId;

    // 检测员工QQ号是否输入
    if (!ui->queryIDLineEdit->text().length()) {
        QMessageBox::information(this, "提示", "请输入员工QQ号");

        ui->queryIDLineEdit->setFocus();
        return;
    }

    // 获取用户输入的QQ号
    int employeeId = ui->queryIDLineEdit->text().toInt();
    QSqlQuery queryInfo(QString("select * from tab_employees where employeeID = %1").arg(employeeId));
    queryInfo.exec();
    if (!queryInfo.next()) {
        QMessageBox::information(this, "提示", "请输入正确的员工QQ号！");
        ui->queryIDLineEdit->setFocus();
        return;
    } else {
        mEmployeeID = employeeId;
    }
}

void Server::initComboBoxData() {
    // 组合框项的文本
    QString itemText;

    // 获取公司总的部门数
    QSqlQueryModel queryModel;
    queryModel.setQuery("select * from tab_department");
    // 部门总数应该减去公司群
    int depCounts = queryModel.rowCount() - 1;
    for (int i = 0; i < depCounts; ++i) {
        itemText = ui->employeeDepBox->itemText(i);
        QSqlQuery queryDepId(
                QString("select departmentID from tab_department where department_name = '%1'").arg(itemText)
        );
        queryDepId.exec();
        queryDepId.first();

        // 设置当前组合框的数据为响应的部门QQ号
        ui->employeeDepBox->setItemData(i, queryDepId.value(0));
    }

    for (int i = 0; i < depCounts; ++i) {
        itemText = ui->departmentBox->itemText(i);
        QSqlQuery queryDepId(
                QString("select departmentID from tab_department where department_name = '%1'").arg(itemText)
        );
        queryDepId.exec();
        queryDepId.first();

        ui->departmentBox->setItemData(i, queryDepId.value(0).toInt());
    }
}

void Server::on_logoutBtn_clicked() {
    ui->queryIDLineEdit->clear();
    ui->departmentBox->setCurrentIndex(0);
    // 检测员工QQ是否输入正确
    if (!ui->logoutIDLineEdit->text().length()) {
        QMessageBox::information(this, "提示", "请输入员工QQ号！");
        ui->logoutIDLineEdit->setFocus();
        return;
    }

    // 获取用户输入的员工QQ号
    int employeeID = ui->logoutIDLineEdit->text().toInt();

    QSqlQuery queryInfo(QString("select employee_name FROM tab_employees where employeeID = %1").arg(employeeID));
    queryInfo.exec();
    if (!queryInfo.next()) {
        QMessageBox::information(this, "提示", "请输入正确的员工QQ号！");
        ui->logoutIDLineEdit->setFocus();
        return;
    } else {
        // 注销操作，更新数据库数据，将员工的状态设置为0
        QSqlQuery sqlUpdate(QString("update tab_employees SET status = 0 where employeeID = %1").arg(employeeID));
        sqlUpdate.exec();

        // 获取注销员工的姓名
        QString strName = queryInfo.value(0).toString();
        QMessageBox::information(this, "提示", QString("员工 %1 的企业QQ: %2已被注销").arg(strName).arg(employeeID));
        ui->logoutIDLineEdit->clear();
    }
}

void Server::on_selectPictureBtn_clicked() {
    // 获取选择头像的路径
    mPixPath = QFileDialog::getOpenFileName(
            this,
            QString::fromLocal8Bit("选择头像"),
            ".",
            "*.png;;*.jpg"
    );

    if (!mPixPath.size()) {
        return;
    }

    // 将头像显示到标签
    QPixmap pixmap;
    pixmap.load(mPixPath);

    qreal widthRatio = (qreal) ui->headLabel->width() / (qreal) pixmap.width();
    qreal heightRatio = (qreal) ui->headLabel->height() / (qreal) pixmap.height();

    QSize size(pixmap.width() * widthRatio, pixmap.height() * heightRatio);
    ui->headLabel->setPixmap(pixmap.scaled(size));
}

void Server::on_addBtn_clicked() {
    // 检测员工姓名的输入
    QString strName = ui->nameLineEdit->text();
    if (!strName.size()) {
        QMessageBox::information(this, "提示", "请输入员工姓名！");
        ui->nameLineEdit->setFocus();
        return;
    }

    //检测员工选择头像
    if (!mPixPath.size()) {
        QMessageBox::information(this, "提示", "请选择员工头像的路径！");
        return;
    }

    // 数据库插入新的员工数据
    // 获取员工QQ号
    QSqlQuery maxEmployeeID("SELECT MAX(employeeID) FROM tab_employees");
    maxEmployeeID.exec();
    maxEmployeeID.next();

    int employeeID = maxEmployeeID.value(0).toInt() + 1;

    // 员工部门QQ号
    int depID = ui->employeeDepBox->currentData().toInt();

    // 图片路径格式设置为,"/"替换为"\"  xxx\xxx\xxx.png
    mPixPath.replace("/", "\\\\");

    QSqlQuery inserSql(
            QString("INSERT INTO tab_employees(departmentID,employeeID,employee_name,picture) VALUES(%1,%2,'%3','%4')")
                    .arg(depID)
                    .arg(employeeID)
                    .arg(strName)
                    .arg(mPixPath));

    inserSql.exec();
    QMessageBox::information(this, "提示", "新增员工成功！");
    mPixPath = "";
    ui->nameLineEdit->clear();
    ui->headLabel->setText(QStringLiteral("  员工寸照  "));
}

void Server::initUdpSocket() {
    mUdpSender = new QUdpSocket(this);
}
