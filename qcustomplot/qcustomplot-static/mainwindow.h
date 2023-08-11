#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"


class myCustomplot:public QCustomPlot
{
public:
    myCustomplot()
    {
        // 创建 QLabel 并设置样式
        label = new QLabel(this);
        label->setStyleSheet("background-color: white; border: 1px solid black; padding: 2px;");
        label->hide();
    }

protected:
    void mouseMoveEvent(QMouseEvent *event) override
    {

         if( this->graphCount() <= 0)
         {
             label->hide();
             return ;
         }

         // 获取鼠标所在点的坐标
         double x = this->xAxis->pixelToCoord(event->pos().x());

         // 查找最接近鼠标位置的数据点
         double distance = std::numeric_limits<double>::max();
         double closest_y = 0.0;
         double closest_x = 0.0;
         QString name;

         //只找与第一条线接近的点，找到后，根据第一条线的x轴获取其他线对应值

         QCPGraph *graph = this->graph(0);
         if(this->graph(0)->dataCount() == 0)
         {
            label->hide();
            return;
         }

         QCPGraphDataContainer::const_iterator it = graph->data()->findBegin(x);
         while (it != graph->data()->end())
         {
             double dataX = it->key;
             double dataY = it->value;
             double currentDistance = qAbs(x - dataX);
             if (currentDistance < distance)
             {
                 name = graph->name();
                 distance = currentDistance;
                 closest_y = dataY;
                 closest_x = dataX;
             }
             ++it;
         }
         QString strToolTip = QString("%1 \nx=%2 y=%3\n").arg(name).arg(closest_x).arg(closest_y);
         //找其他线的值
         for(int t = 1 ;t < this->graphCount();t++)
         {
             auto data = this->graph(t)->data()->at(closest_x);
             if (data)
             {
                 double y = data->value; // 获取 y 值
                 name = this->graph(t)->name();
                 strToolTip = strToolTip + QString("%1 \nx=%2 y=%3").arg(name).arg(closest_x).arg(y);
             }

         }
        QPoint labelPos = event->pos() + QPoint(15, 15);
        label->move(labelPos);
        label->setText(strToolTip);
        label->show();
        //保留父类的默认行为,父类事件不会失效
        QCustomPlot::mouseMoveEvent(event);
    }
private:
    QLabel *label;

};


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
private slots:
    void ShowMenu(const QPoint &pos);
    void test();
    void clear();
    void reset();

public:
    void AddPoint(QString name , double x , double y);
    void AddPoint(QString name, QVector<double> &x, QVector<double> &y);
    void AddSeries(QString series, Qt::GlobalColor color);

private:
    QCustomPlot *chart;
    void createView();
    bool x_isTime;
    QMap<QString ,QCPGraph*> m_series;
    int pen_count;
    QTimer m_timer;
    QLabel label;

};
#endif // MAINWINDOW_H
