#include<iostream>
#include<cstdlib>
#include<ctime>
#include<queue>
using namespace std;

template<class T>
struct BinTreeNode	//数据结构：二叉树结点
{
	BinTreeNode(T d = 0)
		:data(d), leftChild(nullptr), rightChild(nullptr)
	{}
	~BinTreeNode()
	{}

	BinTreeNode* leftChild;	//指向左子树的指针
	BinTreeNode* rightChild;	//指向右子树的指针
	T data;	//储存该结点的数据
};

template<class T>
struct BinTree	//数据结构：二叉树
{
	BinTree(int n = 0, BinTreeNode<T>* r = nullptr)
		:nodeNum(n), root(r) {}
	~BinTree() {}

	void CreatBinTree(queue<T> in, BinTreeNode<T>*& subTree, T refValue)	//创建二叉树的函数
	{
		T item;
		if (!in.empty())	//当栈不为空时
		{
			item = in.front();	//获取队头元素
			in.pop();	//弹出队头元素
			if (item != refValue)	//当item的值不为终止值时
			{
				subTree = new BinTreeNode<T>(item);
				if (subTree == nullptr)
				{
					cerr << "储存分配错误！\n\n";
					exit(1);
				}
				CreatBinTree(in, subTree->leftChild, -1);	//建立左子树
				CreatBinTree(in, subTree->rightChild, -1);	//建立右子树
			}
			else	//若item为终止值
			{
				subTree = nullptr;	//则将其子树指针设为空指针
			}
		}
	}

	int nodeNum;	//结点总数
	BinTreeNode<T>* root;	//指向根的指针
};

int main()
{
	srand(time(0));
	int n = rand() % 5 + 5;	//随机得到二叉树的结点总数（范围0-9）
	cout << n << endl << endl;
	queue<int> data;	//创建一个储存整型数据的栈，作为生成树的数据
	
	//生成二叉树的序列：
	int elemCnt = 0;
	int endCnt = 0;
	for (int i = 0; i < 2 * n; i++)
	{
		if (rand() % 2)
		{
			if (elemCnt < n)
			{
				data.push(rand() % 10);	//随机整数压入栈（0-9）
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
				data.push(-1);	//终止标志-1压入栈
				endCnt++;
			}
			else
			{
				i--;
			}
		}
	}
	data.push(-1);

	//打印序列：
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
	tree.CreatBinTree(data, root, -1);	//执行生成树的函数

	//没有再写从二叉树中提取某结点的功能，是通过打断点来验证生成的树是否正确的

	system("pause");
	return 0;
}