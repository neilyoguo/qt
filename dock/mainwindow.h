#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "DockManager.h"
#include "BusView/busview.h"
#include "SeriesView/seriesview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



static QIcon svgIcon(const QString& File)
{
    QIcon SvgIcon(File);
    SvgIcon.addPixmap(SvgIcon.pixmap(92));
    return SvgIcon;
}
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

    //dock对象
    ads::CDockWidget *dock_bus_a;
    ads::CDockWidget *dock_bus_b;
    ads::CDockWidget *dock_bus_uart_1;
    ads::CDockWidget *dock_bus_uart_2;

    ads::CDockWidget *dock_series;



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
