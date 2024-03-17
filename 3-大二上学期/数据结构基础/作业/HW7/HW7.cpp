#include<iostream>
#include<vector>
using namespace std;

//����һ����Ԫ�飺
struct Trituple
{
	Trituple(int r = 0, int c = 0, int v= 0)
		:row(r), column(c), value(v)
	{}
	void print()	//��ӡ��Ϣ
	{
		cout << "( " << row << ", " << column << ", " << value << " )";	//�����ʽΪ(�У��У�ֵ)
	}

	int row;	//Ԫ���ھ����е���
	int column;	//Ԫ���ھ����е���
	int value;	//Ԫ�ص�ֵ
};

//����ϡ�����ṹ�壺
struct RLSMatrix
{
	RLSMatrix(int** M = 0, int r = 0, int c = 0)
		:row(r), column(c), number(0)
	{
		for (int i = 0; i < r; i++)	//�����������
		{
			for (int j = 0; j < c; j++)	//�����������
			{
				if (M[i][j])	//����Ԫ�ز�Ϊ0
				{
					Trituple temp(i, j, M[i][j]);
					data.push_back(temp);	//�򽫸�Ԫ�ص��С��С�ֵ��������Ԫ����
					number++;
				}
			}
		}
	}
	//RLSMatrix(const RLSMatrix& M)
		//:row(M.row), column(M.column), number(M.number), data(M.data) {}
	~RLSMatrix() {}

	void print()	//��ӡϡ���������Ԫ�����ʽ��ӡ����Ԫ�أ�
	{
		for (int i = 0; i < number; i++)
		{
			if (data[i].value != 0)
			{
				data[i].print();
				cout << endl;
			}
		}
	}

	vector<Trituple> data;	//��Ԫ�飬���ڴ��������ÿ��Ԫ�ص��С��С�ֵ����0�±꿪ʼ���棩
	int row;	//��������
	int column;	//��������
	int number;	//�����з���Ԫ������
};

//��ϡ�����˷��ĺ�����
bool multiply(const RLSMatrix M, const RLSMatrix N, RLSMatrix& result)	//����Ϊ�������˷�ϡ�����M��N�����ڴ�������ľ���result
{
	if (M.column != N.row)	//��������������ƥ�����޷����
	{
		return 0;	//����false
	}

	int** temp = new int* [M.row];	//����һ����ά���������ݴ���
	for (int i = 0; i < M.row; i++)
	{
		temp[i] = new int[N.column];
		for (int j = 0; j < N.column; j++)
		{
			temp[i][j] = 0;	//��ʼ��Ϊ�����
		}
	}

	if (M.number * N.number)	//�����������з���Ԫ�ظ�������Ϊ0���������������Ծ��������˼��㣻�������Ϊ�����
	{
		int count = 0;
		for (int i = 0; i < M.number; i++)	//����M�еķ���Ԫ��
		{
			for (int j = 0; j < N.number; j++)	//����N�еķ���Ԫ��
			{
				if (M.data[i].column == N.data[j].row)
				{
					temp[M.data[i].row][N.data[j].column]
						+= M.data[i].value * N.data[j].value;
				}
			}
		}
	}
	result = RLSMatrix(temp, M.row, N.column);
	return 1;
}

int main()
{
	//��ϡ�����m��n�ö����ϡ�����ṹ�崢�棺
	int** m = new int* [3];
	for (int i = 0; i < 3; i++)
	{
		m[i] = new int[4];
		for (int j = 0; j < 4; j++)
		{
			m[i][j] = 0;
		}
	}
	m[0][0] = 3;
	m[0][3] = 5;
	m[1][1] = -1;
	m[2][0] = 2;
	RLSMatrix M(m, 3, 4);	//����Ϊ3��4��

	int** n = new int* [4];
	for (int i = 0; i < 4; i++)
	{
		n[i] = new int[2];
		for (int j = 0; j < 2; j++)
		{
			n[i][j] = 0;
		}
	}
	n[0][1] = 2;
	n[1][0] = 1;
	n[2][0] = -2;
	n[2][1] = 4;
	RLSMatrix N(n, 4, 2);	//����Ϊ4��2��

	//��ӡ����ϡ�����
	cout << "Matrix M:\n";
	M.print();
	cout << "\nMatrix N:\n";
	N.print();

	RLSMatrix result;
	if (multiply(M, N, result))
	{
		cout << "\nThe result of M * N is:\n";
		result.print();
	}
	else
	{
		cout << "The two matrices don't match!\n";
	}
	cout << endl;

	system("pause");
	return 0;
}