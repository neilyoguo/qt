#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    rc = new BusBoard(this);
    rc->resize(400,400);
    rc->move(100,100);
    ui->horizontalSlider->setRange(0,240);
    ui->horizontalSlider->setValue(0);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    rc->setValue(value);
}

