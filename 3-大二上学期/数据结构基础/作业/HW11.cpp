#include<iostream>
#include<vector>
#include<queue>
#include<cmath>
using namespace std;


//�ࣺ���������
template<class T>
class BinTreeNode
{
public:
	BinTreeNode(BinTreeNode<T>* lC = nullptr, BinTreeNode<T>* rC = nullptr, bool lF = 1, bool rF = 1, T d = 0)
		:leftChild(lC), rightChild(rC), leftFlag(lF), rightFlag(rF), data(d) {}
	BinTreeNode<T>* leftChild;	//����Ů��ǰ��
	BinTreeNode<T>* rightChild;	//����Ů����
	bool leftFlag;	//Ϊ0ʱ��û������Ů��leftChild��ʾǰ����Ϊ1ʱ��ָ������Ů
	bool rightFlag;	//ͬ��
	T data;	//����
};


//�ࣺ������
template<class T>
class BinTree
{
public:
	BinTree(BinTreeNode<T>* r = nullptr)
		:root(r) {}

	/*
	//������������/�Ҳ����½��
	bool InsertChild(const T& d, BinTreeNode<T>* n, bool lr)	//����Ϊ���½ڵ�����ݡ�ָ��Ҫ���뵽�Ľ��ָ�룬������/�ң�0/1��
	{
		if ((lr == 0 && n->leftChild != nullptr)
			|| (lr == 1 && n->rightChild != nullptr))	//��Ҫ���뵽������ң���������Ѵ������ң�����
		{
			return false;	//����ֱ�Ӳ��룬����false
		}

		if (lr)	//���뵽�����
		{
			n->rightChild = new BinTreeNode<T>(nullptr, nullptr, d);
		}
		else	//���뵽�����
		{
			n->leftChild = new BinTreeNode<T>(nullptr, nullptr, d);
		}
		nodeNum++;	//�����+1
		return true;	//����ɹ�������true
	}
	*/

	//�������������
	vector<T> InOrderTraversal()	//����ֵ����Ϊvector
	{
		vector<T>result;
		if (root == nullptr)
		{
			return result;
		}
		Recurrence(result, root);
		return result;
	}

	//������ʵ����������еĵݹ�
	void Recurrence(vector<T>& result,BinTreeNode<T>*r)	//����Ϊ��������������vector�����ڵ�ָ��
	{
		if (r == nullptr)	//�����ڵ�ָ��Ϊ��
		{
			return;	//��ֱ�ӷ���
		}
		Recurrence(result, r->leftChild);	//����ǰ���ڵ������Ů��Ϊ�µĸ��ڵ㣬ִ�к���
		result.push_back(r->data);	//������������ɺ󣬸��ڵ�����ѹ��ջ
		Recurrence(result, r->rightChild);	//�ٱ���������
	}

	//����������δ��ϵ��´�ӡ
	void LevelTraversalPrint(int depth)
	{
		queue<T> nodeQueue[depth];
	}


	BinTreeNode<T>* root;
};


//�����������������������һ��int���͵Ķ���������Ϊָ����int�ͣ�����û��д�ڶ�������class��
//������������㣨�ݹ鴴��������
BinTreeNode<int>* CreatNode(int depth, int range)
{
	BinTreeNode<int>* newNode = new BinTreeNode<int>;	//�����½��	
	newNode->data = rand() % range;	//range��Χ�������������
	newNode->leftChild = newNode->rightChild = nullptr;	//������Ů��Ϊ��

	cout << newNode->data << "    ";

	if (depth - 1 > 0)	//����ȴ���1ʱ�����м������´���������Ҫ
	{
		//����ж��Ƿ���������Ů��
		if (rand() % 2)
		{
			cout << "left-";
			newNode->leftChild = CreatNode(depth - 1, range);	//0.5������������Ů
		}
		else
		{
			cout << "left-null    ";
			newNode->leftChild = nullptr;	//0.5��������ŮΪ��
		}
		//����Ůͬ��
		if (rand() % 2)
		{
			cout << "right-";
			newNode->rightChild = CreatNode(depth - 1, range);
		}
		else
		{
			cout << "right-null    ";
			newNode->rightChild = nullptr;
		}
	}
	return newNode;	//�������ɵĽ��
}

//�������������һ�ô���int�͵Ķ�����
BinTreeNode<int>* CreateRandBinTree(int depth, int range)	//����Ϊ������ȡ����������ֵ��Χ
{
	if (depth <= 0)	//�����Ϊ0������Ϊ��
	{
		return nullptr;	//���ؿ�ָ��
	}
	BinTreeNode<int>* root = new BinTreeNode<int>;	//���������
	root->data = rand() % range;	//range��Χ�������������
	cout << "root-" << root->data << "    ";

	if (depth == 1)	//�����Ϊ1������ֻ��һ�������
	{
		root->leftChild = root->rightChild = nullptr;	//�����������ŮΪ��
	}
	else	//����ȴ���1
	{
		//����ж��Ƿ���������Ů��
		if (rand() % 2)
		{
			cout << "left-";
			root->leftChild = CreatNode(depth - 1, range);	//0.5������������Ů��ʹ��ǰ���CreateNode������Ϊ����
		}
		else
		{

			cout << "left-null    ";
			root->leftChild = nullptr;	//0.5��������ŮΪ��
		}
		//����Ůͬ��
		if (rand() % 2)
		{
			cout << "right-";
			root->rightChild = CreatNode(depth - 1, range);
		}
		else
		{
			cout << "right-null    ";
			root->rightChild = nullptr;
		}
	}
	return root;	//�������ɵĽ��
}

//�ࣺ������������
template<class T>
class ThreadBinTree
{
public:
	ThreadBinTree(BinTree<T>& t)
	{
		root = new BinTreeNode<T>;
		BinTreeNode<T>* pre = nullptr;
		if (t.root == nullptr)	//��������Ϊ��
		{
			return;	//��ֱ�ӷ���
		}
		InOrderThreading(root, t.root, pre);
	}
	
	//��������ģ�����������������Ϊ�µ�������������
	void InOrderThreading(BinTreeNode<T>* threadRoot, BinTreeNode<T>* r, BinTreeNode<T>*& pre)
	{
		if (r != nullptr)	//��ģ���������ǰ���ڵ㲻Ϊ��
		{
			threadRoot = new BinTreeNode<T>;
			threadRoot = root;
			threadRoot->leftFlag = threadRoot->rightFlag = 1;
			InOrderThreading(threadRoot->leftChild, r->leftChild, pre);
			if (r->leftChild == nullptr)	//���������ŮΪ��
			{
				threadRoot->leftFlag = 0;	//leftFlag��Ϊ0
				threadRoot->leftChild = pre;	//leftChildָ��ǰ��
			}
			if (pre != nullptr && pre->rightChild == nullptr)	//��pre��Ϊ����û������Ů
			{
				pre->rightFlag = 0;
				pre->rightChild = threadRoot;
			}
			pre = threadRoot;
			InOrderThreading(threadRoot->rightChild, r->rightChild, pre);
		}
	}

	//�����������������������е����⣬ѭ���޷�������Ӧ�ý����һ�����ĺ����Ϊ�գ���û�ĺã�
	vector<T> InOrderTraversal()
	{
		vector<T> result;
		if (root == nullptr)
		{
			return result;
		}
		BinTreeNode<T>* curNode = root;

		while (curNode != nullptr)
		{
			while (curNode->leftFlag)
			{
				curNode = curNode->leftChild;
			}
			result.push_back(curNode->data);
			while (curNode->rightFlag)
			{
				curNode = curNode->rightChild;
				result.push_back(curNode->data);
			}
			curNode = curNode->rightChild;
		}
		return result;
	}


	BinTreeNode<T>* root;
};

int main()
{
	srand(time(0));
	BinTreeNode<int>* root = CreateRandBinTree(5, 10);	//���Ϊ5������ΧΪ0-9
	BinTree<int> tree(root);

	vector<int> result1 = tree.InOrderTraversal();	//�������
	//��������
	cout << endl << endl;
	for (vector<int>::iterator itr = result1.begin(); itr != result1.end(); itr++)
	{
		cout << *itr << "  ";
	}
	cout << endl << endl;


	ThreadBinTree<int> threadTree(tree);
	vector<int> result2 = threadTree.InOrderTraversal();	//�������
	//��������
	cout << endl << endl;
	for (vector<int>::iterator itr = result2.begin(); itr != result2.end(); itr++)
	{
		cout << *itr << "  ";
	}
	cout << endl << endl;

	system("pause");
	return 0;
}