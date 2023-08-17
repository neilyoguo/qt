#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <QWidget>

class rectangle : public QWidget
{
    Q_OBJECT
public:
    explicit rectangle(QWidget *parent = nullptr);

    void setValue(int newValue);

signals:

protected:
    void paintEvent(QPaintEvent *event) override;
private:
    QString m_value;
    int m_max;
    int m_offset;
public:
    void SetRange(int max);

};

#endif // RECTANGLE_H
