#ifndef __MAIN_WINDOW_H
#define __MAIN_WINDOW_H

#include "ui_mainWindow.h"
#include "mainProxyStyle.h"
#include "../base/baseWindow.h"

class MainWindow : public BaseWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

    void initControl();

private:
    Ui::MainWindow *ui;
};

#endif // __MAIN_WINDOW_H
