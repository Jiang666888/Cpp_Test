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
	cout << "欢迎学生 < " << this->m_Username << " > 登录！" << endl;
	cout << "\t\t----------------------------" << endl;
	cout << "\t\t|                          |" << endl;
	cout << "\t\t|        1.申请预约        |" << endl;
	cout << "\t\t|                          |" << endl;
	cout << "\t\t|        2.查看我的预约    |" << endl;
	cout << "\t\t|                          |" << endl;
	cout << "\t\t|        3.查看所有预约    |" << endl;
	cout << "\t\t|                          |" << endl;
	cout << "\t\t|        4.取消预约        |" << endl;
	cout << "\t\t|                          |" << endl;
	cout << "\t\t|        0.注销登录        |" << endl;
	cout << "\t\t|                          |" << endl;
	cout << "\t\t----------------------------" << endl;
	cout << "请选择你的操作" << endl;
}

void Student::applyOrder()
{
	int date = 0;
	int interval = 0;
	int room = 0;

	cout << "机房预约时间为周一至周五" << endl;
	cout << "请选择预约时间" << endl;
	cout << "1.周一" << endl;
	cout << "2.周二" << endl;
	cout << "3.周三" << endl;
	cout << "4.周四" << endl;
	cout << "5.周五" << endl;
	while (true)
	{
		cin >> date;
		if (date >= 1 && date <= 5)
		{
			break;
		}
		cout << "输入有误，请重新输入：" << endl;
	}

	cout << "请输入预约的时间段" << endl;
	cout << "1.上午" << endl;
	cout << "2.下午" << endl;
	while (true)
	{
		cin >> interval;
		if (interval == 1 || interval == 2)
		{
			break;
		}
		cout << "输入有误，请重新输入：" << endl;
	}

	cout << "请选择机房" << endl;
	for (unsigned int i = 0;i < vCom.size();i++)
	{
		cout << vCom[i].m_ComId << "号机房的容量为" << vCom[i].m_Maxnum << endl;
	}
	while (true)
	{
		cin >> room;
		if (room == 1 || room == 2 || room == 3)
		{
			break;
		}
		cout << "输入有误，请重新输入：" << endl;
	}

	cout << "预约成功，审核中" << endl;

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
		cout << "无预约记录！" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0;i < of.m_Size;i++)
	{
		if (this->m_Id == atoi(of.m_orderData[i]["stuId"].c_str()))
		{
			cout << "预约日期：周" << of.m_orderData[i]["date"];
			cout << " 时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
			cout << " 机房号：" << of.m_orderData[i]["roomId"];
			string status = " 状态：";
			if (of.m_orderData[i]["status"] == "1")
			{
				status += "审核中";
			}
			else if (of.m_orderData[i]["status"] == "2")
			{
				status += "预约成功";
			}
			else if (of.m_orderData[i]["status"] == "3")
			{
				status += "预约失败，审核未通过";
			}
			else
			{
				status += "预约已取消";
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
		cout << "无预约记录！" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0;i < of.m_Size;i++)
	{
		cout << i + 1 << " ";
		cout << "预约日期：周" << of.m_orderData[i]["date"];
		cout << " 时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
		cout << " 学号：" << of.m_orderData[i]["stuId"];
		cout << " 姓名：" << of.m_orderData[i]["stuName"];
		cout << " 机房号：" << of.m_orderData[i]["roomId"];
		string status = " 状态：";
		if (of.m_orderData[i]["status"] == "1")
		{
			status += "审核中";
		}
		else if (of.m_orderData[i]["status"] == "2")
		{
			status += "预约成功";
		}
		else if (of.m_orderData[i]["status"] == "3")
		{
			status += "预约失败，审核未通过";
		}
		else
		{
			status += "预约已取消";
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
		cout << "无预约记录！" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "审核中或预约成功的记录可以取消，请输入你要取消的记录" << endl;

	int index = 1;
	vector<int> v;
	for (int i = 0;i < of.m_Size;i++)
	{
		if (this->m_Id == atoi(of.m_orderData[i]["stuId"].c_str()))
		{
			if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2")
			{
				v.push_back(i);
				cout << i + 1 << "、";
				cout << " 预约日期：周" << of.m_orderData[i]["date"];
				cout << " 时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
				cout << " 机房号：" << of.m_orderData[i]["roomId"];
				string status = " 状态：";
				if (of.m_orderData[i]["status"] == "1")
				{
					status += "审核中";
				}
				else if (of.m_orderData[i]["status"] == "2")
				{
					status += "预约成功";
				}
				cout << status << endl;
			}
		}
	}

	cout << "请输入取消的记录，0代表返回" << endl;
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
				cout << "已取消预约" << endl;
				break;
			}
		}
		cout << "请输入正确的数:" << endl;
	}
	system("pause");
	system("cls");
}