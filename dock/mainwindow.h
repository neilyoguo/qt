#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "DockManager.h"
#include "BusView/busview.h"
#include "SeriesView/seriesview.h"
#include "qqdrawer.h"
#include "tools.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    //dock管理器对象
    ads::CDockManager* m_pDockManager;

    //table对象
    BusView *bus_a;
    BusView *bus_b;
    BusView *bus_uart_1;
    BusView *bus_uart_2;

    SeriesView *series_view;

    qqDrawer *qq_drawer;

    //dock对象
    ads::CDockWidget *dock_bus_a;
    ads::CDockWidget *dock_bus_b;
    ads::CDockWidget *dock_bus_uart_1;
    ads::CDockWidget *dock_bus_uart_2;

    ads::CDockWidget *dock_series;

    ads::CDockWidget *dock_qq;



private:
    Ui::MainWindow *ui;

    //初始化dock管理器
    void InitDock();
    //初始化菜单
    void InitMenuBar();
    //初始化dock
    void InitSubDock();
    //保存布局
    void SaveLayout();
    //加载布局
    void LoadLayout();



};
#endif // MAINWINDOW_H
