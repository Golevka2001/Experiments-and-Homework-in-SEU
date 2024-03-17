#include<iostream>
#include<cstdlib>
#include<ctime>
#include<queue>
using namespace std;

template<class T>
struct BinTreeNode	//���ݽṹ�����������
{
	BinTreeNode(T d = 0)
		:data(d), leftChild(nullptr), rightChild(nullptr)
	{}
	~BinTreeNode()
	{}

	BinTreeNode* leftChild;	//ָ����������ָ��
	BinTreeNode* rightChild;	//ָ����������ָ��
	T data;	//����ý�������
};

template<class T>
struct BinTree	//���ݽṹ��������
{
	BinTree(int n = 0, BinTreeNode<T>* r = nullptr)
		:nodeNum(n), root(r) {}
	~BinTree() {}

	void CreatBinTree(queue<T> in, BinTreeNode<T>*& subTree, T refValue)	//�����������ĺ���
	{
		T item;
		if (!in.empty())	//��ջ��Ϊ��ʱ
		{
			item = in.front();	//��ȡ��ͷԪ��
			in.pop();	//������ͷԪ��
			if (item != refValue)	//��item��ֵ��Ϊ��ֵֹʱ
			{
				subTree = new BinTreeNode<T>(item);
				if (subTree == nullptr)
				{
					cerr << "����������\n\n";
					exit(1);
				}
				CreatBinTree(in, subTree->leftChild, -1);	//����������
				CreatBinTree(in, subTree->rightChild, -1);	//����������
			}
			else	//��itemΪ��ֵֹ
			{
				subTree = nullptr;	//��������ָ����Ϊ��ָ��
			}
		}
	}

	int nodeNum;	//�������
	BinTreeNode<T>* root;	//ָ�����ָ��
};

int main()
{
	srand(time(0));
	int n = rand() % 5 + 5;	//����õ��������Ľ����������Χ0-9��
	cout << n << endl << endl;
	queue<int> data;	//����һ�������������ݵ�ջ����Ϊ������������
	
	//���ɶ����������У�
	int elemCnt = 0;
	int endCnt = 0;
	for (int i = 0; i < 2 * n; i++)
	{
		if (rand() % 2)
		{
			if (elemCnt < n)
			{
				data.push(rand() % 10);	//�������ѹ��ջ��0-9��
				elemCnt++;
			}
			else
			{
				i--;
			}
		}
		else
		{
			if ((endCnt < elemCnt) || (elemCnt == n - 1 && endCnt < n + 1))
			{
				data.push(-1);	//��ֹ��־-1ѹ��ջ
				endCnt++;
			}
			else
			{
				i--;
			}
		}
	}
	data.push(-1);

	//��ӡ���У�
	queue<int>display = data;
	while (!display.empty())
	{
		int a = 0;
		a = display.front();
		display.pop();
		cout << a << endl;
	}

	BinTreeNode<int>* root = new BinTreeNode<int>;
	BinTree<int> tree(n, root);
	tree.CreatBinTree(data, root, -1);	//ִ���������ĺ���

	//û����д�Ӷ���������ȡĳ���Ĺ��ܣ���ͨ����ϵ�����֤���ɵ����Ƿ���ȷ��

	system("pause");
	return 0;
}