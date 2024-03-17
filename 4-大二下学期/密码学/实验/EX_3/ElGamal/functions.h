// functions.h
// 定义了RSA算法中所用到的一系列函数
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <cstdlib>
#include <ctime>
#include <vector>
#include <QString>
#include <QStringList>
using namespace std;

// 函数：判断p是否为素数，是素数返回1，否则返回0：
static bool is_prime(const int num)
{
    if(num < 2)
        return 0;
    int devider = 2;
    for(; devider <= (num / 2); ++devider)
       if(num % devider == 0)
           return 0;
    return 1;
}

// 函数：快速幂算法，返回a^b mod p：
static int pow_mod(const int a, int b, const int p)
{
    int ans = 1;
    int tmp = a % p;
    while (b)
    {
        if (b & 1)
            ans = (ans*tmp) % p;
        b >>= 1;
        tmp = (tmp*tmp) % p;
    }
    return ans % p;
}

// 函数：求本原元：
static int primitive(const int p)
{
    bool flag;
    vector<int> arr;
    for (int i = 2; i < p; ++i)
    {
        flag = 1;
        for (int j = 2; j < p - 1; ++j)
            if (((p-1) % j == 0) && (pow_mod(i, j, p) == 1))
                flag = 0;
        if (flag)
            arr.push_back(i);
    }
    return arr[rand() % arr.size()];
}

// 函数：返回最大公因数：
static int gcd(int a, int b)
{
    return (b == 0) ? a : gcd(b, a % b);
}

// 函数：求解二元一次不等式，并返回gcd(a, b)：
static int exgcd(int a, int b, int& x, int& y)
{
    if (b == 0)
    {
        x = 1, y = 0;
        return a;
    }
    int sum = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return sum;
}

// 函数：求解模逆元：
static int inv(int a, int m)
{
    int x, y;
    exgcd(a, m, x, y);
    return (x % m + m) % m;
}

// 函数：生成密钥，其中q为素数，公钥为P{q, alpha, YA}，私钥为S{XA}
static void generate_key(const int q, int &alpha, int &YA, int &XA)
{
    alpha = primitive(q);
    XA = rand() % (q-1) + 1;
    YA = pow_mod(alpha, XA, q);
}

// 函数：ElGamal加密：
static void encrypt(const int q, const int alpha, const int YA, const QString plain, QString& cipher)
{
    int k = 0;
    QString C1, C2;
    for (int i = 0; i < plain.size(); ++i)
    {
        k = 0;
        while (gcd(k, (q-1)) != 1)
              k = rand() % (q-1) + 1;
        C1.append(QString::number(pow_mod(alpha, k, q), 10) + ' ');
        C2.append(QString::number((int(plain[i].toLatin1()) * pow_mod(YA, k, q)) % q, 10) + ' ');
    }
    cipher.append(C1 + '\n' + C2);
}

// 函数：ElGamal解密：
static void decrypt(const int q, const int XA, const QString cipher, QString& plain)
{
    QStringList cipher_list = cipher.split('\n');
    QStringList C1 = cipher_list[0].split(' ');
    QStringList C2 = cipher_list[1].split(' ');
    for (int i = 0; i < C2.size(); ++i)
        plain.append(QChar((C2[i].toInt() * inv(pow_mod(C1[i].toInt(), XA, q), q)) % q));
}

#endif // FUNCTIONS_H
