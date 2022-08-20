#include "talkWindowShell.h"

extern QString gLoginEmployeeID;

QString gfileName;
QString gfileData;

TalkWindowShell::TalkWindowShell(QWidget *parent) : BaseWindow(parent), ui(new Ui::TalkWindowShell) {
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    loadStyleSheet("talkWindow");
    initControl();
    initTcpSocket();

    QFile file(":/assets/MsgHtml/msgtmpl.js");
    if (!file.size()) { // 文件大小为零则创建文件
        QStringList employeeIDList;
        getEmployeeID(employeeIDList);
        if (!createJsFile(employeeIDList)) {
            QMessageBox::information(this, "提示", "更新js文件数据失败");
        }
    }
}

TalkWindowShell::~TalkWindowShell() {
    delete ui;
    delete mEmotionWindow;
    mEmotionWindow = nullptr;
}

const QMap<QListWidgetItem *, QWidget *> &TalkWindowShell::getTalkWindowItemMap() const {
    return mTalkWindowItemMap;
}

void TalkWindowShell::initControl() {
    setWindowTitle("聊天窗口");

    mEmotionWindow = new EmotionWindow;
    mEmotionWindow->hide();

    QList<int> leftWidgetSize;
    leftWidgetSize << 154 << width() - 154;
    ui->splitter->setSizes(leftWidgetSize);

    ui->listWidget->setStyle(new CustomProxyStyle(this));

    connect(ui->listWidget, &QListWidget::itemClicked, this, &TalkWindowShell::onTalkWindowItemClicked);
    connect(mEmotionWindow, SIGNAL(signalEmotionItemClicked(int)), this, SLOT(onEmotionItemClicked(int)));
}

// 设置当前聊天窗口
void TalkWindowShell::setCurrentWidget(QWidget *widget) {
    ui->rightStackedWidget->setCurrentWidget(widget);
}

// 添加聊天窗口
void TalkWindowShell::addTalkWindow(TalkWindow *talkWindow, TalkWindowItem *talkWindowItem, const QString &uid) {
    ui->rightStackedWidget->addWidget(talkWindow);
    connect(mEmotionWindow, SIGNAL(signalEmotionHide()), talkWindow, SLOT(onSetEmotionBtnStatus()));

    auto *aItem = new QListWidgetItem(ui->listWidget);
    mTalkWindowItemMap.insert(aItem, talkWindow);
    aItem->setSelected(true);

    // 判断群聊还是单聊
    QSqlQueryModel sqlDepModel;
    QString strQuery = QString("select picture from tab_department where departmentID = %1").arg(uid);
    sqlDepModel.setQuery(strQuery);
    int rows = sqlDepModel.rowCount();
    if (rows == 0) { // 单聊
        strQuery = QString("SELECT picture FROM tab_employees WHERE employeeID = %1").arg(uid);
        sqlDepModel.setQuery(strQuery);
    }
    QModelIndex index = sqlDepModel.index(0, 0);
    QImage img;
    img.load(sqlDepModel.data(index).toString());

    talkWindowItem->setAvatarPixmap(QPixmap::fromImage(img));
    ui->listWidget->addItem(aItem);
    ui->listWidget->setItemWidget(aItem, talkWindowItem);

    onTalkWindowItemClicked(aItem);

    connect(talkWindowItem, &TalkWindowItem::signalCloseClocked, [talkWindowItem, talkWindow, aItem, this]() {
        mTalkWindowItemMap.remove(aItem);
        talkWindow->close();
        ui->listWidget->takeItem(ui->listWidget->row(aItem));
        delete talkWindowItem;
        ui->rightStackedWidget->removeWidget(talkWindow);

        // 如果聊天列表关闭完了，则关闭整个窗口
        if (ui->rightStackedWidget->count() < 1) {
            close();
        }
    });
}

// 表情按钮被点击
void TalkWindowShell::onEmotionBtnClicked(bool) {
    mEmotionWindow->setVisible(!mEmotionWindow->isVisible());
    // 将当前控件的相对位置转换为屏幕的绝对位置
    QPoint emotionPoint = this->mapToGlobal(QPoint(0, 0));
    emotionPoint.setX(emotionPoint.x() + 170);
    emotionPoint.setY(emotionPoint.y() + 220);
    mEmotionWindow->move(emotionPoint);
}

// 左侧列表点击后执行的槽函数
void TalkWindowShell::onTalkWindowItemClicked(QListWidgetItem *item) {
    QWidget *talkWindowWidget = mTalkWindowItemMap.find(item).value();
    ui->rightStackedWidget->setCurrentWidget(talkWindowWidget);
}

// 表情被选中
void TalkWindowShell::onEmotionItemClicked(int emotionNum) {
    auto *curTalkWindow = dynamic_cast<TalkWindow *>(ui->rightStackedWidget->currentWidget());
    if (curTalkWindow) {
        curTalkWindow->addEmotionImage(emotionNum);
    }
}

void TalkWindowShell::initTcpSocket() {
    mTcpClientSocket = new QTcpSocket(this);
    mTcpClientSocket->connectToHost("127.0.0.1", TCP_PORT);
}

/**
 * 本数据包格式:
 * 群聊标志 + 发信息员工QQ号 + 收信息员工QQ号(群QQ号) + 信息类型 + 数据长度(5位数) + 数据
 * 表情包数据格式:
 * 群聊标志 + 发信息员工QQ号 + 收信息员工QQ号(群QQ号) + 信息类型 + 表情个数 + images + 数据
 * @param strData
 * @param msgType
 * @param fileName
 */
void TalkWindowShell::updateSendTcpMsg(QString &strData, int &msgType, const QString &fileName) {
    auto *curTalkWindow = dynamic_cast<TalkWindow *>(ui->rightStackedWidget->currentWidget());
    QString talkId = curTalkWindow->getTalkId();

    QString strGroupFlag;
    QString strSend;
    if (talkId.length() == 4) { // 群QQ的长度是4
        strGroupFlag = "1";
    } else {
        strGroupFlag = "0";
    }
    int nstrDataL = strData.length();
    int dataLength = QString::number(nstrDataL).length();
    QString strDataLength;
    if (msgType == 1) { // 发送文本信息
        // 文本信息长度固定为5位数
        if (dataLength == 1) {
            strDataLength = "0000" + QString::number(nstrDataL);
        } else if (dataLength == 2) {
            strDataLength = "000" + QString::number(nstrDataL);
        } else if (dataLength == 3) {
            strDataLength = "00" + QString::number(nstrDataL);
        } else if (dataLength == 4) {
            strDataLength = "0" + QString::number(nstrDataL);
        } else if (dataLength == 5) {
            strDataLength = QString::number(nstrDataL);
        } else {
            QMessageBox::information(this, "提示", "数据长度不合理!");
        }
        // 群聊标志 + 发信息员工QQ号 + 收信息员工QQ号(群QQ号) + 信息类型 +数据长度+数据
        strSend = strGroupFlag + gLoginEmployeeID + talkId + "1" + strDataLength + strData;

    } else if (msgType == 0) { // 表情信息
        // 群聊标志 + 发信息员工QQ号 + 收信息员工QQ号(群QQ号) + 信息类型 + 表情个数 + images + 数据
        strSend = strGroupFlag + gLoginEmployeeID + talkId + "0" + strData;
    } else if (msgType == 2) { // 文件
        // 群聊标志+发信息员工QQ号+收信息员工QQ号+信息类型+文件长度+bytes+文件名+data_begin+文件内容
        QByteArray bt = strData.toUtf8();
        QString strLength = QString::number(bt.length());
        strSend = strGroupFlag + gLoginEmployeeID + talkId + "2" + strLength + "bytes" + fileName + "data_begin" + strData;
    }
    QByteArray dataBt;
    dataBt.resize(strSend.length());
    dataBt = strSend.toUtf8();

    mTcpClientSocket->write(dataBt);
}

bool TalkWindowShell::createJsFile(QStringList &employeeList) {
    QString strFileTxt(qApp->applicationDirPath() + "/msgtmpl.txt");
    QFile fileRead(strFileTxt);
    QString strFile;
    if (fileRead.open(QIODevice::ReadOnly)) {
        strFile = fileRead.readAll();
        fileRead.close();
    } else {
        QMessageBox::information(this, "提示", "msgtmpl.txt读取数据失败");
        return false;
    }
    QFile fileWrite(qApp->applicationDirPath() + "/msgtmpl.js");
    if (fileWrite.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        // 更新空值
        QString strSourceInitNull = "var external = null;";
        // 更新初始化
        QString strSourceInit = "external = channel.objects.external;";
        // 更新newChannel
        QString strSourceNew = "new QWebChannel(qt.webChannelTransport,"
                               "function(channel) {external = channel.objects.external;});";

        QString strSourceRecvHtml;
        // QFile fileRecvHtml("assets/MsgHtml/recvHtml.txt");
        QFile fileRecvHtml(qApp->applicationDirPath() + "/recvHtml.txt");
        if (fileRecvHtml.open(QIODevice::ReadOnly)) {
            strSourceRecvHtml = fileRecvHtml.readAll();
            fileRecvHtml.close();
        } else {
            QMessageBox::information(this, "提示", "recvHtml.txt读取失败");
            return false;
        }

        // 保存替换后的脚本
        QString strReplaceInitNull;
        QString strReplaceInit;
        QString strReplaceNew;
        QString strReplaceRecvHtml;

        for (int i = 0; i < employeeList.length(); i++) {
            // 编辑 替换后的空值
            QString strInitNull = strSourceInitNull;
            strInitNull.replace("external", QString("external_%1").arg(employeeList.at(i)));
            strReplaceInitNull += strInitNull;
            strReplaceInitNull += "\n";

            // 编辑替换后的初始值
            QString strInit = strSourceInit;
            strInit.replace("external", QString("external_%1").arg(employeeList.at(i)));
            strReplaceInit += strInit;
            strReplaceInit += "\n";

            // 编辑替换后的 newWebChannel
            QString strNew = strSourceNew;
            strNew.replace("external", QString("external_%1").arg(employeeList.at(i)));
            strReplaceNew += strNew;
            strReplaceNew += "\n";

            // 编辑替换后的recvHtml
            QString strRecvHtml = strSourceRecvHtml;
            strRecvHtml.replace("external", QString("external_%1").arg(employeeList.at(i)));
            strRecvHtml.replace("recvHtml", QString("recvHtml_%1").arg(employeeList.at(i)));
            strReplaceRecvHtml += strRecvHtml;
            strReplaceRecvHtml += "\n";
        }
        strFile.replace(strSourceInitNull, strReplaceInitNull);
        strFile.replace(strSourceInit, strReplaceInit);
        strFile.replace(strSourceNew, strReplaceNew);
        strFile.replace(strSourceRecvHtml, strReplaceRecvHtml);

        QTextStream stream(&fileWrite);
        stream << strFile;
        return true;
    } else {
        QMessageBox::information(this, "提示", "写msgtmpl.js失败");
        return false;
    }
}

void TalkWindowShell::getEmployeeID(QStringList &employeeList) {
    QSqlQueryModel queryModel;
    queryModel.setQuery("SELECT employeeID FROM tab_employees WHERE `status`= 1");
    // 员工总数
    int employeesNum = queryModel.rowCount();
    QModelIndex index;
    for (int i = 0; i < employeesNum; i++) {
        index = queryModel.index(i, 0);
        employeeList << queryModel.data(index).toString();
    }
}
