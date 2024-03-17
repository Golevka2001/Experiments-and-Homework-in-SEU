//cemployee.cpp
//作者：
//创建时间：2021-07
//功能：职员类，其成员包含了一个职工的所有基本信息：姓名，年龄，工号，入职日期，电话号码，住址。
//     成员函数中包含了从文本流中读取/保存职工信息的功能。

#include "cemployee.h"

//默认构造函数:
CEmployee::CEmployee()
    :m_strName(" "), m_nAge(0),
      m_strNo("0"), m_Date(2020, 01, 01),
      m_strPhone("0"), m_strAddress(" ")    //初始化
{}
//复制构造函数:
CEmployee::CEmployee(const CEmployee &eply)
    :m_strName(eply.m_strName), m_nAge(eply.m_nAge),
      m_strNo(eply.m_strNo), m_Date(eply.m_Date),
      m_strPhone(eply.m_strPhone), m_strAddress(eply.m_strAddress)
{}

//读取职工信息:
void CEmployee::ReadEmployee(QTextStream &stream)
{
    stream >> m_strName;    //读取姓名
    stream >> m_nAge;   //读取年龄
    stream >> m_strNo;  //读取工号

    int t_Y, t_M, t_D;  //临时储存年月日
    stream >> t_Y >> t_M >> t_D;    //依次读取入职日期年月日
    m_Date.setDate(t_Y, t_M, t_D);  //存入QDate对象

    stream >> m_strPhone;   //读取电话号码
    stream >> m_strAddress; //读取住址
}
//保存职工信息:
void CEmployee::SaveEmployee(QTextStream &stream)
{
    stream << m_strName << '\n';    //写入姓名
    stream << m_nAge << '\n';   //写入年龄
    stream << m_strNo << '\n';  //写入工号
    stream << m_Date.year() << " "
            << m_Date.month() << " "
            << m_Date.day() << '\n';    //写入入职日期
    stream << m_strPhone << '\n';   //写入电话号码
    stream << m_strAddress << '\n'; //写入住址
}
