#include "busboard.h"
#include <QDebug>
BusBoard::BusBoard(QWidget *parent) : QWidget(parent)
{

}

void BusBoard::paintEvent(QPaintEvent *event)
{


    painter = new QPainter(this);
    painter->setRenderHint(QPainter::Antialiasing);
    drawMaxCircle(painter);
    drawMinCircle(painter);
    drawLine(painter);
    drawTxt(painter);
    drawSpeed(painter);
    drawPoint(painter);
}

void BusBoard::drawMaxCircle(QPainter *painter)
{
    painter->save();
    //画大圆，设置渐变色
    painter->setPen(Qt::NoPen);
    //设置渐变色k
    QRadialGradient radialGradient(width()/2,height()/2,width()/2);
    radialGradient.setColorAt(1,QColor(0,82,199));
    radialGradient.setColorAt(0.9,Qt::transparent);
    //设置画刷
    painter->setBrush(radialGradient);
    painter->drawEllipse(this->rect());
    painter->restore();
}

void BusBoard::drawMinCircle(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    //小圆半径为大圆半径的90/100；
    QRect min_rect = this->rect().adjusted(0.05*width(),0.05*height(),-0.05*width(),-0.05*height());
    painter->setBrush(QColor(0, 36, 72));
    painter->drawEllipse(min_rect);
    painter->restore();
}

void BusBoard::drawLine(QPainter *painter)
{

    painter->save();
    //画刻度线 0 ~ 240

    //将坐标轴原点放到圆心处
    painter->translate(width()/2,height()/2);

    //画刻度线 13个长线，48个个短线，
    int line_count = 61;
    //每个刻度的角度
    double angle = 240*1.0/60;

    //旋转坐标轴60度  y轴就是0的位置
    painter->rotate(60);
    for(int t = 0; t < line_count; t++)
    {
        if(t < 40)
        {
          painter->setPen(Qt::white);
        }
        else
        {
          painter->setPen(Qt::red);
        }

        //每5条线一个长线
        if(t % 5 == 0)
        {
            painter->drawLine(0,0.90 * (height()/2),0,0.70 * (height()/2));
        }
        else
        {

            painter->drawLine(0,0.90 * (height()/2),0,0.80 * (height()/2));
        }
        painter->rotate(angle);

    }
    painter->restore();
}

void BusBoard::drawTxt(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::red);
    //每个长刻度
    double angle = 240*1.0/60 *5;
    painter->setPen(QColor(255,255,255));
    QFont font;
    font.setFamily("Arial");
    font.setPointSize(10);
    font.setBold(true);
    painter->setFont(font);

    //将坐标轴原点放到圆心处
    painter->translate(width()/2,height()/2);
    //旋转坐标轴150度  x轴就是0的位置
    painter->rotate(150);
    for(int i=0;i<13;++i)
    {
        if(i == 0)
        {
           painter->drawText(0.62 * (width()/2),4,QString::number(i*20));
        }
        //将100前面的刻度值旋转
        else if(i<6 && i !=0)
        {
            painter->save();
            painter->rotate(180);
            painter->drawText(-0.68 * (width()/2),4,QString::number(i*20));
            painter->restore();
        }
        else
        {
            painter->drawText(0.58 * (width()/2),4,QString::number(i*20));
        }


        painter->rotate(angle);
    }
    //还原画笔
    painter->setPen(Qt::NoPen);
    painter->restore();
}
void BusBoard::drawSpeed(QPainter *painter)
{
    painter->save();
    painter->setPen(QColor(255,255,255));
    QFont font;
    font.setFamily("Arial");
    font.setPointSize(45);
    font.setBold(true);
    painter->setFont(font);
    painter->drawText(this->rect(),Qt::AlignCenter,QString::number(m_value));
    font.setPointSize(15);
    painter->setFont(font);
    painter->drawText(this->rect().x(), this->rect().y()+50, width(), height(),Qt::AlignCenter,QString("km/h"));
    painter->restore();
}

void BusBoard::drawPoint(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    painter->setBrush(Qt::red);

    //将坐标轴原点放到圆心处
    painter->translate(width()/2,height()/2);
    //旋转坐标轴150度  x轴就是0的位置
    painter->rotate(150 + m_value);
    static const QPointF points[3] = {
        QPointF(0.58 * (width()/2), 0),
        QPointF(0.25 * (width()/2), -5),
        QPointF(0.25 * (width()/2), 5),
    };
    painter->drawPolygon(points,3); //绘制指针
    painter->restore();
}

void BusBoard::setValue(int value)
{
    m_value = value;
    update();

}
