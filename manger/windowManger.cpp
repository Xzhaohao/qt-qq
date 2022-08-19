#include "windowManger.h"

// 单例模式，创建全局静态对象
Q_GLOBAL_STATIC(WindowManger, theInstance)

WindowManger::WindowManger() : QObject(nullptr), mTalkWindowShell(nullptr) {
}

WindowManger::~WindowManger() = default;

QWidget *WindowManger::findWindowName(const QString &qsWindowName) {
    if (!mWindowMap.contains(qsWindowName)) return nullptr;
    return mWindowMap.value(qsWindowName);
}

void WindowManger::deleteWindowName(const QString &qsWindowName) {
    mWindowMap.remove(qsWindowName);
}

void WindowManger::addWindowName(const QString &qsWindowName, QWidget *qWidget) {
    if (!mWindowMap.contains(qsWindowName)) mWindowMap.insert(qsWindowName, qWidget);
}

WindowManger *WindowManger::getInstance() {
    return theInstance;
}

TalkWindowShell *WindowManger::getTalkWindowShell() {
    return mTalkWindowShell;
}

QString WindowManger::getCreatingTalkId() {
    return mStrCreatingTalkId;
}

void WindowManger::addNewTalkWindow(const QString &uid) {
    if (mTalkWindowShell == nullptr) {
        mTalkWindowShell = new TalkWindowShell;
        connect(mTalkWindowShell, &TalkWindowShell::destroyed, [this](QObject *) {
            mTalkWindowShell = nullptr;
        });
    }

    QWidget *widget = findWindowName(uid);
    if (!widget) {
        mStrCreatingTalkId = uid;
        auto *talkWindow = new TalkWindow(mTalkWindowShell, uid);
        auto *talkWindowItem = new TalkWindowItem(talkWindow);
        mStrCreatingTalkId = "";

        // 判断群聊还是单聊
        QSqlQueryModel sqlDepModel;
        QString strSql = QString("SELECT department_name,sign FROM tab_department WHERE departmentID=%1").arg(uid);
        sqlDepModel.setQuery(strSql);
        int rows = sqlDepModel.rowCount();
        QString strWindowName, strMsgLabel;
        if (rows == 0) { // 单聊
            QString sql = QString("SELECT employee_name,employee_sign FROM tab_employees WHERE employeeID=%1").arg(uid);
            sqlDepModel.setQuery(sql);
        }
        QModelIndex indexDepIndex, signIndex;
        indexDepIndex = sqlDepModel.index(0, 0);
        signIndex = sqlDepModel.index(0, 1);
        strWindowName = sqlDepModel.data(signIndex).toString();
        strMsgLabel = sqlDepModel.data(indexDepIndex).toString();

        talkWindow->setWindowName(strWindowName);           // 窗口名称
        talkWindowItem->setMsgLabelContent(strMsgLabel);    // 左侧联系人文本显示
        mTalkWindowShell->addTalkWindow(talkWindow, talkWindowItem, uid);
    } else { // 窗口已存在
        // 左侧设置为选中
        QListWidgetItem *item = mTalkWindowShell->getTalkWindowItemMap().key(widget);
        item->setSelected(true);

        // 右侧设置为选中
        mTalkWindowShell->setCurrentWidget(widget);
    }
    mTalkWindowShell->show();
    mTalkWindowShell->activateWindow();
}
