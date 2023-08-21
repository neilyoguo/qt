#include "circle.h"
#include <QPainter>
Circle::Circle(QWidget *parent) : QWidget(parent)
{

}

void Circle::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::red);
    painter.drawEllipse(this->rect());


    painter.setBrush(Qt::green);
    //一圈是 360 *16 度， 逆时针为正值，顺时针为负值 ，
    //12点钟方向为 90 *16；3点钟方向 要偏移90，就是 -90*16
    painter.drawPie(this->rect(),90*16,-m_offset*16);

    //绘制文本
    painter.setPen(QPen(Qt::black));
    QFont font;
    font.setPixelSize(width()/10);
    painter.setFont(font);

    painter.drawText(this->rect(),Qt::AlignCenter,m_value);
}



void Circle::setValue(int value)
{
    if(value > 100)
    {
        value = 100;
    }
    m_offset = value * 360/100 * 1.0;
    QString str = QString::number(value);
    m_value = str + "%";
    update();
}
