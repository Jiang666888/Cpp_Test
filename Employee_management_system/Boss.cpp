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
	cout << "ְ����ţ�" << m_ID
		<< "\tְ��������" << m_Name
		<< "\t��λ��" << m_DeptId
		<< "\t��λְ����ɹ�˾��Ӫ������" << endl;
}
string Boss::getDeptName()
{
	return string("�ϰ�");
}