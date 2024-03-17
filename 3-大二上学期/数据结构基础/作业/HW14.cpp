#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

struct AVLTreeNode
{
public:
	AVLTreeNode(int k = 0, AVLTreeNode* p = nullptr)
		:keyWord(k), parent(p)
	{
		height = 1;
		leftChild = rightChild = nullptr;
	}

	int keyWord;
	int height;	//���ĸ߶ȣ����������ĸ߶����ֵ
	AVLTreeNode* parent;
	AVLTreeNode* leftChild;
	AVLTreeNode* rightChild;
};

struct AVLTree
{
public:
	AVLTree(AVLTreeNode r)
		:root(&r)
	{}

	void NewNode(int k, AVLTreeNode* r, bool left)
	{
		if (left)
		{
			r->leftChild = new AVLTreeNode(k, r);
		}
		else
		{
			r->rightChild = new AVLTreeNode(k, r);
		}

		AVLTreeNode* tempNode = r;
		while (tempNode != nullptr)
		{
			tempNode->height++;
			tempNode = tempNode->parent;
		}

		while (tempNode != nullptr)
		{
			if (GetBalanceFactor(tempNode) == -2)
			{
				if (GetBalanceFactor(tempNode->rightChild) == -1)
				{
					LeftRotate(tempNode);
				}
				if (GetBalanceFactor(tempNode->rightChild) == 1)
				{
					RightLeftRotate(tempNode);
				}
			}
			else if (GetBalanceFactor(tempNode) == 2)
			{
				if (GetBalanceFactor(tempNode->leftChild) == 1)
				{
					RightRotate(tempNode);
				}
				if (GetBalanceFactor(tempNode->leftChild) == -1)
				{
					LeftRightRotate(tempNode);
				}
			}
			tempNode = tempNode->parent;
		}
	}

	//����������
	void LeftRotate(AVLTreeNode* r)
	{
		AVLTreeNode* subR = r->rightChild;
		AVLTreeNode* subRL = subR->leftChild;
		
		r->rightChild = subRL;
		subR->leftChild = r;

		if (subRL != nullptr)
		{
			subRL->parent = r;
		}

		if (r->parent->leftChild == r)
		{
			r->parent->leftChild = subR;
		}
		else
		{
			r->parent->rightChild = subR;
		}

		subR->parent = r->parent;
		r->parent = subR;

		GetHeight(root);
	}

	//����������
	void RightRotate(AVLTreeNode* r)
	{
		AVLTreeNode* subL = r->leftChild;
		AVLTreeNode* subLR = subL->rightChild;

		r->leftChild = subLR;
		subL->rightChild = r;

		if (subLR != nullptr)
		{
			subLR->parent = r;
		}

		if (r->parent->leftChild == r)
		{
			r->parent->leftChild = subL;
		}
		else
		{
			r->parent->rightChild = subL;
		}

		subL->parent = r->parent;
		r->parent = subL;

		GetHeight(root);
	}

	//����������˫��
	void LeftRightRotate(AVLTreeNode* r)
	{
		LeftRotate(r->leftChild);
		RightRotate(r);

		GetHeight(root);
	}

	//����������˫��
	void RightLeftRotate(AVLTreeNode* r)
	{
		LeftRotate(r->rightChild);
		RightRotate(r);

		GetHeight(root);
	}

	//��������ȡ���ĸ߶�
	int GetHeight(AVLTreeNode* r)
	{
		if (r == nullptr)	//�������Ϊ��
		{
			return 0;	//�����߶�Ϊ0
		}
		r->height = max(GetHeight(r->leftChild), GetHeight(r->rightChild)) + 1;	//�������¼���
		return r->height;
	}

	//��������������ƽ������
	int GetBalanceFactor(AVLTreeNode* r)
	{
		if (r == nullptr)	//�������Ϊ��
		{
			return 0;	//�����߶�Ϊ0
		}
		return r->leftChild->height - r->rightChild->height;	//ƽ������=�������߶�-�������߶�
	}

	AVLTreeNode* root;
};

int main()
{
	system("pause");
	return 0;
}