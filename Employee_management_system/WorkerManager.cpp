#define _CRT_SECURE_NO_WARNINGS 1

#include "WorkerManager.h"
#include "Employee.h"
#include "Manager.h"
#include "Boss.h"

WorkerManager::WorkerManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open())
	{
		//cout << "�ļ�������" << endl;
		this->m_EmpNum = 0;
		this->m_EmptyArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "�ļ�Ϊ��" << endl;
		this->m_EmpNum = 0;
		this->m_EmptyArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	int num = this->get_EmpNum();
	this->m_EmpNum = num;
	//cout << "��ǰְ������Ϊ��" << this->m_EmpNum << endl;
	this->m_EmptyArray = new Worker * [this->m_EmpNum];
	this->init_Emp();
}
WorkerManager::~WorkerManager()
{
	if (this->m_EmptyArray != NULL)
	{
		for (int i = 0;i < this->m_EmpNum;i++)
		{
			if (this->m_EmptyArray[i] != NULL)
			{
				delete this->m_EmptyArray[i];
			}	
		}
		delete[] this->m_EmptyArray;
		this->m_EmptyArray = NULL;
	}
}

void WorkerManager::Show_Menu()
{
	cout << "*************************************" << endl;
	cout << "******   ��ӭʹ��ְ������ϵͳ   ******" << endl;
	cout << "******      0.�˳��������      ******" << endl;
	cout << "******      1.����ְ����Ϣ      ******" << endl;
	cout << "******      2.��ʾְ����Ϣ      ******" << endl;
	cout << "******      3.ɾ����ְְ��      ******" << endl;
	cout << "******      4.�޸�ְ����Ϣ      ******" << endl;
	cout << "******      5.����ְ����Ϣ      ******" << endl;
	cout << "******      6.���ձ������      ******" << endl;
	cout << "******      7.��������ĵ�      ******" << endl;
	cout << "*************************************" << endl;
	cout << endl;
}
void WorkerManager::exitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}
void WorkerManager::Add_Emp()
{
	cout << "���������ְ��������";
	int addNum = 0;
	cin >> addNum;
	if (addNum > 0)
	{
		int newSize = this->m_EmpNum + addNum;
		Worker** newSpace = new Worker * [newSize];
		if (this->m_EmptyArray != NULL)
		{
			for (int i = 0;i < this->m_EmpNum;i++)
			{
				newSpace[i] = this->m_EmptyArray[i];
			}
		}
		for (int i = 0;i < addNum;i++)
		{
			int id;
			string name;
			int dSelect;
			cout << "�������" << i + 1 << "����ְ����ţ�";
			cin >> id;
			cout << "�������" << i + 1 << "����ְ��������";
			cin >> name;
			cout << "�������ְ����λ��ţ�" << endl;
			cout << "1��Ա��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
			cin >> dSelect;
			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, dSelect);
				break;
			case 2:
				worker = new Manager(id, name, dSelect);
				break;
			case 3:
				worker = new Boss(id, name, dSelect);
				break;
			default:
				break;
			}
			newSpace[this->m_EmpNum + i] = worker;
		}
		delete[] this->m_EmptyArray;
		this->m_EmptyArray = newSpace;
		this->m_EmpNum = newSize;
		this->m_FileIsEmpty = false;
		cout << "�ɹ����" << addNum << "��" << endl;
		this->save();
	}
	else
	{
		cout << "������������" << endl;
	}
	system("pause");
	system("cls");
}

void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	for (int i = 0;i < this->m_EmpNum;i++)
	{
		ofs << this->m_EmptyArray[i]->m_ID << " "
			<< this->m_EmptyArray[i]->m_Name << " "
			<< this->m_EmptyArray[i]->m_DeptId << " " << endl;
	}
	ofs.close();
}
int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int dId;
	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		num++;
	}
	return num;
}

void WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int index = 0;
	int id;
	string name;
	int dId;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker* worker = NULL;
		if (dId == 1)
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2)
		{
			worker = new Manager(id, name, dId);
		}
		else if (dId == 3)
		{
			worker = new Boss(id, name, dId);
		}
		this->m_EmptyArray[index] = worker;
		index++;
	}
	ifs.close();
}

void WorkerManager::show_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ���Ϊ��" << endl;
	}
	else
	{
		for (int i = 0;i < this->m_EmpNum;i++)
		{
			this->m_EmptyArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ�Ϊ��" << endl;
	}
	else
	{
		int id;
		cout << "������Ҫɾ����ְ����ţ�";
		cin >> id;
		int index = this->IsExist(id);
		if (index == -1)
		{
			cout << "δ��ѯ��Ҫɾ��������" << endl;
		}
		else
		{
			for (int i = index;i < this->m_EmpNum-1;i++)
			{
				this->m_EmptyArray[i] = this->m_EmptyArray[i + 1];
			}
			this->m_EmpNum--;
			this->save();
			cout << "����ɾ���ɹ���" << endl;
		}
	}
	system("pause");
	system("cls");
}
int WorkerManager::IsExist(int id)
{
	for (int i = 0;i < this->m_EmpNum;i++)
	{
		if (this->m_EmptyArray[i]->m_ID == id)
		{
			return i;
		}
	}
	return -1;
}
void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ�Ϊ��" << endl;
	}
	else
	{
		cout << "������Ҫɾ����Ա����ţ�";
		int index;
		cin >> index;
		int ret = this->IsExist(index);
		if (ret != -1)
		{
			delete this->m_EmptyArray[ret];
			int id;
			string name;
			int dSelect;
			cout << "��������ְ����ţ�";
			cin >> id;
			cout << "��������ְ��������";
			cin >> name;
			cout << "�������ְ����λ��ţ�" << endl;
			cout << "1��Ա��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
			cin >> dSelect;
			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, dSelect);
				break;
			case 2:
				worker = new Manager(id, name, dSelect);
				break;
			case 3:
				worker = new Boss(id, name, dSelect);
				break;
			default:
				break;
			}
			this->m_EmptyArray[ret] = worker;
			cout << "�޸ĳɹ�" << endl;
			this->save();
		}
		else
		{
			cout << "���޴���" << endl;
		}
	}
	system("pause");
	system("cls");
}
void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ�Ϊ��" << endl;
	}
	else
	{
		int select = 0;
		cout << "��������ҵķ�ʽ" << endl;
		cout << "1�����" << endl;
		cout << "2������" << endl;
		cin >> select;
		if (select == 1)
		{
			int id;
			cout << "�������ѯ���ݵı�ţ�";
			cin >> id;
			int ret = this->IsExist(id);
			if (ret == -1)
			{
				cout << "���޴���" << endl;
			}
			else
			{
				this->m_EmptyArray[ret]->showInfo();
			}
		}
		else if (select == 2)
		{
			string name;
			cout << "�������ѯ���ݵ�������";
			cin >> name;
			bool flag = false;
			int i = 0;
			for (i = 0;i < this->m_EmpNum;i++)
			{
				if (this->m_EmptyArray[i]->m_Name == name)
				{
					cout << "��" << i + 1 << "��ְ������Ϣ����" << endl;
					flag = true;
					this->m_EmptyArray[i]->showInfo();
				}
			}
			if(flag==false)
			{
				cout << "���޴���" << endl;
			}
		}
		else
		{
			cout << "��������ȷ�Ĳ�ѯ��ʽ" << endl;
		}
	}
	system("pause");
	system("cls");
}
void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ�Ϊ��" << endl;
	}
	else
	{
		cout << "��ѡ������ʽ" << endl;
		cout << "1����ְ��������" << endl;
		cout << "2����ְ���Ž���" << endl;
		int select = 0;
		cin >> select;
		if (select == 1)
		{
			for (int i = 0;i < this->m_EmpNum - 1;i++)
			{
				for (int j = 0;j < this->m_EmpNum - 1 - i;j++)
				{
					if (this->m_EmptyArray[j]->m_ID > this->m_EmptyArray[j+1]->m_ID)
					{
						Worker* temp = this->m_EmptyArray[j+1];
						this->m_EmptyArray[j+1] = this->m_EmptyArray[j];
						this->m_EmptyArray[j] = temp;
					}
				}
			}
			cout << "����ɹ���" << endl;
		}
		else if(select==2)
		{
			for (int i = 0;i < this->m_EmpNum - 1;i++)
			{
				for (int j = 0;j < this->m_EmpNum - 1 - i;j++)
				{
					if (this->m_EmptyArray[j]->m_ID < this->m_EmptyArray[j + 1]->m_ID)
					{
						Worker* temp = this->m_EmptyArray[j + 1];
						this->m_EmptyArray[j+1] = this->m_EmptyArray[j];
						this->m_EmptyArray[j] = temp;
					}
				}
			}
			cout << "����ɹ���" << endl;
		}
		else
		{
			cout << "��������" << endl;
		}
		this->save();
	}
	system("pause");
	system("cls");
}
void WorkerManager::Clean_File()
{
	cout << "��ȷ���Ƿ��������" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2��ȡ��" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();
		if (this->m_EmptyArray != NULL)
		{
			for (int i = 0;i < this->m_EmpNum;i++)
			{
				if (this->m_EmptyArray[i] != NULL)
				{
					delete this->m_EmptyArray[i];
				}
			}
			this->m_EmpNum = 0;
			delete[] this->m_EmptyArray;
			this->m_EmptyArray = NULL;
			this->m_FileIsEmpty = true;
		}
		cout << "��ճɹ���" << endl;
	}
	else if (select == 2)
	{
		cout << "ȡ���ɹ�" << endl;
	}
	else
	{
		cout << "��������" << endl;
	}
	system("pause");
	system("cls");
}