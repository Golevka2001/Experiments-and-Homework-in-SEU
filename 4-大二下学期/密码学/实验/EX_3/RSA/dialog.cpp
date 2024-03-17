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
    ui->p->setPlaceholderText("(prime number)");
    ui->q->setPlaceholderText("(prime number)");
    ui->public_key->setPlaceholderText("{e, n}");
    ui->private_key->setPlaceholderText("{d, n}");
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_generate_clicked()
{
    int p = ui->p->toPlainText().toInt();
    int q = ui->q->toPlainText().toInt();

    if (p == q || !is_prime(p) || !is_prime(q))
    {
        QMessageBox::warning(this, "Error", "p and q should be 2 different prime numbers!");
        p = 0;
        q = 0;
        ui->p->clear();
        ui->q->clear();
        return;
    }

    int e = 0, d = 0 , n = 0;
    generate_key(p, q, e, d, n);
    QString pub_key = '{' + QString::number(e, 10) + ", " + QString::number(n, 10) + '}';
    QString pri_key = '{' + QString::number(d, 10) + ", " + QString::number(n, 10) + '}';

    ui->public_key->clear();
    ui->private_key->clear();
    ui->public_key->insertPlainText(pub_key);
    ui->private_key->insertPlainText(pri_key);
}
