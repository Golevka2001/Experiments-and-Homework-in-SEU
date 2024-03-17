// mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "functions.h"
#include "dialog.h"
#include <QString>
using namespace std;

// 主窗口构建函数：
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->input->setPlaceholderText("Please enter the plain or cipher");
    ui->e_d->setPlaceholderText("Please enter the \"e\" or \" d\"");
    ui->n->setPlaceholderText("Please enter the \"n\"");
}

// 主窗口析构函数：
MainWindow::~MainWindow()
{
    delete ui;
}

// 点击"Encrypt"按钮：
void MainWindow::on_encrypt_button_clicked()
{
    /*****明文消息的获取*****/
    QString plain = ui->input->toPlainText();

    /*****密钥的获取*****/
    int e = ui->e_d->toPlainText().toInt();
    int n = ui->n->toPlainText().toInt();

    /*****加密过程*****/
    // 加密：
    QString cipher;
    encrypt(e, n, plain, cipher);
    // 打印密文：
    ui->output->clear();
    ui->output->insertPlainText(cipher);
}

// 点击"Decrypt"按钮：
void MainWindow::on_decryptbutton_clicked()
{
    /*****密文消息的获取*****/
    QString cipher = ui->input->toPlainText();

    /*****密钥的获取*****/
    int d = ui->e_d->toPlainText().toInt();
    int n = ui->n->toPlainText().toInt();

    /*****解密过程*****/
    // 解密：
    QString plain;
    decrypt(d, n, cipher, plain);
    // 打印明文：
    ui->output->clear();
    ui->output->insertPlainText(plain);
}

// 点击"生成密钥"按钮：
void MainWindow::on_key_generator_clicked()
{
    /*****创建密钥生成窗口*****/
    Dialog dialog;
    dialog.exec();
}
