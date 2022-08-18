#include "views/login/login.h"

#include <QApplication>

int main(int argc, char *argv[]) {
#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QApplication a(argc, argv);
    // 最后一个窗口关闭时程序不退出
    QApplication::setQuitOnLastWindowClosed(false);

    Login *login = new Login;
    login->show();

    return QApplication::exec();
}
