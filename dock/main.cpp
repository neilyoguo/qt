#include "mainwindow.h"

#include <QApplication>

#include <QStyleFactory>
#include <QStyle>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


   // auto t = QStyleFactory::keys();
    // Windows   windowsvista  Fusion
    //设置界面风格
    QApplication::setStyle(QStyleFactory::create("Windows"));
    // 设置应用程序的默认字体
    QFont font("微软雅黑", 10);
    a.setFont(font);

    MainWindow w;
    w.setWindowIcon(QIcon(":/images/images/logo.ico"));
    w.show();
    return a.exec();
}
