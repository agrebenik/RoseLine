#include "RSE_ID.h"
#include <string> 

using namespace std;

static const char alphanum[] =
"0123456789"
"!@#$%^&*"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";

int stringLength = sizeof(alphanum) - 1;

RSE_ID::RSE_ID() {
	id = alphanum[rand() % stringLength];;
}

bool RSE_ID::operator==(const RSE_ID* other) {
	return other->id == id;
}

RSE_ID::~RSE_ID() {
}
