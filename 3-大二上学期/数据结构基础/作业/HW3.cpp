#include<iostream>
#include<iomanip>
using namespace std;


//�Թ���ͼ��
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


//��¼�ѷ��ʹ��ĵ㣺
int visited[15][15] = { 0 };


//���ݽṹ����㣺
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


//���ݽṹ��ջ��
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
	void push(T d)	//��ջ
	{
		top = new Node<T>(d, top);
	}
	bool pop(T& d)	//��ջ
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
	bool getTopElem(T& d)	//����ջ��Ԫ��
	{
		if (isEmpty())
		{
			return 0;
		}
		d = top->data;
		return 1;
	}
	bool isEmpty()	//ջ�գ�
	{
		return (top == nullptr) ? 1 : 0;
	}
private:
	Node<T>* top;	//ָ��ջ��
};


//���ݽṹ�����꣺
typedef struct
{
	int r, c;
}Pos;


//������Ѱ�ҵ�ǰ·�����ܵ�ͨ·��
Pos searchNext(Pos curPos)
{
	//����ͨ·ʱ����ͨ·���꣬���򷵻�(-1, -1)

	Pos nextPos;
	nextPos.r = -1;
	nextPos.c = -1;

	int r = curPos.r;
	int c = curPos.c;

	//�ӵ�ǰ�����Ͽ�ʼ����˳ʱ����ң�����ͼ��Ϊͨ·��δ�����ʹ�����Ϊ�յ㣬������Ϊ��һ����
	if ((map[r - 1][c] == 0 && visited[r - 1][c] == 0) || map[r - 1][c] == 3)	//����
	{
		nextPos.r = r - 1;
		nextPos.c = c;
	}
	else if ((map[r][c + 1] == 0 && visited[r][c + 1] == 0) || map[r][c + 1] == 3)	//����
	{
		nextPos.r = r;
		nextPos.c = c + 1;
	}
	else if ((map[r + 1][c] == 0 && visited[r + 1][c] == 0) || map[r + 1][c] == 3)	//����
	{
		nextPos.r = r + 1;
		nextPos.c = c;
	}
	else if ((map[r][c - 1] == 0 && visited[r][c - 1] == 0) || map[r][c - 1] == 3)	//����
	{
		nextPos.r = r;
		nextPos.c = c - 1;
	}
	return nextPos;
}


//��������ͨ·Ѱ���յ㣺
void path()
{
	Stack<Pos> s;	//��¼·����ջ
	Pos curPos, nextPos;	//��ǰλ�ã���һλ��

	//�ҵ���㣺
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (map[i][j] == 2)
			{
				curPos.r = i;
				curPos.c = j;	//���Ϊ(i, j)
			}
		}
	}

	cout << "\n\n����仯���£�\n\n"
		<< '(' << curPos.r << ", " << curPos.c << ')' << endl;

	while (map[curPos.r][curPos.c] != 3)
	{
		visited[curPos.r][curPos.c] = 1;	//���Ϊ�ѷ��ʹ�
		nextPos = searchNext(curPos);	//������ǰ�������ҵ���һ����

		if (nextPos.r != -1)	//����ǰλ����Χ����ͨ·
		{
			s.push(curPos);	//��ջ
			curPos = nextPos;	//��ǰ�����Ϊ��һ����
		}
		else	//����ǰ����Χ��ͨ·
		{
			s.pop(curPos);	//��ǰ�����Ϊ��һ���㣬�������ջ
			cout << "�˻���";
		}
		cout << '(' << curPos.r << ", " << curPos.c << ')' << endl;
	}

	Stack<Pos> t;
	//��ջs�е�Ԫ�����γ�ջ����ѹ��ջt�У�ʵ�ֵ�������
	while (!s.isEmpty())
	{
		Pos temp;
		s.pop(temp);
		t.push(temp);
	}

	cout << "\n\nѰ�ҵ���·�����£�\n\n";
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			Pos temp;
			t.pop(temp);
			if (i == temp.r && j == temp.c)	//��ջ�������뵱ǰѭ������һ��
			{
				cout << "   ";	//����ʾΪ�ո񣬱�ʾͨ·
			}
			else	//����һ��
			{
				cout << ' ' << map[i][j] << ' ';	//����ʾΪԭ��ͼ����
				t.push(temp);	//�����ոյ�����ջ��Ԫ��ѹ��ջ��
			}
		}
		cout << endl;
	}
}


//��������
int main() {
	cout << "��ͼ���£�\n\n";
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