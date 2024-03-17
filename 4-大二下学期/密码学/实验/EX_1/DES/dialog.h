// dialog.h
#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QButtonGroup>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

    QButtonGroup *input_type_buttons;
    QButtonGroup *key_type_buttons;
    QButtonGroup *output_type_buttons;

private:
    Ui::Dialog *ui;
};


#endif // DIALOG_H
