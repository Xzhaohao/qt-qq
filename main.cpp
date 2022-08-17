#include "views/main/mainWindow.h"
#include "views/login/login.h"

#include <QApplication>

int main(int argc, char *argv[]) {
#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QApplication a(argc, argv);
    Login w;
    w.show();
    return QApplication::exec();
}
