#include<iostream>
#include<vector>
#include<stack>
using namespace std;


//�ࣺ���������
template<class T>
class BinTreeNode
{
public:
	BinTreeNode(BinTreeNode* lC = nullptr, BinTreeNode* rC = nullptr, const T& d = 0)
		:leftChild(lC), rightChild(rC), data(d) {}

	BinTreeNode* leftChild;	//������
	BinTreeNode* rightChild;	//������
	T data;	//����
};


//�ࣺ������
template<class T>
class BinTree
{
public:
	BinTree(BinTreeNode<T>* r = nullptr)
		:root(r), nodeNum(1) {}

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

	//�������������������ֵ����Ϊvector
	vector<T> postOrder()
	{
		//���������˳��ӦΪ��������-������-���ڵ�
		//������ã����ڵ�-������-������ ��˳������������󣬶Դ�������������з��򣬵õ��ľ��Ǻ�������Ľ��
		//��Ϊ�������ʱ����ѹջ��������ҪƵ�����ʽ���parent�����ж�parent�����������ķ���״̬�������������

		vector<T>result;	//����һ��vector�����ڴ�ű������

		if (root == nullptr)	//�����ڵ�δ��
		{
			return result;	//ֱ�ӷ��ؿյ�vector
		}

		stack<BinTreeNode<T>*>s;	//����һ��ջ�������ݴ�����ʵĽ��
		s.push(root);	//���ڵ�ѹ��ջ

		while (!s.empty())	//ջδ��ʱѭ��
		{
			BinTreeNode<T>* curNode = s.top();	//����һ��ָ��ָ��ǰջ�����
			result.push_back(curNode->data);	//��ǰ����е����ݴ���vector
			s.pop();	//ջ������ջ

			if (curNode->leftChild != nullptr)	//����ǰ�����������Ϊ��
			{
				s.push(curNode->leftChild);	//������ѹ��ջ
			}
			if (curNode->rightChild != nullptr)	//����ǰ�����������Ϊ��
			{
				s.push(curNode->rightChild);	//���ҽ��ѹ��ջ
			}
		}

		reverse(result.begin(), result.end());	//��vector����

		return result;	//����vector
	}

	BinTreeNode<T>* root;	//���ڵ�
	int nodeNum;	//�ڵ���
};


int main()
{
	BinTreeNode<int> root(nullptr, nullptr, 1);	//���ڵ�
	BinTreeNode<int>* rootPtr = &root;	//ָ����ڵ��ָ��
	BinTree<int> tree(rootPtr);	//������
	//�ֶ���ӽ�㣺
	tree.InsertChild(2, rootPtr, 0);
	tree.InsertChild(3, rootPtr, 1);
	tree.InsertChild(4, rootPtr->leftChild, 0);
	tree.InsertChild(5, rootPtr->leftChild, 1);
	tree.InsertChild(6, rootPtr->rightChild, 0);
	tree.InsertChild(7, rootPtr->rightChild, 1);
	//���Ľṹ���£�
	//        1
	//    2       3
	//  4   5   6   7
	//����������ӦΪ��4��5��2��6��7��3��1
	
	vector<int> result = tree.postOrder();	//������������������vector��
	vector<int>::iterator itr = result.begin();	//������
	for (; itr != result.end(); itr++)	//�������������
	{
		cout << *itr << "  ";
	}
	cout << endl;

	system("pause");
	return 0;
}