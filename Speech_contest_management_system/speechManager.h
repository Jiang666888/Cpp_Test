#define _CRT_SECURE_NO_WARNINGS 1
#pragma once

using namespace std;

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <deque>
#include <algorithm>
#include <numeric>
#include <fstream>

#include "speaker.h"

//�ݽ�������
class SpeechManager
{
public:
	//���캯��
	SpeechManager();
	//��ʾ�˵�
	void Show_Menu();
	//�Ƴ�ϵͳ
	void exitSystem();
	//��ʼ��
	void initSpeech();
	//����ѡ��
	void createSpeaker();
	//��ʼ����
	void startSpeech();
	 //��ǩ
	 void speechDraw();
	 //����
	 void speechContest();
	//��ʾ����
	void showScore();
	//�������
	void saveRecord();
	//��ȡ��¼
	void loadRecord();
	//��ʾ��¼
	void showRecord();
	//��ռ�¼
	void clearRecord();

	//��������
	~SpeechManager();

	vector<int> v1;
	vector<int> v2;
	vector<int> vVictory;
	map<int, Speaker> m_Speaker;
	int m_Index;
	
	bool fileIsEmpty;
	map<int, vector<string>> m_Record;
};