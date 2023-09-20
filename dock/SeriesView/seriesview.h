#ifndef SERIESVIEW_H
#define SERIESVIEW_H

#include <QWidget>
#include "qcustomplot.h"
class SeriesView: public QWidget
{
    Q_OBJECT
public:
    explicit SeriesView(QWidget *parent = nullptr);


private slots:
    void ShowMenu(const QPoint &pos);
    void test();
    void clear();
    void reset();
    void start();
    void stop();
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

#endif // SERIESVIEW_H
