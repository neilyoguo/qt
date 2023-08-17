#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "battery.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Battery * bat = new Battery(this);
    bat->resize(100,40);
    bat->move(100,100);
    QTimer *m_timer = new QTimer();
    m_timer->start(100);

    connect(m_timer, &QTimer::timeout,this,[=]()
    {
       bat->setValue(count-- );
       if(count < 0)
           m_timer->stop();
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

