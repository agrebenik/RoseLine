
#include <chrono>
#include "RSE_Time.h"

using namespace std::chrono;

RSE_Time::RSE_Time() { }

int RSE_Time::start() {
	if (_stopped) {
		_startTime = duration_cast< microseconds >(system_clock::now().time_since_epoch());
		_stopped = false;
		return 0;
	}
	else {
		// cannot start before reseting or stopping
		return 1;
	}
	return -1;
}

int RSE_Time::stop() {
	if (!_stopped) {
		_endTime = duration_cast< microseconds >(system_clock::now().time_since_epoch());
		_stopped = true;
		return 0;
	}
	else {
		// cannot stop before started
		return 1;
	}
	return -1;
}

int RSE_Time::reset() {
	_startTime = 0ms;
	_endTime = 0ms;
	if (_stopped) {
		return 0;
	}
	else {
		_stopped = false;
		return 1;
	}
	return -1;
}

microseconds RSE_Time::getTime() {
	microseconds virtualEndTime = _endTime;
	if (!_stopped) {
		virtualEndTime = duration_cast< microseconds >(system_clock::now().time_since_epoch());
	}
	return virtualEndTime - _startTime;
}

microseconds RSE_Time::getStartTime() {
	return _startTime;
}

microseconds RSE_Time::getEndTime() {
	return _endTime;
}

RSE_Time::~RSE_Time() { }
