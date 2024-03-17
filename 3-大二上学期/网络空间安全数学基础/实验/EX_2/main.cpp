#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cmath>
using namespace std;

//�������ж�num�Ƿ�Ϊ����
bool primeJudge(int num)
{
	if (num % 6 != 1 && num % 6 != 5 && num != 2 && num != 3)//���ڽ��ۣ����ڵ���5����������6�ı������ڣ������ܱ�ʾΪ6n-1��6n+1�Ķ���������
	{
		return false;
	}
	for (int i = 2; i < sqrt(num) + 1; i++)	//����2����num���������ж��Ƿ�����
	{
		if (num % i == 0)	//������num������
		{
			return false;	//��num��������
		}
	}
	return true;	//����num������
}

//�����������������������
int gcd(int p, int q)
{
	if (q > p)	//ʹp���ڵ���q����q���򽻻�����
	{
		int temp = p;
		p = q;
		q = temp;
	}
	int r = p % q;	//rΪpģq
	while (r)	//��r��Ϊ�㣬��q������p
	{
		p = q;
		q = r;
		r = p % q;	//�������ģ
	}
	return q;	//��q����pʱ��r=0������ѭ������ʱ��qΪ�������
}

//��������a^b(mod m)
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

	//Ѱ����������100������
	int count = 0;
	int* prime = new int[2];
	prime[0] = 0;
	prime[1] = 0;
	while (count < 2)	//��count>1ʱ�����Ѿ��ҵ�����������������ѭ��
	{
		int num = rand() % 100 + 100;	//100-199���������ΪѰ�������ķ�Χ
		if (num != prime[0] && primeJudge(num))	//��numû���ظ���numΪ����
		{
			prime[count++] = num;	//��num����prime�����У���count����1
		}
	}
	cout << "//Two prime numbers(found between 100-199): " << prime[0] << ", " << prime[1] << endl;
	int N = prime[0] * prime[1];
	int r = (prime[0] - 1) * (prime[1] - 1);	//r����N��ŷ������
	int e = 0;
	int d = 0;

	//Ѱ��e��
	while (1)
	{
		e = rand() % (r - 2) + 2;	//���һ��2��r-1������
		if (gcd(e, r) == 1)	//��r��e����
		{
			break;	//�����ҵ�e������ѭ��
		}
	}
	//Ѱ��d��
	for (int i = 0;; i++)
	{
		if ((i * r + 1) % e == 0)	//��e����i*r+1
		{
			d = (i * r + 1) / e;	//���ʱe*d��1ͬ�ࣨģr��
			break;	//����ѭ��
		}
	}

	cout << "//N = " << N
		<< ", r = " << r
		<< ", e = " << e
		<< ", d = " << d
		<< ", Public Key: (" << N << ", " << e
		<< ") , Private Key: (" << N << ", " << d << ")"
		<< endl << endl;
	delete[]prime;	//�������������ɹ�Կ˽Կ����������

	//��������
	int m = 0;
	cout << "Message needing encrypting:\n";
	cin >> m;

	//�����ݽ��зֶΣ�
	int pieces = 0;
	while (1)	//����������Ҫ����Ϊ����
	{
		if (m / pow(10000, ++pieces) < 1)
		{
			break;
		}
	}
	int* message = new int[pieces];	//���ٿռ��ŷֶκ������
	for (int i = 0; i < pieces; i++)
	{
		message[i] = m % 10000;
		m = m / 10000;	//�����ݽ��зֶ�
	}
	cout << "\n//Message is split into " << pieces << " pieces��as follows: \n";
	for (int i = pieces - 1; i > -1; i--)
	{
		cout << message[i] << '\t';
	}
	cout << endl << endl;

	//�����ݽ��м��ܣ�
	int* cipher = new int[pieces];	//���ٿռ��ż��ܺ������
	for (int i = 0; i < pieces; i++)
	{
		cipher[i] = powerMod(message[i], e, N);	//����
	}
	cout << "Encrypted message: ";
	for (int i = pieces - 1; i > -1; i--)
	{
		cout << cipher[i] << '\t';
	}
	cout << endl;

	//�����Ľ��н��ܣ�
	int* result = new int[pieces];	//���ٿռ��Ž��ܺ������
	for (int i = 0; i < pieces; i++)
	{
		result[i] = powerMod(cipher[i], d, N);	//����
	}
	cout << "Decrypted message: ";
	for (int i = pieces - 1; i > -1; i--)
	{
		cout << result[i] << '\t';
	}
	cout << endl;

	//���ֶεĽ��ܺ�����ݺϲ�Ϊһ��������
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