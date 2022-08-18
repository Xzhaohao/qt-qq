#include "mainWindow.h"

MainWindow::MainWindow(QWidget *parent) : BaseWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlags(windowFlags() | Qt::Tool);
    loadStyleSheet("mainWindow");
    initControl();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::initControl() {
    // 树获取焦点时不绘制边框
    ui->treeWidget->setStyle(new MainProxyStyle);
}
