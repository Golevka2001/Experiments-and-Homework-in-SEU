//salaryinfotable.cpp
//作者：
//创建时间：2021-07
//功能：月工资数据集，和EmployeeInfoTable差不多一样

#include "salaryinfotable.h"

//构造函数：
SalaryInfoTable::SalaryInfoTable()
{
    CSalary t_EmptySalary(1, 0, 0, 0, 0, 0, 0, 0, 0);
    for(int i = 0; i < 12; i++)
    {
        t_EmptySalary.SetMonth(i + 1);
        m_Salary.push_back(t_EmptySalary);
    }
}

//从文件读取工资信息：
bool SalaryInfoTable::ReadFromFile(const QString &readFileName)
{
    //打开文件：
    QFile t_File(readFileName);    //创建QFile对象
    if(!t_File.exists())
        return false;   //文件不存在
    if(!t_File.open(QIODevice::ReadOnly | QIODevice::Text))  //打开方式为只读, 文本方式
        return false;   //打开失败
    QTextStream t_Stream(&t_File);    //以文本流读取文件
    m_Salary.clear();

    //逐月读取工资信息：
    //QTextStream t_Stream;
    for(int i = 0; i < 12; i++)
    {
        int t_nMonth;
        double t_dData[8];
        t_Stream >> t_nMonth;   //读取月份
        for(int j = 0; j < 8; j++)
            t_Stream >> t_dData[j]; //读取各项数据
        CSalary t_EmptySalary;
        t_EmptySalary.SetAll(t_nMonth, t_dData[0], t_dData[1], t_dData[2],
                t_dData[3], t_dData[4], t_dData[5], t_dData[6], t_dData[7]);
        m_Salary.push_back(t_EmptySalary);
    }

    //结束, 关闭文件：
    t_File.close();
    return true;
}
//保存职工信息到文件：
bool SalaryInfoTable::SaveToFile(const QString &saveFileName)
{
    //打开文件：
    QFile t_File(saveFileName); //构造QFile对象
    if(!t_File.open(QIODevice::WriteOnly | QIODevice::Text))  //打开方式为只写入, 文本方式
        return false;   //打开失败
    QTextStream t_Stream(&t_File);    //以文本流保存文件

    //逐月写入工资信息：
    for(int i = 0; i < 12; i++)
    {
        t_Stream << m_Salary[i].GetMonth() << '\n'; //写入月份
        for(int j = 0; j < 3; j++)
            t_Stream << m_Salary[i].GetSalary(j + 1) << '\n';   //写入各项工资
        for(int j = 0; j < 5; j++)
            t_Stream << m_Salary[i].GetAllowence(j + 1) << '\n';    //写入各项补贴
    }

    //结束, 关闭文件：
    t_File.close();
    return true;

}

//返回某月工资数据的引用：
CSalary &SalaryInfoTable::GetSalary(int index)
{
    return m_Salary[index];
}
