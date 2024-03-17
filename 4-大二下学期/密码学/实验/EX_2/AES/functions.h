// functions.h
// 定义了DES算法中所用到的一系列函数
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <bitset>
#include <cmath>
#include <iomanip>
#include <string>
#include <vector>

#include "matrices.h"
using namespace std;

typedef bitset<8> byte_;
typedef bitset<32> word;

/**********文本类型转换函数**********/

// 函数：字符串（ASCII）转为二进制：
bitset<128> ascii_str_to_bitset(const string str)
{
  bitset<128> bits;
  for (int i = 0; i < 16; ++i)
    for (int j = 0; j < 8; ++j) bits[i * 8 + 7 - j] = ((str[i] >> j) & 1);
  return bits;
}

// 函数：字符串（HEX）转为二进制：
bitset<128> hex_str_to_bitset(const string str)
{
  bitset<128> bits;
  for (int i = 0; i < 32; ++i)
  {
    int oct = 0;
    if (str[i] >= '0' && str[i] <= '9')
      oct = int(str[i] - '0');
    else if (str[i] >= 'A' && str[i] <= 'F')
      oct = int(str[i] - 'A') + 10;
    else
      oct = 0;
    bitset<4> bin(oct);
    for (int j = 0; j < 4; ++j) bits[i * 4 + j] = bin[3 - j];
  }
  return bits;
}

// 函数：二进制转为字符串（ASCII）：
string bitset_to_ascii_str(const bitset<128> bits)
{
  string str = "0000000000000000";
  for (int i = 0; i < 16; ++i)
  {
    int temp_num = 0;
    for (int j = 0; j < 8; ++j) temp_num += bits[i * 8 + j] * pow(2, 7 - j);
    str[i] = temp_num;
  }
  return str;
}

// 函数：二进制转为字符串（HEX）:
string bitset_to_hex_str(const bitset<128> bits)
{
  string str = "00000000000000000000000000000000";
  for (int i = 0; i < 32; ++i)
  {
    int temp_num = bits[i * 4] * 8 + bits[i * 4 + 1] * 4 + bits[i * 4 + 2] * 2 +
                   bits[i * 4 + 3];
    str[i] = (temp_num < 10) ? ('0' + temp_num) : ('A' + temp_num - 10);
  }
  return str;
}

/**********加密的变换函数**********/

// 函数：S盒变换（前四位为行号，后四位）：
void sub_bytes(byte_ mtx[4 * 4])
{
  for (int i = 0; i < 16; ++i)
  {
    int row = mtx[i][7] * 8 + mtx[i][6] * 4 + mtx[i][5] * 2 + mtx[i][4];
    int col = mtx[i][3] * 8 + mtx[i][2] * 4 + mtx[i][1] * 2 + mtx[i][0];
    mtx[i] = S[row][col];
  }
}

// 函数：行变换，按字节循环移位：
void shift_rows(byte_ mtx[4 * 4])
{
  // 第二行循环左移一位：
  byte_ temp = mtx[4];
  for (int i = 0; i < 3; ++i) mtx[i + 4] = mtx[i + 5];
  mtx[7] = temp;
  // 第三行循环左移两位：
  for (int i = 0; i < 2; ++i)
  {
    temp = mtx[i + 8];
    mtx[i + 8] = mtx[i + 10];
    mtx[i + 10] = temp;
  }
  // 第四行循环左移三位：
  temp = mtx[15];
  for (int i = 3; i > 0; --i) mtx[i + 12] = mtx[i + 11];
  mtx[12] = temp;
}

// 函数：有限域上的乘法：
byte_ GF_mul(byte_ a, byte_ b)
{
  byte_ p = 0;
  byte_ hi_bit_set;
  for (int counter = 0; counter < 8; counter++)
  {
    if ((b & byte_(1)) != 0) p ^= a;
    hi_bit_set = (byte_)(a & byte_(0x80));
    a <<= 1;
    if (hi_bit_set != 0) a ^= 0x1b;  // x^8 + x^4 + x^3 + x + 1
    b >>= 1;
  }
  return p;
}

// 函数：列变换：
void mix_columns(byte_ mtx[4 * 4])
{
  byte_ arr[4];
  for (int i = 0; i < 4; ++i)
  {
    for (int j = 0; j < 4; ++j) arr[j] = mtx[i + j * 4];

    mtx[i] = GF_mul(0x02, arr[0]) ^ GF_mul(0x03, arr[1]) ^ arr[2] ^ arr[3];
    mtx[i + 4] = arr[0] ^ GF_mul(0x02, arr[1]) ^ GF_mul(0x03, arr[2]) ^ arr[3];
    mtx[i + 8] = arr[0] ^ arr[1] ^ GF_mul(0x02, arr[2]) ^ GF_mul(0x03, arr[3]);
    mtx[i + 12] = GF_mul(0x03, arr[0]) ^ arr[1] ^ arr[2] ^ GF_mul(0x02, arr[3]);
  }
}

// 函数：轮密钥加变换，将每一列与扩展密钥进行异或：
void add_round_key(byte_ mtx[4 * 4], word k[4])
{
  for (int i = 0; i < 4; ++i)
  {
    word k1 = k[i] >> 24;
    word k2 = (k[i] << 8) >> 24;
    word k3 = (k[i] << 16) >> 24;
    word k4 = (k[i] << 24) >> 24;

    mtx[i] = mtx[i] ^ byte_(k1.to_ulong());
    mtx[i + 4] = mtx[i + 4] ^ byte_(k2.to_ulong());
    mtx[i + 8] = mtx[i + 8] ^ byte_(k3.to_ulong());
    mtx[i + 12] = mtx[i + 12] ^ byte_(k4.to_ulong());
  }
}

/**********解密的逆变换函数**********/

// 函数：逆S盒变换：
void sub_bytes_inv(byte_ mtx[4 * 4])
{
  for (int i = 0; i < 16; ++i)
  {
    int row = mtx[i][7] * 8 + mtx[i][6] * 4 + mtx[i][5] * 2 + mtx[i][4];
    int col = mtx[i][3] * 8 + mtx[i][2] * 4 + mtx[i][1] * 2 + mtx[i][0];
    mtx[i] = S_inv[row][col];
  }
}

// 函数：逆行变换，以字节为单位循环右移：
void shift_rows_inv(byte_ mtx[4 * 4])
{
  // 第二行循环右移一位：
  byte_ temp = mtx[7];
  for (int i = 3; i > 0; --i) mtx[i + 4] = mtx[i + 3];
  mtx[4] = temp;
  // 第三行循环右移两位：
  for (int i = 0; i < 2; ++i)
  {
    temp = mtx[i + 8];
    mtx[i + 8] = mtx[i + 10];
    mtx[i + 10] = temp;
  }
  // 第四行循环右移三位：
  temp = mtx[12];
  for (int i = 0; i < 3; ++i) mtx[i + 12] = mtx[i + 13];
  mtx[15] = temp;
}

// 函数：逆列变换：
void mix_columns_inv(byte_ mtx[4 * 4])
{
  byte_ arr[4];
  for (int i = 0; i < 4; ++i)
  {
    for (int j = 0; j < 4; ++j) arr[j] = mtx[i + j * 4];

    mtx[i] = GF_mul(0x0e, arr[0]) ^ GF_mul(0x0b, arr[1]) ^
             GF_mul(0x0d, arr[2]) ^ GF_mul(0x09, arr[3]);
    mtx[i + 4] = GF_mul(0x09, arr[0]) ^ GF_mul(0x0e, arr[1]) ^
                 GF_mul(0x0b, arr[2]) ^ GF_mul(0x0d, arr[3]);
    mtx[i + 8] = GF_mul(0x0d, arr[0]) ^ GF_mul(0x09, arr[1]) ^
                 GF_mul(0x0e, arr[2]) ^ GF_mul(0x0b, arr[3]);
    mtx[i + 12] = GF_mul(0x0b, arr[0]) ^ GF_mul(0x0d, arr[1]) ^
                  GF_mul(0x09, arr[2]) ^ GF_mul(0x0e, arr[3]);
  }
}

/**********密钥扩展部分**********/

// 函数：将4个byte转为1个word：
word bytes_to_word(byte_& k1, byte_& k2, byte_& k3, byte_& k4)
{
  word result(0x00000000);
  word temp;
  temp = k1.to_ulong();  // K1
  temp <<= 24;
  result |= temp;
  temp = k2.to_ulong();  // K2
  temp <<= 16;
  result |= temp;
  temp = k3.to_ulong();  // K3
  temp <<= 8;
  result |= temp;
  temp = k4.to_ulong();  // K4
  result |= temp;
  return result;
}

// 函数：按字节循环左移一位：
word left_shift(word& rw)
{
  word high = rw << 8;
  word low = rw >> 24;
  return high | low;
}

// 函数：对输入word中的每一个字节进行S-盒变换：
word sub_word(word sw)
{
  word temp;
  for (int i = 0; i < 32; i += 8)
  {
    int row = sw[i + 7] * 8 + sw[i + 6] * 4 + sw[i + 5] * 2 + sw[i + 4];
    int col = sw[i + 3] * 8 + sw[i + 2] * 4 + sw[i + 1] * 2 + sw[i];
    byte_ val = S[row][col];
    for (int j = 0; j < 8; ++j) temp[i + j] = val[j];
  }
  return temp;
}

// 函数：密钥扩展，对128位密钥进行扩展得到w[4*(Nr+1)]：
void key_expansion(byte_ key[4 * Nk], word w[4 * (Nr + 1)])
{
  word temp;
  int i = 0;
  // w[]的前4个就是输入的key
  while (i < Nk)
  {
    w[i] = bytes_to_word(key[4 * i], key[4 * i + 1], key[4 * i + 2],
                         key[4 * i + 3]);
    ++i;
  }

  i = Nk;

  while (i < 4 * (Nr + 1))
  {
    temp = w[i - 1];  // 记录前一个word
    if (i % Nk == 0)
      w[i] = w[i - Nk] ^ sub_word(left_shift(temp)) ^ Rcon[i / Nk - 1];
    else
      w[i] = w[i - Nk] ^ temp;
    ++i;
  }
}

/**********加密和解密函数**********/

// 函数：对明文消息加密得到密文：
void encrypt(byte_ in[4 * 4], word w[4 * (Nr + 1)])
{
  word key[4];
  for (int i = 0; i < 4; ++i) key[i] = w[i];
  add_round_key(in, key);

  for (int round = 1; round < Nr; ++round)
  {
    sub_bytes(in);
    shift_rows(in);
    mix_columns(in);
    for (int i = 0; i < 4; ++i) key[i] = w[4 * round + i];
    add_round_key(in, key);
  }

  sub_bytes(in);
  shift_rows(in);
  for (int i = 0; i < 4; ++i) key[i] = w[4 * Nr + i];
  add_round_key(in, key);
}

// 函数：对密文消息解密得到明文：
void decrypt(byte_ in[4 * 4], word w[4 * (Nr + 1)])
{
  word key[4];
  for (int i = 0; i < 4; ++i) key[i] = w[4 * Nr + i];
  add_round_key(in, key);

  for (int round = Nr - 1; round > 0; --round)
  {
    shift_rows_inv(in);
    sub_bytes_inv(in);
    for (int i = 0; i < 4; ++i) key[i] = w[4 * round + i];
    add_round_key(in, key);
    mix_columns_inv(in);
  }

  shift_rows_inv(in);
  sub_bytes_inv(in);
  for (int i = 0; i < 4; ++i) key[i] = w[i];
  add_round_key(in, key);
}

#endif  // FUNCTIONS_H
