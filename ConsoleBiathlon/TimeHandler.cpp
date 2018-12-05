#include "pch.h"
#include "TimeHandler.h"
#include <ctime>
#include <iostream>
#include <chrono>

using namespace std;

__int64 startTime;
__int64 endTime;

TimeHandler::TimeHandler() {
	startTime = 0;
	endTime = 0;
}

TimeHandler::~TimeHandler() {
	startTime = 0;
	endTime = 0;
}

__int64 TimeHandler::start() {
	startTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	return startTime;
}

__int64 TimeHandler::end() {
	endTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	return endTime;
}

/**
* Get difference between start time and end time in seconds.
* If end time is not set, it will be set to this point.
*/
__int64 TimeHandler::getDifference() {
	if (endTime <= startTime) {
		end();
	}
	return ((endTime - startTime) / 1000);
}

/**
* Get difference between start time and end time in milliseconds.
* If end time is not set, it will be set to this point.
*/
__int64 TimeHandler::getDifferenceInMillis() {
	if (endTime <= startTime) {
		end();
	}
	return (endTime - startTime);
}

/**
* Get difference between start time and current time in seconds.
* Timer will not be stopped by this.
*/
__int64 TimeHandler::getInterval() {
	return ((epoch() - startTime) / 1000);
}

/**
* Get difference between start time and current time in milliseconds.
* Timer will not be stopped by this.
*/
__int64 TimeHandler::getIntervalInMillis() {
	return (epoch() - startTime);
}

/**
* Get epoch time in milliseconds.
*/
__int64 TimeHandler::epoch() {
	return (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
}
