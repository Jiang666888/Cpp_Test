#pragma once

#include "identity.h"

class Student :public Identity
{
public:
	//默认构造
	Student();
	//有参构造
	Student(int id, string username, string password);
	//菜单界面
	virtual void openMenu();
	//申请预约
	void applyOrder();
	//查看我的预约
	void showMyOrder();
	//查看所有预约
	void showAllOrder();
	//取消预约
	void cancelOrder();
	
	//机房容器
	vector<ComputerRoom> vCom;
	//学生学号
	int m_Id;
};