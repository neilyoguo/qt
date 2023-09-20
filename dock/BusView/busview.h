#ifndef BUSVIEW_H
#define BUSVIEW_H

#include <QWidget>
#include <QStandardItemModel>
#include <QTableView>
#include <QMenu>
#include <QLayout>
#include <QList>
#include <QDateTime>
#include <QHeaderView>
#include <QTimer>
class BusView : public QWidget
{
    Q_OBJECT
public:
    explicit BusView(QStringList headList, QWidget *parent = nullptr);

signals:
private:
    void InitTable();
    QStandardItemModel * m_data_model; //数据模型
    QTableView *tableview;
    QStringList m_head;
    QTimer m_timer;
    QList<QString> str_test;
private slots:
    void ShowMenu(const QPoint &pos);
    void clear();
    void Insert();
    void test();

public:
    void InsertData(QList<QString> strlist);
};

#endif // BUSVIEW_H
