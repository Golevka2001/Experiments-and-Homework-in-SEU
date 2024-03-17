// dialog.cpp
#include "dialog.h"
#include "ui_dialog.h"
#include "functions.h"
#include <QMessageBox>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->q->setPlaceholderText("(prime number)");
    ui->public_key->setPlaceholderText("{q, α, YA}");
    ui->private_key->setPlaceholderText("{XA}");
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_generate_clicked()
{
    int q = ui->q->toPlainText().toInt();

    if (!is_prime(q))
    {
        QMessageBox::warning(this, "Error", "q should be a prime number!");
        q = 0;
        ui->q->clear();
        return;
    }

    int alpha = 0, YA = 0, XA = 0;
    generate_key(q, alpha, YA, XA);
    QString pub_key = '{' + QString::number(q, 10) + ", " + QString::number(alpha, 10) + ", " + QString::number(YA, 10) + '}';
    QString pri_key = '{' + QString::number(XA, 10) + '}';

    ui->public_key->clear();
    ui->private_key->clear();
    ui->public_key->insertPlainText(pub_key);
    ui->private_key->insertPlainText(pri_key);
}
