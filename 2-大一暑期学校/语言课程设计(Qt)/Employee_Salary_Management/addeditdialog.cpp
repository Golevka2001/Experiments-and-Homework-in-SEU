//addeditdialog.cpp
//作者：
//创建时间：2021-07
//功能：用于添加新职员/编辑职员的对话框，需要填写姓名年龄工号等一系列信息，不需要填写工资信息。
//     因为添加新职员/编辑职员需要的对话框形式几乎相同，故使用同一个对话框，部分内容按需进行变更。

#include "addeditdialog.h"
#include "ui_addeditdialog.h"

//用于添加新职工的构造函数：
AddEditDialog::AddEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddEditDialog)
{
    ui->setupUi(this);
    ui->spinBoxAge->setRange(16, 60);   //限定年龄范围为16-60

    //设置标签位置、尺寸：
    ui->title->setText("添加新职工");
    ui->title->setGeometry(160, 20, 120, 23);
}
//用于编辑职工的构造函数：
AddEditDialog::AddEditDialog(QWidget *parent, CEmployee &eply) :
    QDialog(parent),
    ui(new Ui::AddEditDialog)
{
    ui->setupUi(this);
    ui->spinBoxAge->setRange(16, 60);   //限定年龄范围为16-60

    //设置标签位置、尺寸：
    ui->title->setText("编辑职工");
    ui->title->setGeometry(170, 20, 96, 23);

    //将文本框中的初始值设为选中职员的当前值：
    ui->lineEditName->setText(eply.m_strName);
    ui->spinBoxAge->setValue(eply.m_nAge);
    ui->lineEditNo->setText(eply.m_strNo);
    ui->dateEdit->setDate(eply.m_Date);
    ui->lineEditPhone->setText(eply.m_strPhone);
    ui->lineEditAddress->setText(eply.m_strAddress);
}
//析构函数：
AddEditDialog::~AddEditDialog()
{
    delete ui;
}

//返回姓名：
QString AddEditDialog::GetName()
{
    return ui->lineEditName->text();
}
//返回年龄：
int AddEditDialog::GetAge()
{
    QString t_strAge = ui->spinBoxAge->text();  //临时string类型变量储存年龄
    return t_strAge.toInt();    //string类型转为int类型后返回
}
//返回工号：
QString AddEditDialog::GetNo()
{
    return ui->lineEditNo->text();
}
//返回入职日期：
QDate AddEditDialog::GetDate()
{
    return ui->dateEdit->date();
}
//返回电话号码：
QString AddEditDialog::GetPhone()
{
    return ui->lineEditPhone->text();
}
//返回住址：
QString AddEditDialog::GetAddress()
{
    return ui->lineEditAddress->text();
}
