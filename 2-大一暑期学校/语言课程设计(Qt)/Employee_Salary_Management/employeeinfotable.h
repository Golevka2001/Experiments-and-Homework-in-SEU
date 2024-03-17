//employeeinfotable.h
//作者：
//创建时间：2021-07
//功能：职工信息表,记录文档中所有的职工。
//     成员函数包含从文件读取、储存职工信息，以及添加、编辑、删除。

#ifndef EMPLOYEEINFOTABLE_H
#define EMPLOYEEINFOTABLE_H

#include <QVector>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>

#include "cemployee.h"

class EmployeeInfoTable
{
public:
    //构造函数：
    EmployeeInfoTable();

    //从文件读取职工信息：
    bool ReadFromFile(const QString &readFileName);
    //保存职工信息到文件：
    bool SaveToFile(const QString &saveFileName);

    //添加新职工：
    void AddEmployee(CEmployee &eply);
    //编辑职工：
    void EditEmployee(int index, CEmployee &eply);
    //移除职工：
    void RemoveEmployee(int index);

    //返回一个职工的引用：
    CEmployee &GetEmployee(int index);
    //返回职工总数：
    int GetEmployeeNum();

private:
    QVector <CEmployee> m_Employees;  //职工列表
    int m_nNumber;  //职工数量
};

#endif // EMPLOYEEINFOTABLE_H
