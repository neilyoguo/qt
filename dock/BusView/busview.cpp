#include "busview.h"

BusView::BusView(QStringList headList, QWidget *parent) : QWidget(parent)
{

    m_head = headList;
    m_head<<"时间";
    m_head.insert(0,"序号");
    InitTable();
    this->setStyleSheet("background-color: #D2E9FF;");
    connect(&m_timer , SIGNAL(timeout()),this ,SLOT(test()));

    for(int t = 0 ;t < headList.count() ; t ++)
        str_test.push_back(QString::number(t));

}
void BusView::InitTable()
{
    tableview = new QTableView(this);
    //设置样式表

    //创建layout 让 tabel充满widget
    QVBoxLayout *layout = new QVBoxLayout(this);
    tableview->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //设置无边界
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(tableview);


    m_data_model = new QStandardItemModel(this);
    //设置标题
    m_data_model->setHorizontalHeaderLabels(m_head);

    tableview->setModel(m_data_model);
    //设置所有列宽度自适应内容
    //tableview->resizeColumnsToContents();
    //设置第1列宽100
    //tableview->setColumnWidth(0, 200);
    // 取消行号显示
    tableview->verticalHeader()->setVisible(false);

    QHeaderView* header = tableview->horizontalHeader();
    //设置表头使其和第一行区分
    header->setStyleSheet("QHeaderView::section{background:white;color: black;}");
    //奇数偶数行颜色交替
    tableview->setAlternatingRowColors(true);
    //设置标题自动调整
    header->setSectionResizeMode(QHeaderView::Interactive);
    //设置标题最后一行自适应
    header->setStretchLastSection(true);
    //禁止编辑
    tableview->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //设置选择行为为选中整行
    tableview->setSelectionBehavior(QAbstractItemView::SelectRows);
    //可弹出右键菜单
    tableview->setContextMenuPolicy(Qt::CustomContextMenu);
    //链接槽函数
    connect(tableview, SIGNAL(customContextMenuRequested(QPoint)), this,SLOT(ShowMenu(QPoint)));
}

void BusView::ShowMenu(const QPoint &pos)
{
    Q_UNUSED(pos);
    QMenu * menu = new QMenu(tableview);

    menu->setStyleSheet("QMenu::item:selected {  background-color: rgb(0,108,227);}"
                        "QMenu::item { background-color: #D2E9FF; }");


    QAction *act_insert = menu->addAction("插入数据");
    QAction *act_clear = menu->addAction("清理");
    connect(act_clear, SIGNAL(triggered()), this, SLOT(clear()));
    connect(act_insert, SIGNAL(triggered()), this, SLOT(Insert()));
    menu->exec(QCursor::pos());
}

void BusView::clear()
{
    m_data_model->removeRows(0,m_data_model->rowCount());
}

void BusView::Insert()
{
    m_timer.start(1000);
}

void BusView::test()
{

    InsertData(str_test);
}

void BusView::InsertData(QList<QString> strlist)
{
    int row = m_data_model->rowCount();
    strlist.insert(0,QString::number(row));
    // 获取当前时间
    QDateTime currentDateTime = QDateTime::currentDateTime();
    // 将当前时间转换为字符串
    QString time = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");
    strlist.append(time);


    for(int t = 0 ;t < strlist.count(); t++)
    {
        QStandardItem *item_value = new QStandardItem(strlist.at(t));
        m_data_model->setItem(row,t,item_value);
    }

    //超过1000行 移除第一行
    if(row >1000)
        m_data_model->removeRow(0);
    //设置滚动轴在最后
    tableview->scrollToBottom();
}


