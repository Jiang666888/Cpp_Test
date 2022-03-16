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

//演讲管理类
class SpeechManager
{
public:
	//构造函数
	SpeechManager();
	//显示菜单
	void Show_Menu();
	//推出系统
	void exitSystem();
	//初始化
	void initSpeech();
	//创建选手
	void createSpeaker();
	//开始比赛
	void startSpeech();
	 //抽签
	 void speechDraw();
	 //比赛
	 void speechContest();
	//显示分数
	void showScore();
	//保存分数
	void saveRecord();
	//读取记录
	void loadRecord();
	//显示记录
	void showRecord();
	//清空记录
	void clearRecord();

	//析构函数
	~SpeechManager();

	vector<int> v1;
	vector<int> v2;
	vector<int> vVictory;
	map<int, Speaker> m_Speaker;
	int m_Index;
	
	bool fileIsEmpty;
	map<int, vector<string>> m_Record;
};