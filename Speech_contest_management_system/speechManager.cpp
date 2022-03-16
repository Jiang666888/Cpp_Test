#define _CRT_SECURE_NO_WARNINGS 1

#include "speechManager.h"

SpeechManager::SpeechManager()
{
	this->initSpeech();
	this->createSpeaker();
	this->loadRecord();
}
SpeechManager::~SpeechManager()
{
	
}

void SpeechManager::Show_Menu()
{
	cout << "**********************************" << endl;
	cout << "*******  ��ӭ�μ��ݽ�����  *******" << endl;
	cout << "******    1.��ʼ�ݽ�����    ******" << endl;
	cout << "******    2.�ۿ������¼    ******" << endl;
	cout << "******    3.��ձ�����¼    ******" << endl;
	cout << "******    0.�˳�����ϵͳ    ******" << endl;
	cout << "**********************************" << endl;
	cout << endl;
}

void SpeechManager::exitSystem()
{
	cout << "��ӭ�´μ���ʹ�ã�" << endl;
	system("pause");
	exit(0);
}

void SpeechManager::initSpeech()
{
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();
	this->m_Index = 1;
	this->m_Record.clear();
}

void SpeechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (unsigned int i = 0;i < nameSeed.size();i++)
	{
		string name = "ѡ��";
		name += nameSeed[i];

		Speaker sp;
		sp.m_Name = name;
		for (int j = 0;j < 2;j++)
		{
			sp.m_Socre[j] = 0;
		}
		this->v1.push_back(i + 10001);
		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}
}

void  SpeechManager::speechDraw()
{
	cout << "�� << " << this->m_Index << " >> �ֱ�����ѡ�����ڳ�ǩ" << endl;
	cout << "------------------" << endl;
	cout << "��ǩ�������" << endl;
	if (this->m_Index == 1)
	{
		random_shuffle(this->v1.begin(), this->v1.end());
		for (vector<int>::iterator itv1 = this->v1.begin();itv1 != this->v1.end();itv1++)
		{
			cout << *itv1 << " ";
		}
		cout << endl;
	}
	else
	{
		random_shuffle(this->v2.begin(), this->v2.end());
		for (vector<int>::iterator itv2 = this->v2.begin();itv2 != this->v2.end();itv2++)
		{
			cout << *itv2 << " ";
		}
		cout << endl;
	}
	cout << "------------------" << endl;
	system("pause");
}

void SpeechManager::speechContest()
{
	cout << "---------�� << " << this->m_Index << " >> �ֱ�����ʽ��ʼ--------" << endl;
	vector<int> v_Src;
	multimap<double, int, greater<double>> groupScore;
	int num = 0;
	if (this->m_Index == 1)
	{
		v_Src = this->v1;
	}
	else
	{
		v_Src = this->v2;
	}
	for (vector<int>::iterator it = v_Src.begin();it != v_Src.end();it++)
	{
		num++;
		deque<double> d;
		for (int i = 0;i < 10;i++)
		{
			double score = (rand() % 401 + 600) / 10.f;
			d.push_back(score);
		}
		sort(d.begin(), d.end(),greater<double>());
		d.pop_front();
		d.pop_back();
		double sum = accumulate(d.begin(), d.end(), 0.0);
		double avg = sum / (double)d.size();

		//cout << *it << " " << this->m_Speaker[*it].m_Name << " " << avg << endl;
		this->m_Speaker[*it].m_Socre[this->m_Index - 1] = avg;

		groupScore.insert(make_pair(avg, *it));

		if (num % 6 == 0)
		{
			cout << "�� " << num / 6 << "С���������" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin();it != groupScore.end();it++)
			{
				cout << "��ţ�" << it->second << " ������" << this->m_Speaker[it->second].m_Name
					<< " �ɼ���" << this->m_Speaker[it->second].m_Socre[this->m_Index-1] << endl;
			}
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin();it != groupScore.end() && count < 3;it++,count++)
			{
				if (this->m_Index == 1)
				{
					this->v2.push_back(it->second);
				}
				else
				{
					this->vVictory.push_back(it->second);
				}

			}
			groupScore.clear();
		}
	}
	cout << "---------�� << " << this->m_Index << " >> �ֱ�������--------" << endl;
	system("pause");
}

void SpeechManager::showScore()
{
	cout << "----------�� << " << this->m_Index << " >> ������Ա����----------" << endl;
	vector<int> v;
	if (this->m_Index == 1)
	{
		v = this->v2;
	}
	else
	{
		v = this->vVictory;
	}
	for (vector<int>::iterator it = v.begin();it != v.end();it++)
	{
		cout << "��ţ�" << *it << " ������" << this->m_Speaker[*it].m_Name
			<< " �ɼ���" << this->m_Speaker[*it].m_Socre[this->m_Index - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	if (this->m_Index == 1)
	{
		this->Show_Menu();
	}
}

void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);
	for (vector<int>::iterator it = this->vVictory.begin();it != this->vVictory.end();it++)
	{
		ofs << *it << "," << this->m_Speaker[*it].m_Socre[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "�ļ���¼�ɹ�" << endl;
	this->fileIsEmpty = false;
	this->Show_Menu();
}

void SpeechManager::startSpeech()
{
	this->speechDraw();
	this->speechContest();
	this->showScore();
	this->m_Index++;
	this->speechDraw();
	this->speechContest();
	this->showScore();
	this->saveRecord();
	this->initSpeech();
	this->createSpeaker();
	this->loadRecord();
	cout << "����������" << endl;
	system("pause");
	system("cls");
}

void SpeechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in);
	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		//cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		this->fileIsEmpty = true;
		//cout << "�ļ�Ϊ��" << endl;
		ifs.close();
		return;
	}

	this->fileIsEmpty = false;
	ifs.putback(ch);
	
	string data;
	int index = 0;
	while (ifs >> data)
	{
		vector<string> v;
		int pos = -1;
		int start = 0;
		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				break;
			}
			string temp = data.substr(start, pos - start);
			v.push_back(temp);
			start = pos + 1;
		}
		this->m_Record.insert(make_pair(index, v));
		v.clear();
		index++;
	}
	ifs.close();
}

void SpeechManager::showRecord()
{
	if (this->fileIsEmpty)
	{
		cout << "�ļ������ڻ���Ϊ��" << endl;
	}
	else
	{
		for (unsigned int i = 0;i < this->m_Record.size();i++)
		{
			cout << "��" << i + 1 << "��"
				<< " �ھ���ţ�" << this->m_Record[i][0] << "���÷֣�" << this->m_Record[i][1] << " "
				<< " �Ǿ���ţ�" << this->m_Record[i][2] << "���÷֣�" << this->m_Record[i][3] << " "
				<< " ������ţ�" << this->m_Record[i][4] << "���÷֣�" << this->m_Record[i][5] << endl;
		}
	}
	system("pause");
	system("cls");
}

void SpeechManager::clearRecord()
{
	cout << "ȷ����գ�" << endl;
	cout << "1.ȷ��" << endl;
	cout << "2.ȡ��" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();
		this->initSpeech();
		this->createSpeaker();
		this->loadRecord();
		cout << "��ճɹ���" << endl;
	}
	system("pause");
	system("cls");
}