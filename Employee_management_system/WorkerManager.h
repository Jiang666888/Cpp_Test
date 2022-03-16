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
	//��ʾ�˵�
	void Show_Menu();
	//�Ƴ�ϵͳ
	void exitSystem();
	//����ְ������
	int m_EmpNum;
	//ְ������ָ��
	Worker** m_EmptyArray;
	//���ְ��
	void Add_Emp();
	//�ļ�����
	void save();
	//�ļ��Ƿ�Ϊ��
	bool m_FileIsEmpty;
	//�ж��Ƿ�������
	int get_EmpNum();
	//��ʼ����
	void init_Emp();
	//��ʾְ��
	void show_Emp();
	//ɾ��ְ��
	void Del_Emp();
	//�ж�ְ���Ƿ����
	int IsExist(int id);
	//�޸�ְ��
	void Mod_Emp();
	//����ְ��
	void Find_Emp();
	//����
	void Sort_Emp();
	//�������
	void Clean_File();
	~WorkerManager();
};