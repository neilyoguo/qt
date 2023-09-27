#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDockWidget>
#include <QTextEdit>
#include <QComboBox>
#include <QLayout>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QDebug>
#include <QSettings>
#include <SvcGuid.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    InitDock();
    InitSubDock();
    InitMenuBar();


    LoadLayout();

}

MainWindow::~MainWindow()
{
    SaveLayout();
    delete ui;
}

void MainWindow::InitDock()
{
    //设置鼠标选中高亮
    ads::CDockManager::setConfigFlag(ads::CDockManager::FocusHighlighting, true);
    // uncomment if you would like to enable dock widget auto hiding
    ads::CDockManager::setAutoHideConfigFlags({ads::CDockManager::DefaultAutoHideConfig});
    m_pDockManager = new ads::CDockManager(this);




    // 设置主窗口的背景色
    QPalette palette = this->centralWidget()->palette();
    palette.setColor(QPalette::Background, Qt::red);
    this->centralWidget()->setAutoFillBackground(true);
    this->centralWidget()->setPalette(palette);

}

void MainWindow::InitMenuBar()
{


    //创建一个菜单栏
    QMenuBar *menu_bar = new QMenuBar(this);
    //设置为MainWindow的菜单栏
    this->setMenuBar(menu_bar);
    //设置菜单栏背景色
    QString styleSheet = "QMenuBar::item:selected { background-color: #fcdcbc; }"
                          "QMenuBar { background-color: #D2E9FF; }";
    menu_bar->setStyleSheet(styleSheet);
    //创建菜单
    QMenu *file_menu = new QMenu("文件");
    QMenu *view_menu = new QMenu("视图");
    QMenu *set_menu = new QMenu("设置");
    QMenu *help_menu = new QMenu("帮助");
    menu_bar->addMenu(file_menu);
    menu_bar->addMenu(view_menu);
    menu_bar->addMenu(set_menu);
    menu_bar->addMenu(help_menu);


    //文件菜单
    QAction *new_act = new QAction("新建", this);
    QAction *open_act = new QAction("打开", this);
    QAction *exit_act = new QAction("exit", this);
    file_menu->addAction(new_act);
    file_menu->addAction(open_act);
    file_menu->addSeparator();
    file_menu->addAction(exit_act);

    //视图菜单
    QMenu *can_menu = new QMenu("can总线监视");
    view_menu->addMenu(can_menu);
    //菜单选择窗口不消失
    dock_bus_a->setToggleViewActionMode(ads::CDockWidget::ActionModeShow);
    dock_bus_b->setToggleViewActionMode(ads::CDockWidget::ActionModeShow);
    dock_bus_a->setIcon(svgIcon(":/images/images/文件.svg"));
    dock_bus_b->setIcon(svgIcon(":/images/images/文件.svg"));
    can_menu->addAction(dock_bus_b->toggleViewAction());
    can_menu->addAction(dock_bus_a->toggleViewAction());

    QMenu *uart_menu = new QMenu("串口总线监视");
    view_menu->addMenu(uart_menu);
    dock_bus_uart_1->setToggleViewActionMode(ads::CDockWidget::ActionModeShow);
    dock_bus_uart_2->setToggleViewActionMode(ads::CDockWidget::ActionModeShow);
    dock_bus_uart_1->setIcon(svgIcon(":/images/images/文档.svg"));
    dock_bus_uart_2->setIcon(svgIcon(":/images/images/文档.svg"));
    uart_menu->addAction(dock_bus_uart_1->toggleViewAction());
    uart_menu->addAction(dock_bus_uart_2->toggleViewAction());

    dock_series->setIcon(QIcon(":/images/images/series.ico"));
    dock_series->setToggleViewActionMode(ads::CDockWidget::ActionModeShow);
    view_menu->addAction(dock_series->toggleViewAction());


    dock_qq->setToggleViewActionMode(ads::CDockWidget::ActionModeShow);
    view_menu->addAction(dock_qq->toggleViewAction());

}

void MainWindow::SaveLayout()
{
    QSettings Settings("Settings.ini", QSettings::IniFormat);
    Settings.setValue("mainWindow/Geometry", this->saveGeometry());
    Settings.setValue("mainWindow/State", this->saveState());
    Settings.setValue("mainWindow/DockingState", m_pDockManager->saveState());
}

void MainWindow::LoadLayout()
{
    QSettings Settings("Settings.ini", QSettings::IniFormat);
    this->restoreGeometry(Settings.value("mainWindow/Geometry").toByteArray());
    this->restoreState(Settings.value("mainWindow/State").toByteArray());
    m_pDockManager->restoreState(Settings.value("mainWindow/DockingState").toByteArray());
}

void MainWindow::InitSubDock()
{
   QStringList can_head ={"通道","T/R","ID","长度","数据"};
   dock_bus_a = new ads::CDockWidget("can_a总线监视",this);
   bus_a = new BusView(can_head);
   dock_bus_a->setWidget(bus_a);
   m_pDockManager->addDockWidget(ads::TopDockWidgetArea, dock_bus_a);


   bus_b = new BusView(can_head);
   dock_bus_b = new ads::CDockWidget("can_b总线监视",this);
   dock_bus_b->setWidget(bus_b);
   m_pDockManager->addDockWidget(ads::TopDockWidgetArea, dock_bus_b);

   QStringList uart_head ={"通道","T/R","长度","数据"};
   bus_uart_1 = new BusView(uart_head);
   dock_bus_uart_1 = new ads::CDockWidget("uart_1_总线监视",this);
   dock_bus_uart_1->setWidget(bus_uart_1);
   m_pDockManager->addDockWidget(ads::TopDockWidgetArea, dock_bus_uart_1);

   bus_uart_2 = new BusView(uart_head);
   dock_bus_uart_2 = new ads::CDockWidget("uart_2_总线监视",this);
   dock_bus_uart_2->setWidget(bus_uart_2);
   m_pDockManager->addDockWidget(ads::TopDockWidgetArea, dock_bus_uart_2);

   series_view = new SeriesView();
   dock_series = new ads::CDockWidget("pointView",this);
   dock_series->setWidget(series_view);
   m_pDockManager->addDockWidget(ads::CenterDockWidgetArea,dock_series);


   qq_drawer = new qqDrawer();
   dock_qq = new ads::CDockWidget("qqView",this);
   dock_qq->setWidget(qq_drawer);
   m_pDockManager->addDockWidget(ads::CenterDockWidgetArea,dock_qq);

}



