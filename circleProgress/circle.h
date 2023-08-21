#ifndef CIRCLE_H
#define CIRCLE_H

#include <QWidget>

class Circle : public QWidget
{
    Q_OBJECT
public:
    explicit Circle(QWidget *parent = nullptr);

signals:
protected:
    void paintEvent(QPaintEvent *event) override;
public:
    void setValue(int value);
private:
    QString m_value;
    double m_offset;

};

#endif // CIRCLE_H
