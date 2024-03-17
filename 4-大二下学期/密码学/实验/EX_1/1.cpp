#include<iostream>
#include<string>
#include<iomanip>
using namespace std;

const string cipher = "UZQSOVUOHXMOPVGPOZPEVSGZWSZOPFPESXUDBMETSXAIZVUEPHZHMDZSHZOWSFPAPPDTSVPQUZWYMXUZUHSXEPYEPOPDZSZUFPOMBZWPFUPZHMDJUDTMOHMQ";
const int length = cipher.size();
string plain = cipher;

void replace(char from, char to)
{
	cout << from << " -> " << to << endl;
	for (int i = 0; i < length; ++i)
		if (plain[i] == from)
			plain[i] = to;
	cout << plain << endl << endl;
}

int main()
{
	int frequency[26] = { 0 };
	for (int i = 0; i < length; ++i)
		++frequency[int(cipher[i] - 'A')];
	// 统计各字母出现频率：
	for (int i = 0; i < 26; ++i)
		cout << char('A' + i) << ": "
		<< setw(2) << frequency[i] << " / " << length << " = "
		<< double(frequency[i]) / length << endl;
	cout << endl;

	replace('P', 'e');
	replace('Z', 't');
	replace('W', 'h');
	replace('S', 'a');
	replace('U', 'i');
	replace('O', 's');
	replace('Q', 'w');
	replace('M', 'o');
	replace('H', 'c');
	replace('V', 'd');
	replace('X', 'l');
	replace('E', 'r');
	replace('F', 'v');
	replace('G', 'y');
	replace('D', 'n');
	replace('B', 'f');
	replace('T', 'm');
	replace('A', 'b');
	replace('I', 'u');
	replace('Y', 'p');
	replace('J', 'g');
	cout << "The result is:\n"
		<< "It was disclosed yesterday that several informal but direct contacts have been made with political representatives of the Viet Cong in Moscow.\n\n";

	system("pause");
	return 0;
}