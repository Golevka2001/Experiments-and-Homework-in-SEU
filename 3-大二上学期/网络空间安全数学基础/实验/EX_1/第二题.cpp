#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

int main()
{
	//ѧ��Ϊ��12345678
	//����Ϊ��87654321
	int a = 12345678;
	int b = 87654321;

	if (b > a)	//��a >= b
	{
		int temp = a;
		a = b;
		b = temp;
	}
	while (a % b)	//��b������a�����ѭ��
	{
		int temp = a % b;
		a = b;
		b = temp;
	}
	int gcd = b;
	cout << "(a, b) = " << gcd << endl << endl;

	a = 12345678;
	b = 87654321;

	int lcm = a * b / gcd;
	cout << "[a, b] = " << lcm << endl << endl;

	system("pause");
	return 0;
}
