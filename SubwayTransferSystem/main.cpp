#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPixmap pixmap(":/icon/icon/splash2.png");
    QSplashScreen splash2(pixmap);//程序启动画面
    for(qint64 i=5555555;i>0;i--)
        splash2.show();

    MainWindow w;
    w.show();

    splash2.finish(&w);

    return a.exec();
}
