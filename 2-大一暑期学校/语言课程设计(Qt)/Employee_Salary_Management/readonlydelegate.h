//readonlydelegate.h
//作者：
//创建时间：2021-07
//功能：用于设置TableView中的某些单元格的只读模式。

#ifndef READONLYDELEGATE_H
#define READONLYDELEGATE_H

#include <QItemDelegate>

class ReadOnlyDelegate: public QItemDelegate
{
public:
    //构造函数：
    ReadOnlyDelegate(QWidget *parent = NULL)
        :QItemDelegate(parent)
    {}

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,const QModelIndex &index) const override;
};

#endif // READONLYDELEGATE_H
