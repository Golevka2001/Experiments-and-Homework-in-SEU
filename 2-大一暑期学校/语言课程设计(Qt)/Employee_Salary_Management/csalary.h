//csalary.h
//作者：
//创建时间：2021-07
//功能：月工资类，其成员包含了一个职工某月的工资信息：
//     月份，基本工资、岗位工资、工龄工资，津贴、岗贴、补贴、房贴、交通补贴
//     成员函数的全是针对这些值的set、get函数。

#ifndef CSALARY_H
#define CSALARY_H

class CSalary
{
public:
    //构造函数：
    CSalary(int M = 1, double S1 = 0, double S2 = 0, double S3 = 0,
            double A1 = 0, double A2 = 0, double A3 = 0, double A4 = 0, double A5 = 0);
    //复制构造函数：
    CSalary(const CSalary &slry);

    //设定所有成员变量的值：
    void SetAll(int M, double S1, double S2, double S3,
                double A1, double A2, double A3, double A4, double A5);

    //分别设定各成员变量的值：
    void SetMonth(int M);
    void SetSalary1(double S1);
    void SetSalary2(double S2);
    void SetSalary3(double S3);
    void SetAllowence1(double A1);
    void SetAllowence2(double A2);
    void SetAllowence3(double A3);
    void SetAllowence4(double A4);
    void SetAllowence5(double A5);

    //返回所需的成员变量的值：
    int GetMonth();
    double GetSalary(int index);
    double GetAllowence(int index);

    //返回工资、补贴之和，用于计算个人所得税和实发数：
    double GetSum();

private:
    int m_nMonth;   //月份

    double m_dSalary1;  //基本工资
    double m_dSalary2;  //岗位工资
    double m_dSalary3;  //工龄工资

    double m_dAllowence1;   //津贴
    double m_dAllowence2;   //岗贴
    double m_dAllowence3;   //补贴
    double m_dAllowence4;   //房贴
    double m_dAllowence5;   //交通补贴
};

#endif // CSALARY_H
