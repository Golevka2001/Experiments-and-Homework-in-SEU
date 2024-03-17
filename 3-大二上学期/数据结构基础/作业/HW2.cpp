#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

//创建一个单向链表的结点类：
class ListNode
{
public:
	int value;
	ListNode* next;
};

//展示链表的函数：
void display(ListNode* p)
{
	while (p != nullptr)	//若不是尾结点
	{
		cout << p->value << '\t';	//则输出结点储存的值
		p = p->next;	//并移动到下一结点
	}
	cout << endl;
}

//冒泡排序函数：
void sort(ListNode* head, int size)
{
	ListNode* p;
	for (int i = 0; i < size; i++)
	{
		p = head;	//每次排序将指针置于头结点位置
		for (int j = 0; j < size - i - 1; j++)
		{
			if (p->value > (p->next)->value)
			{
				//若当前结点的值大于后一结点的值则互换：
				int tempValue = p->value;
				p->value = (p->next)->value;
				(p->next)->value = tempValue;
			}
			p = p->next;	//指针向后移动
		}
	}
}

//主函数：
int main() {
	srand(time(0));

	//声明两个链表的头结点和指针：
	//（这里La和Lb是头结点不是指针，是不是最后就不需要删除了，不知道这样对不对）
	ListNode La;
	ListNode Lb;
	ListNode* pa = &La;
	ListNode* pb = &Lb;
	//随机设定两链表的长度（10-14），并用0-99随机数填充：
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
	//展示La、Lb两链表：
	cout << "La:\t";
	display(&La);
	cout << "Lb:\t";
	display(&Lb);
	//冒泡排序：
	sort(&La, size_a);
	sort(&Lb, size_b);
	//展示La、Lb两链表：
	cout << "\n排序后:\n";
	cout << "La:\t";
	display(&La);
	cout << "Lb:\t";
	display(&Lb);

	//声明Lc的头结点
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
	//合并链表：
	while (pa != nullptr && pb != nullptr)	//pa和pb至少有一个到达尾结点时跳出循环
	{
		if (pa->value < pb->value)	//若pa指向结点的值更小
		{
			pc->next = pa;	//则pc的next指向这一结点
			pa = pa->next;	//pa后移
		}
		else	//若pb指向结点的值更大或与pa的相等
		{
			pc->next = pb;	//则pc的next指向这一结点
			pb = pb->next;	//pb后移
		}
		pc = pc->next;	//pc后移
	}
	pc->next = (pa == nullptr ? pb : pa);	//将未至尾结点的链表接在Lc的最后
	//展示数组：
	cout << "\n合并后:\n";
	cout << "Lc:\t";
	display(&Lc);

	system("pause");
	return 0;
}