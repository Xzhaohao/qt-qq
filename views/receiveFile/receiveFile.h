#ifndef QQ_RECEIVE_FILE_H
#define QQ_RECEIVE_FILE_H

#include "../base/baseWindow.h"
#include "ui_receiveFile.h"
#include <QMessageBox>
#include <QFileDialog>

class ReceiveFile : public BaseWindow {
Q_OBJECT

public:
    explicit ReceiveFile(QWidget *parent = nullptr);

    ~ReceiveFile() override;

    void setMsg(QString &msgLabel);

signals:

    void refuseFile();

private slots:

    void on_cancelBtn_clicked();

    void on_okBtn_clicked();

private:
    Ui::ReceiveFile ui{};
};

#endif // QQ_RECEIVE_FILE_H
