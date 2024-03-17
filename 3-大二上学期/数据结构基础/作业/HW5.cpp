#include<iostream>
using namespace std;

void getNextArr(const char* str, int* next)	//����next����
{
	int j = 1;
	int k = 0;
	next[1] = 0;

	while (j < next[0])	//j��1��ʼ��ѭ������ĩβλ��
	{
		if (k == 0 || str[j] == str[k])	//��j��kλ��Ԫ����ͬ
		{
			j++;
			k++;	//j��k�����һλ
			next[j] = k;
		}
		else	//����ͬ
		{
			k = next[k];	//��k���ݵ�next[k]��λ��
		}
	}
}

int KMP(const char* targetStr, int targetSize, const char* patternStr, int patternSize, int pos)	//KMP�㷨��posΪĿ�괮�п�ʼƥ���λ��
{
	int i = pos;
	int j = 1;
	int* next = new int[patternSize];	//��ģʽ�����ȷ���next�����С
	next[0] = patternSize;	//��һλ��ų���

	getNextArr(patternStr, next);	//����next����

	while (i < targetSize && j < patternSize)	//��Ŀ�괮��ģʽ������ƥ��
	{
 		if (j == 0 || targetStr[i] == patternStr[j])	//��j����Ϊ0��������ƥ��
		{
			i++;
			j++;	//i��j�����һλ����ƥ��
		}
		else	//��ʧ��
		{
			j = next[j];	//��j���ݵ�next[j]��λ��
		}
	}
	if (j == patternSize)	//����ɶ�ģʽ����ƥ��
	{
		return i - j;	//����i-j����Ŀ�괮��ƥ�����ʼλ��
	}
	else	//��û�гɹ�ƥ��
	{
		return -1;	//����-1
	}
}


int main()
{
	const char* str_a = "aaaaaaaabaabbcac";
	const char* str_b = "aabbca";

	int result = KMP(str_a, strlen(str_a), str_b, strlen(str_b), 1);
	if (result == -1)
	{
		cout << "δ����ƥ��λ��\n\n";
	}
	else
	{
		cout << "ƥ��λ��Ϊ: " << result << endl << endl;
	}

	system("pause");
	return 0;
}