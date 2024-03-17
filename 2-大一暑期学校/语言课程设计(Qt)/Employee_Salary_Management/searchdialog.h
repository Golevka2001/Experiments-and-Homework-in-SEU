//searchdialog.h
//作者：
//创建时间：2021-07
//功能：查找对话框，内容根据选择的查找方式改变，并可选精确/模糊查找，
//     模糊查找要求包含即可，精确查找要求完全一致。

#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>
#include <QString>
#include <QDate>

namespace Ui {
class SearchDialog;
}

class SearchDialog : public QDialog
{
    Q_OBJECT

public:
    //构造函数：
    explicit SearchDialog(QWidget *parent = nullptr, int slct = 0, int num = 0);
    //析构函数：
    ~SearchDialog();

    //返回文本框中的内容(int型)：
    int GetInt();
    //返回文本框中的内容(string型)：
    QString GetString();
    //返回文本框中的内容(qdate型)：
    QDate GetDate();

    //返回查找方式（精确/模糊）：
    int GetSelection();

private:
    Ui::SearchDialog *ui;
};

#endif // SEARCHDIALOG_H
