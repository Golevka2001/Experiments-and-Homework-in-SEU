#include<iostream>
using namespace std;

int main()
{
	const char* S = "010203045607";	//Ŀ�괮
	const char* P = "4560";			//ģʽ��

	int Strlen_S = strlen(S);	//Ŀ�괮�ĳ���
	int Strlen_P = strlen(P);	//ģʽ���ĳ���

	bool match;	//�Ƿ�ƥ��

	for (int i = 0; i <= Strlen_S - Strlen_P; i++)
	{
		int pos = i;	//��ʱ���浱ǰi��λ��
		for (int j = 0; j < Strlen_P; j++)
		{
			if (S[i] == P[j])	//��S[i]��P[j]��ͬ
			{
				match = 1;
				i++;
				continue;	//��i��j�����һλ�����Ƚϣ�ֱ��ģʽ����ĩβ
			}
			else	//��S[i]��P[j]��ͬ
			{
				match = 0;
				i = pos;
				break;	//��i���ݣ�����ģʽ����ѭ��
			}
		}
		if (match)	//����ƥ��
		{
			cout << "��Ŀ�괮�е�λ��Ϊ" << pos << endl << endl;
			break;	//������������ѭ��
		}
	}

	system("pause");
	return 0;
}