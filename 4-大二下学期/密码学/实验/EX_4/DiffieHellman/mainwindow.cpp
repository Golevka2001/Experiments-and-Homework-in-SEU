// mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "functions.h"
#include <cstdlib>
#include <ctime>
#include <QMessageBox>
#include <QString>

int a_p, a_g, a_x, a_X, a_Y, a_K1;
int b_p, b_g, b_y, b_X, b_Y, b_K2;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand(time(0));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_a_random_g_clicked()
{
    a_p = ui->a_p->toPlainText().toInt();
    if (!is_prime(a_p))
    {
        QMessageBox::warning(this, "Error", "p should be a prime number!");
        a_p = 0;
        ui->a_p->clear();
        return;
    }
    a_g = primitive(a_p);
    ui->a_g->clear();
    ui->a_g->insertPlainText(QString::number(a_g));
}

void MainWindow::on_a_send_pg_clicked()
{
    a_p = ui->a_p->toPlainText().toInt();
    if (a_g == 0)
    {
        QMessageBox::warning(this, "Error", "Generate g!");
        return;
    }
    b_p = a_p;
    b_g = a_g;
    ui->b_p->clear();
    ui->b_g->clear();
    ui->b_p->insertPlainText(QString::number(b_p));
    ui->b_g->insertPlainText(QString::number(b_g));
}

void MainWindow::on_a_random_x_clicked()
{
    a_p = ui->a_p->toPlainText().toInt();
    if (a_g == 0)
    {
        QMessageBox::warning(this, "Error", "Generate p!");
        return;
    }
    a_x = rand() % (a_p-1) + 1;
    a_X = pow_mod(a_g, a_x, a_p);
    ui->a_x->clear();
    ui->a_X->clear();
    ui->a_x->insertPlainText(QString::number(a_x));
    ui->a_X->insertPlainText(QString::number(a_X));
}

void MainWindow::on_b_random_y_clicked()
{
    a_p = ui->a_p->toPlainText().toInt();
    if (b_p == 0)
    {
        QMessageBox::warning(this, "Error", "Receive p and g!");
        return;
    }
    b_y = rand() % (b_p-1) + 1;
    b_Y = pow_mod(b_g, b_y, b_p);
    ui->b_y->clear();
    ui->b_Y->clear();
    ui->b_y->insertPlainText(QString::number(b_y));
    ui->b_Y->insertPlainText(QString::number(b_Y));
}

void MainWindow::on_a_send_X_clicked()
{
    a_p = ui->a_p->toPlainText().toInt();
    if (a_X == 0)
    {
        QMessageBox::warning(this, "Error", "Generate x!");
        return;
    }
    b_X = a_X;
    ui->b_X->clear();
    ui->b_X->insertPlainText(QString::number(b_X));
}

void MainWindow::on_b_send_Y_clicked()
{
    a_p = ui->a_p->toPlainText().toInt();
    if (b_Y == 0)
    {
        QMessageBox::warning(this, "Error", "Generate y!");
        return;
    }
    a_Y = b_Y;
    ui->a_Y->clear();
    ui->a_Y->insertPlainText(QString::number(a_Y));
}

void MainWindow::on_calculate_clicked()
{
    a_p = ui->a_p->toPlainText().toInt();
    if (a_x == 0)
    {
        QMessageBox::warning(this, "Error", "Generate x!");
        return;
    }
    if (b_y == 0)
    {
        QMessageBox::warning(this, "Error", "Generate y!");
        return;
    }
    if (a_Y == 0)
    {
        QMessageBox::warning(this, "Error", "Receive Y!");
        return;
    }
    if (b_X == 0)
    {
        QMessageBox::warning(this, "Error", "Receive X!");
        return;
    }
    a_K1 = pow_mod(a_Y, a_x, a_p);
    b_K2 = pow_mod(b_X, b_y, b_p);
    ui->a_K1->clear();
    ui->a_K1->insertPlainText(QString::number(a_K1));
    ui->b_K2->clear();
    ui->b_K2->insertPlainText(QString::number(b_K2));
    if (a_K1 == b_K2)
    {
        ui->equal->clear();
        ui->equal->setText("=");
    }
}
