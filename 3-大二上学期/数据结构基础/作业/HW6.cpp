#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

//��ӡ����ĺ�����
void printMatrix(int** M, int r, int c)	//����Ϊ����;����������
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

	//��������
	int n = rand() % 16 + 5;	//�����СΪ5-20���������
	int** A;	//��ά����ͷ
	A = new int* [n];	//��̬����n��
	for (int i = 0; i < n; i++)
	{
		A[i] = new int[n];	//ÿһ������n��Ԫ��
	}
	
	//������
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (j > i - 2 && j < i + 2)	//���Խ����з����λ������i-2<j<i+2
			{
				A[i][j] = rand() % 9 + 1;	//�����㣬������1-9���������
			}
			else
			{
				A[i][j] = 0;	//��������0
			}
		}
	}
	
	//��ӡ����
	cout << "Matrix A:\n\n";
	printMatrix(A, n, n);

	//ѹ������
	int* B = new int[n * 3 - 2];	//n�����Խ����еķ���Ԫ�ظ���Ϊ3n-2
	for (int i = 0; i < n * 3 - 2; i++)
	{
		int r = (i + 1) / 3;	//���������еĵ�i��Ԫ�������Խ����е�����Ϊ(i+1)/3����
		int c = i - r * 2;	//�����Խ����е�����Ϊi-r*2
		B[i] = A[r][c];
	}

	//��ӡ���飺
	cout << "Array B:\n\n";
	for (int i = 0; i < n * 3 - 2; i++)
	{
		cout << B[i] << "  ";
	}
	cout << endl << endl;

	//���黹ԭΪ����(�����Ѱ��������±�i��j����������ȡ���ݵĲ���)��
	//�����¾���
	int** C;
	C = new int* [n];
	for (int i = 0; i < n; i++)
	{
		C[i] = new int[n];
	}
	//�������л�ԭ��
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

	//��ӡ��ԭ��ľ���
	cout << "Matrix C:\n\n";
	printMatrix(C, n, n);

	//ɾ����������飺
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