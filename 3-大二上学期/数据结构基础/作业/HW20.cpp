#include <iostream>
#include<cstdlib>
#include<ctime>
#include<vector>
using namespace std;


//函数：快速排序
void QuickSort(int left, int right, vector<int>& v)
{
	if (left >= right)
	{
		return;
	}
	int base = v[left];	//以首元素的关键字为基准
	int i = left, j = right;
	while (i < j)
	{
		while (v[j] >= base && i < j)	//j向左移动，直到找到小于基准关键字的停下
		{
			j--;
		}
		while (v[i] <= base && i < j)	//i再向右移动，直到找到大于基准关键字的停下
		{
			i++;
		}
		if (i < j)	//若左边的关键字小于右边的
		{
			swap(v[i], v[j]);	//则交换
		}
	}
	//将基准数归位
	v[left] = v[i];
	v[i] = base;
	QuickSort(left, i - 1, v);	//递归左边
	QuickSort(i + 1, right, v);	//递归右边
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

	QuickSort(0, size - 1, initial);

	for (int i = 0; i < size; i++)
	{
		cout << initial[i] << '\t';
	}
	cout << endl;

	system("pause");
	return 0;
}