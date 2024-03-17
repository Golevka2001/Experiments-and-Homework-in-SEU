#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

class GreatestHeap
{
public:
	GreatestHeap(int* array)	//����Ϊ�������ɶѵ�����
	{
		heap.resize(*array + 1);	//����ռ�
		heap.clear();
		for (int i = 0; i < *array + 1; i++)
		{
			heap.push_back(*(array + i));	//���
		}
	}

	//����������������Ԫ��
	void Swap(int positionA, int positionB)
	{
		int temp = heap[positionA];
		heap[positionA] = heap[positionB];
		heap[positionB] = temp;
	}

	//�������ѵ���
	void Adjust(int position)
	{
		int child = 0;
		bool left = 1;
		for (int i = position; 2 * i <= heap[0]; i = child)
		{
			child = 2 * i;	//��child���±�
			if (child + 1 <= heap[0] && heap[child + 1] > heap[child])	//��������child����child������child
			{
				child++;	//��Ϊ��child
				left = 0;
			}
			if (heap[child] > heap[i])	//��child����
			{
				Swap(child, i);	//����child����
			}
			else
			{
				break;
			}
		}
	}

	//����������
	void Insert(int data)	//����ΪҪ�����Ԫ��
	{
		heap.push_back(data);
		heap[0]++;
		for (int i = heap[0]; i >= 1; i = i / 2)
		{
			Adjust(i);
		}
	}

	//��������ʾ�Ѵ��������
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

	//�����������ѵ�ԭʼ���ݣ�
	int initialData[27] = { 0 };
	initialData[0] = 26;
	cout << "Initial data:\n";
	for (int i = 0; i < 26; i++)
	{
		initialData[i + 1] = rand() % 90 + 10;	//��λ����������
		cout << initialData[i + 1] << "  ";
	}
	cout << endl << endl;

	//�����ѣ�
	GreatestHeap GHeap(initialData);
	cout << "Before adjustmen:\n";
	GHeap.Display();

	//����Ϊ���ѣ�
	for (int i = initialData[0]; i > 0; i--)	//�Ӷ������һ��Ԫ�ؿ�ʼ��ǰ����
	{
		GHeap.Adjust(i);	//���ε�����������Ԫ��
	}
	cout << "After adjustment:\n";
	GHeap.Display();

	//����Ԫ��33��
	GHeap.Insert(100);
	GHeap.Display();

	system("pause");
	return 0;
}