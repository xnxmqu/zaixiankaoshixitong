#include <QApplication>

#include "serverlogin.h"

int main(int argc, char* argv[]) {
    if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))  //设置屏幕自适应，不受高分辨率影响
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    ServerLogin w;
    w.show();

    return a.exec();
}
