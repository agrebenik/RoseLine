#pragma once
#include <chrono>

using namespace std::chrono;

class RSE_Time
{
private:
	microseconds _startTime;
	bool _stopped;
	microseconds _endTime;
public:
	RSE_Time();
	int start();
	int stop();
	int reset();
	microseconds getTime();
	microseconds getStartTime();
	microseconds getEndTime();
	~RSE_Time();
};

