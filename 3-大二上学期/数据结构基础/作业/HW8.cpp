#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

struct Node
{
	int index;
	int data;
};

Node getParent(Node* root, int index)	//���ظ��ڵ�
{
	int parentIndex = index / 2;
	return *(root + parentIndex);
}

Node getRightChild(Node* root, int index)	//�����Һ���
{
	int rightChildIndex = index * 2 + 1;
	return *(root + rightChildIndex);
}
int main()
{
	srand(time(0));
	int n = rand() % 10 + 10;	//����õ��������Ľ����������Χ10-19��
	cout << n << endl << endl;
	Node* Tree = new Node[n + 1];

	for (int i = 0; i < n; i++)
	{
		int tempData = rand() % 10;	//���һ��0-9��������Ϊ��������������
		Tree[i + 1].index = i + 1;	//�����
		Tree[i + 1].data = tempData;	//�������
		cout << i + 1 << ":\t" << tempData << endl;
	}

	int index = 0;
	cout << "\nGet parent:\n";
	cin >> index;
	cout << "\nParent's index: " << getParent(Tree, index).index << "\tParent's data: " << getParent(Tree, index).data << endl;

	cout << "\nGet right child:\n";
	cin >> index;
	cout << "\nRight child's index: " << getRightChild(Tree, index).index << "\tRight child's data: " << getRightChild(Tree, index).data << endl;

	
	system("pause");
	return 0;
}