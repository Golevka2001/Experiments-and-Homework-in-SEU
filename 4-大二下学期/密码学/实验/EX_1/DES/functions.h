// functions.h
// 定义了DES算法中所用到的一系列函数
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iomanip>
#include <string>
#include <vector>
#include <bitset>
#include <cmath>
#include "matrices.h"
using namespace std;

// 函数：字符串（ASCII）转为二进制：
bitset<64> ascii_str_to_bitset(const string str)
{
    bitset<64> bits;
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            bits[i * 8 + 7 - j] = ((str[i] >> j) & 1);
    return bits;
}

// 函数：字符串（HEX）转为二进制：
bitset<64> hex_str_to_bitset(const string str)
{
    bitset<64> bits;
    for (int i = 0; i < 16; ++i)
    {
        int oct = 0;
        if (str[i] >= '0' && str[i] <= '9')
            oct = int(str[i] - '0');
        else if (str[i] >= 'A' && str[i] <= 'F')
            oct = int(str[i] - 'A') + 10;
        else
            oct = 0;
        bitset<4> bin(oct);
        for (int j = 0; j < 4; ++j)
            bits[i * 4 + j] = bin[3 - j];
    }
    return bits;
}

// 函数：二进制转为字符串（ASCII）：
string bitset_to_ascii_str(const bitset<64> bits)
{
    string str = "00000000";
    for (int i = 0; i < 8; ++i)
    {
        int temp_num = 0;
        for (int j = 0; j < 8; ++j)
            temp_num += bits[i * 8 + j] * pow(2, 7 - j);
        str[i] = temp_num;
    }
    return str;
}

// 函数：二进制转为字符串（HEX）:
string bitset_to_hex_str(const bitset<64> bits)
{
    string str = "0000000000000000";
    for (int i = 0; i < 16; ++i)
    {
        int temp_num = bits[i * 4] * 8 + bits[i * 4 + 1] * 4 + bits[i * 4 + 2] * 2 + bits[i * 4 + 3];
        str[i] = (temp_num < 10) ? ('0' + temp_num) : ('A' + temp_num - 10);
    }
    return str;
}

// 函数：左移：
bitset<28> left_shift(const bitset<28> input, const int bit)
{
    bitset<28> output;
    for (int i = 0; i < 28; ++i)
        output[i] = input[(i + bit) % 28];
    return output;
}

// 函数：生成16个48位的子密钥：
void generate_sub_keys(const bitset<64> init_key, bitset<48>(&sub_keys)[16])
{
    // 按表PC_1进行置换，得到去除奇偶校验位的密钥：
    bitset<56> real_key;
    for (int i = 0; i < 56; ++i)
        real_key[i] = init_key[PC_1[i] - 1];
    // 前28位与后28位分别填入left和rjght中：
    bitset<28> left;
    bitset<28> right;
    for (int j = 0; j < 28; ++j)
    {
        left[j] = real_key[j];
        right[j] = real_key[j + 28];
    }
    // 生成16个子密钥：
    for (int i = 0; i < 16; ++i)
    {
        // 左移：
        left = left_shift(left, shift_bits[i]);
        right = left_shift(right, shift_bits[i]);
        // 合并left与D_i：
        for (int j = 0; j < 28; ++j)
            real_key[j] = left[j];
        for (int j = 28; j < 56; ++j)
            real_key[j] = right[j - 28];
        // 按表PC_2进行压缩置换，由56位变为48位：
        bitset<48> comp_key;
        for (int j = 0; j < 48; ++j)
            comp_key[j] = real_key[PC_2[j] - 1];
        // 赋值给第i个子密钥：
        sub_keys[i] = comp_key;
    }
}

// 函数：将32位扩展为48位：
bitset<48> expend(const bitset<32> input)
{
    bitset<48> output;
    for (int i = 0; i < 48; ++i)
        output[i] = input[E[i] - 1];
    return output;
}

// 函数：加密操作的内部函数f：
bitset<32> f(const bitset<32> input, const bitset<48> key)
{
    // 按表E进行扩展至48位，再与key进行异或操作：
    bitset<48> bits_48 = expend(input) ^ key;
    // 分为8组，每组在对应的S盒中查找对应的输出结果：
    bitset<32> temp_output;
    for (int i = 0; i < 8; ++i)
    {
        // 确定在S盒中对应的行、列号：
        int row = bits_48[i * 6] * 2 + bits_48[i * 6 + 5];  // 取每组的第一位和最后一位组成的二进制数作为行号
        int column = bits_48[i * 6 + 1] * 8 + bits_48[i * 6 + 2] * 4 + bits_48[i * 6 + 3] * 2 + bits_48[i * 6 + 4];  // 取中间四位组成的二进制数作为列号
        // 查S盒得到变换的数，并转为二进制：
        bitset<4> bits_4(S[i][row][column]);
        // 将8组4比特数（倒序）合并为32位序列：
        for (int j = 0; j < 4; ++j)
            temp_output[i * 4 + j] = bits_4[3 - j];
    }
    // 再按表P进行置换：
    bitset<32> output;
    for (int i = 0; i < 32; ++i)
        output[i] = temp_output[P[i] - 1];
    // 返回：
    return output;
}

// 函数：对明文消息进行加密得到密文：
void encrypt(const bitset<64> plain, const bitset<64> key, bitset<64>(&cipher))
{
    // 由初始密钥生成16个子密钥，并存储在sub_keys中：
    bitset<48> sub_keys[16];
    generate_sub_keys(key, sub_keys);
    // 将明文按表IP进行初始置换：
    bitset<64> cur_bits;
    for (int i = 0; i < 64; ++i)
        cur_bits[i] = plain[IP[i] - 1];
    // 前32位和后32位分别填入left和right中：
    bitset<32> left;
    bitset<32> right;
    for (int i = 0; i < 32; ++i)
    {
        left[i] = cur_bits[i];
        right[i] = cur_bits[i + 32];
    }
    // 经历16轮迭代：
    for (int i = 0; i < 16; ++i)
    {
        bitset<32> temp_right = right;
        right = left ^ f(right, sub_keys[i]);
        left = temp_right;
    }
    // 合并left和right，并按表IP_inverse进行逆置换：
    for (int i = 0; i < 64; ++i)
        cipher[i] = (IP_inverse[i] - 1 < 32) ? right[IP_inverse[i] - 1] : left[IP_inverse[i] - 1 - 32];
}

// 函数：对密文进行解密得到明文：
void decrypt(const bitset<64> cipher, const bitset<64> key, bitset<64>(&plain))
{
    // 由初始密钥生成16个子密钥，并存储在sub_keys中：
    bitset<48> sub_keys[16];
    generate_sub_keys(key, sub_keys);
    // 将明文按表IP进行初始置换：
    bitset<64> cur_bits;
    for (int i = 0; i < 64; ++i)
        cur_bits[i] = cipher[IP[i] - 1];
    // 前32位和后32位分别填入left和right中：
    bitset<32> left;
    bitset<32> right;
    for (int i = 0; i < 32; ++i)
    {
        left[i] = cur_bits[i];
        right[i] = cur_bits[i + 32];
    }
    // 经历16轮迭代：
    for (int i = 0; i < 16; ++i)
    {
        bitset<32> temp_right = right;
        right = left ^ f(right, sub_keys[15 - i]);
        left = temp_right;
    }
    // 合并left和right，并按表IP_inverse进行逆置换：
    for (int i = 0; i < 64; ++i)
        plain[i] = (IP_inverse[i] - 1 < 32) ? right[IP_inverse[i] - 1] : left[IP_inverse[i] - 1 - 32];
}


#endif // FUNCTIONS_H
