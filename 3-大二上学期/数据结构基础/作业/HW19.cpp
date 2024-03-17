#include <iostream>
#include<cstdlib>
#include<ctime>
#include<vector>
using namespace std;

//函数：路插入排序算法
void InsertSort(vector<int>& v)
{
	int size = v.size();	//需要开辟空间的大小
	vector<int>sorted(size);	//开辟空间
	sorted[0] = v[0];	//0号元素作为中间元素
	int first = 0, final = 0;	//两个指针，first指向头端（关键字最小），final指向尾端（关键字最大），初始时都指向0号元素

	cout << endl;
	for (int j = 0; j < size; j++)
	{
		cout << sorted[j] << '\t';
	}
	cout << endl;

	for (int i = 1; i < size; i++)
	{
		if (v[i] < sorted[first])	//小于最小关键字
		{
			first = (first + size -1) % size;	//循环序列，所以需要-1并对size取模
			sorted[first] = v[i];	//将该元素放进序列
		}
		else if (v[i] > sorted[final])	//大于最大关键字
		{
			final++;	//final后移一位，因为final一开始在队头，所以不会下标越界，就不用对size取模
			sorted[final] = v[i];
		}
		else	//在最大最小关键字之间
		{
			//折半查找
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