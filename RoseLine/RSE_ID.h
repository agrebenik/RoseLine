#pragma once
#include <string>

using namespace std;

class RSE_ID
{
	string id;
public:
	RSE_ID();
	bool operator==(const RSE_ID*);
	~RSE_ID();
};

