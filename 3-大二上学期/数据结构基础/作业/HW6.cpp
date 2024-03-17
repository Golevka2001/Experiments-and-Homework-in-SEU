#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

//打印矩阵的函数：
void printMatrix(int** M, int r, int c)	//参数为矩阵和矩阵的行列数
{
	cout << "The size of this matrix is " << r << " * " << c << endl << endl;
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			cout << M[i][j] << "  ";
		}
		cout << endl;
	}
	cout << endl;
}

int main()
{
	srand(time(0));

	//构建矩阵：
	int n = rand() % 16 + 5;	//矩阵大小为5-20的随机整数
	int** A;	//二维数组头
	A = new int* [n];	//动态生成n行
	for (int i = 0; i < n; i++)
	{
		A[i] = new int[n];	//每一行生成n个元素
	}
	
	//填充矩阵：
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (j > i - 2 && j < i + 2)	//三对角阵中非零的位置满足i-2<j<i+2
			{
				A[i][j] = rand() % 9 + 1;	//若满足，则填入1-9的随机整数
			}
			else
			{
				A[i][j] = 0;	//否则填入0
			}
		}
	}
	
	//打印矩阵：
	cout << "Matrix A:\n\n";
	printMatrix(A, n, n);

	//压缩矩阵：
	int* B = new int[n * 3 - 2];	//n阶三对角阵中的非零元素个数为3n-2
	for (int i = 0; i < n * 3 - 2; i++)
	{
		int r = (i + 1) / 3;	//存在数组中的第i个元素在三对角阵中的行数为(i+1)/3的商
		int c = i - r * 2;	//在三对角阵中的列数为i-r*2
		B[i] = A[r][c];
	}

	//打印数组：
	cout << "Array B:\n\n";
	for (int i = 0; i < n * 3 - 2; i++)
	{
		cout << B[i] << "  ";
	}
	cout << endl << endl;

	//数组还原为矩阵(其中已包含了由下标i、j从数组中提取数据的操作)：
	//创建新矩阵：
	int** C;
	C = new int* [n];
	for (int i = 0; i < n; i++)
	{
		C[i] = new int[n];
	}
	//从数组中还原：
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (j > i - 2 && j < i + 2)
			{
				C[i][j] = B[2 * i + j];
			}
			else
			{
				C[i][j] = 0;
			}
		}
	}

	//打印还原后的矩阵：
	cout << "Matrix C:\n\n";
	printMatrix(C, n, n);

	//删除矩阵和数组：
	for (int i = 0; i < n; i++)
	{
		delete []A[i];
		delete []C[i];
	}
	delete []A;
	delete []B;
	delete []C;


	system("pause");
	return 0;
}