#include "circle.h"
#include <QPainter>
Circle::Circle(QWidget *parent) : QWidget(parent)
{

}



void Circle::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setPen(QPen(Qt::red));
    //画外面的大圆
    painter.drawEllipse(this->rect());

    painter.setBrush(Qt::blue);
    painter.drawPie(this->rect(), 90*16,-m_offset*16);
    //画里面的小圆,将背景刷为白色
    painter.setBrush(Qt::white);
    //像素点 起始点 往右 和往下，所以为正 ， 结束点往上和往左，所以为负
    QRect minRect = this->rect().adjusted(width()/10,height()/10,-width()/10,-height()/10);

    painter.drawEllipse(minRect);
    painter.setPen(QPen(Qt::black));
    QFont font;
    font.setPixelSize(minRect.width()/5);
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
