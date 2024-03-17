// functions.h
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include <cstdlib>
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

#endif // FUNCTIONS_H
