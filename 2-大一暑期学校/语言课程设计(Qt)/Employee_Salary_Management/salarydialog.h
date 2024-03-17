//salarydialog.h
//作者：
//创建时间：2021-07
//功能：查看职工工资的对话框，包含一个TableView，
//     显示12个月的各项工资信息，并计算个人所得税和实发数。

#ifndef SALARYDIALOG_H
#define SALARYDIALOG_H

#include <QDialog>
#include <QString>
#include <QStandardItemModel>

#include "salaryinfotable.h"

namespace Ui {
class SalaryDialog;
}

class SalaryDialog : public QDialog
{
    Q_OBJECT

public:
    //构造函数：
    explicit SalaryDialog(QWidget *parent = nullptr, QString name = " ");
    //析构函数：
    ~SalaryDialog();

    //返回当前选中的行号：
    int GetRowIndex();
    //返回当前选中的列号：
    int GetColumnIndex();

    //显示工资表格：
    void ShowSalaryList();
    //刷新个人所得税、实发数：
    void Refresh(int index);

    SalaryInfoTable m_InfoTable;  //数据汇总类

    QString m_strFileName;  //储存文件名

private:
    Ui::SalaryDialog *ui;   //窗口类
    QStandardItemModel *salaryInfoModel;  //显示表格的信息数据类型

private slots:
    void on_tableView_changed();    //表格数据改动
};

#endif // SALARYDIALOG_H
