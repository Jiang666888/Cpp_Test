#pragma once

#include "identity.h"

class Teacher :public Identity
{
public:
	//默认构造
	Teacher();
	//有参构造
	Teacher(int empId, string username, string password);
	//菜单界面
	virtual void openMenu();
	//查看所有预约
	void showAllOrder();
	//审核预约
	void validOrder();

	//教职工号
	int m_EmpId;
};