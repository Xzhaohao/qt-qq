#ifndef __LOGIN_H
#define __LOGIN_H

#include "ui_login.h"
#include "../base/baseWindow.h"

class Login : public BaseWindow {
Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);

    ~Login() override;

private:
    Ui::Login *ui;
};

#endif // __LOGIN_H
