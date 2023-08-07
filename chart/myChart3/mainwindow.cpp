#include "mainwindow.h"
#include "ui_mainwindow.h"



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
    this->setCentralWidget(chartView);


    // 创建x轴QValueAxis实例
    axisX = new QValueAxis();
    axisX->setRange(0, 20); // 设置范围
    axisX->setTickCount(20);
    //axisX->setLabelFormat("%d"); // 设置标签格式
    chart->addAxis(axisX, Qt::AlignBottom);

    // 创建y轴QValueAxis实例
    QValueAxis *yAxis = new QValueAxis;
    yAxis->setRange(0, 20); // 设置范围
    yAxis->setTickCount(20);
    //yAxis->setLabelFormat("%d"); // 设置标签格式
    yAxis->setGridLineVisible(true); // 显示网格线
    // 将y轴添加到chart中
    chart->addAxis(yAxis, Qt::AlignLeft);
    // 在chart上绘制数据
    series = new QSplineSeries();
    series->setName("line1");
    chart->addSeries(series);
    // 将series与x轴和y轴关联
    series->attachAxis(axisX);
    series->attachAxis(yAxis);

    m_timer.start(1000);
}


void MainWindow::AddPoint()
{
    //是否替换第一个点
    int tickCount = axisX->tickCount();

    if (series->count() > tickCount)
    {
        series->remove(0);
        for (int i = 0; i < series->count(); i++)
        {
            QPointF point = series->at(i);
            point.setX(i);
            series->replace(i, point);
        }
    }
    // 获取全局的随机数生成器对象
    QRandomGenerator *generator = QRandomGenerator::global();

    // 生成介于0和20之间的随机数
    int num = generator->bounded(20);

    series->append(series->count(), num);


}



