#pragma once

#ifndef EZLOG_TIMESTAMP_H
#define EZLOG_TIMESTAMP_H

#ifdef EZLOG_EXPORTS
#define EZLOG_API __declspec(dllexport)
#else
#define EZLOG_API __declspec(dllimport)
#endif

struct EZLOG_API TimeStamp
{
	unsigned int day;
	unsigned int month;
	unsigned int year;
	unsigned int hour;
	unsigned int min;
	unsigned int sec;
};

#endif // !EZLOG_TIMESTAMP_H
