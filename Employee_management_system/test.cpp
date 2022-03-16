#define _CRT_SECURE_NO_WARNINGS 1

#include "Boss.h"
#include "Employee.h"
#include "Manager.h"

void test01()
{
	Worker* worker;
	worker = new Employee(1, "张三", 1);
	worker->showInfo();
	delete worker;

	worker = new Manager(2, "李四", 2);
	worker->showInfo();
	delete worker;

	worker = new Boss(3, "王五", 3);
	worker->showInfo();
	delete worker;
}