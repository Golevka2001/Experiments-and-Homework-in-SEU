//mainwindow.cpp
//作者：
//创建时间：2021-07
//功能：主窗口，包含了窗口中的各项操作。

#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QFileDevice>
#include <QTextStream>
#include <QtEvents>
#include <QString>
#include <QStandardItemModel>
#include <QAbstractItemDelegate>
#include <QVariant>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addeditdialog.h"
#include "selectdialog.h"
#include "searchdialog.h"
#include "readonlydelegate.h"
#include "salarydialog.h"

bool g_bFlagOpen = 0;   //标记：判断是否打开了一个文件
bool g_bFlagSearch = 0; //标记：是否完成查找
QString g_strLastFileName = " ";    //最后一次使用的文件名
int g_nEmployeeNum = 0; //职工总数

//主窗口构造函数：
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);    //单次选择
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);    //选中一个item

    employeeInfoModel = new QStandardItemModel();   //QStandardItemModel类对象用于储存一个二维项数据数组，储存数据
    ui->tableView->setModel(employeeInfoModel);

    //建立信号与槽的关联：
    connect(ui->tableView->itemDelegate(),
            &QAbstractItemDelegate::closeEditor, this, &MainWindow::on_tableView_changed);
    connect(ui->tableView,SIGNAL(clicked(QModelIndex)),this,SLOT(show_list()));
}

//主窗口析构函数：
MainWindow::~MainWindow()
{
    delete ui;
    delete employeeInfoModel;
    delete readOnlyDelegate;
}

//窗口改变大小的时候列表控件跟着改变：
void MainWindow::resizeEvent(QResizeEvent *event)
{
    //父类的保持：
    QMainWindow::resizeEvent(event);

    //主窗口宽度、高度：
    int x = this->frameGeometry().width();
    int y = this->frameGeometry().height();

    //设定列表尺寸：
    ui->tableView->setGeometry(x*0.013, 61, x*0.97625, y*0.785);
    for(int i = 0; i < 6; i++)
        ui->tableView->setColumnWidth(i, ui->tableView->width()/6);
}

//表格数据改动：
void MainWindow::on_tableView_changed()
{
    QModelIndex t_Index = ui->tableView->currentIndex();
    CEmployee &t_Employee = m_InfoTable.GetEmployee(GetRowIndex()); //获取当前选中职员的引用
    QString t_strSalaryFileName = g_strLastFileName.left(g_strLastFileName.size() - 4)
            + "_" + t_Employee.m_strNo + ".txt";
    QFile t_SalaryFile(t_strSalaryFileName);
    QString t_strRename;
    QVariant t_Data;    //暂时储存数据
    t_Data = employeeInfoModel->data(t_Index);  //获取数值
    switch(GetColumnIndex())    //根据列号选择编辑的内容
    {
    case 0: //姓名
        t_Employee.m_strName = t_Data.toString();
        break;
    //case 1: //年龄，设为只读，防止错误输入
    case 2: //工号
        t_Employee.m_strNo = t_Data.toString();
        t_strRename = g_strLastFileName.left(g_strLastFileName.size() - 4)
                + "_" + t_Employee.m_strNo + ".txt";
        t_SalaryFile.rename(t_strRename);   //该职工对应工资文件重命名
        break;
    //case 3: //入职日期，设为只读，防止错误输入
    case 4: //电话号码
        t_Employee.m_strPhone = t_Data.toString();
        break;
    case 5: //住址
        t_Employee.m_strAddress = t_Data.toString();
        break;
    }
}

//显示全部职工列表：
void MainWindow::ShowEmployeeList()
{
    //初始化：
    employeeInfoModel->clear(); //清空数据信息
    employeeInfoModel->setColumnCount(6);   //设置为6列
    for(int i = 0; i < 6; i++)
        ui->tableView->setColumnWidth(i, ui->tableView->width()/6); //设定列宽
    int t_nRowCount = m_InfoTable.GetEmployeeNum();
    employeeInfoModel->setRowCount(t_nRowCount);   //根据职工数量设置行数

    //表头：
    //姓名，年龄，工号，入职日期，电话号码，住址
    QStringList t_List;
    t_List.append("姓名");
    t_List.append("年龄");
    t_List.append("工号");
    t_List.append("入职日期");
    t_List.append("电话号码");
    t_List.append("住址");
    employeeInfoModel->setHorizontalHeaderLabels(t_List);   //设定表头内容

    //遍历、插入数据：
    QStandardItem *t_Item;  //创建临时Item对象
    QString t_Str;

    //依次从储存职工的Vector中读取，并存在临时职工对象中：
    for(int i = 0; i < t_nRowCount; i++)
    {
        CEmployee t_Employee = m_InfoTable.GetEmployee(i);
        //填入姓名：
        t_Item = new QStandardItem(t_Employee.m_strName);
        employeeInfoModel->setItem(i, 0, t_Item);
        //居中显示文本：
        t_Item->setTextAlignment(Qt::AlignCenter);

        //填入年龄：
        t_Str = QString::number(t_Employee.m_nAge); //int类型转为string类型
        t_Item = new QStandardItem(t_Str);
        employeeInfoModel->setItem(i, 1, t_Item);
        //居中显示文本：
        t_Item->setTextAlignment(Qt::AlignCenter);

        //填入工号：
        t_Item = new QStandardItem(t_Employee.m_strNo);
        employeeInfoModel->setItem(i, 2, t_Item);
        //居中显示文本：
        t_Item->setTextAlignment(Qt::AlignCenter);

        //填入入职日期：
        t_Str = t_Employee.m_Date.toString("yyyy-MM-dd");   //QDate类型转为string类型
        t_Item = new QStandardItem(t_Str);
        employeeInfoModel->setItem(i, 3, t_Item);
        //居中显示文本：
        t_Item->setTextAlignment(Qt::AlignCenter);

        //填入电话号码：
        t_Item = new QStandardItem(t_Employee.m_strPhone);
        employeeInfoModel->setItem(i, 4, t_Item);
        //居中显示文本：
        t_Item->setTextAlignment(Qt::AlignCenter);

        //填入住址：
        t_Item = new QStandardItem(t_Employee.m_strAddress);
        employeeInfoModel->setItem(i, 5, t_Item);
        //居中显示文本：
        t_Item->setTextAlignment(Qt::AlignCenter);
    }
    //设置年龄、入职日期为只读
    ui->tableView->setItemDelegateForColumn(1, readOnlyDelegate);
    ui->tableView->setItemDelegateForColumn(3, readOnlyDelegate);
}
//显示部分职工列表：
void MainWindow::ShowEmployeeList(QVector <int> index)
{
    //初始化：
    employeeInfoModel->clear(); //清空数据信息
    employeeInfoModel->setColumnCount(6);   //设置为6列
    for(int i = 0; i < 6; i++)
        ui->tableView->setColumnWidth(i, ui->tableView->width()/6); //设定列宽
    employeeInfoModel->setRowCount(index.size());   //根据职工数量设置行数

    //表头：
    //姓名，年龄，工号，入职日期，电话号码，住址
    QStringList t_List;
    t_List.append("姓名");
    t_List.append("年龄");
    t_List.append("工号");
    t_List.append("入职日期");
    t_List.append("电话号码");
    t_List.append("住址");
    employeeInfoModel->setHorizontalHeaderLabels(t_List);   //设定表头内容

    //遍历、插入数据：
    QStandardItem *t_Item;  //创建临时Item对象
    QString t_Str;

    //依次从储存职工的Vector中读取，并存在临时职工对象中：
    for(int i = 0; i < index.size(); i++)
    {
        CEmployee t_Employee = m_InfoTable.GetEmployee(index[i]);
        //填入姓名：
        t_Item = new QStandardItem(t_Employee.m_strName);
        employeeInfoModel->setItem(i, 0, t_Item);
        //居中显示文本：
        t_Item->setTextAlignment(Qt::AlignCenter);

        //填入年龄：
        t_Str = QString::number(t_Employee.m_nAge); //int类型转为string类型
        t_Item = new QStandardItem(t_Str);
        employeeInfoModel->setItem(i, 1, t_Item);
        //居中显示文本：
        t_Item->setTextAlignment(Qt::AlignCenter);

        //填入工号：
        t_Item = new QStandardItem(t_Employee.m_strNo);
        employeeInfoModel->setItem(i, 2, t_Item);
        //居中显示文本：
        t_Item->setTextAlignment(Qt::AlignCenter);

        //填入入职日期：
        t_Str = t_Employee.m_Date.toString("yyyy-MM-dd");   //QDate类型转为string类型
        t_Item = new QStandardItem(t_Str);
        employeeInfoModel->setItem(i, 3, t_Item);
        //居中显示文本：
        t_Item->setTextAlignment(Qt::AlignCenter);

        //填入电话号码：
        t_Item = new QStandardItem(t_Employee.m_strPhone);
        employeeInfoModel->setItem(i, 4, t_Item);
        //居中显示文本：
        t_Item->setTextAlignment(Qt::AlignCenter);

        //填入住址：
        t_Item = new QStandardItem(t_Employee.m_strAddress);
        employeeInfoModel->setItem(i, 5, t_Item);
        //居中显示文本：
        t_Item->setTextAlignment(Qt::AlignCenter);
    }
    for(int i = 0; i < 6; i++)
        ui->tableView->setItemDelegateForColumn(i, readOnlyDelegate);
}

//返回当前选中的行号：
int MainWindow::GetRowIndex()
{
    int t_nRowIndex = -1;
    t_nRowIndex = ui->tableView->currentIndex().row();    //获取当前选择的行号
    return t_nRowIndex;
}
//返回当前选中的列号：
int MainWindow::GetColumnIndex()
{
    int t_nColumnIndex = -1;
    t_nColumnIndex = ui->tableView->currentIndex().column();    //获取当前选择的行号
    return t_nColumnIndex;
}

//点击“打开”：
void MainWindow::on_actionOpen_triggered()
{
    QString t_strCurPath = QDir::currentPath(); //当前路径
    QString t_strDlgTitle = "选择一个文件";
    QString t_strFilter = "文本文件(*.txt)";    //文件类型过滤
    QString t_strFileName = QFileDialog::getOpenFileName(this, t_strDlgTitle, t_strCurPath, t_strFilter);  //文件名

    if(t_strFileName.isEmpty()) //文件名为空
        return;

    //创建成功,打开文件：
    g_bFlagOpen = 1;    //打开文件标记设为1
    g_strLastFileName = t_strFileName;  //记录文件名
    m_InfoTable.ReadFromFile(t_strFileName);    //读取职工信息
    ShowEmployeeList(); //显示在表中
    g_nEmployeeNum = m_InfoTable.GetEmployeeNum();
}

//点击“保存”：
void MainWindow::on_actionSave_triggered()
{
    if(g_bFlagOpen) //判断是否有文件被打开，若有，继续执行保存
        m_InfoTable.SaveToFile(g_strLastFileName);
    else    //若没有文件被打开，提示错误
    {
        QMessageBox::warning(this, tr("警告"), tr("请先新建或打开文件"));
        return;
    }
}

//点击“另存为”：
void MainWindow::on_actionSave_As_triggered()
{
    if(g_bFlagOpen) //判断是否有文件被打开，若有，继续执行保存
    {
        QString t_strCurPath = QDir::currentPath(); //当前路径
        QString t_strDlgTitle = "选择一个文件";
        QString t_strFilter = "文本文件(*.txt)";    //文件类型过滤
        QString t_strFileName = QFileDialog::getOpenFileName(this, t_strDlgTitle, t_strCurPath, t_strFilter);  //文件名

        if(t_strFileName.isEmpty()) //文件名为空
            return;

        m_InfoTable.SaveToFile(t_strFileName);
    }
    else    //若没有文件被打开，提示错误
    {
        QMessageBox::warning(this, tr("警告"), tr("请先新建或打开文件"));
        return;
    }
}

//点击“添加新职工”：
void MainWindow::on_actionAdd_triggered()
{
    if(g_bFlagOpen) //判断是否有文件被打开，若有，弹出编辑窗口
    {
        AddEditDialog ADlg(this);   //创建添加新职工对话框
        int ret = ADlg.exec();

        if(ret == AddEditDialog::Accepted)  //OK按钮被点击
        {
            CEmployee t_Employee;   //创建临时职员对象
            //从dialog中获取：
            t_Employee.m_strName = ADlg.GetName();
            t_Employee.m_nAge = ADlg.GetAge();
            t_Employee.m_strNo = ADlg.GetNo();
            t_Employee.m_Date = ADlg.GetDate();
            t_Employee.m_strPhone = ADlg.GetPhone();
            t_Employee.m_strAddress = ADlg.GetAddress();
            m_InfoTable.AddEmployee(t_Employee);    //将新职员添加到列表中
            ShowEmployeeList(); //显示变更后的列表

            //在同一目录下创建该职工的工资信息文件：
            QString t_strSalaryFileName = g_strLastFileName.left(g_strLastFileName.size() - 4)  //-4用于删去原文件名末尾的.txt
                    + "_" + t_Employee.m_strNo + ".txt";  //以“主文件名_工号.txt”的格式命名
            QFile t_SalaryFile(t_strSalaryFileName);
            t_SalaryFile.open(QIODevice::WriteOnly | QIODevice::Text);
            SalaryInfoTable t_InfoTable;
            t_InfoTable.SaveToFile(t_strSalaryFileName);
            t_SalaryFile.close();

            g_nEmployeeNum++;
        }
    }
    else        //若没有文件被打开，提示错误
    {
        QMessageBox::warning(this, tr("警告"), tr("请先新建或打开文件"));
        return;
    }
}

//点击“编辑职工”：
void MainWindow::on_actionEdit_triggered()
{
    if(g_bFlagOpen) //判断是否有文件被打开，若有，弹出编辑窗口
    {
        if(g_nEmployeeNum == 0) //若当前文件中没有职工，提示错误
        {
            QMessageBox::warning(this, tr("警告"), tr("请先添加新职工"));
            return;
        }
        if(GetRowIndex() == -1) //没有选择职工
        {
            QMessageBox::warning(NULL, "警告", "请先选择一位职工");
            return;
        }

        if(g_bFlagSearch == 1)    //列表显示为查找窗口
        {
            QMessageBox::warning(NULL, "警告", "请在总列表中进行编辑操作");
            return;
        }
        AddEditDialog EDlg(this, m_InfoTable.GetEmployee(GetRowIndex()));   //创建编辑职工对话框

        QString t_strSalaryFileName = g_strLastFileName.left(g_strLastFileName.size() - 4)
                + "_" + m_InfoTable.GetEmployee(GetRowIndex()).m_strNo + ".txt";
        QFile t_SalaryFile(t_strSalaryFileName);

        int ret = EDlg.exec();

        if(ret == AddEditDialog::Accepted)  //OK按钮被点击
        {
            CEmployee t_Employee;   //创建临时职员对象
            //从dialog中获取：
            t_Employee.m_strName = EDlg.GetName();
            t_Employee.m_nAge = EDlg.GetAge();
            t_Employee.m_strNo = EDlg.GetNo();
            t_Employee.m_Date = EDlg.GetDate();
            t_Employee.m_strPhone = EDlg.GetPhone();
            t_Employee.m_strAddress = EDlg.GetAddress();
            m_InfoTable.EditEmployee(GetRowIndex(), t_Employee);    //对选中的职员进行替换

            QString t_strRename = g_strLastFileName.left(g_strLastFileName.size() - 4)
                    + "_" + EDlg.GetNo() + ".txt";
            t_SalaryFile.rename(t_strRename);   //该职工对应工资文件重命名

            ShowEmployeeList(); //显示变更后的列表
        }
    }
    else    //若没有文件被打开，提示错误
    {
        QMessageBox::warning(this, tr("警告"), tr("请先新建或打开文件"));
        return;
    }
}

//点击“移除职工”：
void MainWindow::on_actionDelete_triggered()
{
    if(g_bFlagOpen) //判断是否有文件被打开，若有，弹出编辑窗口
    {
        if(g_nEmployeeNum == 0) //若当前文件中没有职工，提示错误
        {
            QMessageBox::warning(this, tr("警告"), tr("请先添加新职工"));
            return;
        }
        if(GetRowIndex() == -1) //没有选择职工
        {
            QMessageBox::warning(NULL, "警告", "请先选择一位职工");
            return;
        }
        if(g_bFlagSearch == 1)    //列表显示为查找窗口
        {
            QMessageBox::warning(NULL, "警告", "请在总列表中进行移除操作");
            return;
        }

        //弹出确认提示：
        QString t_strQuestion = "是否移除职工" +
                m_InfoTable.GetEmployee(GetRowIndex()).m_strName + "?";
        if(QMessageBox::question(NULL, "确认", t_strQuestion,
                                 QMessageBox::Yes |
                                 QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes)    //点击Yes
        {
            QString t_strSalaryFileName = g_strLastFileName.left(g_strLastFileName.size() - 4)
                    + "_" + m_InfoTable.GetEmployee(GetRowIndex()).m_strNo + ".txt";
            QFile t_SalaryFile(t_strSalaryFileName);
            t_SalaryFile.remove();  //删除该职工对应的工资文件
            m_InfoTable.RemoveEmployee(GetRowIndex());  //移除职工
            ShowEmployeeList(); //显示变更后的列表

            g_nEmployeeNum--;
        }
    }
    else    //若没有文件被打开，提示错误
    {
        QMessageBox::warning(this, tr("警告"), tr("请先新建或打开文件"));
        return;
    }
}

//点击“查找”：
void MainWindow::on_actionSearch_triggered()
{
    if(g_bFlagOpen) //判断是否有文件被打开，若有，弹出编辑窗口
    {
        if(g_nEmployeeNum == 0) //若当前文件中没有职工，提示错误
        {
            QMessageBox::warning(this, tr("警告"), tr("请先添加新职工"));
            return;
        }

        SelectDialog SlctDlg(this); //创建选择查找方式对话框
        int SlctRet = SlctDlg.exec();
        if(SlctRet == SelectDialog::Accepted)  //选择查找方式对话框的OK按钮被点击
        {
            SearchDialog ScDlg(this, SlctDlg.GetSelection(), g_nEmployeeNum);   //创建查找对话框
            int ScRet = ScDlg.exec();
            if(ScRet == SearchDialog::Accepted) //查找对话框的OK按钮被点击
            {
                QVector <int> index;    //用于储存符合条件的职工下标
                switch(SlctDlg.GetSelection())
                {
                case 0: //按序号查找（int），不区分精确/模糊查找
                    index.clear();  //清空
                    index.push_back(ScDlg.GetInt() - 1);    //记录下标（序号-1）
                    break;
                case 1: //按姓名查找（string）
                    index.clear();  //清空
                    //遍历所有职工
                    for(int i = 0; i < g_nEmployeeNum; i++)
                    {
                        if(ScDlg.GetSelection())    //模糊查找
                        {
                            if(m_InfoTable.GetEmployee(i).m_strName.contains(ScDlg.GetString()))
                                index.push_back(i); //若职工姓名与输入相等，记录下标
                        }
                        else    //精确查找
                        {
                            if(m_InfoTable.GetEmployee(i).m_strName == ScDlg.GetString())
                                index.push_back(i); //若职工姓名中包含输入的字符，记录下标
                        }
                    }
                    break;
                case 2: //按年龄查找（int），不区分精确/模糊查找
                    index.clear();  //清空
                    //遍历所有职工
                    for(int i = 0; i < g_nEmployeeNum; i++)
                        if(m_InfoTable.GetEmployee(i).m_nAge == ScDlg.GetInt())
                            index.push_back(i); //若职工年龄与输入相等，记录下标
                    break;
                case 3: //按工号查找（string）
                    index.clear();  //清空
                    //遍历所有职工
                    for(int i = 0; i < g_nEmployeeNum; i++)
                    {
                        if(ScDlg.GetSelection())    //模糊查找
                        {
                            if(m_InfoTable.GetEmployee(i).m_strNo.contains(ScDlg.GetString()))
                                index.push_back(i); //若职工工号与输入相等，记录下标
                        }
                        else    //精确查找
                        {
                            if(m_InfoTable.GetEmployee(i).m_strNo == ScDlg.GetString())
                                index.push_back(i); //若职工工号中包含输入的字符，记录下标
                        }
                    }
                    break;
                case 4: //按入职日期查找（date），不区分精确/模糊查找
                    index.clear();  //清空
                    //遍历所有职工
                    for(int i = 0; i < g_nEmployeeNum; i++)
                        if(m_InfoTable.GetEmployee(i).m_Date == ScDlg.GetDate())
                            index.push_back(i); //若职工入职日期与输入相等，记录下标
                    break;
                case 5: //按电话号码查找（string）
                    index.clear();  //清空
                    //遍历所有职工
                    for(int i = 0; i < g_nEmployeeNum; i++)
                    {
                        if(ScDlg.GetSelection())    //模糊查找
                        {
                            if(m_InfoTable.GetEmployee(i).m_strPhone.contains(ScDlg.GetString()))
                                index.push_back(i); //若职工电话号码与输入相等，记录下标
                        }
                        else    //精确查找
                        {
                            if(m_InfoTable.GetEmployee(i).m_strPhone == ScDlg.GetString())
                                index.push_back(i); //若职工电话号码中包含输入的字符，记录下标
                        }
                    }
                    break;
                case 6: //按住址查找（string）
                    index.clear();  //清空
                    //遍历所有职工
                    for(int i = 0; i < g_nEmployeeNum; i++)
                    {
                        if(ScDlg.GetSelection())    //模糊查找
                        {
                            if(m_InfoTable.GetEmployee(i).m_strAddress.contains(ScDlg.GetString()))
                                index.push_back(i); //若职工姓名与输入相等，记录下标
                        }
                        else    //精确查找
                        {
                            if(m_InfoTable.GetEmployee(i).m_strAddress == ScDlg.GetString())
                                index.push_back(i); //若职工姓名中包含输入的字符，记录下标
                        }
                    }
                    break;
                //不需要default
                }
                ShowEmployeeList(index);    //显示查找到的职员列表
                g_bFlagSearch = 1;
            }
        }
    }
    else            //若没有文件被打开，提示错误
    {
        QMessageBox::warning(this, tr("警告"), tr("请先新建或打开文件"));
        return;
    }
}

//点击“显示所有职工”：
void MainWindow::on_actionShowAll_triggered()
{
    if(g_bFlagOpen) //判断是否有文件被打开，若有，显示
    {
        ShowEmployeeList();
        g_bFlagSearch = 0;
    }
    else    //若没有文件被打开，提示错误
    {
        QMessageBox::warning(this, tr("警告"), tr("请先新建或打开文件"));
        return;
    }
}

//点击“查看职工工资”：
void MainWindow::on_actionSalary_triggered()
{
    if(g_bFlagOpen) //判断是否有文件被打开，若有，弹出编辑窗口
    {
        if(g_nEmployeeNum == 0) //若当前文件中没有职工，提示错误
        {
            QMessageBox::warning(this, tr("警告"), tr("请先添加新职工"));
            return;
        }
        if(GetRowIndex() == -1) //没有选择职工
        {
            QMessageBox::warning(NULL, "警告", "请先选择一位职工");
            return;
        }
        else
        {
            SalaryDialog SlryDlg(this, m_InfoTable.GetEmployee(GetRowIndex()).m_strName);   //创建职工工资信息对话框
            QString t_strSalaryFileName = g_strLastFileName.left(g_strLastFileName.size() - 4)
                    + "_" + m_InfoTable.GetEmployee(GetRowIndex()).m_strNo + ".txt";
            SlryDlg.m_strFileName = t_strSalaryFileName;    //记录文件名
            SlryDlg.m_InfoTable.ReadFromFile(t_strSalaryFileName);  //读取文件
            SlryDlg.ShowSalaryList();
            SlryDlg.exec();
        }
    }
    else    //若没有文件被打开，提示错误
    {
        QMessageBox::warning(this, tr("警告"), tr("请先新建或打开文件"));
        return;
    }
}
