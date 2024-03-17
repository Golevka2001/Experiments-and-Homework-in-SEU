//salarydialog.cpp
//作者：
//创建时间：2021-07
//功能：查看职工工资的对话框，包含一个TableView，
//     显示12个月的各项工资信息，并计算个人所得税和实发数。

#include "salarydialog.h"
#include "ui_salarydialog.h"
#include "readonlydelegate.h"

//构造函数：
SalaryDialog::SalaryDialog(QWidget *parent, QString name) :
    QDialog(parent),
    ui(new Ui::SalaryDialog)
{
    ui->setupUi(this);
    ui->title->setText(name + "的月工资数据集");   //设定标题
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);    //单次选择
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);    //选中一个item

    salaryInfoModel = new QStandardItemModel(); //QStandardItemModel类对象用于储存一个二维项数据数组，储存数据

    //建立信号与槽的关联：
    ui->tableView->setModel(salaryInfoModel);
    connect(ui->tableView->itemDelegate(),
            &QAbstractItemDelegate::closeEditor, this, &SalaryDialog::on_tableView_changed);
    connect(ui->tableView,SIGNAL(clicked(QModelIndex)),this,SLOT(show_list()));
}
//析构函数：
SalaryDialog::~SalaryDialog()
{
    delete ui;
    delete salaryInfoModel;
}

//返回当前选中的行号：
int SalaryDialog::GetRowIndex()
{
    int t_nRowIndex = 0;
    t_nRowIndex = ui-> tableView ->currentIndex().row();    //获取当前选择的行号
    return t_nRowIndex;
}
//返回当前选中的列号：
int SalaryDialog::GetColumnIndex()
{
    int t_nColumnIndex = 0;
    t_nColumnIndex = ui-> tableView ->currentIndex().column();    //获取当前选择的行号
    return t_nColumnIndex;
}

//表格数据改动：
void SalaryDialog::on_tableView_changed()
{
    QModelIndex t_Index = ui->tableView->currentIndex();
    CSalary &t_Salary = m_InfoTable.GetSalary(GetColumnIndex());    //获取当前选中月份工资数据的引用
    QVariant t_Data;    //暂时储存数据
    t_Data = salaryInfoModel->data(t_Index);  //获取数值
    switch(GetRowIndex())    //根据行号选择编辑的内容
    {
    case 0: //基本工资
        t_Salary.SetSalary1(t_Data.toDouble());
        break;
    case 1: //岗位工资
        t_Salary.SetSalary2(t_Data.toDouble());
        break;
    case 2: //工龄工资
        t_Salary.SetSalary3(t_Data.toDouble());
        break;
    case 3: //津贴
        t_Salary.SetAllowence1(t_Data.toDouble());
        break;
    case 4: //岗贴
        t_Salary.SetAllowence2(t_Data.toDouble());
        break;
    case 5: //补贴
        t_Salary.SetAllowence3(t_Data.toDouble());
        break;
    case 6: //房贴
        t_Salary.SetAllowence4(t_Data.toDouble());
        break;
    case 7: //交通补贴
        t_Salary.SetAllowence5(t_Data.toDouble());
        break;
    //case 6: //个人所得税，设为只读
    //case 7: //实发数，设为只读
    }
    Refresh(GetColumnIndex());
    m_InfoTable.SaveToFile(m_strFileName);
    //ShowSalaryList();
}

//显示工资表格：
void SalaryDialog::ShowSalaryList()
{
    //初始化：
    salaryInfoModel->clear(); //清空数据信息
    salaryInfoModel->setRowCount(10);   //设置为10行
    salaryInfoModel->setColumnCount(12);   //设置为12列
    for(int i = 0; i < 12; i++)
        ui->tableView->setColumnWidth(i, ui->tableView->width() / 13);  //设定列宽
    for(int i = 0; i < 10; i++)
        ui->tableView->setRowHeight(i, ui->tableView->height() / 11);   //设定行高
    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->tableView->horizontalHeader()->setFixedHeight(ui->tableView->height() / 11);
    ui->tableView->verticalHeader()->setFixedWidth(ui->tableView->width() / 13);
    ui->tableView->verticalHeader()->setDefaultAlignment(Qt::AlignCenter);

    //表头：
    QStringList t_List;
    t_List.append("1月");
    t_List.append("2月");
    t_List.append("3月");
    t_List.append("4月");
    t_List.append("5月");
    t_List.append("6月");
    t_List.append("7月");
    t_List.append("8月");
    t_List.append("9月");
    t_List.append("10月");
    t_List.append("11月");
    t_List.append("12月");
    salaryInfoModel->setHorizontalHeaderLabels(t_List);   //设定水平表头内容

    t_List.clear();
    t_List.append("基本工资");
    t_List.append("岗位工资");
    t_List.append("工龄工资");
    t_List.append("津贴");
    t_List.append("岗贴");
    t_List.append("补贴");
    t_List.append("房贴");
    t_List.append("交通补贴");
    t_List.append("个人所得税");
    t_List.append("实发数");
    salaryInfoModel->setVerticalHeaderLabels(t_List);   //设置垂直表头内容

    //遍历、插入数据：
    QStandardItem *t_Item;  //创建临时Item对象
    //依次从储存工资的Vector中读取，并存在临时工资对象中：
    for(int i = 0; i < 12; i++)
    {
        CSalary t_Salary = m_InfoTable.GetSalary(i);    //临时月工资对象
        for(int j = 0; j < 3; j++)
        {
            //填入基本/岗位/工龄工资：
            t_Item = new QStandardItem(QString::number(t_Salary.GetSalary(j + 1)));
            salaryInfoModel->setItem(j, i, t_Item);
            //居中显示文本：
            t_Item->setTextAlignment(Qt::AlignCenter);
        }
        for(int j = 0; j < 5; j++)
        {
            //填入津贴/岗贴/补贴/房贴/交通补贴：
            t_Item = new QStandardItem(QString::number(t_Salary.GetAllowence(j + 1)));
            salaryInfoModel->setItem(j + 3, i, t_Item);
            //居中显示文本：
            t_Item->setTextAlignment(Qt::AlignCenter);
        }

        Refresh(i);
    }
    //设置个人所得税、实发数为只读：
    ReadOnlyDelegate *readOnlyDelegate = new ReadOnlyDelegate(this);
    ui->tableView->setItemDelegateForRow(8, readOnlyDelegate);
    ui->tableView->setItemDelegateForRow(9, readOnlyDelegate);
}

//刷新个人所得税、实发数：
void SalaryDialog::Refresh(int index)
{
    double t_dSum = m_InfoTable.GetSalary(index).GetSum();
    double t_dTax;
    QStandardItem *t_Item;
    if(t_dSum < 800)
        t_dTax = 0;
    else if(t_dSum >= 800 && t_dSum < 1000)
        t_dTax = (t_dSum - 800) * 0.05;
    else if(t_dSum >= 1000 && t_dSum <5000)
        t_dTax = 10 + (t_dSum - 1000) * 0.1;
    else
        t_dTax = 10 + 400 + (t_dSum - 5000) * 0.2;

    //填入个人所得税：
    t_Item = new QStandardItem(QString::number(t_dTax));
    salaryInfoModel->setItem(8, index, t_Item);    
    //居中显示文本：
    t_Item->setTextAlignment(Qt::AlignCenter);

    //填入实发数：
    t_Item = new QStandardItem(QString::number(t_dSum - t_dTax));
    salaryInfoModel->setItem(9, index, t_Item);
    //居中显示文本：
    t_Item->setTextAlignment(Qt::AlignCenter);

    ui->tableView->setRowHeight(8, ui->tableView->height() / 11);   //设定行高
    ui->tableView->setRowHeight(9, ui->tableView->height() / 11);   //设定行高
}
