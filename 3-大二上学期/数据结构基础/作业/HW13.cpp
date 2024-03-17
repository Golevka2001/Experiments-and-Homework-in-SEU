#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

//函数：折半查找
bool Search(vector<int>vec, int target, int& position)
{
	int low = 0;
	int mid;
	int high = vec.size() - 1;
	while (1)
	{
		mid = (low + high) / 2;	//计算mid

		if ((low == mid || high == mid)&&target!=vec[mid])	//若low或high与mid重合且还未找到
		{
			position = -1;
			return false;	//则查找失败
		}
		if (target == vec[low])	//若与low处数值相等
		{
			position = low;
			return true;
		}
		if (target == vec[mid])	//若与mid处数值相等
		{
			position = mid;
			return true;
		}
		if (target == vec[high])	//若与high处数值相等
		{
			position = high;
			return true;
		}

		//变换low或high的位置
		if (target < vec[mid])
		{
			high = mid - 1;
		}
		if (target > vec[mid])
		{
			low = mid + 1;
		}
	}
}


int main()
{
	srand(time(0));

	vector<int> vec(100);

	//随机填充：
	for (int i = 0; i < 100; i++)
	{
		vec[i] = rand() % 1000;	//范围：0-999
	}

	//打印原始数据：
	cout << "Initial:\n";
	for (int i = 0; i < 100; i++)
	{
		cout << vec[i] << '\t';
	}
	cout << endl << endl;

	//数据升序排序：
	sort(vec.begin(), vec.end());

	//打印排序后顺序：
	cout << "Ascending order:\n";
	for (int i = 0; i < 100; i++)
	{
		cout << vec[i] << '\t';
	}
	cout << endl << endl;

	//输入查找的目标数值：
	int target = 0;
	int position = 0;
	cout << "Target number: ";
	cin >> target;

	if (Search(vec, target, position))	//查找成功
	{
		cout << "\nFound\nPosition: " << position << endl << endl;	//打印成功+位置
	}
	else	//查找失败
	{
		cout << "\nNot Found\n\n";	//打印失败
	}

	system("pause");
	return 0;
}