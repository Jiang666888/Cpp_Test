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
			cout << "�鿴����ԤԼ" << endl;
			stu->showAllOrder();
			break;
		case 2:
			cout << "���ԤԼ" << endl;
			stu->validOrder();
			break;
		default:
			delete manager;
			cout << "ע���˺ųɹ���" << endl;
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
			cout << "����ԤԼ" << endl;
			stu->applyOrder();
			break;
		case 2:
			cout << "�鿴����ԤԼ" << endl;
			stu->showMyOrder();
			break;
		case 3:
			cout << "�鿴����ԤԼ" << endl;
			stu->showAllOrder();
			break;
		case 4:
			cout << "ȡ��ԤԼ" << endl;
			stu->cancelOrder();
			break;
		default:
			delete manager;
			cout << "ע���˺ųɹ���" << endl;
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
			cout << "����˺�" << endl;
			man->addPerson();
			break;
		case 2:
			cout << "�鿴�˺�" << endl;
			man->showPerson();
			break;
		case 3:
			cout << "�鿴����" << endl;
			man->showComputer();
			break;
		case 4:
			cout << "���ԤԼ��Ϣ" << endl;
			man->clearFile();
			break;
		default:
			delete manager;
			cout << "ע���˺ųɹ���" << endl;
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
		cout << "�ļ������ڻ���Ϊ��" << endl;
		ifs.close();
		return;
	}

	int id = 0;
	string username;
	string password;

	if (type == 1)
	{
		cout << "���������ѧ�ţ�";
		cin >> id;
	}
	else if (type == 2)
	{
		cout << "���������ְ���ţ�";
		cin >> id;
	}
	
	cout << "�������û�����";
	cin >> username;
	cout << "���������룺";
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
				cout << "ѧ����֤�ɹ�" << endl;
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
				cout << "��ʦ��֤�ɹ�" << endl;
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
				cout << "����Ա��֤�ɹ�" << endl;
				system("pause");
				system("cls");
				person = new Manager(username, password);
				managerMenu(person);
				return;
			}
		}
	}

	cout << "��֤��¼ʧ�ܣ�" << endl;
	system("pause");
	system("cls");
	return;
}

int main()
{
	int select = 0;
	while (true)
	{
		cout << "----------------------��ӭ��������ԤԼϵͳ----------------------" << endl;
		cout << "������������" << endl;
		cout << "\t\t----------------------------" << endl;
		cout << "\t\t|                          |" << endl;
		cout << "\t\t|        1.ѧ������        |" << endl;
		cout << "\t\t|                          |" << endl;
		cout << "\t\t|        2.��    ʦ        |" << endl;
		cout << "\t\t|                          |" << endl;
		cout << "\t\t|        3.�� �� Ա        |" << endl;
		cout << "\t\t|                          |" << endl;
		cout << "\t\t|        0.��    ��        |" << endl;
		cout << "\t\t|                          |" << endl;
		cout << "\t\t----------------------------" << endl;
		cout << "��ȷ�����ѡ��" << endl;
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
			cout << "��ӭ�´�ʹ�ã�" << endl;
			system("pause");
			return 0;
			break;
		default:
			cout << "��������������ѡ��" << endl;
			system("pause");
			system("cls");
			break;
		}
	}

	system("pause");
	return 0;
}