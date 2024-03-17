#include<iostream>
#include<vector>
using namespace std;

//定义一个三元组：
struct Trituple
{
	Trituple(int r = 0, int c = 0, int v= 0)
		:row(r), column(c), value(v)
	{}
	void print()	//打印信息
	{
		cout << "( " << row << ", " << column << ", " << value << " )";	//输出格式为(行，列，值)
	}

	int row;	//元素在矩阵中的行
	int column;	//元素在矩阵中的列
	int value;	//元素的值
};

//定义稀疏矩阵结构体：
struct RLSMatrix
{
	RLSMatrix(int** M = 0, int r = 0, int c = 0)
		:row(r), column(c), number(0)
	{
		for (int i = 0; i < r; i++)	//遍历矩阵的行
		{
			for (int j = 0; j < c; j++)	//遍历矩阵的列
			{
				if (M[i][j])	//若该元素不为0
				{
					Trituple temp(i, j, M[i][j]);
					data.push_back(temp);	//则将该元素的行、列、值储存在三元组中
					number++;
				}
			}
		}
	}
	//RLSMatrix(const RLSMatrix& M)
		//:row(M.row), column(M.column), number(M.number), data(M.data) {}
	~RLSMatrix() {}

	void print()	//打印稀疏矩阵（以三元组的形式打印非零元素）
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

	vector<Trituple> data;	//三元组，用于储存矩阵中每个元素的行、列、值（从0下标开始储存）
	int row;	//矩阵行数
	int column;	//矩阵列数
	int number;	//矩阵中非零元素总数
};

//做稀疏矩阵乘法的函数：
bool multiply(const RLSMatrix M, const RLSMatrix N, RLSMatrix& result)	//参数为两个做乘法稀疏矩阵M、N和用于传出结果的矩阵result
{
	if (M.column != N.row)	//若二者行列数不匹配则无法相乘
	{
		return 0;	//返回false
	}

	int** temp = new int* [M.row];	//构造一个二维数组用于暂存结果
	for (int i = 0; i < M.row; i++)
	{
		temp[i] = new int[N.column];
		for (int j = 0; j < N.column; j++)
		{
			temp[i][j] = 0;	//初始化为零矩阵
		}
	}

	if (M.number * N.number)	//若两个矩阵中非零元素个数都不为0，即不是零矩阵，则对矩阵进行相乘计算；否则输出为零矩阵
	{
		int count = 0;
		for (int i = 0; i < M.number; i++)	//遍历M中的非零元素
		{
			for (int j = 0; j < N.number; j++)	//遍历N中的非零元素
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
	//将稀疏矩阵m、n用定义的稀疏矩阵结构体储存：
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
	RLSMatrix M(m, 3, 4);	//矩阵为3行4列

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
	RLSMatrix N(n, 4, 2);	//矩阵为4行2列

	//打印两个稀疏矩阵：
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