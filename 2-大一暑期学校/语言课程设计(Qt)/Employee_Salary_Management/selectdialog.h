//Selectdialog.h
//作者：
//创建时间：2021-07
//功能：选择查找方式对话框，下拉选择查找方式。

#ifndef SELECTDIALOG_H
#define SELECTDIALOG_H

#include <QDialog>

namespace Ui {
class SelectDialog;
}

class SelectDialog : public QDialog
{
    Q_OBJECT

public:
    //构造函数：
    explicit SelectDialog(QWidget *parent = nullptr);
    //析构函数：
    ~SelectDialog();

    //返回当前的选择：
    int GetSelection();

private:
    Ui::SelectDialog *ui;
};

#endif // SELECTDIALOG_H
