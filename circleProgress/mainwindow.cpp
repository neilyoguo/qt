#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "circle.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Circle * rc = new Circle(this);
    rc->resize(400, 400);
    rc->move(100,100);


    QTimer *m_timer = new QTimer();
    m_timer->start(100);

    connect(m_timer, &QTimer::timeout,this,[=]()
    {
       rc->setValue(count++);
       if(count > 100)
           m_timer->stop();
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

