#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

//结构：边表结点
struct EdgeNode
{
	int adjvex; //邻接顶点在表中的下标
	EdgeNode* next; //指向下一个边结点
};

//结构：顶点表结点
struct VertexNode
{
	int data; //储存顶点数据
	EdgeNode* firstedge;    //指向边表中的第一个结点
};

//类：图：
const int MaxSize = 10;
int visited[MaxSize] = { 0 };   //标记顶点是否已被访问过
class Graph
{
public:
	Graph(int a[], int vn, int en)    //顶点数为vn，边数为en
		:vertexNum(vn), edgeNum(en)
	{
		//储存顶点：
		for (int i = 0; i < vertexNum; i++)
		{
			vertexList[i].data = a[i];
			vertexList[i].firstedge = nullptr;
		}

		for (int k = 0; k < edgeNum; k++)
		{
			int i, j;
			cin >> i >> j;
			EdgeNode* s = new EdgeNode;
			s->adjvex = j;	//下标为j的顶点为边结点的邻接顶点
			s->next = vertexList[i].firstedge;	//下一个边结点
			vertexList[i].firstedge = s;	//i顶点的边设为边结点s
		}
	}

	//函数：深度优先遍历
	void DFSTraaverse(int v)
	{
		cout << vertexList[v].data;	//打印顶点储存的数据
		visited[v] = 1;	//设为已访问
		EdgeNode* p = vertexList[v].firstedge;	//指向边结点
		while (p != nullptr)
		{
			int i = p->adjvex;	//边结点对应的邻接顶点
			if (visited[i] == 0)	//若未被访问过
			{
				DFSTraaverse(i);	//继续向前执行
			}
			p = p->next;
		}
	}
private:
	VertexNode vertexList[MaxSize];    //储存顶点
	int vertexNum, edgeNum; //顶点数、边数
};

int main()
{
	srand(time(0));

	int array[10];
	for (int i = 0; i < 10; i++)
	{
		array[i] = rand() % 10;
	}
	Graph g(array, 10, 14);
	g.DFSTraaverse(5);

	system("pause");
	return 0;
}