#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

class GreatestHeap
{
public:
	GreatestHeap(int* array)	//参数为用于生成堆的数组
	{
		heap.resize(*array + 1);	//分配空间
		heap.clear();
		for (int i = 0; i < *array + 1; i++)
		{
			heap.push_back(*(array + i));	//填充
		}
	}

	//函数：交换堆中两元素
	void Swap(int positionA, int positionB)
	{
		int temp = heap[positionA];
		heap[positionA] = heap[positionB];
		heap[positionB] = temp;
	}

	//函数：堆调整
	void Adjust(int position)
	{
		int child = 0;
		bool left = 1;
		for (int i = position; 2 * i <= heap[0]; i = child)
		{
			child = 2 * i;	//左child的下标
			if (child + 1 <= heap[0] && heap[child + 1] > heap[child])	//若存在右child且右child大于左child
			{
				child++;	//变为右child
				left = 0;
			}
			if (heap[child] > heap[i])	//若child更大
			{
				Swap(child, i);	//则与child交换
			}
			else
			{
				break;
			}
		}
	}

	//函数：插入
	void Insert(int data)	//参数为要插入的元素
	{
		heap.push_back(data);
		heap[0]++;
		for (int i = heap[0]; i >= 1; i = i / 2)
		{
			Adjust(i);
		}
	}

	//函数：显示堆储存的内容
	void Display()
	{
		for (int i = 0; pow(2, i) < heap[0]; i++)
		{
			cout << i << '\t';
			for (int j = 0; j < pow(2, i) && pow(2, i) + j <= heap[0]; j++)
			{
				cout << heap[pow(2, i) + j] << "  ";
			}
			cout << endl;
		}

		cout << endl << endl;
	}


	vector<int>heap;
};

int main()
{
	srand(time(0));

	//生成用于填充堆的原始数据：
	int initialData[27] = { 0 };
	initialData[0] = 26;
	cout << "Initial data:\n";
	for (int i = 0; i < 26; i++)
	{
		initialData[i + 1] = rand() % 90 + 10;	//两位数随机数填充
		cout << initialData[i + 1] << "  ";
	}
	cout << endl << endl;

	//创建堆：
	GreatestHeap GHeap(initialData);
	cout << "Before adjustmen:\n";
	GHeap.Display();

	//调整为最大堆：
	for (int i = initialData[0]; i > 0; i--)	//从堆中最后一个元素开始向前遍历
	{
		GHeap.Adjust(i);	//依次调整遍历到的元素
	}
	cout << "After adjustment:\n";
	GHeap.Display();

	//插入元素33：
	GHeap.Insert(100);
	GHeap.Display();

	system("pause");
	return 0;
}