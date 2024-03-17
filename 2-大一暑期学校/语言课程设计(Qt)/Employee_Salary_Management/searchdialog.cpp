//searchdialog.cpp
//作者：
//创建时间：2021-07
//功能：查找对话框，内容根据选择的查找方式改变，并可选精确/模糊查找，
//     模糊查找要求包含即可，精确查找要求完全一致。

#include "searchdialog.h"
#include "ui_searchdialog.h"

SearchDialog::SearchDialog(QWidget *parent, int slct, int num) :
    QDialog(parent),
    ui(new Ui::SearchDialog)
{
    ui->setupUi(this);

    ui->Title->setGeometry(140, 20, 120, 23);   //设置标题位置、尺寸
    ui->label->setGeometry(30, 70, 70, 23); //设置标签位置、尺寸

    //根据所选择的搜索方式变更内容：
    switch(slct)
    {
    case 0: //按序号查找（int）
        ui->Title->setText("按序号查找");    //设置标题内容
        ui->label->setText("序    号");   //设置标签内容

        ui->spinBox->setRange(1, num);  //设置序号查找范围

        ui->lineEdit->hide();
        ui->dateEdit->hide();   //隐藏不需要的文本框
        ui->comboBox->hide();   //不区分精确/模糊查找
        break;
    case 1: //按姓名查找（string）
        ui->Title->setText("按姓名查找");    //设置标题内容
        ui->label->setText("姓    名");   //设置标签内容

        ui->spinBox->hide();
        ui->dateEdit->hide();   //隐藏不需要的文本框
        break;
    case 2: //按年龄查找（int）
        ui->Title->setText("按年龄查找");    //设置标题内容
        ui->label->setText("年    龄");   //设置标签内容

        ui->spinBox->setRange(16, 60);  //设置年龄查找范围

        ui->lineEdit->hide();
        ui->dateEdit->hide();   //隐藏不需要的文本框
        ui->comboBox->hide();   //不区分精确/模糊查找
        break;
    case 3: //按工号查找（string）
        ui->Title->setText("按工号查找");    //设置标题内容
        ui->label->setText("工    号");   //设置标签内容

        ui->spinBox->hide();
        ui->dateEdit->hide();   //隐藏不需要的文本框
        break;
    case 4: //按入职日期查找（qdate）
        ui->Title->setText("按入职日期查找");  //设置标题内容
        ui->Title->setGeometry(116, 20, 168, 23);   //改变标题位置、尺寸
        ui->label->setText("入职日期");   //设置标签内容

        ui->lineEdit->hide();
        ui->spinBox->hide();   //隐藏不需要的文本框
        ui->comboBox->hide();   //不区分精确/模糊查找
        break;
    case 5: //按电话号码查找（string）
        ui->Title->setText("按电话号码查找");  //设置标题内容
        ui->Title->setGeometry(116, 20, 168, 23);   //改变标题位置、尺寸
        ui->label->setText("电话号码");   //设置标签内容

        ui->spinBox->hide();
        ui->dateEdit->hide();   //隐藏不需要的文本框
        break;
    case 6: //按住址查找（string）
        ui->Title->setText("按住址查找");    //设置标题内容
        ui->label->setText("住    址");   //设置标签内容

        ui->spinBox->hide();
        ui->dateEdit->hide();   //隐藏不需要的文本框
        break;
    }
}
//析构函数：
SearchDialog::~SearchDialog()
{
    delete ui;
}

//返回文本框中的内容(int型)：
int SearchDialog::GetInt()
{
    return ui->spinBox->value();
}
//返回文本框中的内容(string型)：
QString SearchDialog::GetString()
{
    return ui->lineEdit->text();
}
//返回文本框中的内容(qdate型)：
QDate SearchDialog::GetDate()
{
    return ui->dateEdit->date();
}

//返回查找方式（精确/模糊）：
int SearchDialog::GetSelection()
{
    return ui->comboBox->currentIndex();
}
