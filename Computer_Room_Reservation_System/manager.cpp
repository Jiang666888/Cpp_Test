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
	//cout << "����������Ϊ��" << vCom.size() << endl;
}

void Manager::openMenu()
{
	cout << "��ӭ����Ա < " << this->m_Username << " > ��¼��" << endl;
	cout << "\t\t----------------------------" << endl;
	cout << "\t\t|                          |" << endl;
	cout << "\t\t|        1.����˺�        |" << endl;
	cout << "\t\t|                          |" << endl;
	cout << "\t\t|        2.�鿴�˺�        |" << endl;
	cout << "\t\t|                          |" << endl;
	cout << "\t\t|        3.�鿴����        |" << endl;
	cout << "\t\t|                          |" << endl;
	cout << "\t\t|        4.���ԤԼ        |" << endl;
	cout << "\t\t|                          |" << endl;
	cout << "\t\t|        0.ע����¼        |" << endl;
	cout << "\t\t|                          |" << endl;
	cout << "\t\t----------------------------" << endl;
	cout << "��ѡ����Ĳ���" << endl;
}

void Manager::addPerson()
{
	cout << "��������ӵ�����" << endl;
	cout << "1.���ѧ��" << endl;
	cout << "2.�����ʦ" << endl;

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
			tip = "������ѧ�ţ�";
			errorTip = "ѧ�������ظ������������룡";
			break;
		}
		else if (select == 2)
		{
			Filename = TEACHER_FILE;
			tip = "������ְ����ţ�";
			errorTip = "ְ����������ظ������������룡";
			break;
		}
		cout << "������������������!" << endl;
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
	cout << "�������û�����" << endl;
	cin >> fUsername;
	cout << "���������룺" << endl;
	cin >> fPassword;

	ofs << fId << " " << fUsername << " " << fPassword << " "  << endl;
	cout << "��ӳɹ���" << endl;
	this->initVector();

	system("pause");
	system("cls");
	ofs.close();
}

void printStudent(Student& s)
{
	cout << "ѧ�ţ�" << s.m_Id << " ������" << s.m_Username << " ���룺" << s.m_Password << endl;
}

void printTeacher(Teacher& t)
{
	cout << "ְ����ţ�" << t.m_EmpId << " ������" << t.m_Username << " ���룺" << t.m_Password << endl;
}
void Manager::showPerson()
{
	cout << "��ѡ��鿴������" << endl;
	cout << "1.ѧ������" << endl;
	cout << "2.��ʦ����" << endl;
	int select = 0;
	while (true)
	{
		cin >> select;
		if (select == 1)
		{
			cout << "����ѧ����Ϣ����" << endl;
			for_each(this->vStu.begin(), this->vStu.end(), printStudent);
			break;
		}
		else if (select == 2)
		{
			cout << "������ʦ��Ϣ����" << endl;
			for_each(this->vTea.begin(), this->vTea.end(), printTeacher);
			break;
		}
		cout << "�����������������룺" << endl;
	}
	system("pause");
	system("cls");
}

void Manager::showComputer()
{
	for (vector<ComputerRoom>::iterator it = this->vCom.begin();it != this->vCom.end();it++)
	{
		cout << "������ţ�" << it->m_ComId << " ����������" << it->m_Maxnum << endl;
	}
	system("pause");
	system("cls");
}

void Manager::clearFile()
{
	ofstream ofs;
	ofs.open(ORDER_FILE, ios::trunc);

	cout << "��ճɹ���" << endl;
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
		cout << "�ļ���ȡʧ��" << endl;
		return;
	}
	Student s;
	while (ifs >> s.m_Id && ifs >> s.m_Username && ifs >> s.m_Password)
	{
		vStu.push_back(s);
	}
	//cout << "��ǰѧ������Ϊ" << vStu.size() << endl;
	ifs.close();

	ifs.open(TEACHER_FILE, ios::in);
	Teacher t;
	while (ifs >> t.m_EmpId && ifs >> t.m_Username && ifs >> t.m_Password)
	{
		vTea.push_back(t);
	}
	//cout << "��ǰ��ʦ����Ϊ" << vTea.size() << endl;
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

