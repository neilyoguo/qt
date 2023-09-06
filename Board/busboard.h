#ifndef BUSBOARD_H
#define BUSBOARD_H

#include <QWidget>
#include <QPainter>


class BusBoard : public QWidget
{
    Q_OBJECT
public:
    explicit BusBoard(QWidget *parent = nullptr);

signals:
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    QPainter *painter;
    void drawMaxCircle(QPainter *painter);
    void drawMinCircle(QPainter *painter);
    void drawLine(QPainter *painter);
    void drawTxt(QPainter *painter);
    void drawSpeed(QPainter *painter);
    void drawPoint(QPainter *painter);
    int m_value = 0;
public:
    void setValue(int value);

};

#endif // BUSBOARD_H
