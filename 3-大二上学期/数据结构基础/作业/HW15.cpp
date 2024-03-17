#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

//�ṹ���߱���
struct EdgeNode
{
	int adjvex; //�ڽӶ����ڱ��е��±�
	EdgeNode* next; //ָ����һ���߽��
};

//�ṹ���������
struct VertexNode
{
	int data; //���涥������
	EdgeNode* firstedge;    //ָ��߱��еĵ�һ�����
};

//�ࣺͼ��
const int MaxSize = 10;
int visited[MaxSize] = { 0 };   //��Ƕ����Ƿ��ѱ����ʹ�
class Graph
{
public:
	Graph(int a[], int vn, int en)    //������Ϊvn������Ϊen
		:vertexNum(vn), edgeNum(en)
	{
		//���涥�㣺
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
			s->adjvex = j;	//�±�Ϊj�Ķ���Ϊ�߽����ڽӶ���
			s->next = vertexList[i].firstedge;	//��һ���߽��
			vertexList[i].firstedge = s;	//i����ı���Ϊ�߽��s
		}
	}

	//������������ȱ���
	void DFSTraaverse(int v)
	{
		cout << vertexList[v].data;	//��ӡ���㴢�������
		visited[v] = 1;	//��Ϊ�ѷ���
		EdgeNode* p = vertexList[v].firstedge;	//ָ��߽��
		while (p != nullptr)
		{
			int i = p->adjvex;	//�߽���Ӧ���ڽӶ���
			if (visited[i] == 0)	//��δ�����ʹ�
			{
				DFSTraaverse(i);	//������ǰִ��
			}
			p = p->next;
		}
	}
private:
	VertexNode vertexList[MaxSize];    //���涥��
	int vertexNum, edgeNum; //������������
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