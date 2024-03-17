#include<iostream>
#include<vector>
#include<stack>
using namespace std;


//类：二叉树结点
template<class T>
class BinTreeNode
{
public:
	BinTreeNode(BinTreeNode* lC = nullptr, BinTreeNode* rC = nullptr, const T& d = 0)
		:leftChild(lC), rightChild(rC), data(d) {}

	BinTreeNode* leftChild;	//左子树
	BinTreeNode* rightChild;	//右子树
	T data;	//数据
};


//类：二叉树
template<class T>
class BinTree
{
public:
	BinTree(BinTreeNode<T>* r = nullptr)
		:root(r), nodeNum(1) {}

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

	//函数：后序遍历，返回值类型为vector
	vector<T> postOrder()
	{
		//后序遍历的顺序应为：左子树-右子树-根节点
		//这里采用：根节点-右子树-左子树 的顺序遍历整棵树后，对储存结果的数组进行反向，得到的就是后序遍历的结果
		//因为后序遍历时，在压栈过程中需要频繁访问结点的parent，并判断parent的左右子树的访问状态，并不方便操作

		vector<T>result;	//声明一个vector，用于存放遍历结果

		if (root == nullptr)	//若根节点未空
		{
			return result;	//直接返回空的vector
		}

		stack<BinTreeNode<T>*>s;	//声明一个栈，用于暂存待访问的结点
		s.push(root);	//根节点压入栈

		while (!s.empty())	//栈未空时循环
		{
			BinTreeNode<T>* curNode = s.top();	//声明一个指针指向当前栈顶结点
			result.push_back(curNode->data);	//当前结点中的数据存入vector
			s.pop();	//栈顶结点出栈

			if (curNode->leftChild != nullptr)	//若当前结点左子树不为空
			{
				s.push(curNode->leftChild);	//则将左结点压入栈
			}
			if (curNode->rightChild != nullptr)	//若当前结点右子树不为空
			{
				s.push(curNode->rightChild);	//则将右结点压入栈
			}
		}

		reverse(result.begin(), result.end());	//将vector反向

		return result;	//返回vector
	}

	BinTreeNode<T>* root;	//根节点
	int nodeNum;	//节点数
};


int main()
{
	BinTreeNode<int> root(nullptr, nullptr, 1);	//根节点
	BinTreeNode<int>* rootPtr = &root;	//指向根节点的指针
	BinTree<int> tree(rootPtr);	//二叉树
	//手动添加结点：
	tree.InsertChild(2, rootPtr, 0);
	tree.InsertChild(3, rootPtr, 1);
	tree.InsertChild(4, rootPtr->leftChild, 0);
	tree.InsertChild(5, rootPtr->leftChild, 1);
	tree.InsertChild(6, rootPtr->rightChild, 0);
	tree.InsertChild(7, rootPtr->rightChild, 1);
	//树的结构如下：
	//        1
	//    2       3
	//  4   5   6   7
	//后序遍历结果应为：4、5、2、6、7、3、1
	
	vector<int> result = tree.postOrder();	//后序遍历，结果储存在vector中
	vector<int>::iterator itr = result.begin();	//迭代器
	for (; itr != result.end(); itr++)	//输出后序遍历结果
	{
		cout << *itr << "  ";
	}
	cout << endl;

	system("pause");
	return 0;
}