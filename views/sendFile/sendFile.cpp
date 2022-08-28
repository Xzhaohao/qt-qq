#include "sendFile.h"

SendFile::SendFile(QWidget *parent) : BaseWindow(parent), m_filePath("") {
    ui.setupUi(this);
    // 资源回收
    setAttribute(Qt::WA_DeleteOnClose);
    initTitleBar();
    setTitleBarTitle("", ":/assets/qqlogoclassic.png");
    loadStyleSheet("sendFile");
    this->move(100, 400);

    auto *talkWindowShell = WindowManger::getInstance()->getTalkWindowShell();

    connect(this, &SendFile::sendFileClicked, talkWindowShell, &TalkWindowShell::updateSendTcpMsg);
}

SendFile::~SendFile() = default;

void SendFile::on_openBtn_clicked() {
    m_filePath = QFileDialog::getOpenFileName(this, "选择文件", "/", "发送的文件(*.txt *.doc);;所有文件(*.*);;");
    ui.lineEdit->setText(m_filePath);
}

void SendFile::on_sendBtn_clicked() {
    if (!m_filePath.isEmpty()) {
        QFile file(m_filePath);
        if (file.open(QIODevice::ReadOnly)) {
            int msgType = 2;
            QString str = file.readAll();

            // 文件名称
            QFileInfo fileInfo(m_filePath);
            QString fileName = fileInfo.fileName();
            emit sendFileClicked(str, msgType, fileName);
            file.close();
        } else {
            QMessageBox::information(this, "提示", QString("读取文件:%1失败!").arg(m_filePath));
            return;
        }
        m_filePath.clear();
        this->close();
    }
}
