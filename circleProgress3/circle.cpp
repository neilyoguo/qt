#include "circle.h"
#include <QPainter>



Circle::Circle(QWidget *parent) : QWidget(parent)
{

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this , SLOT(updateSin()));

    timer->start(100);
}
void Circle::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    //将绘制限制在指定的剪辑路径内部，本次为圆内
    QPainterPath cliPath;

    cliPath.addEllipse(this->rect().center(),height()/2- amplitude,height()/2- amplitude);

    painter.setClipPath(cliPath);

    QPainterPath path;


    for(int i = 0 ;i < width() ; i++)
    {
        if(i == 0)
        {
            path.moveTo(i,amplitude * sin(4*3.14/width()*i+ sin_offset) + (height()- m_offset));
        }
        else
        {
            path.lineTo(i,amplitude * sin(4*3.14/width()*i+ sin_offset) + (height()- m_offset));
        }
    }

    //连接右小脚
    path.lineTo(this->rect().bottomRight());
    //连接做下脚
    path.lineTo(this->rect().bottomLeft());
    //将左下角和第一个点连接
    path.closeSubpath();

    painter.setPen(Qt::NoPen);
    //海水颜色
    QColor col(40,150,200);
    painter.setBrush(col);
    painter.drawPath(path);


    painter.setPen(Qt::red);
    painter.setBrush(Qt::NoBrush);
    //画圆， 半径为高度一半减去波峰的值
    painter.drawEllipse(this->rect().center(),height()/2 - amplitude,height()/2 - amplitude );

    QFont font;
    font.setPixelSize(width()/10);
    painter.setFont(font);
    painter.drawText(this->rect(),Qt::AlignCenter, m_value);

}

void Circle::updateSin()
{
    sin_offset += 5;
    if(sin_offset > width())
        sin_offset = 0;
    update();
}
void Circle::setValue(int value)
{
    if(value > 100)
    {
        value = 100;
    }
    m_offset = height()/100 * 1.0 * value;
    QString str = QString::number(value);
    m_value = str + "%";
}

void Circle::setAmplitude(int value)
{
    amplitude = value;
}

void Circle::setFrequency(int value)
{
    timer->stop();
    timer->start(value);
}
