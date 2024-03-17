#include <iostream>
using namespace std;

#define INFINITE 0xFFFFFFFF //���ڱ�ʾ���۵������
#define vertexCounts 6  //��������
char vextex[] = { 'A', 'B', 'C', 'D', 'E', 'F' };
unsigned int adjMatrixrix[][vertexCounts] = { 0 };	//�ֶ������ڽӾ���

 //���ݽṹ�����ڴ����㷨����Ҫ�ĸ�����Ϣ
struct node
{
	int adjVertex;	//����������U�еĶ���
	unsigned int lowestCost;	//��¼�ö�����u�и������С�Ĵ���
}closedge[vertexCounts];

//���ݽṹ����
struct Arc
{
	int u;
	int v;
	unsigned int cost;  //�ߵĴ���
};

//������Ѱ����С���۱�
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
	return index;	//���رߵ��±�
}

//����������ķ�㷨
void MiniSpanTree_Prim(unsigned int adjMatrix[][vertexCounts], int s)	//������sΪ��ʼ�Ķ���
{
	for (int i = 0; i < vertexCounts; i++)
	{
		closedge[i].lowestCost = INFINITE;	//closegde�е���С���۶���Ϊ�����
	}

	closedge[s].adjVertex = s;	//�Ӷ���s��ʼ
	closedge[s].lowestCost = 0;
	
	for (int i = 0; i < vertexCounts; i++)  //��ʼ����������
	{
		if (i != s)
		{
			closedge[i].adjVertex = s;
			closedge[i].lowestCost = adjMatrix[s][i];
		}
	}

	for (int e = 1; e <= vertexCounts - 1; e++)  //n-1����ʱ�˳�
	{
		int k = Minmum(closedge);  //ѡ����С���۱�
		cout << vextex[closedge[k].adjVertex] << "--" << vextex[k] << endl;	//���뵽��С������
		closedge[k].lowestCost = 0;	//������Ϊ0
		for (int i = 0; i < vertexCounts; i++)	//����V�ж�����С���۱���Ϣ
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