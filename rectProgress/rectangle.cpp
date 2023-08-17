#include "rectangle.h"
#include <QPainter>
#include <QDebug>
rectangle::rectangle(QWidget *parent) : QWidget(parent)
{

    m_max = 0;
    m_offset = 0;
}

void rectangle::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);


    QPainter painter(this);
    painter.setBrush(Qt::gray);
    //启用抗锯齿
    painter.setRenderHint(QPainter::Antialiasing);

    //绘制长方形
    painter.drawRect(this->rect());

    //绘制渐变色
    QLinearGradient gradient(this->rect().x(), this->rect().y(), width(), height());
    gradient.setColorAt(0, Qt::green);
    gradient.setColorAt(1, Qt::red);
    painter.setBrush(gradient);
    painter.setPen(QPen(Qt::black));
    painter.drawRect(this->rect().x(),this->rect().y(),m_offset,this->rect().height());

    //绘制文本
    painter.drawText(this->rect(),Qt::AlignCenter,m_value);

}

void rectangle::SetRange(int max)
{
    m_max = max;
}

void rectangle::setValue(int newValue)
{
    if(newValue > m_max)
    {
        newValue = m_max;
    }
    m_offset = (double)newValue / m_max * width();
    double ret = (double)m_offset / width() *100;
    QString str = QString::number( ret,'f',2);
    m_value = str + "%";
    update();
}
