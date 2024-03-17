//salaryinfotable.h
//作者：
//创建时间：2021-07
//功能：月工资数据集，和EmployeeInfoTable差不多一样

#ifndef SALARYINFOTABLE_H
#define SALARYINFOTABLE_H

#include <QVector>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>

#include "csalary.h"

class SalaryInfoTable
{
public:
    //构造函数：
    SalaryInfoTable();

    //从文件读取工资信息：
    bool ReadFromFile(const QString &readFileName);
    //保存职工信息到文件：
    bool SaveToFile(const QString &saveFileName);

    //返回某月工资数据的引用：
    CSalary &GetSalary(int index);

private:
    QVector <CSalary> m_Salary;   //月工资数据集
};

#endif // SALARYINFOTABLE_H
