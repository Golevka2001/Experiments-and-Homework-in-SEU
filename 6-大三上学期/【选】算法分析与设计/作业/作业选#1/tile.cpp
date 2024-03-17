#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

// 打印地板:
// f是储存地板的数组, m是边长
void printFloor(int **f, int m)
{
    for (int l = 0; l < m; ++l)
    {
        for (int c = 0; c < m; ++c)
            cout << setw(2) << f[l][c] << ' '; // 输出
        cout << endl;
    }
}

// 选择四种方向地板中的一种来铺放:
// f是储存地板的数组, type是地板的四种可能的方向(0-▜, 1-▟, 2-▙, 3-▛), l和c是空缺对应数组中的位置, n是填入的编号
void brickType(int **f, int type, int c, int l, int n)
{
    switch (type)
    {
    case (0): // ▜
        f[l - 1][c] = n;
        f[l - 1][c + 1] = n;
        f[l][c + 1] = n;
        break;
    case (1): // ▟
        f[l][c + 1] = n;
        f[l + 1][c + 1] = n;
        f[l + 1][c] = n;
        break;
    case (2): // ▙
        f[l + 1][c] = n;
        f[l + 1][c - 1] = n;
        f[l][c - 1] = n;
        break;
    case (3): // ▛
        f[l][c - 1] = n;
        f[l - 1][c - 1] = n;
        f[l - 1][c] = n;
        break;
    }
}

int n = 1; // 记录铺砖编号
//铺砖:
// f是储存地板的数组, m是边长, x和y是空缺位置, l和u是所要铺的部分的左上角的位置
void tile(int **f, int m, int x, int y, int l, int u)
{
    m /= 2; // 新一轮递归的m为原来的一半
    // 将要铺的部分分为四大块, 确定空缺位于哪一块, 铺上相应方向的砖,
    // 再分为四块, 刚才铺放的砖的三个空格分别位于这三块中, 递归:
    if (x >= m && y < m) // 位于右上块
    {
        brickType(f, 2, l + m, u + m - 1, n++); // ▙
        if (m < 2)                              // 已铺满
            return;
        tile(f, m, x - m, y, l + m, u); // 右上块递归(空缺所在块)
        tile(f, m, 0, 0, l + m, u + m); // 右下块递归
        tile(f, m, m - 1, 0, l, u + m); // 左下块递归
        tile(f, m, m - 1, m - 1, l, u); // 左上块递归
    }
    else if (x >= m && y >= m) // 位于右下块
    {
        brickType(f, 3, l + m, u + m, n++); // ▛
        if (m < 2)
            return;
        tile(f, m, x - m, y - m, l + m, u + m); // 右下块递归(空缺所在块)
        tile(f, m, m - 1, 0, l, u + m);         // 左下块递归
        tile(f, m, m - 1, m - 1, l, u);         // 左上块递归
        tile(f, m, 0, m - 1, l + m, u);         // 右上块递归
    }
    else if (x < m && y >= m) // 位于左下块
    {
        brickType(f, 0, l + m - 1, u + m, n++); // ▜
        if (m < 2)
            return;
        tile(f, m, x, y - m, l, u + m); // 左下块递归(空缺所在块)
        tile(f, m, m - 1, m - 1, l, u); // 左上块递归
        tile(f, m, 0, m - 1, l + m, u); // 右上块递归
        tile(f, m, 0, 0, l + m, u + m); // 右下块递归
    }
    else if (x < m && y < m) // 位于左上块
    {
        brickType(f, 1, l + m - 1, u + m - 1, n++); // ▟
        if (m < 2)
            return;
        tile(f, m, x, y, l, u);         // 左上块递归(空缺所在块)
        tile(f, m, 0, m - 1, l + m, u); // 右上块递归
        tile(f, m, 0, 0, l + m, u + m); // 右下块递归
        tile(f, m, m - 1, 0, l, u + m); // 左下块递归
    }
}

int main()
{
    // 输入尺寸:
    int m = 0;
    int n = 0;
    cout << "Size: (2^n) * (2^n)\n"
         << "n = ";
    cin >> n;
    m = pow(2, n);

    // 地板二维数组:
    int **floor = new int *[m];
    for (int i = 0; i < m; ++i)
        floor[i] = new int[m];
    for (int l = 0; l < m; ++l)
        for (int c = 0; c < m; ++c)
            floor[l][c] = 0;

    // 空缺位置:
    int x = -1;
    int y = -1;
    while (x < 0 || x >= m || y < 0 || y >= m)
    {
        cout << "Position of blank brick:" << endl
             << "x = ";
        cin >> x;
        cout << "y = ";
        cin >> y;
    }
    floor[y][x] = -1; // 空缺位置填入-1
    cout << endl;

    // 打印信息:
    cout << "Size: " << m << " * " << m << endl
         << "Position of blank brick: (" << x << ", " << y << ")" << endl
         << endl;
    printFloor(floor, m);
    cout << endl
         << endl;

    // 铺砖:
    tile(floor, m, x, y, 0, 0);

    // 打印地板:
    printFloor(floor, m);

    // 释放地板数组空间:
    for (int i = 0; i < m; ++i)
        delete[] floor[i];
    delete[] floor;

    return 0;
}