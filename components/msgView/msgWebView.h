#ifndef QQ_MSG_WEB_VIEW_H
#define QQ_MSG_WEB_VIEW_H

#include <QWebEngineView>
#include <QDomNode>
#include <QFile>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include <QWebChannel>
#include <QSqlQueryModel>

// 信息网页对象，用于发送信息的对象，和网页交互的必须成员
class MsgHtmlObj : public QObject {
Q_OBJECT

    Q_PROPERTY(QString msgLHtmlTmpl MEMBER m_msgLHtmlTmpl NOTIFY signalMsgHtml)   // 左动态属性 // 别人发的信息
    Q_PROPERTY(QString msgRHtmlTmpl MEMBER m_msgRHtmlTmpl NOTIFY signalMsgHtml)   // 右动态属性 // 自己发的信息
public:
    explicit MsgHtmlObj(QObject *parent, QString msgLPicPath = "");

signals:

    void signalMsgHtml(const QString &html);

private:
    // 初始化聊天网页
    void initHtmlTmpl();

    // 获取信息网
    QString getMsgTmplHtml(const QString &code);

private:
    QString m_msgLHtmlTmpl; // 别人发的信息
    QString m_msgRHtmlTmpl; // 自己发的信息
    QString m_msgPicPath;    // 图片路径
};


// 信息网页记录
class MsgWebPage : public QWebEnginePage {
Q_OBJECT

public:
    explicit MsgWebPage(QObject *parent = nullptr) : QWebEnginePage(parent) {}

protected:
    bool acceptNavigationRequest(const QUrl &url, NavigationType type, bool isMainFrame);
};

/**
 * 显示网页内容
 */
class MsgWebView : public QWebEngineView {
Q_OBJECT

public:
    explicit MsgWebView(QWidget *parent);

    ~MsgWebView() override;

    void appendMsg(const QString &html, QString strObj = "0");

private:
    // 解析，用于提取用户发来的表情和信息
    QList<QStringList> parseHtml(const QString &html);

    // Qt 中所有dom节点都可以使用DOM 进行操作
    QList<QStringList> parseDocNode(const QDomNode &node);

signals:

    void signalSendMsg(QString &strData, int &msgType, QString sFile = "");

private:
    MsgHtmlObj *m_msgHtmlObj;
    QWebChannel *m_channel;    // 网络通道
};

#endif // QQ_MSG_WEB_VIEW_H
