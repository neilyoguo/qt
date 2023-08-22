#ifndef CIRCLE_H
#define CIRCLE_H

#include <QWidget>
#include <QTimer>

class Circle : public QWidget
{
    Q_OBJECT
public:
    explicit Circle(QWidget *parent = nullptr);

signals:
protected:
    void paintEvent(QPaintEvent *event) override;
private slots:
    void updateSin();
public:
    void setValue(int value);
    void setAmplitude(int value);
    void setFrequency(int value);
private:
    QString m_value;
    int m_offset = 0;
    int sin_offset = 0;
    QTimer *timer ;

    int amplitude = 20;
    int frequency = 20;
};

#endif // CIRCLE_H
