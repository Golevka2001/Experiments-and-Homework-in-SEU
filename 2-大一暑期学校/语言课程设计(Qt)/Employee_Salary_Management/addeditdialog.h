//addeditdialog.h
//作者：
//创建时间：2021-07
//功能：用于添加新职员/编辑职员的对话框，需要填写姓名年龄工号等一系列信息，不需要填写工资信息。
//     因为添加新职员/编辑职员需要的对话框形式几乎相同，故使用同一个对话框，部分内容按需进行变更。

#ifndef ADDEDITDIALOG_H
#define ADDEDITDIALOG_H

#include <QDialog>
#include <QString>
#include <QDate>
#include <QTextEdit>

#include "cemployee.h"

namespace Ui {
class AddEditDialog;
}

class AddEditDialog : public QDialog
{
    Q_OBJECT

public:
    //用于添加新职工的构造函数：
    explicit AddEditDialog(QWidget *parent);
    //用于编辑职工的构造函数：
    explicit AddEditDialog(QWidget *parent, CEmployee &eply);
    //析构函数：
    ~AddEditDialog();

    //返回姓名：
    QString GetName();
    //返回年龄：
    int GetAge();
    //返回工号：
    QString GetNo();
    //返回入职日期：
    QDate GetDate();
    //返回电话号码：
    QString GetPhone();
    //返回住址：
    QString GetAddress();

private:
    Ui::AddEditDialog *ui;  //窗口类
};

#endif // ADDEDITDIALOG_H
