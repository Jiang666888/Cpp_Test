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
	cout << "ְ����ţ�" << m_ID
		<< "\tְ��������" << m_Name
		<< "\t��λ��" << m_DeptId
		<< "\t��λְ����ɾ�����������" << endl;
}
string Employee::getDeptName()
{
	return string("Ա��");
}