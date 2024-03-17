#include <iostream>
#include<cstdlib>
#include<ctime>
#include<vector>
using namespace std;

//������·���������㷨
void InsertSort(vector<int>& v)
{
	int size = v.size();	//��Ҫ���ٿռ�Ĵ�С
	vector<int>sorted(size);	//���ٿռ�
	sorted[0] = v[0];	//0��Ԫ����Ϊ�м�Ԫ��
	int first = 0, final = 0;	//����ָ�룬firstָ��ͷ�ˣ��ؼ�����С����finalָ��β�ˣ��ؼ�����󣩣���ʼʱ��ָ��0��Ԫ��

	cout << endl;
	for (int j = 0; j < size; j++)
	{
		cout << sorted[j] << '\t';
	}
	cout << endl;

	for (int i = 1; i < size; i++)
	{
		if (v[i] < sorted[first])	//С����С�ؼ���
		{
			first = (first + size -1) % size;	//ѭ�����У�������Ҫ-1����sizeȡģ
			sorted[first] = v[i];	//����Ԫ�طŽ�����
		}
		else if (v[i] > sorted[final])	//�������ؼ���
		{
			final++;	//final����һλ����Ϊfinalһ��ʼ�ڶ�ͷ�����Բ����±�Խ�磬�Ͳ��ö�sizeȡģ
			sorted[final] = v[i];
		}
		else	//�������С�ؼ���֮��
		{
			//�۰����
			int low = 0, high = (final - first + size) % size;
			int temp(first), end(high);
			while (low <= high)
			{
				int m = (low + high) / 2;
				if (v[i] < sorted[(m + temp + size) % size])
				{
					high = m - 1;
				}
				else
				{
					low = m + 1;
				}
			}
			for (int j = end; j >= high + 1; --j) {
				sorted[(j + temp + 1 + size) % size] = sorted[(j + temp + size) % size];
			}
			sorted[(high + temp + 1 + size) % size] = v[i];
			final++;
		}
		for (int j = 0; j < size; j++)
		{
			cout << sorted[j] << '\t';
		}
		cout << endl;
	}
	for (int i = 0; i < size; i++)
	{
		v[i] = sorted[(first + i) % size];
	}
}


int main()
{
	const int size = 15;
	srand(time(0));
	vector<int>initial(size);
	for (int i = 0; i < size; i++)
	{
		initial[i] = rand() % 100;
	}

	for (int i = 0; i < size; i++)
	{
		cout << initial[i] << '\t';
	}
	cout << endl;

	InsertSort(initial);

	for (int i = 0; i < size; i++)
	{
		cout << initial[i] << '\t';
	}
	cout << endl;

	system("pause");
	return 0;
}