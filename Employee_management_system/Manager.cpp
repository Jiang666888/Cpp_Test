#define _CRT_SECURE_NO_WARNINGS 1

#include "Manager.h"

Manager::Manager(int id, string name, int deptid)
{
	this->m_Name = name;
	this->m_ID = id;
	this->m_DeptId = deptid;
}
void Manager::showInfo()
{
	cout << "职工编号：" << m_ID
		<< "\t职工姓名：" << m_Name
		<< "\t岗位：" << m_DeptId
		<< "\t岗位职责：完成老板交代的任务" << endl;
}
string Manager::getDeptName()
{
	return string("经理");
}