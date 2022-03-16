#define _CRT_SECURE_NO_WARNINGS 1
#define FILENAME "empFile.txt"

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "Worker.h"

using namespace std;

void test01();

class WorkerManager
{
public:
	WorkerManager();
	//显示菜单
	void Show_Menu();
	//推出系统
	void exitSystem();
	//声明职工人数
	int m_EmpNum;
	//职工数组指针
	Worker** m_EmptyArray;
	//添加职工
	void Add_Emp();
	//文件保存
	void save();
	//文件是否为空
	bool m_FileIsEmpty;
	//判断是否有数据
	int get_EmpNum();
	//初始数据
	void init_Emp();
	//显示职工
	void show_Emp();
	//删除职工
	void Del_Emp();
	//判断职工是否存在
	int IsExist(int id);
	//修改职工
	void Mod_Emp();
	//查找职工
	void Find_Emp();
	//排序
	void Sort_Emp();
	//清空数据
	void Clean_File();
	~WorkerManager();
};