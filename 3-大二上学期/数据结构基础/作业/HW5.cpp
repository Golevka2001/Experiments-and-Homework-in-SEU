#include<iostream>
using namespace std;

void getNextArr(const char* str, int* next)	//计算next数组
{
	int j = 1;
	int k = 0;
	next[1] = 0;

	while (j < next[0])	//j从1开始，循环到串末尾位置
	{
		if (k == 0 || str[j] == str[k])	//若j、k位置元素相同
		{
			j++;
			k++;	//j、k向后移一位
			next[j] = k;
		}
		else	//若不同
		{
			k = next[k];	//则k回溯到next[k]的位置
		}
	}
}

int KMP(const char* targetStr, int targetSize, const char* patternStr, int patternSize, int pos)	//KMP算法，pos为目标串中开始匹配的位置
{
	int i = pos;
	int j = 1;
	int* next = new int[patternSize];	//以模式串长度分配next矩阵大小
	next[0] = patternSize;	//第一位存放长度

	getNextArr(patternStr, next);	//计算next数组

	while (i < targetSize && j < patternSize)	//对目标串与模式串进行匹配
	{
 		if (j == 0 || targetStr[i] == patternStr[j])	//若j被置为0或两个串匹配
		{
			i++;
			j++;	//i、j向后移一位继续匹配
		}
		else	//若失配
		{
			j = next[j];	//则j回溯到next[j]的位置
		}
	}
	if (j == patternSize)	//若完成对模式串的匹配
	{
		return i - j;	//返回i-j，即目标串中匹配的起始位置
	}
	else	//若没有成功匹配
	{
		return -1;	//返回-1
	}
}


int main()
{
	const char* str_a = "aaaaaaaabaabbcac";
	const char* str_b = "aabbca";

	int result = KMP(str_a, strlen(str_a), str_b, strlen(str_b), 1);
	if (result == -1)
	{
		cout << "未发现匹配位置\n\n";
	}
	else
	{
		cout << "匹配位置为: " << result << endl << endl;
	}

	system("pause");
	return 0;
}