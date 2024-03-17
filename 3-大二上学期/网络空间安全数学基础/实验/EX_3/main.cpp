#include<iostream>
using namespace std;

void Display(const char* cards[13])
{
	for (int i = 0; i < 13; i++)
		cout << cards[i] << "  ";
	cout << endl << endl;
}

void Shuffle(const char* cards[13], const char* order[13])
{
	for (int i = 0; i < 13; i++)
	{
		const char* c = cards[i];
		if (c == "A")
			cards[i] = order[0];
		else if (c == "2")
			cards[i] = order[1];
		else if (c == "3")
			cards[i] = order[2];
		else if (c == "4")
			cards[i] = order[3];
		else if (c == "5")
			cards[i] = order[4];
		else if (c == "6")
			cards[i] = order[5];
		else if (c == "7")
			cards[i] = order[6];
		else if (c == "8")
			cards[i] = order[7];
		else if (c == "9")
			cards[i] = order[8];
		else if (c == "10")
			cards[i] = order[9];
		else if (c == "J")
			cards[i] = order[10];
		else if (c == "Q")
			cards[i] = order[11];
		else if (c == "K")
			cards[i] = order[12];
	}
	Display(cards);
}

int main()
{
	const char* cards[13] = { "A","2","3","4","5","6","7","8","9","10","J","Q","K" };
	const int r1 = 2;
	const int r2 = 3;
	const int r3 = 8;
	const char* G1[13] = { "10","Q","A","5","2","6","K","3","8","9","7","J","4" };
	const char* G2[13] = { "3","6","7","A","10","K","4","2","J","Q","9","5","8" };
	const char* G3[13] = { "4","A","3","K","J","10","6","Q","8","9","5","7","2" };

	cout << "Initial:\n";
	Display(cards);

	cout << "Shuffle-G1:\n";
	for (int i = 0; i < r1; i++)
		Shuffle(cards, G1);

	cout << "Shuffle-G2:\n";
	for (int i = 0; i < r2; i++)
		Shuffle(cards, G2);

	cout << "Shuffle-G3:\n";
	for (int i = 0; i < r3; i++)
		Shuffle(cards, G3);

	cout << endl << endl;

	//G1可写为(A 10 9 8 3)(2 Q J 7 K 4 5)(16)；5、7、1最小公倍数为35
	//G2可写为(A 3 7 4)(2 6 K 8)(5 10 Q)(9 J)；4、4、3、2最小公倍数为12
	//G3可写为(A 4 K 2)(3)(5 J)(6 10 9 8 Q 7)；4、1、2、6最小公倍数为12
	for (int i = 0; i < 12-r3; i++)
		Shuffle(cards, G3);
	for (int i = 0; i < 12-r2; i++)
		Shuffle(cards, G2);
	for (int i = 0; i < 35-r1; i++)
		Shuffle(cards, G1);

	system("pause");
	return 0;
}