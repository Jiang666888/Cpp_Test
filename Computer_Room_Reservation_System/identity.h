#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include "globalFile.h"
#include "computerRoom.h"
#include "orderFile.h"

using namespace std;

class Identity
{
public:
	virtual void openMenu() = 0;
	string m_Username;
	string m_Password;
};