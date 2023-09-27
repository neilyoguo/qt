#include "qqdrawer.h"
#include "ui_qqdrawer.h"
#include "tools.h"
qqDrawer::qqDrawer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::qqDrawer)
{
    ui->setupUi(this);
    init();
}

qqDrawer::~qqDrawer()
{
    delete ui;
}

void qqDrawer::init()
{
    ui->verticalLayout ->setContentsMargins(0, 0, 0, 0);
    ui->verticalLayout->setSpacing(0);
    // 添加一个可伸缩的空间 使控件显示在布局顶端
    ui->verticalLayout->addStretch();



    ui->scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    // 设置QScrollArea的属性，显示垂直滚动条
    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);


    //将scrollarea放入布局，使其自适应dock
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(ui->scrollArea);









    //初始化按钮
    ui->bt_1->setIcon(svgIcon(":/images/images/方向-向右.svg"));
    ui->bt_2->setIcon(svgIcon(":/images/images/方向-向右.svg"));
    ui->bt_3->setIcon(svgIcon(":/images/images/方向-向右.svg"));
    ui->bt_4->setIcon(svgIcon(":/images/images/方向-向右.svg"));
    //
    QString style = "QPushButton {border: 2px solid #8f8f91;text-align: left;}";
    ui->bt_1->setStyleSheet(style);
    ui->bt_2->setStyleSheet(style);
    ui->bt_3->setStyleSheet(style);
    ui->bt_4->setStyleSheet(style);
    ui->bt_1->setText("1");
    ui->bt_2->setText("2");
    ui->bt_3->setText("3");
    ui->bt_4->setText("4");
    ui->tb_1->hide();
    ui->tb_2->hide();
    ui->tb_3->hide();
    ui->tb_4->hide();
}



void qqDrawer::on_bt_1_clicked()
{
    if(bt_1_show)
    {
        ui->tb_1->show();
        ui->bt_1->setIcon(svgIcon(":/images/images/方向-向下.svg"));
        bt_1_show = false;
    }
    else
    {
        ui->tb_1->hide();
        ui->bt_1->setIcon(svgIcon(":/images/images/方向-向右.svg"));
        bt_1_show = true;
    }
}


void qqDrawer::on_bt_2_clicked()
{
    if(bt_2_show)
    {
        ui->tb_2->show();
        ui->bt_2->setIcon(svgIcon(":/images/images/方向-向下.svg"));
        bt_2_show = false;
    }
    else
    {
        ui->tb_2->hide();
        ui->bt_2->setIcon(svgIcon(":/images/images/方向-向右.svg"));
        bt_2_show = true;
    }
}


void qqDrawer::on_bt_3_clicked()
{
    if(bt_3_show)
    {
        ui->tb_3->show();
        ui->bt_3->setIcon(svgIcon(":/images/images/方向-向下.svg"));
        bt_3_show = false;
    }
    else
    {
        ui->tb_3->hide();
        ui->bt_3->setIcon(svgIcon(":/images/images/方向-向右.svg"));
        bt_3_show = true;
    }
}


void qqDrawer::on_bt_4_clicked()
{
    if(bt_4_show)
    {
        ui->tb_4->show();
        ui->bt_4->setIcon(svgIcon(":/images/images/方向-向下.svg"));
        bt_4_show = false;
    }
    else
    {
        ui->tb_4->hide();
        ui->bt_4->setIcon(svgIcon(":/images/images/方向-向右.svg"));
        bt_4_show = true;
    }
}

