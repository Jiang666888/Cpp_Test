#define _CRT_SECURE_NO_WARNINGS 1

#pragma once

#include "Worker.h"

using namespace std;

class Boss :public Worker
{
public:
	Boss(int id, string name, int deptid);
	void showInfo();
	string getDeptName();
};