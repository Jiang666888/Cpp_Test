#define _CRT_SECURE_NO_WARNINGS 1

#include "student.h"

Student::Student()
{

}

Student::Student(int id, string username, string password)
{
	this->m_Id = id;
	this->m_Username = username;
	this->m_Password = password;

	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	ComputerRoom com;
	while (ifs >> com.m_ComId && ifs >> com.m_Maxnum)
	{
		vCom.push_back(com);
	}
	ifs.close();
}

void Student::openMenu()
{
	cout << "��ӭѧ�� < " << this->m_Username << " > ��¼��" << endl;
	cout << "\t\t----------------------------" << endl;
	cout << "\t\t|                          |" << endl;
	cout << "\t\t|        1.����ԤԼ        |" << endl;
	cout << "\t\t|                          |" << endl;
	cout << "\t\t|        2.�鿴�ҵ�ԤԼ    |" << endl;
	cout << "\t\t|                          |" << endl;
	cout << "\t\t|        3.�鿴����ԤԼ    |" << endl;
	cout << "\t\t|                          |" << endl;
	cout << "\t\t|        4.ȡ��ԤԼ        |" << endl;
	cout << "\t\t|                          |" << endl;
	cout << "\t\t|        0.ע����¼        |" << endl;
	cout << "\t\t|                          |" << endl;
	cout << "\t\t----------------------------" << endl;
	cout << "��ѡ����Ĳ���" << endl;
}

void Student::applyOrder()
{
	int date = 0;
	int interval = 0;
	int room = 0;

	cout << "����ԤԼʱ��Ϊ��һ������" << endl;
	cout << "��ѡ��ԤԼʱ��" << endl;
	cout << "1.��һ" << endl;
	cout << "2.�ܶ�" << endl;
	cout << "3.����" << endl;
	cout << "4.����" << endl;
	cout << "5.����" << endl;
	while (true)
	{
		cin >> date;
		if (date >= 1 && date <= 5)
		{
			break;
		}
		cout << "�����������������룺" << endl;
	}

	cout << "������ԤԼ��ʱ���" << endl;
	cout << "1.����" << endl;
	cout << "2.����" << endl;
	while (true)
	{
		cin >> interval;
		if (interval == 1 || interval == 2)
		{
			break;
		}
		cout << "�����������������룺" << endl;
	}

	cout << "��ѡ�����" << endl;
	for (unsigned int i = 0;i < vCom.size();i++)
	{
		cout << vCom[i].m_ComId << "�Ż���������Ϊ" << vCom[i].m_Maxnum << endl;
	}
	while (true)
	{
		cin >> room;
		if (room == 1 || room == 2 || room == 3)
		{
			break;
		}
		cout << "�����������������룺" << endl;
	}

	cout << "ԤԼ�ɹ��������" << endl;

	ofstream ofs;
	ofs.open(ORDER_FILE, ios::app);
	ofs << "date:" << date << " ";
	ofs << "interval:" << interval << " ";
	ofs << "stuId:" << this->m_Id << " ";
	ofs << "stuName:" << this->m_Username << " ";
	ofs << "roomId:" << room << " ";
	ofs << "status:" << 1 << " ";

	system("pause");
	system("cls");
}

void Student::showMyOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "��ԤԼ��¼��" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0;i < of.m_Size;i++)
	{
		if (this->m_Id == atoi(of.m_orderData[i]["stuId"].c_str()))
		{
			cout << "ԤԼ���ڣ���" << of.m_orderData[i]["date"];
			cout << " ʱ��Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����");
			cout << " �����ţ�" << of.m_orderData[i]["roomId"];
			string status = " ״̬��";
			if (of.m_orderData[i]["status"] == "1")
			{
				status += "�����";
			}
			else if (of.m_orderData[i]["status"] == "2")
			{
				status += "ԤԼ�ɹ�";
			}
			else if (of.m_orderData[i]["status"] == "3")
			{
				status += "ԤԼʧ�ܣ����δͨ��";
			}
			else
			{
				status += "ԤԼ��ȡ��";
			}
			cout << status << endl;
		}
	}
	system("pause");
	system("cls");
}

void Student::showAllOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "��ԤԼ��¼��" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0;i < of.m_Size;i++)
	{
		cout << i + 1 << " ";
		cout << "ԤԼ���ڣ���" << of.m_orderData[i]["date"];
		cout << " ʱ��Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����");
		cout << " ѧ�ţ�" << of.m_orderData[i]["stuId"];
		cout << " ������" << of.m_orderData[i]["stuName"];
		cout << " �����ţ�" << of.m_orderData[i]["roomId"];
		string status = " ״̬��";
		if (of.m_orderData[i]["status"] == "1")
		{
			status += "�����";
		}
		else if (of.m_orderData[i]["status"] == "2")
		{
			status += "ԤԼ�ɹ�";
		}
		else if (of.m_orderData[i]["status"] == "3")
		{
			status += "ԤԼʧ�ܣ����δͨ��";
		}
		else
		{
			status += "ԤԼ��ȡ��";
		}
		cout << status << endl;
	}
	system("pause");
	system("cls");
}

void Student::cancelOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "��ԤԼ��¼��" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "����л�ԤԼ�ɹ��ļ�¼����ȡ������������Ҫȡ���ļ�¼" << endl;

	int index = 1;
	vector<int> v;
	for (int i = 0;i < of.m_Size;i++)
	{
		if (this->m_Id == atoi(of.m_orderData[i]["stuId"].c_str()))
		{
			if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2")
			{
				v.push_back(i);
				cout << i + 1 << "��";
				cout << " ԤԼ���ڣ���" << of.m_orderData[i]["date"];
				cout << " ʱ��Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����");
				cout << " �����ţ�" << of.m_orderData[i]["roomId"];
				string status = " ״̬��";
				if (of.m_orderData[i]["status"] == "1")
				{
					status += "�����";
				}
				else if (of.m_orderData[i]["status"] == "2")
				{
					status += "ԤԼ�ɹ�";
				}
				cout << status << endl;
			}
		}
	}

	cout << "������ȡ���ļ�¼��0������" << endl;
	int select = 0;
	while (true)
	{
		cin >> select;
		if (select >= 0 && select <= v.size())
		{
			if (select == 0)
			{
				break;
			}
			else
			{
				of.m_orderData[v[select - 1]]["status"] = "0";
				of.uploadOrder();
				cout << "��ȡ��ԤԼ" << endl;
				break;
			}
		}
		cout << "��������ȷ����:" << endl;
	}
	system("pause");
	system("cls");
}