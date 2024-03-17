// mainwindow.cpp
#include "mainwindow.h"

#include <QString>

#include "dialog.h"
#include "functions.h"
#include "matrices.h"
#include "ui_mainwindow.h"
using namespace std;

// 主窗口构建函数：
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  ui->input->setPlaceholderText("Please enter the plain or cipher");
  ui->key->setPlaceholderText("Please enter the key");
}

// 主窗口析构函数：
MainWindow::~MainWindow() { delete ui; }

// 点击"Encrypt"按钮：
void MainWindow::on_encrypt_button_clicked()
{
  /*****创建类型选择窗口*****/
  Dialog dialog;
  dialog.exec();

  /*****明文消息的输入、处理*****/
  // 获取明文类型：
  int plain_type = dialog.input_type_buttons->checkedId();
  // 获取明文消息：
  string plain_str = ui->input->toPlainText().toStdString();
  // 若明文消息字符数不足16（或32）的整数倍（一位ASCII字符用8bit表示、一位十六进制用4bit表示），则末尾用0补足：
  int zero_num =
      (plain_str.size() % (16 * plain_type))
          ? ((16 * plain_type) - plain_str.size() % (16 * plain_type))
          : 0;
  plain_str.append(zero_num, '0');
  // 字符串每16（或32）位划分一组：
  const int group_num = plain_str.size() / (16 * plain_type);
  vector<string> plain_split(group_num);
  for (int i = 0; i < group_num; ++i)
    plain_split[i] = plain_str.substr(i * (16 * plain_type), (16 * plain_type));
  // 每组字符串转为二进制：
  vector<bitset<128>> plain_bin(group_num);
  for (int i = 0; i < group_num; ++i)
    plain_bin[i] = (plain_type == 1) ? (ascii_str_to_bitset(plain_split[i]))
                                     : (hex_str_to_bitset(plain_split[i]));
  // 每组二进制转为byte数组：
  vector<byte_[16]> plain_byte(group_num);
  for (int i = 0; i < group_num; ++i)
    for (int j = 0; j < 16; ++j)
      for (int k = 0; k < 8; ++k) plain_byte[i][j][k] = plain_bin[i][j * 8 + k];

  /*****密钥的输入、处理*****/
  // 获取密钥类型：
  int key_type = dialog.key_type_buttons->checkedId();
  // 获取密钥：
  string key_str = ui->key->toPlainText().toStdString();
  // 若输入的密钥长度少于16（或32）位字符则后面补0:
  if (key_str.size() < (16 * key_type))
    key_str.append((16 * key_type) - key_str.size(), '0');
  // 若输入的密钥长度超过16（或32）位字符则只取前16（或32）位：
  key_str = key_str.substr(0, (8 * key_type));
  // 转为二进制：
  bitset<128> key_bin = (key_type == 1) ? ascii_str_to_bitset(key_str)
                                        : hex_str_to_bitset(key_str);
  // 转为byte数组：
  byte_ key_byte[4 * Nk];
  for (int i = 0; i < 4 * Nk; ++i)
    for (int j = 0; j < 8; ++j) key_byte[i][j] = key_bin[i * 8 + j];

  /*****加密过程*****/
  // 获取密文类型：
  int cipher_type = dialog.output_type_buttons->checkedId();
  // 对每组密文完成加密：
  word w[4 * (Nr + 1)];
  key_expansion(key_byte, w);
  vector<byte_[16]> cipher_byte(group_num);
  for (int i = 0; i < group_num; ++i)
  {
    for (int j = 0; j < 16; ++j) cipher_byte[i][j] = plain_byte[i][j];
    encrypt(cipher_byte[i], w);
  }
  // 打印密文：
  vector<bitset<128>> cipher_bin(group_num);
  for (int i = 0; i < group_num; ++i)
    for (int j = 0; j < 16; ++j)
      for (int k = 0; k < 8; ++k)
        cipher_bin[i][j * 8 + k] = cipher_byte[i][j][k];
  QString cipher_str;
  for (int i = 0; i < group_num; ++i)
    cipher_str +=
        (cipher_type == 1)
            ? QString::fromStdString(bitset_to_ascii_str(cipher_bin[i]))
            : QString::fromStdString(bitset_to_hex_str(cipher_bin[i]));
  ui->output->clear();
  ui->output->insertPlainText(cipher_str);
}

// 点击"Decrypt"按钮：
void MainWindow::on_decryptbutton_clicked()
{
  /*****创建类型选择窗口*****/
  Dialog dialog;
  dialog.exec();

  /*****密文消息的输入、处理*****/
  // 获取密文类型：
  int cipher_type = dialog.input_type_buttons->checkedId();
  // 获取密文消息：
  string cipher_str = ui->input->toPlainText().toStdString();
  // 字符串每16（或32）位划分一组：
  const int group_num = cipher_str.size() / (16 * cipher_type);
  vector<string> cipher_split(group_num);
  for (int i = 0; i < group_num; ++i)
    cipher_split[i] =
        cipher_str.substr(i * (16 * cipher_type), (16 * cipher_type));
  // 每组字符串转为二进制：
  vector<bitset<128>> cipher_bin(group_num);
  for (int i = 0; i < group_num; ++i)
    cipher_bin[i] = (cipher_type == 1) ? (ascii_str_to_bitset(cipher_split[i]))
                                       : (hex_str_to_bitset(cipher_split[i]));
  // 每组二进制转为byte数组：
  vector<byte_[16]> cipher_byte(group_num);
  for (int i = 0; i < group_num; ++i)
    for (int j = 0; j < 16; ++j)
      for (int k = 0; k < 8; ++k)
        cipher_byte[i][j][k] = cipher_bin[i][j * 8 + k];

  /*****密钥的输入、处理*****/
  // 获取密钥类型：
  int key_type = dialog.key_type_buttons->checkedId();
  // 获取密钥：
  string key_str = ui->key->toPlainText().toStdString();
  // 若输入的密钥长度少于16（或32）位字符则后面补0:
  if (key_str.size() < (16 * key_type))
    key_str.append((16 * key_type) - key_str.size(), '0');
  // 若输入的密钥长度超过16（或32）位字符则只取前8位：
  key_str = key_str.substr(0, (16 * key_type));
  // 转为二进制：
  bitset<128> key_bin = (key_type == 1) ? ascii_str_to_bitset(key_str)
                                        : hex_str_to_bitset(key_str);
  // 转为byte数组：
  byte_ key_byte[4 * Nk];
  for (int i = 0; i < 4 * Nk; ++i)
    for (int j = 0; j < 8; ++j) key_byte[i][j] = key_bin[i * 8 + j];

  /*****解密过程*****/
  // 获取明文类型：
  int plain_type = dialog.output_type_buttons->checkedId();
  // 对每组密文完成解密：
  word w[4 * (Nr + 1)];
  key_expansion(key_byte, w);
  vector<byte_[16]> plain_byte(group_num);
  for (int i = 0; i < group_num; ++i)
  {
    for (int j = 0; j < 16; ++j) plain_byte[i][j] = cipher_byte[i][j];
    decrypt(plain_byte[i], w);
  }
  // 打印明文：
  vector<bitset<128>> plain_bin(group_num);
  for (int i = 0; i < group_num; ++i)
    for (int j = 0; j < 16; ++j)
      for (int k = 0; k < 8; ++k) plain_bin[i][j * 8 + k] = plain_byte[i][j][k];
  QString plain_str;
  for (int i = 0; i < group_num; ++i)
    plain_str += (plain_type == 1)
                     ? QString::fromStdString(bitset_to_ascii_str(plain_bin[i]))
                     : QString::fromStdString(bitset_to_hex_str(plain_bin[i]));
  for (int i = plain_str.size() - 1; i >= 0; --i)
  {
    if (plain_str[i] != '0') break;
    plain_str.chop(1);
  }
  ui->output->clear();
  ui->output->insertPlainText(plain_str);
}
