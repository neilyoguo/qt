#include "battery.h"
#include <QPainter>
Battery::Battery(QWidget *parent) : QWidget(parent)
{

}

void Battery::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setBrush(Qt::white);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.drawRect(this->rect());


    if(m_value > 40)
    {
        painter.setBrush(Qt::green);
    }
    else if(m_value <= 40 && m_value >20)
    {
        painter.setBrush(Qt::yellow);
    }
    else
    {
        painter.setBrush(Qt::red);
    }
    painter.drawRect(this->rect().x(),this->rect().y(),m_offset,height());

    painter.setPen(Qt::black);

    //绘制文本
    painter.drawText(this->rect(),Qt::AlignCenter,str_value);

}

void Battery::setValue(int value)
{
    m_value = value;
    m_offset = (double)value / 100 * width();
    str_value = QString::number(value) + "%";
    update();
}
