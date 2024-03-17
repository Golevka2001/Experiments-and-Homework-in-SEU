//employeeinfotable.cpp
//作者：
//创建时间：2021-07
//功能：职工信息表,记录文档中所有的职工。
//     成员函数包含从文件读取、储存职工信息，以及添加、编辑、删除。
#include "employeeinfotable.h"

//构造函数：
EmployeeInfoTable::EmployeeInfoTable()
{
    m_Employees.clear();  //初始化职工列表
    m_nNumber = 0;  //职工数量归零
}

//从文件读取职工信息：
bool EmployeeInfoTable::ReadFromFile(const QString &readFileName)
{
    //打开文件：
    QFile aFile(readFileName);    //创建QFile对象
    if(!aFile.exists())
        return false;   //文件不存在
    if(!aFile.open(QIODevice::ReadOnly | QIODevice::Text))  //打开方式为只读, 文本方式
        return false;   //打开失败
    QTextStream aStream(&aFile);    //以文本流读取文件
    aStream.setCodec(QTextCodec::codecForName("system")); //显示汉字

    //初始化：
    m_Employees.clear();
    m_nNumber = 0;

    //逐个读取职员信息：
    aStream >> m_nNumber;   //职员数量
    CEmployee t_Employee;   //临时职员对象
    for(int i = 0; i < m_nNumber; i++)
    {
        t_Employee.ReadEmployee(aStream);
        m_Employees.push_back(t_Employee);  //向vector中追加新职员
    }

    //结束, 关闭文件：
    aFile.close();
    return true;
}
//保存职工信息到文件：
bool EmployeeInfoTable::SaveToFile(const QString &saveFileName)
{
    //打开文件：
    QFile aFile(saveFileName); //构造QFile对象
    if(!aFile.open(QIODevice::WriteOnly | QIODevice::Text))  //打开方式为只写入, 文本方式
        return false;   //打开失败
    QTextStream aStream(&aFile);    //以文本流保存文件
    aStream.setCodec(QTextCodec::codecForName("system"));   //显示汉字

    //逐个写入职员信息：
    aStream << m_nNumber << '\n';   //职员数量
    for(int i = 0; i < m_nNumber; i++)
        m_Employees[i].SaveEmployee(aStream);

    //结束, 关闭文件：
    aFile.close();
    return true;
}

//添加新职工：
void EmployeeInfoTable::AddEmployee(CEmployee &eply)
{
    m_Employees.push_back(eply);    //向vector中追加新职员
    m_nNumber++;    //职员数量+1
}
//编辑职工：
void EmployeeInfoTable::EditEmployee(int index, CEmployee &eply)
{
    m_Employees.replace(index, eply);   //对该下标对应的职员进行替换
}
//删除职工：
void EmployeeInfoTable::RemoveEmployee(int index)
{
    m_Employees.remove(index);  //移除该下标对应的职员
    m_nNumber--;    //职员数量-1
}
//返回一个职工的引用：
 CEmployee &EmployeeInfoTable::GetEmployee(int index)
 {
     return m_Employees[index];  //返回下标对应的职员对象的引用
 }
 //返回职工总数：
 int EmployeeInfoTable::GetEmployeeNum()
 {
     m_nNumber = m_Employees.size(); //职员数量通过vector的size来获取
     return m_nNumber;
 }
