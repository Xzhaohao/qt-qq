#ifndef __SEND_FILE_H
#define __SEND_FILE_H

#include "../base/baseWindow.h"
#include "../../manger/windowManger.h"
#include "ui_sendFile.h"
#include <QFileDialog>

class SendFile : public BaseWindow {
Q_OBJECT

public:
    explicit SendFile(QWidget *parent = nullptr);

    ~SendFile() override;

signals:

    // 发送文件发射的信号
    void sendFileClicked(QString &, int &msgType, QString flieName);

private slots:

    void on_openBtn_clicked();

    void on_sendBtn_clicked();

private:
    Ui::SendFile ui;

    // 文件路径
    QString m_filePath;
};

#endif // __SEND_FILE_H
