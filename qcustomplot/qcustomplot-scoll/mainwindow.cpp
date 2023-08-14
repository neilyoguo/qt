#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    x_isTime = false;
    createView();
    this->setCentralWidget(chart);
    connect(&m_timer , SIGNAL(timeout()),this ,SLOT(test()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::createView()
{
    chart = new myCustomplot();
    //设置范围

    //设置x轴有20个坐标
    if(x_isTime)
    {
        QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);//日期做X轴
        dateTicker->setDateTimeFormat("mm:ss");
        dateTicker->setTickCount(10);
        chart->xAxis->setTicker(dateTicker);//设置X轴为时间轴
    }
    chart->xAxis->setRange(0,100);
    chart->yAxis->setRange(0,30);
    // 支持鼠标拖拽轴、滚动缩放，左键点选图层
    chart->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    //启用自定义上下文菜单策略,用户右键点击控件时弹出的菜单
    chart->setContextMenuPolicy(Qt::CustomContextMenu);



    //链接槽函数
    connect(chart, &QCustomPlot::customContextMenuRequested, this,&MainWindow::ShowMenu);


    AddSeries("test1",Qt::red);
    m_timer.start(1000);

}

void MainWindow::AddSeries(QString name,Qt::GlobalColor color)
{
    if(m_series.find(name) == m_series.end())
    {
        auto series = chart->addGraph();
        series->setPen(QPen(color));
        series->setName(name);
        chart->legend->setVisible(true);
        m_series.insert(name,series);
        pen_count++;
    }
}

void MainWindow::AddPoint(QString name, double x, double y)
{

    if(m_series.find(name) != m_series.end())
    {
       m_series[name]->addData(x, y);
    }

    int count = chart->graph(0)->dataCount();
    if(count > 100)
    {
        // 移除第一个点
        double firstX = chart->graph(0)->data()->at(0)->key;
        chart->graph(0)->data()->remove(firstX);
        // 更新x轴范围，实现滚动效果
        chart->xAxis->moveRange(+1);
    }

    chart->replot();
}

void MainWindow::AddPoint(QString name, QVector<double> &x, QVector<double> &y)
{
    if(m_series.find(name) != m_series.end())
    {
       m_series[name]->setData(x, y);
    }
    chart->replot();
}
void MainWindow::ShowMenu(const QPoint &pos)
{
    Q_UNUSED(pos);
    QMenu * menu = new QMenu();
    QAction *act_reset = menu->addAction("自动调整");
    QAction *act_clear = menu->addAction("清理");

    connect(act_clear, SIGNAL(triggered()), this, SLOT(clear()));
    connect(act_reset, SIGNAL(triggered()), this, SLOT(reset()));
    menu->exec(QCursor::pos());
}




void MainWindow::test()
{
    static int  x1  = 0;
    QRandomGenerator *generator = QRandomGenerator::global();
    int num = generator->bounded(20);
    AddPoint("test1",x1,num);
    num = generator->bounded(20);
    AddPoint("test2",x1,num);
    x1++;
}

void MainWindow::clear()
{
    chart->clearGraphs();
    chart->replot();
}
void MainWindow::reset()
{
    chart->rescaleAxes();
    chart->replot();
}
