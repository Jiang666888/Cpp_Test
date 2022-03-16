#define _CRT_SECURE_NO_WARNINGS 1

#include "WorkerManager.h"

using namespace std;

int main()
{
	//test01();
	WorkerManager wm;
	while (true)
	{
		wm.Show_Menu();
		int choice = 0;
		cout << "ÇëÊäÈëÄãµÄÑ¡Ôñ£º" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0:
			wm.exitSystem();
			break;
		case 1:
			wm.Add_Emp();
			break;
		case 2:
			wm.show_Emp();
			break;
		case 3:
			wm.Del_Emp();
			break;
		case 4:
			wm.Mod_Emp();
			break;
		case 5:
			wm.Find_Emp();
			break;
		case 6:
			wm.Sort_Emp();
			break;
		case 7:
			wm.Clean_File();
			break;
		default:
			system("cls");
			break;
		}
	}

	system("pause");
	return 0;
}