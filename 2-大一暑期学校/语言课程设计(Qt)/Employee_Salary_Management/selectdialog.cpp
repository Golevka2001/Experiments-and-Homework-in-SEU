//selectdialog.cpp
//作者：
//创建时间：2021-07
//功能：选择查找方式对话框，下拉选择查找方式。

#include "selectdialog.h"
#include "ui_selectdialog.h"

//构造函数：
SelectDialog::SelectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectDialog)
{
    ui->setupUi(this);
}
//析构函数：
SelectDialog::~SelectDialog()
{
    delete ui;
}

//返回当前的选择：
int SelectDialog::GetSelection()
{
    return ui->comboBoxSelect->currentIndex();
}
