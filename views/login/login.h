#ifndef LOGIN_H
#define LOGIN_H

#include "ui_login.h"
#include "../base/baseWindow.h"
#include "../main/mainWindow.h"

class Login : public BaseWindow {
Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);

    ~Login() override;

private slots:

    void onLoginBtnClicked();

private:
    void initControl();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
