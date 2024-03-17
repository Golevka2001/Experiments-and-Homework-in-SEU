#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

int main()
{
	//学号为：1234567
	//反序为：7654321
	//求不大于7654321的所有素数
	int number = 7654321;

	vector<int>prime;	//记录不大于sqrt(number)的素数
	prime.push_back(2);	//首先存放一个2进去

	for (int i = 2; i <= sqrt(number); i++)	//遍历从2到sqrt(number)的所有整数
	{
		bool flag = 1;
		for (vector<int>::iterator itr = prime.begin(); itr != prime.end(); itr++)	//遍历已储存的所有素数
		{
			if (i % (*itr) == 0)	//若所储存的素数中存在可以整除当前整数的
			{
				flag = 0;	//flag设为0
				break;	//并结束第二层循环，开始判断下一个整数
			}
		}
		if (flag)	//若flag为1，即已发现的素数都不可整除当前整数
		{
			prime.push_back(i);	//则将当前整数添加到素数中
		}
	}

	cout << "不大于sqrt(number)的所有素数为:\n";
	int count = 1;
	for (vector<int>::iterator itr = prime.begin(); itr != prime.end(); itr++)
	{
		cout << *itr << '\t';
		if (count++ % 10 == 0)
		{
			cout << endl;	//10个数一换行
		}
	}
	cout << endl << endl;

	vector<int>allPrime;	//记录不大于number的所有素数
	for (int i = 2; i <= number; i++)	//将2到number的所有整数添加到vector中
	{
		allPrime.push_back(i);
	}

	for (vector<int>::iterator itr_1 = prime.begin(); itr_1 != prime.end(); itr_1++)	//遍历不大于sqrt(number)的素数（从2之后开始）
	{
		for (vector<int>::iterator itr_2 = allPrime.begin(); itr_2 != allPrime.end(); itr_2++)	//遍历不大于number的整数
		{
			if ((*itr_2) % (*itr_1) == 0)	//若当前整数可被某素数整除，则剔除该整数
			{
				if (itr_2 < allPrime.end() - 1)	//这里的判断是避免迭代器越界
				{
					itr_2 = allPrime.erase(itr_2);
				}
				else
				{
					allPrime.erase(itr_2);
					break;
				}
			}
		}
	}

	allPrime.insert(allPrime.begin(), prime.begin(), prime.end());	//将不大于sqrt(number)的素数插入回来
	cout << "不大于number的所有素数为:\n";
	count = 1;
	for (vector<int>::iterator itr = allPrime.begin(); itr != allPrime.end(); itr++)
	{
		cout << *itr << '\t';	//输出所有素数
		if (count++ % 10 == 0)
		{
			cout << endl;	//10个数一换行
		}
	}
	cout << endl << endl;

	system("pause");
	return 0;
}
