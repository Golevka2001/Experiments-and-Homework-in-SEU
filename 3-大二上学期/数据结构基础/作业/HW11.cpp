#include<iostream>
#include<vector>
#include<queue>
#include<cmath>
using namespace std;


//类：二叉树结点
template<class T>
class BinTreeNode
{
public:
	BinTreeNode(BinTreeNode<T>* lC = nullptr, BinTreeNode<T>* rC = nullptr, bool lF = 1, bool rF = 1, T d = 0)
		:leftChild(lC), rightChild(rC), leftFlag(lF), rightFlag(rF), data(d) {}
	BinTreeNode<T>* leftChild;	//左子女或前驱
	BinTreeNode<T>* rightChild;	//右子女或后继
	bool leftFlag;	//为0时，没有左子女，leftChild表示前驱；为1时，指向左子女
	bool rightFlag;	//同上
	T data;	//数据
};


//类：二叉树
template<class T>
class BinTree
{
public:
	BinTree(BinTreeNode<T>* r = nullptr)
		:root(r) {}

	/*
	//函数：向结点左/右插入新结点
	bool InsertChild(const T& d, BinTreeNode<T>* n, bool lr)	//参数为：新节点的数据、指向要插入到的结点指针，插在左/右（0/1）
	{
		if ((lr == 0 && n->leftChild != nullptr)
			|| (lr == 1 && n->rightChild != nullptr))	//若要插入到结点左（右），但结点已存在左（右）子树
		{
			return false;	//则不能直接插入，返回false
		}

		if (lr)	//插入到结点右
		{
			n->rightChild = new BinTreeNode<T>(nullptr, nullptr, d);
		}
		else	//插入到结点左
		{
			n->leftChild = new BinTreeNode<T>(nullptr, nullptr, d);
		}
		nodeNum++;	//结点数+1
		return true;	//插入成功，返回true
	}
	*/

	//函数：中序遍历
	vector<T> InOrderTraversal()	//返回值类型为vector
	{
		vector<T>result;
		if (root == nullptr)
		{
			return result;
		}
		Recurrence(result, root);
		return result;
	}

	//函数：实现中序遍历中的递归
	void Recurrence(vector<T>& result,BinTreeNode<T>*r)	//参数为：储存遍历结果的vector、根节点指针
	{
		if (r == nullptr)	//若根节点指针为空
		{
			return;	//则直接返回
		}
		Recurrence(result, r->leftChild);	//将当前根节点的左子女作为新的根节点，执行函数
		result.push_back(r->data);	//左子树遍历完成后，根节点数据压入栈
		Recurrence(result, r->rightChild);	//再遍历右子树
	}

	//函数：按层次从上到下打印
	void LevelTraversalPrint(int depth)
	{
		queue<T> nodeQueue[depth];
	}


	BinTreeNode<T>* root;
};


//以下两个函数用于随机生成一棵int类型的二叉树，因为指定了int型，所以没有写在二叉树的class里
//函数：创建结点（递归创建子树）
BinTreeNode<int>* CreatNode(int depth, int range)
{
	BinTreeNode<int>* newNode = new BinTreeNode<int>;	//创建新结点	
	newNode->data = rand() % range;	//range范围内随机整数填入
	newNode->leftChild = newNode->rightChild = nullptr;	//左右子女设为空

	cout << newNode->data << "    ";

	if (depth - 1 > 0)	//当深度大于1时，才有继续向下创建结点的需要
	{
		//随机判定是否生成左子女：
		if (rand() % 2)
		{
			cout << "left-";
			newNode->leftChild = CreatNode(depth - 1, range);	//0.5概率生成左子女
		}
		else
		{
			cout << "left-null    ";
			newNode->leftChild = nullptr;	//0.5概率左子女为空
		}
		//右子女同理：
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
	return newNode;	//返回生成的结点
}

//函数：随机生成一棵储存int型的二叉树
BinTreeNode<int>* CreateRandBinTree(int depth, int range)	//参数为：树深度、储存的整型值范围
{
	if (depth <= 0)	//若深度为0，则树为空
	{
		return nullptr;	//返回空指针
	}
	BinTreeNode<int>* root = new BinTreeNode<int>;	//创建根结点
	root->data = rand() % range;	//range范围内随机整数填入
	cout << "root-" << root->data << "    ";

	if (depth == 1)	//若深度为1，则树只有一个根结点
	{
		root->leftChild = root->rightChild = nullptr;	//根结点左右子女为空
	}
	else	//若深度大于1
	{
		//随机判定是否生成左子女：
		if (rand() % 2)
		{
			cout << "left-";
			root->leftChild = CreatNode(depth - 1, range);	//0.5概率生成左子女，使用前面的CreateNode函数作为辅助
		}
		else
		{

			cout << "left-null    ";
			root->leftChild = nullptr;	//0.5概率左子女为空
		}
		//右子女同理：
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
	return root;	//返回生成的结点
}

//类：线索化二叉树
template<class T>
class ThreadBinTree
{
public:
	ThreadBinTree(BinTree<T>& t)
	{
		root = new BinTreeNode<T>;
		BinTreeNode<T>* pre = nullptr;
		if (t.root == nullptr)	//若二叉树为空
		{
			return;	//则直接返回
		}
		InOrderThreading(root, t.root, pre);
	}
	
	//函数：将模板二叉树线索化，存为新的线索化二叉树
	void InOrderThreading(BinTreeNode<T>* threadRoot, BinTreeNode<T>* r, BinTreeNode<T>*& pre)
	{
		if (r != nullptr)	//若模板二叉树当前根节点不为空
		{
			threadRoot = new BinTreeNode<T>;
			threadRoot = root;
			threadRoot->leftFlag = threadRoot->rightFlag = 1;
			InOrderThreading(threadRoot->leftChild, r->leftChild, pre);
			if (r->leftChild == nullptr)	//若结点左子女为空
			{
				threadRoot->leftFlag = 0;	//leftFlag设为0
				threadRoot->leftChild = pre;	//leftChild指向前驱
			}
			if (pre != nullptr && pre->rightChild == nullptr)	//若pre不为空且没有右子女
			{
				pre->rightFlag = 0;
				pre->rightChild = threadRoot;
			}
			pre = threadRoot;
			InOrderThreading(threadRoot->rightChild, r->rightChild, pre);
		}
	}

	//函数：遍历线索二叉树（有点问题，循环无法结束，应该将最后一个结点的后继设为空，还没改好）
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
	BinTreeNode<int>* root = CreateRandBinTree(5, 10);	//深度为5，数范围为0-9
	BinTree<int> tree(root);

	vector<int> result1 = tree.InOrderTraversal();	//中序遍历
	//输出结果：
	cout << endl << endl;
	for (vector<int>::iterator itr = result1.begin(); itr != result1.end(); itr++)
	{
		cout << *itr << "  ";
	}
	cout << endl << endl;


	ThreadBinTree<int> threadTree(tree);
	vector<int> result2 = threadTree.InOrderTraversal();	//中序遍历
	//输出结果：
	cout << endl << endl;
	for (vector<int>::iterator itr = result2.begin(); itr != result2.end(); itr++)
	{
		cout << *itr << "  ";
	}
	cout << endl << endl;

	system("pause");
	return 0;
}