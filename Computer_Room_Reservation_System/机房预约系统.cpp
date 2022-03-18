#define _CRT_SECURE_NO_WARNINGS 1

#include "identity.h"
#include "globalFile.h"
#include "student.h"
#include "teacher.h"
#include "manager.h"

using namespace std;

void teacherMenu(Identity*& manager)
{
	while (true)
	{
		manager->openMenu();
		int select = 0;
		Teacher* stu = (Teacher*)manager;
		cin >> select;
		switch (select)
		{
		case 1:
			cout << "查看所有预约" << endl;
			stu->showAllOrder();
			break;
		case 2:
			cout << "审核预约" << endl;
			stu->validOrder();
			break;
		default:
			delete manager;
			cout << "注销账号成功！" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

void studentMenu(Identity*& manager)
{
	while (true)
	{
		manager->openMenu();
		int select = 0;
		Student* stu = (Student*)manager;
		cin >> select;
		switch (select)
		{
		case 1:
			cout << "申请预约" << endl;
			stu->applyOrder();
			break;
		case 2:
			cout << "查看自身预约" << endl;
			stu->showMyOrder();
			break;
		case 3:
			cout << "查看所有预约" << endl;
			stu->showAllOrder();
			break;
		case 4:
			cout << "取消预约" << endl;
			stu->cancelOrder();
			break;
		default:
			delete manager;
			cout << "注销账号成功！" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}
void managerMenu(Identity*& manager)
{
	while (true)
	{
		manager->openMenu();
		int select = 0;
		Manager* man = (Manager*)manager;
		cin >> select;

		switch (select)
		{
		case 1:
			cout << "添加账号" << endl;
			man->addPerson();
			break;
		case 2:
			cout << "查看账号" << endl;
			man->showPerson();
			break;
		case 3:
			cout << "查看机房" << endl;
			man->showComputer();
			break;
		case 4:
			cout << "清空预约信息" << endl;
			man->clearFile();
			break;
		default:
			delete manager;
			cout << "注销账号成功！" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

void LoginIn(string filename, int type)
{
	Identity* person = NULL;

	ifstream ifs;
	ifs.open(filename, ios::in);

	if (!ifs.is_open())
	{
		cout << "文件不存在或者为空" << endl;
		ifs.close();
		return;
	}

	int id = 0;
	string username;
	string password;

	if (type == 1)
	{
		cout << "请输入你的学号：";
		cin >> id;
	}
	else if (type == 2)
	{
		cout << "请输入你的职工号：";
		cin >> id;
	}
	
	cout << "请输入用户名：";
	cin >> username;
	cout << "请输入密码：";
	cin >> password;

	if (type == 1)
	{
		int fId;
		string fUsername;
		string fPassword;
		while (ifs >> fId && ifs >> fUsername && ifs >> fPassword)
		{
			if (fId == id && fUsername == username && fPassword == password)
			{
				cout << "学生验证成功" << endl;
				system("pause");
				system("cls");
				person = new Student(id, username, password);
				studentMenu(person);
				return;
			}
		}
	}
	else if (type == 2)
	{
		int fId;
		string fUsername;
		string fPassword;
		while (ifs >> fId && ifs >> fUsername && ifs >> fPassword)
		{
			if (fId == id && fUsername == username && fPassword == password)
			{
				cout << "老师验证成功" << endl;
				system("pause");
				system("cls");
				person = new Teacher(id, username, password);
				teacherMenu(person);
				return;
			}
		}
	}
	else if (type == 3)
	{
		string fUsername;
		string fPassword;
		while (ifs >> fUsername && ifs >> fPassword)
		{
			if (fUsername == username && fPassword == password)
			{
				cout << "管理员验证成功" << endl;
				system("pause");
				system("cls");
				person = new Manager(username, password);
				managerMenu(person);
				return;
			}
		}
	}

	cout << "验证登录失败！" << endl;
	system("pause");
	system("cls");
	return;
}

int main()
{
	int select = 0;
	while (true)
	{
		cout << "----------------------欢迎来到机房预约系统----------------------" << endl;
		cout << "请输入你的身份" << endl;
		cout << "\t\t----------------------------" << endl;
		cout << "\t\t|                          |" << endl;
		cout << "\t\t|        1.学生代表        |" << endl;
		cout << "\t\t|                          |" << endl;
		cout << "\t\t|        2.教    师        |" << endl;
		cout << "\t\t|                          |" << endl;
		cout << "\t\t|        3.管 理 员        |" << endl;
		cout << "\t\t|                          |" << endl;
		cout << "\t\t|        0.退    出        |" << endl;
		cout << "\t\t|                          |" << endl;
		cout << "\t\t----------------------------" << endl;
		cout << "请确认你的选择：" << endl;
		cin >> select;
		switch (select)
		{
		case 1:
			LoginIn(STUDENT_FILE, 1);
			break;
		case 2:
			LoginIn(TEACHER_FILE, 2);
			break;
		case 3:
			LoginIn(ADMIN_FILE, 3);
			break;
		case 0:
			cout << "欢迎下次使用！" << endl;
			system("pause");
			return 0;
			break;
		default:
			cout << "输入有误，请重新选择" << endl;
			system("pause");
			system("cls");
			break;
		}
	}

	system("pause");
	return 0;
}