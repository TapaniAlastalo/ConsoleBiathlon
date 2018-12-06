#pragma once

#ifndef TIMEHANDLER_H
#define TIMEHANDLER_H

#include <iostream>
#include <string>

class TimeHandler {
private:
	__int64 startTime;
	__int64 endTime;
public:
	TimeHandler();
	~TimeHandler();
	__int64 start();
	__int64 end();
	__int64 getDifference();
	__int64 getDifferenceInMillis();
	__int64 getInterval();
	__int64 getIntervalInMillis();
	__int64 epoch();
	std::string getHumanReadableTime(__int64);
};
#endif