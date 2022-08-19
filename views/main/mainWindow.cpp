#include "mainWindow.h"

MainWindow::MainWindow(QWidget *parent) : BaseWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlags(windowFlags() | Qt::Tool);
    loadStyleSheet("mainWindow");
    initControl();
    initTimer();
}

MainWindow::~MainWindow() {
    delete ui;
}

// 自动升级，60秒一级
void MainWindow::initTimer() {
    auto *timer = new QTimer(this);
    timer->setInterval(60000);
    connect(timer, &QTimer::timeout, [this] {
        static int level = 1;
        if (level == 99) level = 1;
        level++;
        setLevelPixmap(level);
    });
    timer->start();
}

void MainWindow::initControl() {
    // 树获取焦点时不绘制边框
    ui->treeWidget->setStyle(new MainProxyStyle);
    setAvatarPixmap(":/assets/avatar.bmp");
    setLevelPixmap(1);
    setStatusMenuIcon(":/assets/StatusSucceeded.png");

    auto *appUpLayout = new QHBoxLayout;
    appUpLayout->setContentsMargins(0, 0, 0, 0);
    appUpLayout->addWidget(addOtherAppExtension(":/assets/app/app_7.png", "app_7"));
    appUpLayout->addWidget(addOtherAppExtension(":/assets/app/app_2.png", "app_2"));
    appUpLayout->addWidget(addOtherAppExtension(":/assets/app/app_3.png", "app_3"));
    appUpLayout->addWidget(addOtherAppExtension(":/assets/app/app_4.png", "app_4"));
    appUpLayout->addWidget(addOtherAppExtension(":/assets/app/app_5.png", "app_5"));
    appUpLayout->addWidget(addOtherAppExtension(":/assets/app/app_6.png", "app_6"));
    appUpLayout->addWidget(addOtherAppExtension(":/assets/app/skin.png", "app_skin"));
    appUpLayout->addStretch();
    appUpLayout->setSpacing(2);
    ui->appWidget->setLayout(appUpLayout);

    ui->bottomLayout_up->addWidget(addOtherAppExtension(":/assets/app/app_10.png", "app_10"));
    ui->bottomLayout_up->addWidget(addOtherAppExtension(":/assets/app/app_8.png", "app_8"));
    ui->bottomLayout_up->addWidget(addOtherAppExtension(":/assets/app/app_11.png", "app_11"));
    ui->bottomLayout_up->addWidget(addOtherAppExtension(":/assets/app/app_9.png", "app_9"));
    ui->bottomLayout_up->addStretch();

    // 初始化联系人
    initContactTree();

    // 个性签名、好友搜索   事件过滤器
    ui->signature->installEventFilter(this);
    ui->searchInput->installEventFilter(this);

    connect(ui->sysMin, SIGNAL(clicked(bool)), this, SLOT(onShowHide(bool)));
    connect(ui->sysClose, SIGNAL(clicked(bool)), this, SLOT(onShowClose(bool)));

    // 皮肤改变，更新搜索框样式
    connect(NotifyManger::getInstance(), &NotifyManger::signalSkinChanged, [this]() {
        updateSearchStyle();
    });

    // 设置系统托盘
    new SystemTray(this);
}

void MainWindow::setUsername(const QString &username) {
    ui->nameLabel->adjustSize();
    // 省略过长文本
    QString name = ui->nameLabel->fontMetrics().elidedText(username, Qt::ElideRight, ui->nameLabel->width());
    ui->nameLabel->setText(name);
}

void MainWindow::setLevelPixmap(int level) {
    QPixmap pix(ui->levelBtn->size());
    pix.fill(Qt::transparent);

    QPainter painter(&pix);
    painter.drawPixmap(0, 4, QPixmap(":/assets/lv.png"));

    int unitNum = level % 10;   // 个位数
    int tenNum = level / 10;    // 十位数

    // 绘制图片的部分内容，十位数的等级
    painter.drawPixmap(10, 4, QPixmap(":/assets/levelvalue.png"), tenNum * 6, 0, 6, 7);
    // 个位数等级
    painter.drawPixmap(16, 4, QPixmap(":/assets/levelvalue.png"), unitNum * 6, 0, 6, 7);

    ui->levelBtn->setIcon(pix);
    ui->levelBtn->setIconSize(ui->levelBtn->size());
}

void MainWindow::setAvatarPixmap(const QString &avatar) {
    QPixmap pix;
    pix.load(":/assets/head_mask.png");
    ui->headLabel->setPixmap(getRoundImage(QPixmap(avatar), pix, ui->headLabel->size()));
}

void MainWindow::setStatusMenuIcon(const QString &statusPath) {
    QPixmap statusBtnPixmap(ui->statusBtn->size());
    statusBtnPixmap.fill(Qt::transparent);

    QPainter painter(&statusBtnPixmap);
    painter.drawPixmap(4, 4, QPixmap(statusPath));

    ui->statusBtn->setIcon(statusBtnPixmap);
    ui->statusBtn->setIconSize(ui->statusBtn->size());
}

QWidget *MainWindow::addOtherAppExtension(const QString &appPath, const QString &appName) {
    auto *btn = new QPushButton(this);
    btn->setFixedSize(20, 20);

    QPixmap pixmap(btn->size());
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    QPixmap appPixmap(appPath);

    painter.drawPixmap((btn->width() - appPixmap.width()) / 2, (btn->height() - appPixmap.height()) / 2, appPixmap);
    btn->setIcon(pixmap);
    btn->setIconSize(btn->size());
    btn->setObjectName(appName);
    btn->setProperty("hasBorder", true);

    connect(btn, &QPushButton::clicked, this, &MainWindow::onAppIconClicked);
    return btn;
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    setUsername("琉璃之鸟");
    BaseWindow::resizeEvent(event);
}

// 事件过滤器
bool MainWindow::eventFilter(QObject *obj, QEvent *event) {
    if (ui->searchInput == obj) {
        if (event->type() == QEvent::FocusIn) {
            ui->searchWidget->setStyleSheet(
                    QString("QWidget#searchWidget{background-color: rgb(255, 255, 255);"
                            "border-bottom: 1px solid rgba(%1, %2, %3, 100);}"
                            "QPushButton#searchBtn{"
                            "border-image: url(:/assets/search/main_search_deldown.png);}"
                            "QPushButton#searchBtn:hover{"
                            "border-image: url(:/assets/search/main_search_delhighlight.png);}"
                            "QPushButton#searchBtn:pressed{"
                            "border-image: url(:/assets/search/main_search_delhighdown.png);}")
                            .arg(mColorBackground.red())
                            .arg(mColorBackground.green())
                            .arg(mColorBackground.blue()));
        } else if (event->type() == QEvent::FocusOut) {
            updateSearchStyle();
        }
    }
    return false;
}

// 更新搜索框样式
void MainWindow::updateSearchStyle() {
    ui->searchWidget->setStyleSheet(QString("QWidget#searchWidget{"
                                            "background-color:rgba(%1,%2,%3,50);"
                                            "border-bottom:1px solid rgba(%1,%2,%3,30);}"
                                            "QPushButton#searchBtn{"
                                            "border-image:url(:/assets/search/search_icon.png);}")
                                            .arg(mColorBackground.red())
                                            .arg(mColorBackground.green())
                                            .arg(mColorBackground.blue()));
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (qApp->widgetAt(event->pos()) != ui->searchInput && ui->searchInput->hasFocus()) {
        ui->searchInput->clearFocus();
    } else if (qApp->widgetAt(event->pos()) != ui->signature && ui->signature->hasFocus()) {
        ui->signature->clearFocus();
    }
    BaseWindow::mousePressEvent(event);
}

void MainWindow::onAppIconClicked() {
    // 判断信号发送者的对象名是否是 皮肤修改图标
    if (sender()->objectName() == "app_skin") {
        Skin *skin = new Skin;
        skin->show();
    }
}

// 初始化联系人
void MainWindow::initContactTree() {
    // 展开与收缩时的信号
    connect(ui->treeWidget, SIGNAL(itemClicked(QTreeWidgetItem * , int)), this,
            SLOT(onItemClicked(QTreeWidgetItem * , int)));
    connect(ui->treeWidget, SIGNAL(itemExpanded(QTreeWidgetItem * )), this,
            SLOT(onItemExpanded(QTreeWidgetItem * )));
    connect(ui->treeWidget, SIGNAL(itemCollapsed(QTreeWidgetItem * )), this,
            SLOT(onItemCollapsed(QTreeWidgetItem * )));
    connect(ui->treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem * , int)), this,
            SLOT(onItemDoubleClicked(QTreeWidgetItem * , int)));

    // 根节点
    auto *pRootGroupItem = new QTreeWidgetItem;
    pRootGroupItem->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);
    pRootGroupItem->setData(0, Qt::UserRole, 0);

    auto *pItemName = new RootContactItem(true, ui->treeWidget);
    pItemName->setText("星铭科技");

    // 插入分组节点
    ui->treeWidget->addTopLevelItem(pRootGroupItem);
    ui->treeWidget->setItemWidget(pRootGroupItem, 0, pItemName);

    QStringList compDeps;
    compDeps << "技术部";
    compDeps << "运营部";
    compDeps << "市场部";
    compDeps << "行政部";

    for (int i = 0; i < compDeps.length(); ++i) {
        addCompanyDeps(pRootGroupItem, compDeps.at(i));
    }
}

// 添加联系人
void MainWindow::addCompanyDeps(QTreeWidgetItem *pRootGroupItem, const QString &deps) {
    auto *pChild = new QTreeWidgetItem;
    QPixmap pix;
    pix.load(":/assets/head_mask.png");

    // 子项数据设置为1，进行区别
    pChild->setData(0, Qt::UserRole, 1);
    pChild->setData(0, Qt::UserRole + 1, QString::number((int) pChild));
    auto *pContactItem = new ContactItem(ui->treeWidget);
    pContactItem->setAvatarPixmap(getRoundImage(QPixmap(":/assets/avatar.bmp"),
                                                pix, pContactItem->getAvatarSize()));
    pContactItem->setUserName(deps);
    pRootGroupItem->addChild(pChild);
    ui->treeWidget->setItemWidget(pChild, 0, pContactItem);

    mGroupMap.insert(pChild, deps);
}

// 点击联系人 Item
void MainWindow::onItemClicked(QTreeWidgetItem *item, int) {
    bool isChild = item->data(0, Qt::UserRole).toBool();
    if (!isChild) {
        item->setExpanded(!item->isExpanded());
    }
}

// 展开联系人 Item
void MainWindow::onItemExpanded(QTreeWidgetItem *item) {
    bool isChild = item->data(0, Qt::UserRole).toBool();
    if (!isChild) {
        auto *pRootItem = dynamic_cast<RootContactItem *>(ui->treeWidget->itemWidget(item, 0));
        if (pRootItem) {
            pRootItem->setExpanded(true);
        }
    }
}

// 收缩联系人 Item
void MainWindow::onItemCollapsed(QTreeWidgetItem *item) {
    bool isChild = item->data(0, Qt::UserRole).toBool();
    if (!isChild) {
        auto *pRootItem = dynamic_cast<RootContactItem *>(ui->treeWidget->itemWidget(item, 0));
        if (pRootItem) {
            pRootItem->setExpanded(false);
        }
    }
}

// 双击联系人 Item
void MainWindow::onItemDoubleClicked(QTreeWidgetItem *item, int) {
    bool isChild = item->data(0, Qt::UserRole).toBool();
    if (isChild) {
        // WindowManger::getInstance()->addNewTalkWindow(item->data(0,Qt::UserRole + 1).toString());
        QString group = mGroupMap.value(item);
        if (group == "技术部") {
            WindowManger::getInstance()->addNewTalkWindow(item->data(0, Qt::UserRole + 1).toString());
        } else if (group == "运营部") {

        } else if (group == "市场部") {

        } else {

        }
    }
}