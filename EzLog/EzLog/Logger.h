#pragma once
#ifndef EZLOG_LOGGER_H
#define EZLOG_LOGGER_H

#ifdef EZLOG_EXPORTS
#define EZLOG_API __declspec(dllexport)
#else
#define EZLOG_API __declspec(dllimport)
#endif

#include <string>
#include <ctime>

class EZLOG_API Logger
{
public:
	Logger();

	void LogFatal(std::string fatal);
	void LogInfo(std::string info);

private:
	std::string CreateFileName();
	std::string GetLogTimeString();
	tm* GetTimeStruct();

	std::string fileName;
};

#endif
