#pragma once

#include "identity.h"

class Teacher :public Identity
{
public:
	//Ĭ�Ϲ���
	Teacher();
	//�вι���
	Teacher(int empId, string username, string password);
	//�˵�����
	virtual void openMenu();
	//�鿴����ԤԼ
	void showAllOrder();
	//���ԤԼ
	void validOrder();

	//��ְ����
	int m_EmpId;
};