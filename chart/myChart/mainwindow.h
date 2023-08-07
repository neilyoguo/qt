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
        // 获取 QChartView 对象
        QChartView *chartView = qobject_cast<QChartView *>(this);
        // 获取 QChart 对象
        QChart *chart = chartView->chart();
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
