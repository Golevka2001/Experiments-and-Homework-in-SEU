#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

int main()
{
	//ѧ��Ϊ��1234567
	//����Ϊ��7654321
	//�󲻴���7654321����������
	int number = 7654321;

	vector<int>prime;	//��¼������sqrt(number)������
	prime.push_back(2);	//���ȴ��һ��2��ȥ

	for (int i = 2; i <= sqrt(number); i++)	//������2��sqrt(number)����������
	{
		bool flag = 1;
		for (vector<int>::iterator itr = prime.begin(); itr != prime.end(); itr++)	//�����Ѵ������������
		{
			if (i % (*itr) == 0)	//��������������д��ڿ���������ǰ������
			{
				flag = 0;	//flag��Ϊ0
				break;	//�������ڶ���ѭ������ʼ�ж���һ������
			}
		}
		if (flag)	//��flagΪ1�����ѷ��ֵ�����������������ǰ����
		{
			prime.push_back(i);	//�򽫵�ǰ������ӵ�������
		}
	}

	cout << "������sqrt(number)����������Ϊ:\n";
	int count = 1;
	for (vector<int>::iterator itr = prime.begin(); itr != prime.end(); itr++)
	{
		cout << *itr << '\t';
		if (count++ % 10 == 0)
		{
			cout << endl;	//10����һ����
		}
	}
	cout << endl << endl;

	vector<int>allPrime;	//��¼������number����������
	for (int i = 2; i <= number; i++)	//��2��number������������ӵ�vector��
	{
		allPrime.push_back(i);
	}

	for (vector<int>::iterator itr_1 = prime.begin(); itr_1 != prime.end(); itr_1++)	//����������sqrt(number)����������2֮��ʼ��
	{
		for (vector<int>::iterator itr_2 = allPrime.begin(); itr_2 != allPrime.end(); itr_2++)	//����������number������
		{
			if ((*itr_2) % (*itr_1) == 0)	//����ǰ�����ɱ�ĳ�������������޳�������
			{
				if (itr_2 < allPrime.end() - 1)	//������ж��Ǳ��������Խ��
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

	allPrime.insert(allPrime.begin(), prime.begin(), prime.end());	//��������sqrt(number)�������������
	cout << "������number����������Ϊ:\n";
	count = 1;
	for (vector<int>::iterator itr = allPrime.begin(); itr != allPrime.end(); itr++)
	{
		cout << *itr << '\t';	//�����������
		if (count++ % 10 == 0)
		{
			cout << endl;	//10����һ����
		}
	}
	cout << endl << endl;

	system("pause");
	return 0;
}
