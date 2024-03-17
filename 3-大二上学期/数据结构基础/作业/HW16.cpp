#include <iostream>
using namespace std;

#define INFINITE 0xFFFFFFFF //用于表示代价的无穷大
#define vertexCounts 6  //顶点数量
char vextex[] = { 'A', 'B', 'C', 'D', 'E', 'F' };
unsigned int adjMatrixrix[][vertexCounts] = { 0 };	//手动输入邻接矩阵

 //数据结构：用于储存算法中需要的辅助信息
struct node
{
	int adjVertex;	//边所依附的U中的顶点
	unsigned int lowestCost;	//记录该顶点与u中各点间最小的代价
}closedge[vertexCounts];

//数据结构：边
struct Arc
{
	int u;
	int v;
	unsigned int cost;  //边的代价
};

//函数：寻找最小代价边
int Minmum(struct node* closedge)
{
	unsigned int min = INFINITE;
	int index = -1;
	for (int i = 0; i < vertexCounts; i++)
	{
		if (closedge[i].lowestCost < min && closedge[i].lowestCost != 0)
		{
			min = closedge[i].lowestCost;
			index = i;
		}
	}
	return index;	//返回边的下标
}

//函数：普里姆算法
void MiniSpanTree_Prim(unsigned int adjMatrix[][vertexCounts], int s)	//参数：s为起始的顶点
{
	for (int i = 0; i < vertexCounts; i++)
	{
		closedge[i].lowestCost = INFINITE;	//closegde中的最小代价都置为无穷大
	}

	closedge[s].adjVertex = s;	//从顶点s开始
	closedge[s].lowestCost = 0;
	
	for (int i = 0; i < vertexCounts; i++)  //初始化辅助数组
	{
		if (i != s)
		{
			closedge[i].adjVertex = s;
			closedge[i].lowestCost = adjMatrix[s][i];
		}
	}

	for (int e = 1; e <= vertexCounts - 1; e++)  //n-1条边时退出
	{
		int k = Minmum(closedge);  //选择最小代价边
		cout << vextex[closedge[k].adjVertex] << "--" << vextex[k] << endl;	//加入到最小生成树
		closedge[k].lowestCost = 0;	//代价置为0
		for (int i = 0; i < vertexCounts; i++)	//更新V中顶点最小代价边信息
		{
			if (adjMatrix[k][i] < closedge[i].lowestCost)
			{
				closedge[i].adjVertex = k;
				closedge[i].lowestCost = adjMatrix[k][i];
			}
		}
	}
}

int main()
{


	system("pause");
	return 0;
}