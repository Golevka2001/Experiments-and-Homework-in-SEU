// functions.h
// 定义了RSA算法中所用到的一系列函数
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include <QString>
#include <QStringList>
using namespace std;

// 函数：判断p是否为素数，是素数返回1，否则返回0：
static bool is_prime(int num)
{
    if(num < 2)
        return 0;
    int devider = 2;
    for(; devider <= (num / 2); ++devider)
       if(num % devider == 0)
           return 0;
    return 1;
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

// 函数：生成密钥，其中p、q互质，公钥为P{e, n}，私钥为S{d, n}
static void generate_key(int p, int q, int &e, int &d, int &n)
{
    n = p * q;
    // n的欧拉函数（在调用该函数之前已对p、q做出判断，保证p、q不相等且都为素数）：
    int Euler_n = (p - 1) * (q - 1);
    // 随机选择一个e(2<e<t) ,使得gcd(t,e)=1：
    e = rand() % (Euler_n - 1) + 2;
    while (gcd(Euler_n, e) != 1)
        e = rand() % (Euler_n - 1) + 2;
    // 计算e的模Euler_n逆元d：
    d = inv(e, Euler_n);
}

// 函数：二进制转换，返回二进制位数：
static int oct_to_bin(int num, int bin_num[])
{
    int i = 0, mod = 0;
    // 转换为二进制，逆向暂存temp[]数组中
    while(num != 0)
    {
        mod = num % 2;
        bin_num[i] = mod;
        num = num / 2;
        i++;
    }
    return i;
}

// 函数：反复平方求幂：
static int modular_exonentiation(int a, int b, int m)
{
    int c = 0, bin_num[1000];
    long long d = 1;
    int k = oct_to_bin(b, bin_num) - 1;
    for(int i = k; i >= 0; --i)
    {
        c = 2 * c;
        d = (d * d) % m;
        if(bin_num[i] == 1)
        {
            c = c + 1;
            d = (d * a) % m;
        }
    }
    return d;
}

// 函数：RSA加密：
static void encrypt(int e, const int n, const QString plain, QString &cipher)
{
    for (int i = 0; i < plain.size(); ++i)
        cipher.append(QString::number(modular_exonentiation(int(plain[i].toLatin1()), e, n), 10) + ' ');
}

// 函数：RSA解密：
static void decrypt(int d, const int n, const QString cipher, QString &plain)
{
    QStringList cipher_list = cipher.split(" ");
    for (QString str : cipher_list)
        plain.append(QChar(modular_exonentiation(str.toInt(), d, n)));

}

#endif // FUNCTIONS_H
