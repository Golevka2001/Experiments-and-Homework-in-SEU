//cemployee.h
//作者：
//创建时间：2021-07
//功能：职员类，其成员包含了一个职工的所有基本信息：姓名，年龄，工号，入职日期，电话号码，住址。
//     成员函数中包含了从文本流中读取/保存职工信息的功能。

#ifndef CEMPLOYEE_H
#define CEMPLOYEE_H

#include <QString>
#include <QDate>
#include <QTextStream>
#include <QTextCodec>
#include <QByteArray>

#include "csalary.h"

class CEmployee
{
public:
    //默认构造函数：
    CEmployee();
    //复制构造函数：
    CEmployee(const CEmployee &eply);

    //读取职工信息：
    void ReadEmployee(QTextStream &stream);
    //保存职工信息：
    void SaveEmployee(QTextStream &stream);

    //姓名，年龄，工号，入职日期，电话号码，住址
    //为方便调用，设为了public
    QString m_strName;      //姓名
    int m_nAge;             //年龄
    QString m_strNo;        //工号
    QDate m_Date;           //入职日期
    QString m_strPhone;     //电话号码
    QString m_strAddress;   //住址
};

#endif // CEMPLOYEE_H
