#define _CRT_SECURE_NO_WARNINGS 1

#include "Boss.h"

Boss::Boss(int id, string name, int deptid)
{
	this->m_Name = name;
	this->m_ID = id;
	this->m_DeptId = deptid;
}
void Boss::showInfo()
{
	cout << "职工编号：" << m_ID
		<< "\t职工姓名：" << m_Name
		<< "\t岗位：" << m_DeptId
		<< "\t岗位职责：完成公司运营的任务" << endl;
}
string Boss::getDeptName()
{
	return string("老板");
}