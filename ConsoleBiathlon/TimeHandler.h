#pragma once

#ifndef TIMEHANDLER_H
#define TIMEHANDLER_H

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
	__int64 epoch();
};
#endif