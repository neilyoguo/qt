#include "mainwindow.h"
#include "ui_mainwindow.h"


#define X_RANGE 20
#define X_COUNT 20


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    CreatChart();
    m_count = 0;
    connect(&m_timer,SIGNAL(timeout()),this,SLOT(AddPoint()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::CreatChart()
{
    chart = new QChart();
    //设置chart背景
    chart->setTitle("动态波形图");//设置标题
    chart->setTheme(QChart::ChartThemeQt);
    chartView = new CustomChartView(chart);
   // chartView->setChart(chart);
    this->setCentralWidget(chartView);


    // 创建x轴QValueAxis实例
    axisX = new QValueAxis();
    axisX->setRange(0, X_RANGE); // 设置范围
    axisX->setTickCount(X_COUNT);
    axisX->setLabelFormat("%d"); // 设置标签格式
    chart->addAxis(axisX, Qt::AlignBottom);

    // 创建y轴QValueAxis实例
    QValueAxis *yAxis = new QValueAxis;
    yAxis->setRange(0, 20); // 设置范围
    yAxis->setTickCount(20);
    yAxis->setLabelFormat("%d"); // 设置标签格式
    yAxis->setGridLineVisible(true); // 显示网格线
    // 将y轴添加到chart中
    chart->addAxis(yAxis, Qt::AlignLeft);
    // 在chart上绘制数据
    series = new QLineSeries();
    series->setName("line1");
    chart->addSeries(series);
    // 将series与x轴和y轴关联
    series->attachAxis(axisX);
    series->attachAxis(yAxis);


    m_timer.start(1000);
}


void MainWindow::AddPoint()
{
    //是否开始滚动
    if(series->count()> X_COUNT )
    {
        //求x轴滚动距离
        qreal x = chart->plotArea().width()/axisX->tickCount();
        chart->scroll(x/(X_COUNT/X_RANGE), 0);
        //移除第一个点
        series->removePoints(0,1);
    }
    //
    QRandomGenerator *ran1 = QRandomGenerator::global();
    int num = ran1->bounded(20);
    series->append(m_count, num);


    m_count++;
}
