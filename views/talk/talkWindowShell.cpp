#include "talkWindowShell.h"
#include "../../manger/windowManger.h"

extern QString gLoginEmployeeID;

QString gfileName;
QString gfileData;
const int gUdpPort = 6666;

TalkWindowShell::TalkWindowShell(QWidget *parent) : BaseWindow(parent), ui(new Ui::TalkWindowShell) {
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    loadStyleSheet("talkWindow");
    initControl();
    initTcpSocket();
    initUdpSocket();

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

void TalkWindowShell::onProcessPendingData() {
    // 端口中有未处理的数据
    while (mUdpReceiver->hasPendingDatagrams()) {
        // 群聊标志占位
        const static int groupFlagWidth = 1;
        // 群QQ号宽度
        const static int groupWidth = 4;
        // 员工QQ号宽度
        const static int employeeWidth = 5;
        // 信息类型宽度
        const static int msgTypeWidth = 1;
        // 文本信息长度的宽度
        const static int msgLengthWidth = 5;
        // 表情图片的宽度
        const static int picturehWidth = 3;

        // 读取UDP数据
        QByteArray btData;
        btData.resize(mUdpReceiver->pendingDatagramSize());
        mUdpReceiver->readDatagram(btData.data(), btData.size());

        QString strData = btData.data();
        // 聊天窗口ID，群聊是群号，单聊是员工QQ号
        QString strWindowID;
        // 发送及接口
        QString strSendEmployeeID, strReceieEmployeeeID;
        // 数据
        QString strMsg;

        // 数据长度
        int msgLen;
        // 数据类型
        int msgType;

        strSendEmployeeID = strData.mid(groupFlagWidth, employeeWidth);
        if (strSendEmployeeID == gLoginEmployeeID) return;

        if (btData[0] == '1') { // 群聊
            // 群QQ号
            strWindowID = strData.mid(groupFlagWidth + employeeWidth, groupWidth);
            QByteRef cMsgType = btData[groupFlagWidth + employeeWidth + groupWidth];
            if (cMsgType == '1') { // 文本
                msgType = 1;
                msgLen = strData.mid(groupFlagWidth + employeeWidth + groupWidth + msgTypeWidth,
                                     msgLengthWidth).toInt();
                strMsg = strData.mid(groupFlagWidth + employeeWidth + groupWidth + msgTypeWidth + msgLengthWidth,
                                     msgLen);
            } else if (cMsgType == '0') { // 图片
                msgType = 0;
                int posImage = strData.indexOf("images");
                strMsg = strData.right(strData.length() - posImage - QString("iamges").length());
            } else if (cMsgType == '2') { // 文件
                msgType = 2;
                // 文件名称
                int bytesWidth = QString("bytes").length();
                int posBytes = strData.indexOf("bytes");
                int posData_begin = strData.indexOf("data_begin");

                QString fileName = strData.mid(posBytes + bytesWidth, posData_begin - bytesWidth - posBytes);
                gfileName = fileName;

                // 文件内容
                int dataLengthWidth;
                int posData = posData_begin + QString("data_begin").length();
                strMsg = strData.mid(posData);
                gfileData = strMsg;

                // 获取发送者姓名
                QString sender;
                int employeeID = strSendEmployeeID.toInt();
                QSqlQuery querySenderName(
                        QString("SELECT employee_name FROM tab_employees WHERE employeeID=%1").arg(employeeID));
                querySenderName.exec();

                if (querySenderName.next()) {
                    sender = querySenderName.value(0).toString();
                }
                // 接收文件操作 .....
//                ReceiveFile* receiveFile = new ReceiveFile(this);
//                connect(receiveFile, &ReceiveFile::refuseFile, [this]() {
//                    return;
//                });
//                QString msgLebel = "收到来自" + sender + "发来的文件.是否接受?";
//                receiveFile->setMsg(msgLebel);
//                receiveFile->show();
            }
        } else if (btData[0] == '0') { // 单聊
            strReceieEmployeeeID = strData.mid(groupFlagWidth + employeeWidth, employeeWidth);
            strWindowID = strSendEmployeeID;

            // 不是发给我的消息不做处理
            if (strReceieEmployeeeID != gLoginEmployeeID) return;

            QByteRef cMsgType = btData[groupFlagWidth + employeeWidth + employeeWidth];
            if (cMsgType == '1') { // 文本信息
                msgType = 1;
                msgLen = strData.mid(groupFlagWidth + employeeWidth + employeeWidth + msgTypeWidth,
                                     msgLengthWidth).toInt();

                strMsg = strData.mid(groupFlagWidth + employeeWidth + employeeWidth + msgTypeWidth + msgLengthWidth,
                                     msgLen);

            } else if (cMsgType == '0') { // 表情信息
                msgType = 0;
                int posImags = strData.indexOf("images");
                int imagesWidth = QString("images").length();
                strMsg = strData.mid(posImags + imagesWidth);
            } else if (cMsgType == '2') {
                msgType = 2;
                // 文件名称
                int bytesWidth = QString("bytes").length();
                int posBytes = strData.indexOf("bytes");
                int posData_begin = strData.indexOf("data_begin");
                // 11000520022bytesexit.txtdata_beginAre you ok?
                QString fileName = strData.mid(posBytes + bytesWidth, posData_begin - bytesWidth - posBytes);
                gfileName = fileName;
                // 文件内容
                int dataLengthWidth;
                int posData = posData_begin + QString("data_begin").length();
                strMsg = strData.mid(posData);
                gfileData = strMsg;

                // 获取发送者姓名
                QString sender;
                int employeeID = strSendEmployeeID.toInt();
                QSqlQuery querySenderName(
                        QString("SELECT employee_name FROM tab_employees WHERE employeeID=%1").arg(employeeID));
                querySenderName.exec();

                if (querySenderName.next()) {
                    sender = querySenderName.value(0).toString();
                }
                // 接收文件操作
                // ReceiveFile* receiveFile = new ReceiveFile(this);
                // connect(receiveFile, &ReceiveFile::refuseFile, [this]() {
                //     return;
                // });
                // QString msgLebel = QString::fromLocal8Bit("收到来自") + sender +
                //                    QString::fromLocal8Bit("发来的文件.是否接受?");
                // receiveFile->setMsg(msgLebel);
                // receiveFile->show();
            }
        }

        // 将聊天窗口设置为活动的
        QWidget *widget = WindowManger::getInstance()->findWindowName(strWindowID);
        if (widget) { // 聊天窗口存在
            this->setCurrentWidget(widget);
            // 同步激活左侧聊天窗口
            QListWidgetItem *item = mTalkWindowItemMap.key(widget);
            item->setSelected(true);
        } else { // 聊天窗口未打开
            return;
        }

        // 文件信息另做处理
        if (msgType != 2) {
            handleReceivedMsg(strSendEmployeeID.toInt(), msgType, strMsg);
        }
    }
}

void TalkWindowShell::initTcpSocket() {
    mTcpClientSocket = new QTcpSocket(this);
    mTcpClientSocket->connectToHost("127.0.0.1", TCP_PORT);
}

void TalkWindowShell::initUdpSocket() {
    mUdpReceiver = new QUdpSocket(this);
    for (quint16 port = gUdpPort; port < gUdpPort + 200; ++port) {
        if (mUdpReceiver->bind(port, QUdpSocket::ShareAddress)) {
            break;
        }
    }

    connect(mUdpReceiver, &QUdpSocket::readyRead, this, &TalkWindowShell::onProcessPendingData);
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
        strSend = strGroupFlag + gLoginEmployeeID + talkId + "2" + strLength + "bytes" + fileName + "data_begin" +
                  strData;
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

void TalkWindowShell::handleReceivedMsg(int senderEmployeeID, int msgType, QString strMsg) {
    QMsgTextEdit msgTextEdit;
    msgTextEdit.setText(strMsg);

    if (msgType == 1) { // 文本
        msgTextEdit.toHtml();
    } else if (msgType == 0) { // 表情信息处理
        const int emotionWidth = 3;
        int emotionNum = strMsg.length() / emotionWidth;

        for (int i = 0; i < emotionNum; i++) {
            msgTextEdit.addEmotionUrl(strMsg.mid(i * 3, emotionWidth).toInt());
        }
    }
    QString html = msgTextEdit.document()->toHtml();

    // 文本HTML如果没有字体则添加字体
    if (!html.contains(".png") && !html.contains("</span>")) {
        QString fontHtml;
        QFile file("./MsgHtml/msgFont.txt");
        if (file.open(QIODevice::ReadOnly)) {
            fontHtml = file.readAll();
            fontHtml.replace("%1", strMsg);
            file.close();
        } else {
            QMessageBox::information(this, "提示", "msgFont.txt 不存在");
            return;
        }
        if (!html.contains(fontHtml)) {
            html.replace(strMsg, fontHtml);
        }
    }

    auto *talkWindow = dynamic_cast<TalkWindow *> (ui->rightStackedWidget->currentWidget());
    talkWindow->ui->msgWidget->appendMsg(html, QString::number(senderEmployeeID));
}
