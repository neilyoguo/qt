#ifndef QQDRAWER_H
#define QQDRAWER_H

#include <QWidget>

namespace Ui {
class qqDrawer;
}

class qqDrawer : public QWidget
{
    Q_OBJECT

public:
    explicit qqDrawer(QWidget *parent = nullptr);
    ~qqDrawer();

private slots:

    void on_bt_1_clicked();

    void on_bt_2_clicked();

    void on_bt_3_clicked();

    void on_bt_4_clicked();

private:
    Ui::qqDrawer *ui;

    void init();

    bool bt_1_show = true;
    bool bt_2_show = true;
    bool bt_3_show = true;
    bool bt_4_show = true;

};



#endif // QQDRAWER_H
