#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimer>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    rc = new Circle(this);
    rc->resize(400,400);
    rc->move(100,100);
    rc->setValue(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString str = ui->Edit_Value->text();
    bool ok;
    rc->setValue(str.toInt(&ok));
}


void MainWindow::on_pushButton_2_clicked()
{
    QString str = ui->Edit_Fre->text();
    bool ok;
    rc->setFrequency(str.toInt(&ok));
}


void MainWindow::on_pushButton_3_clicked()
{
    QString str = ui->Edit_Amp->text();
    bool ok;
    rc->setAmplitude(str.toInt(&ok));
}

