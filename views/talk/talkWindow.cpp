#include "talkWindow.h"
#include "../../manger/windowManger.h"

extern QString gLoginEmployeeID;

TalkWindow::TalkWindow(QWidget *parent, const QString &uid) : QWidget(parent), ui(new Ui::TalkWindow), mTalkId(uid) {
    ui->setupUi(this);
    WindowManger::getInstance()->addWindowName(uid, this);
    setAttribute(Qt::WA_DeleteOnClose);
    initGroupTalkStatus();
    initControl();
}

TalkWindow::~TalkWindow() {
    delete ui;
    WindowManger::getInstance()->deleteWindowName(mTalkId);
}

void TalkWindow::addEmotionImage(int emotionNum) {
    ui->textEdit->setFocus();
    ui->textEdit->addEmotionUrl(emotionNum);
}

void TalkWindow::setWindowName(const QString &name) {
    ui->nameLabel->setText(name);
}

void TalkWindow::onSendBtnClicked(bool) {
    // debug:发送方的页面接受消息有问题 接受方没有问题
    if (ui->textEdit->toPlainText().isEmpty()) {
        QToolTip::showText(this->mapToGlobal(QPoint(630, 660)),
                           "发送的信息不能为空",
                           this, QRect(0, 0, 120, 100), 2000);
        return;
    }
    QString html = ui->textEdit->document()->toHtml();

    // 文本HTML如果没有字体则添加字体
    if (!html.contains(".png") && !html.contains("</span>")) {
        QString fontHtml;
        QString text = ui->textEdit->toPlainText();
        QFile file(":/assets/MsgHtml/msgFont.txt");
        if (file.open(QIODevice::ReadOnly)) {
            fontHtml = file.readAll();
            fontHtml.replace("%1", text);
            file.close();
        } else {
            QMessageBox::information(this, "提示", "msgFont.txt 不存在");
            return;
        }
        if (!html.contains(fontHtml)) {
            html.replace(text, fontHtml);
        }
    }
    ui->textEdit->clear();
    ui->textEdit->deleteAllEmotionImage();

    // 收信息窗口
    ui->msgWidget->appendMsg(html);
}

QString TalkWindow::getTalkId() {
    return mTalkId;
}

void TalkWindow::onItemDoubleClicked(QTreeWidgetItem *item, int) {
    bool bIsChild = item->data(0, Qt::UserRole).toBool();
    if (bIsChild) {
        QString strEmployeeID = item->data(0, Qt::UserRole + 1).toString();
        if (strEmployeeID == gLoginEmployeeID) return;
        WindowManger::getInstance()->addNewTalkWindow(strEmployeeID);
    }
}

void TalkWindow::initControl() {
    QList<int> rightWidgetSize;
    rightWidgetSize << 600 << 138;
    ui->bodySplitter->setSizes(rightWidgetSize);

    ui->textEdit->setFontPointSize(10);
    ui->textEdit->setFocus();

    connect(ui->sysMin, SIGNAL(clicked(bool)), parent(), SLOT(onShowMin(bool)));
    connect(ui->sysClose, SIGNAL(clicked(bool)), parent(), SLOT(onShowClose(bool)));
    connect(ui->closeBtn, SIGNAL(clicked(bool)), parent(), SLOT(onShowClose(bool)));
    connect(ui->faceBtn, SIGNAL(clicked(bool)), parent(), SLOT(onEmotionBtnClicked(bool)));
    connect(ui->sendBtn, SIGNAL(clicked(bool)), this, SLOT(onSendBtnClicded(bool)));
    connect(ui->treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem * , int)),
            this, SLOT(onItemDoubleClicked(QTreeWidgetItem * , int)));
    connect(ui->fileopenBtn, SIGNAL(clicked(bool)), this, SLOT(onFileOpenBtnClicked(bool)));

    if (mIsGroupTalk) {
        initTalkWindow();
    } else {
        initPtoPTalk();
    }
}

void TalkWindow::initGroupTalkStatus() {
    QSqlQueryModel sqlDepModel;
    QString sql = QString("SELECT * FROM tab_department WHERE departmentID = %1").arg(mTalkId);

    sqlDepModel.setQuery(sql);
    int rows = sqlDepModel.rowCount();
    if (rows == 0) { // 单独聊天
        mIsGroupTalk = false;
    } else { // 群聊
        mIsGroupTalk = true;
    }
}

int TalkWindow::getCompDepID() {
    QSqlQuery queryDepID(QString("SELECT departmentID FROM tab_department WHERE department_name='%1'")
                                 .arg("公司群"));
    queryDepID.exec();
    queryDepID.next();

    return queryDepID.value(0).toInt();
}

void TalkWindow::initTalkWindow() {
    auto *pRootItem = new QTreeWidgetItem();
    pRootItem->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);
    pRootItem->setData(0, Qt::UserRole, 0);
    auto *pItemName = new RootContactItem(false, ui->treeWidget);
    ui->treeWidget->setFixedHeight(646);

    // 当前聊天的群组名或人名
    QString strGroupName;
    QSqlQuery queryGroupName(QString("SELECT department_name FROM tab_department WHERE departmentID=%1")
                                     .arg(mTalkId));
    queryGroupName.exec();
    if (queryGroupName.first()) {
        strGroupName = queryGroupName.value(0).toString();
    }

    int nEmployeeNum = 0;
    // 获取员工人数
    QSqlQueryModel queryEmployeeModel;
    if (getCompDepID() == mTalkId.toInt()) { // 公司群
        queryEmployeeModel.setQuery("SELECT employeeID FROM tab_employees WHERE `status`=1");
    } else {
        queryEmployeeModel.setQuery(QString("SELECT employeeID FROM tab_employees WHERE `status`=1 AND departmentID=%1")
                                            .arg(mTalkId));
    }
    nEmployeeNum = queryEmployeeModel.rowCount();
    QString qsGroupName = QString("%1 %2/%3").arg(strGroupName).arg(0).arg(nEmployeeNum);
    pItemName->setText(qsGroupName);

    // 插入分组节点
    ui->treeWidget->addTopLevelItem(pRootItem);
    ui->treeWidget->setItemWidget(pRootItem, 0, pItemName);

    // 展开
    pRootItem->setExpanded(true);
    for (int i = 0; i < nEmployeeNum; i++) {
        // 添加子节点
        int employeeID;
        QModelIndex modelIndex = queryEmployeeModel.index(i, 0);
        employeeID = queryEmployeeModel.data(modelIndex).toInt();

        addPeoInfo(pRootItem, employeeID);
    }
}

void TalkWindow::initPtoPTalk() {
    QPixmap pixSkin;
    pixSkin.load(":/assets/skin.png");
    ui->widget->setFixedSize(pixSkin.size());

    auto *skinLabel = new QLabel(ui->widget);
    skinLabel->setPixmap(pixSkin);
    skinLabel->setFixedSize(ui->widget->size());
}

void TalkWindow::addPeoInfo(QTreeWidgetItem *pRootGroupItem, int employeeID) {
    auto *pChild = new QTreeWidgetItem();

    // 添加子节点
    pChild->setData(0, Qt::UserRole, 1);
    pChild->setData(0, Qt::UserRole + 1, employeeID);
    auto *pContactItem = new ContactItem(ui->treeWidget);

    // 获取名 签名 头像路径
    QString strName, strSign, strPicPath, strQuery;
    QSqlQueryModel queryInfoModel;
    queryInfoModel.setQuery(
            QString("SELECT employee_name,employee_sign,picture FROM tab_employees WHERE employeeID=%1")
                    .arg(employeeID));
    QModelIndex nameIndex, signIndex, picIndex;
    nameIndex = queryInfoModel.index(0, 0);
    signIndex = queryInfoModel.index(0, 1);
    picIndex = queryInfoModel.index(0, 2);
    strName = queryInfoModel.data(nameIndex).toString();
    strSign = queryInfoModel.data(signIndex).toString();
    strPicPath = queryInfoModel.data(picIndex).toString();

    QPixmap pix1;
    pix1.load(":/assets/head_mask.png");
    QImage imageHead;
    imageHead.load(strPicPath);
    pContactItem->setAvatarPixmap(
            CommonUtils::getRoundImage(QPixmap::fromImage(imageHead), pix1, pContactItem->getAvatarSize()));
    pContactItem->setUserName(strName);
    pContactItem->setSignName(strSign);

    pRootGroupItem->addChild(pChild);
    ui->treeWidget->setItemWidget(pChild, 0, pContactItem);

    QString str = pContactItem->getUserName();
    mGroupPeopleMap.insert(pChild, str);
}
