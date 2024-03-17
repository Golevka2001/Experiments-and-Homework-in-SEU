#include <iostream>
#include<cstdlib>
#include<ctime>
#include<vector>
using namespace std;


//��������������
void QuickSort(int left, int right, vector<int>& v)
{
	if (left >= right)
	{
		return;
	}
	int base = v[left];	//����Ԫ�صĹؼ���Ϊ��׼
	int i = left, j = right;
	while (i < j)
	{
		while (v[j] >= base && i < j)	//j�����ƶ���ֱ���ҵ�С�ڻ�׼�ؼ��ֵ�ͣ��
		{
			j--;
		}
		while (v[i] <= base && i < j)	//i�������ƶ���ֱ���ҵ����ڻ�׼�ؼ��ֵ�ͣ��
		{
			i++;
		}
		if (i < j)	//����ߵĹؼ���С���ұߵ�
		{
			swap(v[i], v[j]);	//�򽻻�
		}
	}
	//����׼����λ
	v[left] = v[i];
	v[i] = base;
	QuickSort(left, i - 1, v);	//�ݹ����
	QuickSort(i + 1, right, v);	//�ݹ��ұ�
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