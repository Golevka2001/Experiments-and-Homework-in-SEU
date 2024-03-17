#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

int main()
{
	srand(time(0));

	char str[40] = { ' ' };
	int frequency[6] = { 0 };
	char order[6] = { 'a','b','c','d','e','f' };
	char* HuffmanCode[6] = { nullptr };

	//����ַ�������ͳ��ÿ���ַ����ֵĴ�����
	for (int i = 0; i < 40; i++)
	{
		int offset = rand() % 6;
		str[i] = 'a' + offset;	//��ΧΪa-f
		frequency[offset]++;
	}

	//����ַ�����
	cout << "Initial string:\n";
	for (int i = 0; i < 40; i++)
	{
		cout << str[i] << ' ';
	}
	cout << endl << endl;

	//����ַ����ִ�����
	cout << "Frequency:\n";
	for (int i = 0; i < 6; i++)
	{
		cout << order[i] << ": " << frequency[order[i] - 'a'] << '\t';
	}
	cout << endl << endl;

	//���ݳ��ִ������Ӵ�С���ַ���������
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6 - i - 1; j++)
		{
			if (frequency[order[j] - 'a'] < frequency[order[j + 1] - 'a'])
			{
				char temp = order[j];
				order[j] = order[j + 1];
				order[j + 1] = temp;
			}
		}
	}

	//�����������
	cout << "After sorted:\n";
	for (int i = 0; i < 6; i++)
	{
		cout << order[i] << ": " << frequency[order[i] - 'a'] << '\t';
	}
	cout << endl << endl;

	//���������룺
	for (int i = 0; i < 5; i++)
	{
		HuffmanCode[order[i] - 'a'] = new char[i + 2];
		for (int j = 0; j < i + 1; j++)
		{
			HuffmanCode[order[i] - 'a'][j] = '0';
		}
		HuffmanCode[order[i] - 'a'][i + 1] = '\0';
	}
	HuffmanCode[order[5] - 'a'] = new char[4 + 2];	//���һ���͵����ڶ������볤����ͬ�������һ����������
	for (int i = 0; i < 4; i++)
	{
		HuffmanCode[order[5] - 'a'][i] = '0';
	}
	HuffmanCode[order[5] - 'a'][4] = '1';
	HuffmanCode[order[5] - 'a'][4 + 1] = '\0';

	//�����������
	cout << "Huffman code:\n";
	for (int i = 0; i < 6; i++)
	{
		cout << char('a' + i) << ": ";
		for (int j = 0; HuffmanCode[i][j] != '\0'; j++)
		{
			cout << HuffmanCode[i][j];
		}
		cout << endl;
	}
	cout << endl;

	//�ͷţ�
	for (int i = 0; i < 6; i++)
	{
		delete[] HuffmanCode[i];
	}

	system("pause");
	return 0;
}