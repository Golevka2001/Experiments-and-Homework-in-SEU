#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

int main()
{
	//学号为：12345678
	//反序为：87654321
	int a = 12345678;
	int b = 87654321;

	if (b > a)	//令a >= b
	{
		int temp = a;
		a = b;
		b = temp;
	}
	while (a % b)	//若b不整除a则继续循环
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
