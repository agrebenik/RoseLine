#pragma once

#include <map>
#include <string>

#include "ENM_Direction.h"

using namespace std;

class RSE_MenuItem
{
private:
	RSE_MenuItem* _left;
	RSE_MenuItem* _right;
	RSE_MenuItem* _up;
	RSE_MenuItem* _down;
	RSE_MenuItem* getItemFromDirection(ENM_Direction);
public:
	string data;

	RSE_MenuItem();
	RSE_MenuItem(string);
	RSE_MenuItem* getLink(ENM_Direction);
	void linkItem(RSE_MenuItem*, ENM_Direction);
	~RSE_MenuItem();
};

