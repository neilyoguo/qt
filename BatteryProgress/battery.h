#ifndef BATTERY_H
#define BATTERY_H

#include <QWidget>

class Battery : public QWidget
{
    Q_OBJECT
public:
    explicit Battery(QWidget *parent = nullptr);

signals:

protected:
    void paintEvent(QPaintEvent *event) override;
public:
    void setValue(int value);
private:
    int m_offset;
    int m_value = 100;
    QString str_value;

};

#endif // BATTERY_H
