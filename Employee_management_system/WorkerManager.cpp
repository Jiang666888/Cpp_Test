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
		//cout << "文件不存在" << endl;
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
		//cout << "文件为空" << endl;
		this->m_EmpNum = 0;
		this->m_EmptyArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	int num = this->get_EmpNum();
	this->m_EmpNum = num;
	//cout << "当前职工人数为：" << this->m_EmpNum << endl;
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
	cout << "******   欢迎使用职工管理系统   ******" << endl;
	cout << "******      0.退出管理程序      ******" << endl;
	cout << "******      1.增加职工信息      ******" << endl;
	cout << "******      2.显示职工信息      ******" << endl;
	cout << "******      3.删除离职职工      ******" << endl;
	cout << "******      4.修改职工信息      ******" << endl;
	cout << "******      5.查找职工信息      ******" << endl;
	cout << "******      6.按照编号排序      ******" << endl;
	cout << "******      7.清空所有文档      ******" << endl;
	cout << "*************************************" << endl;
	cout << endl;
}
void WorkerManager::exitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}
void WorkerManager::Add_Emp()
{
	cout << "请输入添加职工数量：";
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
			cout << "请输入第" << i + 1 << "个新职工编号：";
			cin >> id;
			cout << "请输入第" << i + 1 << "个新职工姓名：";
			cin >> name;
			cout << "请输入该职工岗位编号：" << endl;
			cout << "1、员工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
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
		cout << "成功添加" << addNum << "人" << endl;
		this->save();
	}
	else
	{
		cout << "输入数据有误！" << endl;
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
		cout << "文件不存在或者为空" << endl;
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
		cout << "文件不存在或为空" << endl;
	}
	else
	{
		int id;
		cout << "请输入要删除的职工编号：";
		cin >> id;
		int index = this->IsExist(id);
		if (index == -1)
		{
			cout << "未查询到要删除的数据" << endl;
		}
		else
		{
			for (int i = index;i < this->m_EmpNum-1;i++)
			{
				this->m_EmptyArray[i] = this->m_EmptyArray[i + 1];
			}
			this->m_EmpNum--;
			this->save();
			cout << "数据删除成功！" << endl;
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
		cout << "文件不存在或为空" << endl;
	}
	else
	{
		cout << "请输入要删除的员工编号：";
		int index;
		cin >> index;
		int ret = this->IsExist(index);
		if (ret != -1)
		{
			delete this->m_EmptyArray[ret];
			int id;
			string name;
			int dSelect;
			cout << "请输入新职工编号：";
			cin >> id;
			cout << "请输入新职工姓名：";
			cin >> name;
			cout << "请输入该职工岗位编号：" << endl;
			cout << "1、员工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
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
			cout << "修改成功" << endl;
			this->save();
		}
		else
		{
			cout << "查无此人" << endl;
		}
	}
	system("pause");
	system("cls");
}
void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或为空" << endl;
	}
	else
	{
		int select = 0;
		cout << "请输入查找的方式" << endl;
		cout << "1、编号" << endl;
		cout << "2、姓名" << endl;
		cin >> select;
		if (select == 1)
		{
			int id;
			cout << "请输入查询数据的编号：";
			cin >> id;
			int ret = this->IsExist(id);
			if (ret == -1)
			{
				cout << "查无此人" << endl;
			}
			else
			{
				this->m_EmptyArray[ret]->showInfo();
			}
		}
		else if (select == 2)
		{
			string name;
			cout << "请输入查询数据的姓名：";
			cin >> name;
			bool flag = false;
			int i = 0;
			for (i = 0;i < this->m_EmpNum;i++)
			{
				if (this->m_EmptyArray[i]->m_Name == name)
				{
					cout << "第" << i + 1 << "个职工的信息如下" << endl;
					flag = true;
					this->m_EmptyArray[i]->showInfo();
				}
			}
			if(flag==false)
			{
				cout << "查无此人" << endl;
			}
		}
		else
		{
			cout << "请输入正确的查询方式" << endl;
		}
	}
	system("pause");
	system("cls");
}
void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或为空" << endl;
	}
	else
	{
		cout << "请选择排序方式" << endl;
		cout << "1、按职工号升序" << endl;
		cout << "2、按职工号降序" << endl;
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
			cout << "排序成功！" << endl;
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
			cout << "排序成功！" << endl;
		}
		else
		{
			cout << "输入有误" << endl;
		}
		this->save();
	}
	system("pause");
	system("cls");
}
void WorkerManager::Clean_File()
{
	cout << "请确认是否清空数据" << endl;
	cout << "1、确认" << endl;
	cout << "2、取消" << endl;
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
		cout << "清空成功！" << endl;
	}
	else if (select == 2)
	{
		cout << "取消成功" << endl;
	}
	else
	{
		cout << "输入有误" << endl;
	}
	system("pause");
	system("cls");
}