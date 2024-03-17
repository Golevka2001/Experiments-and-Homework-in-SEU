#include<iostream>
#include<iomanip>
using namespace std;


//迷宫地图：
int map[15][15] = {
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1 },
		{ 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1 },
		{ 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1 },
		{ 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 } };


//记录已访问过的点：
int visited[15][15] = { 0 };


//数据结构：结点：
template <class T>
class Node
{
public:
	Node(T d, Node<T>* n = nullptr)
		:data(d)
		, next(n) {}
	~Node() {}
	T data;
	Node<T>* next;
};


//数据结构：栈：
template <class T>
class Stack
{
public:
	Stack()
		:top(nullptr) {}
	~Stack()
	{
		while (!isEmpty())
		{
			T temp;
			pop(temp);
		}
	}
	void push(T d)	//入栈
	{
		top = new Node<T>(d, top);
	}
	bool pop(T& d)	//出栈
	{
		if (isEmpty())
		{
			return 0;
		}
		Node<T>* tempNode = top;
		top = top->next;
		d = tempNode->data;
		delete tempNode;
		return 1;
	}
	bool getTopElem(T& d)	//返回栈顶元素
	{
		if (isEmpty())
		{
			return 0;
		}
		d = top->data;
		return 1;
	}
	bool isEmpty()	//栈空？
	{
		return (top == nullptr) ? 1 : 0;
	}
private:
	Node<T>* top;	//指向栈顶
};


//数据结构：坐标：
typedef struct
{
	int r, c;
}Pos;


//函数：寻找当前路径四周的通路：
Pos searchNext(Pos curPos)
{
	//存在通路时返回通路坐标，否则返回(-1, -1)

	Pos nextPos;
	nextPos.r = -1;
	nextPos.c = -1;

	int r = curPos.r;
	int c = curPos.c;

	//从当前点向上开始，按顺时针查找，若地图上为通路且未被访问过，或为终点，则设置为下一坐标
	if ((map[r - 1][c] == 0 && visited[r - 1][c] == 0) || map[r - 1][c] == 3)	//向上
	{
		nextPos.r = r - 1;
		nextPos.c = c;
	}
	else if ((map[r][c + 1] == 0 && visited[r][c + 1] == 0) || map[r][c + 1] == 3)	//向右
	{
		nextPos.r = r;
		nextPos.c = c + 1;
	}
	else if ((map[r + 1][c] == 0 && visited[r + 1][c] == 0) || map[r + 1][c] == 3)	//向下
	{
		nextPos.r = r + 1;
		nextPos.c = c;
	}
	else if ((map[r][c - 1] == 0 && visited[r][c - 1] == 0) || map[r][c - 1] == 3)	//向左
	{
		nextPos.r = r;
		nextPos.c = c - 1;
	}
	return nextPos;
}


//函数：沿通路寻找终点：
void path()
{
	Stack<Pos> s;	//记录路径的栈
	Pos curPos, nextPos;	//当前位置，下一位置

	//找到起点：
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (map[i][j] == 2)
			{
				curPos.r = i;
				curPos.c = j;	//起点为(i, j)
			}
		}
	}

	cout << "\n\n坐标变化如下：\n\n"
		<< '(' << curPos.r << ", " << curPos.c << ')' << endl;

	while (map[curPos.r][curPos.c] != 3)
	{
		visited[curPos.r][curPos.c] = 1;	//标记为已访问过
		nextPos = searchNext(curPos);	//搜索当前点四周找到下一个点

		if (nextPos.r != -1)	//若当前位置周围存在通路
		{
			s.push(curPos);	//入栈
			curPos = nextPos;	//当前点更新为下一个点
		}
		else	//若当前点周围无通路
		{
			s.pop(curPos);	//当前点更新为上一个点，并将其出栈
			cout << "退回至";
		}
		cout << '(' << curPos.r << ", " << curPos.c << ')' << endl;
	}

	Stack<Pos> t;
	//将栈s中的元素依次出栈，再压入栈t中，实现倒序排列
	while (!s.isEmpty())
	{
		Pos temp;
		s.pop(temp);
		t.push(temp);
	}

	cout << "\n\n寻找到的路径如下：\n\n";
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			Pos temp;
			t.pop(temp);
			if (i == temp.r && j == temp.c)	//若栈顶坐标与当前循环坐标一致
			{
				cout << "   ";	//则显示为空格，表示通路
			}
			else	//若不一致
			{
				cout << ' ' << map[i][j] << ' ';	//则显示为原地图内容
				t.push(temp);	//并将刚刚弹出的栈顶元素压回栈中
			}
		}
		cout << endl;
	}
}


//主函数：
int main() {
	cout << "地图如下：\n\n";
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			cout << ' ' << map[i][j] << ' ';
		}
		cout << endl;
	}

	path();
	cout << endl;

	system("pause");
	return 0;
}