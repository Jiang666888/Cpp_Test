#pragma once

#include "identity.h"
#include "student.h"
#include "teacher.h"

class Manager :public Identity
{
public:
	//Ĭ�Ϲ���
	Manager();
	//�вι���
	Manager(string username, string password);
	//ѡ��˵�
	virtual void openMenu();
	//����˺�
	void addPerson();
	//�鿴�˺�
	void showPerson();
	//�鿴������Ϣ
	void showComputer();
	//���ԤԼ��¼
	void clearFile();
	//��ʼ������
	void initVector();
	//ѧ������
	vector<Student> vStu;
	//��ʦ����
	vector<Teacher> vTea;
	//����ظ�
	bool checkRepeat(int id, int type);
	//��������
	vector<ComputerRoom> vCom;
};