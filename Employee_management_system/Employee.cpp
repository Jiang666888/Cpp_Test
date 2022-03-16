#define _CRT_SECURE_NO_WARNINGS 1

#include "Employee.h"

Employee::Employee(int id, string name, int deptid)
{
	this->m_Name = name;
	this->m_ID = id;
	this->m_DeptId = deptid;
}
void Employee::showInfo()
{
	cout << "职工编号：" << m_ID
		<< "\t职工姓名：" << m_Name
		<< "\t岗位：" << m_DeptId
		<< "\t岗位职责：完成经理交代的任务" << endl;
}
string Employee::getDeptName()
{
	return string("员工");
}