#include<iostream>
using namespace std;

// ����Ԫһ�β���ʽ������gcd(a, b)��
int exgcd(int a, int b, int& x, int& y)
{
    if (b == 0)
    {
        x = 1, y = 0;
        return a;
    }
    cout << a << " = " << b << " * " << a / b << " + " << a - b * (a / b) << endl;
    int sum = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return sum;
}

// ���ģ��Ԫ��
int inv(int a, int p)
{
    int x, y;
    exgcd(a, p, x, y);
    return (x % p + p) % p;
}

int main()
{
    char sel = ' ';
    while (1)
    {
        cout << "A.����������\nB.���˷���Ԫ\nQ.�˳�\n>>>";
        cin >> sel;
        cout << endl;
        if (sel == 'A')
        {
            int a = 0, b = 0, x = 0, y = 0;
            cout << "a = ";
            cin >> a;
            cout << "b = ";
            cin >> b;
            cout << endl;
            cout << "=> gcd(" << a << ", " << b << ") = "
                << exgcd(a, b, x, y) << " = "
                << a << " * " << x << " + " << b << " * " << y
                << "\n\n\n";
        }
        else if (sel == 'B')
        {
            int a = 0, p = 0, x = 0;
            cout << "p = ";
            cin >> p;
            cout << "a = ";
            cin >> a;
            cout << endl;
            cout << a << "x = 1 (mod " << p << ")\n\n";
            cout << "=> x = " << inv(a, p)
                << "\n\n\n";
        }
        else if (sel == 'Q')
            break;
    }
    system("pause");
    return 0;
}
