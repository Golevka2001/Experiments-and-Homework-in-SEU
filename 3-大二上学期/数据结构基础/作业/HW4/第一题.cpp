#include<iostream>
using namespace std;

int main()
{
	const char* S = "010203045607";	//目标串
	const char* P = "4560";			//模式串

	int Strlen_S = strlen(S);	//目标串的长度
	int Strlen_P = strlen(P);	//模式串的长度

	bool match;	//是否匹配

	for (int i = 0; i <= Strlen_S - Strlen_P; i++)
	{
		int pos = i;	//临时储存当前i的位置
		for (int j = 0; j < Strlen_P; j++)
		{
			if (S[i] == P[j])	//若S[i]与P[j]相同
			{
				match = 1;
				i++;
				continue;	//则i、j均向后一位继续比较，直到模式串的末尾
			}
			else	//若S[i]与P[j]不同
			{
				match = 0;
				i = pos;
				break;	//则i回溯，结束模式串的循环
			}
		}
		if (match)	//若已匹配
		{
			cout << "在目标串中的位置为" << pos << endl << endl;
			break;	//输出结果，结束循环
		}
	}

	system("pause");
	return 0;
}