#define _CRT_SECURE_NO_WARNINGS 1

#include "manager.h"

Manager::Manager()
{
	
}

Manager::Manager(string username, string password)
{
	this->m_Username = username;
	this->m_Password = password;

	this->initVector();

	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	ComputerRoom com;
	while (ifs >> com.m_ComId && ifs >> com.m_Maxnum)
	{
		vCom.push_back(com);
	}
	ifs.close();
	//cout << "机房的数量为：" << vCom.size() << endl;
}

void Manager::openMenu()
{
	cout << "欢迎管理员 < " << this->m_Username << " > 登录！" << endl;
	cout << "\t\t----------------------------" << endl;
	cout << "\t\t|                          |" << endl;
	cout << "\t\t|        1.添加账号        |" << endl;
	cout << "\t\t|                          |" << endl;
	cout << "\t\t|        2.查看账号        |" << endl;
	cout << "\t\t|                          |" << endl;
	cout << "\t\t|        3.查看机房        |" << endl;
	cout << "\t\t|                          |" << endl;
	cout << "\t\t|        4.清空预约        |" << endl;
	cout << "\t\t|                          |" << endl;
	cout << "\t\t|        0.注销登录        |" << endl;
	cout << "\t\t|                          |" << endl;
	cout << "\t\t----------------------------" << endl;
	cout << "请选择你的操作" << endl;
}

void Manager::addPerson()
{
	cout << "请输入添加的类型" << endl;
	cout << "1.添加学生" << endl;
	cout << "2.添加老师" << endl;

	string Filename;
	string tip;
	string errorTip;
	ofstream ofs;

	int select = 0;
	cin >> select;

	while (true)
	{
		if (select == 1)
		{
			Filename = STUDENT_FILE;
			tip = "请输入学号：";
			errorTip = "学号输入重复，请重新输入！";
			break;
		}
		else if (select == 2)
		{
			Filename = TEACHER_FILE;
			tip = "请输入职工编号：";
			errorTip = "职工编号输入重复，请重新输入！";
			break;
		}
		cout << "输入有误，请重新输入!" << endl;
	}
	
	ofs.open(Filename, ios::out | ios::app);
	int fId;
	string fUsername;
	string fPassword;

	cout << tip << endl;
	while (true)
	{
		cin >> fId;
		bool ret = this->checkRepeat(fId, select);
		if (ret)
		{
			cout << errorTip << endl;
		}
		else
		{
			break;
		}
	}
	cout << "请输入用户名：" << endl;
	cin >> fUsername;
	cout << "请输入密码：" << endl;
	cin >> fPassword;

	ofs << fId << " " << fUsername << " " << fPassword << " "  << endl;
	cout << "添加成功！" << endl;
	this->initVector();

	system("pause");
	system("cls");
	ofs.close();
}

void printStudent(Student& s)
{
	cout << "学号：" << s.m_Id << " 姓名：" << s.m_Username << " 密码：" << s.m_Password << endl;
}

void printTeacher(Teacher& t)
{
	cout << "职工编号：" << t.m_EmpId << " 姓名：" << t.m_Username << " 密码：" << t.m_Password << endl;
}
void Manager::showPerson()
{
	cout << "请选择查看的内容" << endl;
	cout << "1.学生内容" << endl;
	cout << "2.教师内容" << endl;
	int select = 0;
	while (true)
	{
		cin >> select;
		if (select == 1)
		{
			cout << "所有学生信息如下" << endl;
			for_each(this->vStu.begin(), this->vStu.end(), printStudent);
			break;
		}
		else if (select == 2)
		{
			cout << "所有老师信息如下" << endl;
			for_each(this->vTea.begin(), this->vTea.end(), printTeacher);
			break;
		}
		cout << "输入有误，请重新输入：" << endl;
	}
	system("pause");
	system("cls");
}

void Manager::showComputer()
{
	for (vector<ComputerRoom>::iterator it = this->vCom.begin();it != this->vCom.end();it++)
	{
		cout << "机房编号：" << it->m_ComId << " 机房容量：" << it->m_Maxnum << endl;
	}
	system("pause");
	system("cls");
}

void Manager::clearFile()
{
	ofstream ofs;
	ofs.open(ORDER_FILE, ios::trunc);

	cout << "清空成功！" << endl;
	system("pause");
	system("cls");
}

void Manager::initVector()
{
	this->vStu.clear();
	this->vTea.clear();
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件读取失败" << endl;
		return;
	}
	Student s;
	while (ifs >> s.m_Id && ifs >> s.m_Username && ifs >> s.m_Password)
	{
		vStu.push_back(s);
	}
	//cout << "当前学生个数为" << vStu.size() << endl;
	ifs.close();

	ifs.open(TEACHER_FILE, ios::in);
	Teacher t;
	while (ifs >> t.m_EmpId && ifs >> t.m_Username && ifs >> t.m_Password)
	{
		vTea.push_back(t);
	}
	//cout << "当前老师个数为" << vTea.size() << endl;
}

bool Manager::checkRepeat(int id, int type)
{
	if (type == 1)
	{
		for (vector<Student>::iterator it = this->vStu.begin();it != this->vStu.end();it++)
		{
			if (id == it->m_Id)
			{
				return true;
			}
		}
	}
	else if (type == 2)
	{
		for (vector<Teacher>::iterator it = this->vTea.begin();it != this->vTea.end();it++)
		{
			if (id == it->m_EmpId)
			{
				return true;
			}
		}
	}
	return false;
}

