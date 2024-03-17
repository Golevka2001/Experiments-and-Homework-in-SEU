#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

//�������۰����
bool Search(vector<int>vec, int target, int& position)
{
	int low = 0;
	int mid;
	int high = vec.size() - 1;
	while (1)
	{
		mid = (low + high) / 2;	//����mid

		if ((low == mid || high == mid)&&target!=vec[mid])	//��low��high��mid�غ��һ�δ�ҵ�
		{
			position = -1;
			return false;	//�����ʧ��
		}
		if (target == vec[low])	//����low����ֵ���
		{
			position = low;
			return true;
		}
		if (target == vec[mid])	//����mid����ֵ���
		{
			position = mid;
			return true;
		}
		if (target == vec[high])	//����high����ֵ���
		{
			position = high;
			return true;
		}

		//�任low��high��λ��
		if (target < vec[mid])
		{
			high = mid - 1;
		}
		if (target > vec[mid])
		{
			low = mid + 1;
		}
	}
}


int main()
{
	srand(time(0));

	vector<int> vec(100);

	//�����䣺
	for (int i = 0; i < 100; i++)
	{
		vec[i] = rand() % 1000;	//��Χ��0-999
	}

	//��ӡԭʼ���ݣ�
	cout << "Initial:\n";
	for (int i = 0; i < 100; i++)
	{
		cout << vec[i] << '\t';
	}
	cout << endl << endl;

	//������������
	sort(vec.begin(), vec.end());

	//��ӡ�����˳��
	cout << "Ascending order:\n";
	for (int i = 0; i < 100; i++)
	{
		cout << vec[i] << '\t';
	}
	cout << endl << endl;

	//������ҵ�Ŀ����ֵ��
	int target = 0;
	int position = 0;
	cout << "Target number: ";
	cin >> target;

	if (Search(vec, target, position))	//���ҳɹ�
	{
		cout << "\nFound\nPosition: " << position << endl << endl;	//��ӡ�ɹ�+λ��
	}
	else	//����ʧ��
	{
		cout << "\nNot Found\n\n";	//��ӡʧ��
	}

	system("pause");
	return 0;
}