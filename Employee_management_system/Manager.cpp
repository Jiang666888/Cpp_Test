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
	cout << "ְ����ţ�" << m_ID
		<< "\tְ��������" << m_Name
		<< "\t��λ��" << m_DeptId
		<< "\t��λְ������ϰ彻��������" << endl;
}
string Manager::getDeptName()
{
	return string("����");
}