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

private slots:
    void on_generate_clicked();

private:
    Ui::Dialog *ui;
};


#endif // DIALOG_H
