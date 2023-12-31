#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rectangle.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    rectangle * rc = new rectangle(this);
    rc->SetRange(100);
    rc->resize(400, 50);
    rc->move(100,100);


    QTimer *m_timer = new QTimer();
    m_timer->start(100);

    connect(m_timer, &QTimer::timeout,this,[=]()
    {
       rc->setValue(count++);
       if(count > 1000)
           m_timer->stop();
    });


}

MainWindow::~MainWindow()
{
    delete ui;
}

