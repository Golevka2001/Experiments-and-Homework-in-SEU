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

	//填充字符串，并统计每个字符出现的次数：
	for (int i = 0; i < 40; i++)
	{
		int offset = rand() % 6;
		str[i] = 'a' + offset;	//范围为a-f
		frequency[offset]++;
	}

	//输出字符串：
	cout << "Initial string:\n";
	for (int i = 0; i < 40; i++)
	{
		cout << str[i] << ' ';
	}
	cout << endl << endl;

	//输出字符出现次数：
	cout << "Frequency:\n";
	for (int i = 0; i < 6; i++)
	{
		cout << order[i] << ": " << frequency[order[i] - 'a'] << '\t';
	}
	cout << endl << endl;

	//根据出现次数，从大到小对字符进行排序：
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

	//输出排序结果：
	cout << "After sorted:\n";
	for (int i = 0; i < 6; i++)
	{
		cout << order[i] << ": " << frequency[order[i] - 'a'] << '\t';
	}
	cout << endl << endl;

	//霍夫曼编码：
	for (int i = 0; i < 5; i++)
	{
		HuffmanCode[order[i] - 'a'] = new char[i + 2];
		for (int j = 0; j < i + 1; j++)
		{
			HuffmanCode[order[i] - 'a'][j] = '0';
		}
		HuffmanCode[order[i] - 'a'][i + 1] = '\0';
	}
	HuffmanCode[order[5] - 'a'] = new char[4 + 2];	//最后一个和倒数第二个编码长度相同，对最后一个单独设置
	for (int i = 0; i < 4; i++)
	{
		HuffmanCode[order[5] - 'a'][i] = '0';
	}
	HuffmanCode[order[5] - 'a'][4] = '1';
	HuffmanCode[order[5] - 'a'][4 + 1] = '\0';

	//输出编码结果：
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

	//释放：
	for (int i = 0; i < 6; i++)
	{
		delete[] HuffmanCode[i];
	}

	system("pause");
	return 0;
}