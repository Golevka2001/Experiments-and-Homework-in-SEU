//readonlydelegate.cpp
//作者：
//创建时间：2021-07
//功能：用于设置TableView中的某些单元格的只读模式。

#include "readonlydelegate.h"

QWidget *ReadOnlyDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const //final
{
    Q_UNUSED(parent)
    Q_UNUSED(option)
    Q_UNUSED(index)
    return NULL;
}
