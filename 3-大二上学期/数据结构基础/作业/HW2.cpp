#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

//����һ����������Ľ���ࣺ
class ListNode
{
public:
	int value;
	ListNode* next;
};

//չʾ����ĺ�����
void display(ListNode* p)
{
	while (p != nullptr)	//������β���
	{
		cout << p->value << '\t';	//�������㴢���ֵ
		p = p->next;	//���ƶ�����һ���
	}
	cout << endl;
}

//ð����������
void sort(ListNode* head, int size)
{
	ListNode* p;
	for (int i = 0; i < size; i++)
	{
		p = head;	//ÿ������ָ������ͷ���λ��
		for (int j = 0; j < size - i - 1; j++)
		{
			if (p->value > (p->next)->value)
			{
				//����ǰ����ֵ���ں�һ����ֵ�򻥻���
				int tempValue = p->value;
				p->value = (p->next)->value;
				(p->next)->value = tempValue;
			}
			p = p->next;	//ָ������ƶ�
		}
	}
}

//��������
int main() {
	srand(time(0));

	//�������������ͷ����ָ�룺
	//������La��Lb��ͷ��㲻��ָ�룬�ǲ������Ͳ���Ҫɾ���ˣ���֪�������Բ��ԣ�
	ListNode La;
	ListNode Lb;
	ListNode* pa = &La;
	ListNode* pb = &Lb;
	//����趨������ĳ��ȣ�10-14��������0-99�������䣺
	int size_a = rand() % 5 + 10;
	int size_b = rand() % 5 + 10;
	cout << "La's size is " << size_a << ", Lb's size is " << size_b << ".\n\n";
	for (int i = 0; i < size_a; i++)
	{
		pa->value = rand() % 100;
		if (i < size_a - 1)
		{
			pa->next = new ListNode;
			pa = pa->next;
		}
		else
		{
			pa->next = nullptr;
		}
	}
	for (int i = 0; i < size_b; i++)
	{
		pb->value = rand() % 100;
		if (i < size_b - 1)
		{
			pb->next = new ListNode;
			pb = pb->next;
		}
		else
		{
			pb->next = nullptr;
		}
	}
	//չʾLa��Lb������
	cout << "La:\t";
	display(&La);
	cout << "Lb:\t";
	display(&Lb);
	//ð������
	sort(&La, size_a);
	sort(&Lb, size_b);
	//չʾLa��Lb������
	cout << "\n�����:\n";
	cout << "La:\t";
	display(&La);
	cout << "Lb:\t";
	display(&Lb);

	//����Lc��ͷ���
	ListNode Lc;
	if (La.value < Lb.value)
	{
		Lc = La;
		pa = La.next;
		pb = &Lb;
	}
	else
	{
		Lc = Lb;
		pa = &La;
		pb = Lb.next;
	}
	ListNode* pc = &Lc;
	//�ϲ�����
	while (pa != nullptr && pb != nullptr)	//pa��pb������һ������β���ʱ����ѭ��
	{
		if (pa->value < pb->value)	//��paָ�����ֵ��С
		{
			pc->next = pa;	//��pc��nextָ����һ���
			pa = pa->next;	//pa����
		}
		else	//��pbָ�����ֵ�������pa�����
		{
			pc->next = pb;	//��pc��nextָ����һ���
			pb = pb->next;	//pb����
		}
		pc = pc->next;	//pc����
	}
	pc->next = (pa == nullptr ? pb : pa);	//��δ��β�����������Lc�����
	//չʾ���飺
	cout << "\n�ϲ���:\n";
	cout << "Lc:\t";
	display(&Lc);

	system("pause");
	return 0;
}