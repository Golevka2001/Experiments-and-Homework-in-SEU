#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cmath>
using namespace std;

//函数：判断num是否为素数
bool primeJudge(int num)
{
	if (num % 6 != 1 && num % 6 != 5 && num != 2 && num != 3)//存在结论：大于等于5的素数均与6的倍数相邻，即不能表示为6n-1或6n+1的都不是素数
	{
		return false;
	}
	for (int i = 2; i < sqrt(num) + 1; i++)	//遍历2到√num的整数，判断是否整除
	{
		if (num % i == 0)	//若存在num的因数
		{
			return false;	//则num不是素数
		}
	}
	return true;	//否则，num是素数
}

//函数：求两个数的最大公因数
int gcd(int p, int q)
{
	if (q > p)	//使p大于等于q，若q大则交换两数
	{
		int temp = p;
		p = q;
		q = temp;
	}
	int r = p % q;	//r为p模q
	while (r)	//若r不为零，即q不整除p
	{
		p = q;
		q = r;
		r = p % q;	//则继续求模
	}
	return q;	//当q整除p时，r=0，结束循环，此时的q为最大公因数
}

//函数：求a^b(mod m)
int powerMod(int a, int b, int m)
{
	int result = 1;
	a = a % m;
	while (b > 0)
	{
		if (b % 2 == 1)
			result = (result * a) % m;
		b = b / 2;
		a = (a * a) % m;
	}
	return result;
}
int main()
{
	srand(time(0));

	//寻找两个大于100的素数
	int count = 0;
	int* prime = new int[2];
	prime[0] = 0;
	prime[1] = 0;
	while (count < 2)	//当count>1时，即已经找到了两个素数，结束循环
	{
		int num = rand() % 100 + 100;	//100-199随机数，即为寻找素数的范围
		if (num != prime[0] && primeJudge(num))	//若num没有重复且num为素数
		{
			prime[count++] = num;	//则将num存入prime数组中，且count自增1
		}
	}
	cout << "//Two prime numbers(found between 100-199): " << prime[0] << ", " << prime[1] << endl;
	int N = prime[0] * prime[1];
	int r = (prime[0] - 1) * (prime[1] - 1);	//r等于N的欧拉函数
	int e = 0;
	int d = 0;

	//寻找e：
	while (1)
	{
		e = rand() % (r - 2) + 2;	//随机一个2到r-1的整数
		if (gcd(e, r) == 1)	//若r与e互素
		{
			break;	//则已找到e，结束循环
		}
	}
	//寻找d：
	for (int i = 0;; i++)
	{
		if ((i * r + 1) % e == 0)	//若e整除i*r+1
		{
			d = (i * r + 1) / e;	//则此时e*d与1同余（模r）
			break;	//结束循环
		}
	}

	cout << "//N = " << N
		<< ", r = " << r
		<< ", e = " << e
		<< ", d = " << d
		<< ", Public Key: (" << N << ", " << e
		<< ") , Private Key: (" << N << ", " << d << ")"
		<< endl << endl;
	delete[]prime;	//将两个用于生成公钥私钥的素数销毁

	//输入数据
	int m = 0;
	cout << "Message needing encrypting:\n";
	cin >> m;

	//对数据进行分段：
	int pieces = 0;
	while (1)	//计算数据需要被分为几段
	{
		if (m / pow(10000, ++pieces) < 1)
		{
			break;
		}
	}
	int* message = new int[pieces];	//开辟空间存放分段后的数据
	for (int i = 0; i < pieces; i++)
	{
		message[i] = m % 10000;
		m = m / 10000;	//对数据进行分段
	}
	cout << "\n//Message is split into " << pieces << " pieces，as follows: \n";
	for (int i = pieces - 1; i > -1; i--)
	{
		cout << message[i] << '\t';
	}
	cout << endl << endl;

	//对数据进行加密：
	int* cipher = new int[pieces];	//开辟空间存放加密后的数据
	for (int i = 0; i < pieces; i++)
	{
		cipher[i] = powerMod(message[i], e, N);	//加密
	}
	cout << "Encrypted message: ";
	for (int i = pieces - 1; i > -1; i--)
	{
		cout << cipher[i] << '\t';
	}
	cout << endl;

	//对密文进行解密：
	int* result = new int[pieces];	//开辟空间存放解密后的数据
	for (int i = 0; i < pieces; i++)
	{
		result[i] = powerMod(cipher[i], d, N);	//解密
	}
	cout << "Decrypted message: ";
	for (int i = pieces - 1; i > -1; i--)
	{
		cout << result[i] << '\t';
	}
	cout << endl;

	//将分段的解密后的数据合并为一个整数：
	int mergedResult = 0;
	for (int i = 0; i < pieces; i++)
	{
		mergedResult += result[i] * pow(10000, i);
	}
	cout << "Merged message: " << mergedResult << endl << endl;

	delete[]message;
	delete[]cipher;
	delete[]result;

	system("pause");
	return 0;
}