//mainwindow.h
//作者：
//创建时间：2021-07
//功能：主窗口，包含了窗口中的各项操作。

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QVector>

#include "employeeinfotable.h"
#include "readonlydelegate.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //主窗口构造函数：
    MainWindow(QWidget *parent = nullptr);
    //析构函数：
    ~MainWindow();

    //返回当前选中的行号：
    int GetRowIndex();
    //返回当前选中的列号：
    int GetColumnIndex();

    //窗口改变大小的时候列表控件跟着改变：
    void resizeEvent(QResizeEvent *event);

    //显示全部职工列表：
    void ShowEmployeeList();
    //显示部分职工列表：
    void ShowEmployeeList(QVector <int> index);

private:
    Ui::MainWindow *ui; //窗口类
    QStandardItemModel *employeeInfoModel;  //显示表格的信息数据类型
    EmployeeInfoTable m_InfoTable;  //数据汇总类
    ReadOnlyDelegate *readOnlyDelegate = new ReadOnlyDelegate(this);    //只读

private slots:
    void on_tableView_changed();        //表格数据改动
    void on_actionOpen_triggered();     //点击“打开”
    void on_actionSave_triggered();     //点击“保存”
    void on_actionSave_As_triggered();  //点击“另存为”
    void on_actionAdd_triggered();      //点击“添加新职员”
    void on_actionEdit_triggered();     //点击“编辑职员”
    void on_actionDelete_triggered();   //点击“移除职员”
    void on_actionSearch_triggered();   //点击“查找”
    void on_actionShowAll_triggered();  //点击“显示所有职员”
    void on_actionSalary_triggered();   //点击“查看职工工资”
};

#endif // MAINWINDOW_H
