#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QtCharts>
#include <QtCharts/QValueAxis>
#include <QDateTime>
QT_CHARTS_USE_NAMESPACE


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE





class CustomChartView : public QChartView
{
public:
    CustomChartView(QChart *chart, QWidget *parent = nullptr)
        : QChartView(chart, parent)
    {
        setMouseTracking(true);
        CreateLabel();

    }

protected:
    void mouseMoveEvent(QMouseEvent *event) override
    {
        // 获取鼠标事件的位置
         QPoint pos = event->pos();
        // 获取 QChart 对象
        QChart *chart = this->chart();
        // 检查鼠标位置是否在图表的绘图区域内
        if (!chart->plotArea().contains(event->pos()))
        {
            return;
        }

        // 获取 QAbstractSeries 对象
        QList<QAbstractSeries *> seriesList = chart->series();
        if(!seriesList.empty())
        {
            QPointF value = chart->mapToValue(pos, seriesList.at(0));
            // 更新 QLabel 的位置并显示
            QPoint labelPos = event->pos() + QPoint(15, 15);
            label->move(labelPos);
            label->setText(QString("Values: (%1, %2)").arg(value.x()).arg(value.y()));
            label->show();
        }
        //进行拖拽
        if (event->buttons() & Qt::LeftButton)
        {
            QPoint delta = event->pos() - m_lastPos;
            chart->scroll(-delta.x(), delta.y());
            m_lastPos = event->pos();
        }
        QChartView::mouseMoveEvent(event);
    }
    void wheelEvent(QWheelEvent *event) override
    {
        // 获取 QChart 对象
        QChart *chart = this->chart();

        // 判断滚轮方向并执行相应的缩放操作

        // 设置缩放因子 放大或者缩小一格

        if (event->angleDelta().y() > 0)
        {
            //放大
            chart->zoom(1.1);
        }
        else
        {
            // 缩小
            chart->zoom(0.9);
        }

        // 更新视口
        QChartView::wheelEvent(event);
    }
    void mousePressEvent(QMouseEvent *event) override
    {
        if (event->button() == Qt::LeftButton)
        {
            m_lastPos = event->pos();
        }

        QChartView::mousePressEvent(event);
    }

private:
    void CreateLabel()
    {
        // 创建 QLabel 并设置样式
        label = new QLabel(this);
        label->setStyleSheet("background-color: white; border: 1px solid black; padding: 2px;");
        label->hide();
    }
private:
    QLabel *label;
    QPoint m_lastPos;
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
private slots:
    void AddPoint();

private:
    QChartView *chartView;
    QChart *chart;
    QValueAxis *axisX;
    QLineSeries *series;
    QTimer m_timer;
    int m_count;

public:
    void CreatChart();
};

#endif // MAINWINDOW_H
