#pragma once

#include <iostream>
#include <map>
#include <fstream>
#include "globalFile.h"

using namespace std;

class OrderFile
{
public:
	OrderFile();
	void uploadOrder();
	map<int, map<string, string>> m_orderData;
	int m_Size;
};