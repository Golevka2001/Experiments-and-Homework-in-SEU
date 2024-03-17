//csalary.cpp
//作者：
//创建时间：2021-07
//功能：月工资类，其成员包含了一个职工某月的工资信息：
//     月份，基本工资、岗位工资、工龄工资，津贴、岗贴、补贴、房贴、交通补贴
//     成员函数的全是针对这些值的set、get函数。

#include "csalary.h"

//构造函数：
CSalary::CSalary(int M, double S1, double S2, double S3,
                 double A1, double A2, double A3, double A4, double A5)
{
    SetAll(M, S1, S2, S3, A1, A2, A3, A4, A5);  //初始化，月份为1，其他都是0
}
//复制构造函数：
CSalary::CSalary(const CSalary &slry)
{
    SetAll(slry.m_nMonth,
           slry.m_dSalary1, slry.m_dSalary2, slry.m_dSalary3,
           slry.m_dAllowence1, slry.m_dAllowence2, slry.m_dAllowence3,
           slry.m_dAllowence4, slry.m_dAllowence5);
}

//设定所有成员变量的值：
void CSalary::SetAll(int M, double S1, double S2, double S3,
            double A1, double A2, double A3, double A4, double A5)
{
    SetMonth(M);
    SetSalary1(S1);
    SetSalary2(S2);
    SetSalary3(S3);
    SetAllowence1(A1);
    SetAllowence2(A2);
    SetAllowence3(A3);
    SetAllowence4(A4);
    SetAllowence5(A5);
}

//分别设定各成员变量的值：
void CSalary::SetMonth(int M)
{
    if(M < 1)
        m_nMonth = 1;   //若输入月份小于1，设为1
    else if(M > 12)
        m_nMonth = 12;  //若输入月份大于12,设为12
    else
        m_nMonth = M;   //输入月份在正确区间内
}
void CSalary::SetSalary1(double S1)
{
    if(S1 > 0)
        m_dSalary1 = S1;//输入工资大于0
    else
        m_dSalary1 = 0; //否则设为0,下同
}
void CSalary::SetSalary2(double S2)
{
    if(S2 > 0)
        m_dSalary2 = S2;
    else
        m_dSalary2 = 0;
}
void CSalary::SetSalary3(double S3)
{
    if(S3 > 0)
        m_dSalary3 = S3;
    else
        m_dSalary3 = 0;
}
void CSalary::SetAllowence1(double A1)
{
    if(A1 > 0)
        m_dAllowence1 = A1;
    else
        m_dAllowence1 = 0;
}
void CSalary::SetAllowence2(double A2)
{
    if(A2 > 0)
        m_dAllowence2 = A2;
    else
        m_dAllowence2 = 0;
}
void CSalary::SetAllowence3(double A3)
{
    if(A3 > 0)
        m_dAllowence3 = A3;
    else
        m_dAllowence3 = 0;
}
void CSalary::SetAllowence4(double A4)
{
    if(A4 > 0)
        m_dAllowence4 = A4;
    else
        m_dAllowence4 = 0;
}
void CSalary::SetAllowence5(double A5)
{
    if(A5 > 0)
        m_dAllowence5 = A5;
    else
        m_dAllowence5 = 0;
}

//返回所需的成员变量的值：
int CSalary::GetMonth()
{
    return m_nMonth;    //返回月份
}
double CSalary::GetSalary(int index)
{
    switch(index)
    {
    case 1:
        return m_dSalary1;  //返回基本工资
    case 2:
        return m_dSalary2;  //返回岗位工资
    case 3:
        return m_dSalary3;  //返回工龄工资
    default:
        return 0;   //若输入下标超出范围返回0
    }
}
double CSalary::GetAllowence(int index)
{
    switch(index)
    {
    case 1:
        return m_dAllowence1;   //返回津贴
    case 2:
        return m_dAllowence2;   //返回岗贴
    case 3:
        return m_dAllowence3;   //返回补贴
    case 4:
        return m_dAllowence4;   //返回房贴
    case 5:
        return m_dAllowence5;   //返回交通补贴
    default:
        return 0;   //若输入下标超出范围返回0
    }
}
//返回工资、补贴之和，用于计算个人所得税和实发数：
double CSalary::GetSum()
{
    return m_dSalary1 + m_dSalary2 + m_dSalary3 +
            m_dAllowence1 + m_dAllowence2 + m_dAllowence3 + m_dAllowence4 + m_dAllowence5;
}
