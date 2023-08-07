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
    axisX->setRange(0, 100); // 设置范围
    axisX->setTickCount(100);
    axisX->setLabelsVisible(false); //隐藏坐标值
    //axisX->setLabelFormat("%d"); // 设置标签格式
    chart->addAxis(axisX, Qt::AlignBottom);

    // 创建y轴QValueAxis实例
    QValueAxis *yAxis = new QValueAxis;
    yAxis->setRange(-10, 50); // 设置范围
    yAxis->setTickCount(50);
    //yAxis->setLabelFormat("%d"); // 设置标签格式
    yAxis->setGridLineVisible(true); // 显示网格线
    yAxis->setLabelsVisible(false);
    // 将y轴添加到chart中
    chart->addAxis(yAxis, Qt::AlignLeft);
    // 在chart上绘制数据
    series = new QSplineSeries();
    series->setName("line1");
    chart->addSeries(series);
    // 将series与x轴和y轴关联
    series->attachAxis(axisX);
    series->attachAxis(yAxis);

    m_timer.start(30);
}


void MainWindow::AddPoint()
{
    static int count_pos = 0;
    // 获取全局的随机数生成器对象
    QRandomGenerator *generator = QRandomGenerator::global();

    // 生成介于0和2之间的随机数
    int num = generator->bounded(2);
    //心跳，每20个点跳动一下
    if(count_pos % 20 == 0)
    {
        num = generator->bounded(40,50);
    }


    //是否替换第一个点
    int tickCount = axisX->tickCount();



    if (series->count() > tickCount)
    {
        if(count_pos > tickCount-1)
            count_pos = 0;
        // 获取要更改的点
        QPointF point = series->points().at(count_pos);
        // 将其y值更改为所需值
        point.setY(num);
        // 更新数据集中的点
        series->replace(count_pos, point);


    }
    else
    {
        series->append(series->count(), num);
    }
    count_pos++;
}



