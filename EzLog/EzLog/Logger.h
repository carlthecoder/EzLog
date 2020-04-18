#pragma once
#ifndef EZLOG_LOGGER_H
#define EZLOG_LOGGER_H

#ifdef EZLOG_EXPORTS
#define EZLOG_API __declspec(dllexport)
#else
#define EZLOG_API __declspec(dllimport)
#endif

#include "LogLevels.h"
#include <ctime>
#include <string>

class EZLOG_API Logger
{
public:
	Logger();
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;

	void LogFatal(std::string fatal);
	void LogError(std::string error);
	void LogWarn(std::string warning);
	void LogInfo(std::string info);
	void LogDebug(std::string debugMessage);
	void LogTrace(std::string traceMessage);

	void SetLogLevel(LogLevels level);
	void SetLogToOuput(bool allowed);

private:
	void LogToFile(std::string& logString);
	void LogToOutput(std::string& logString);
	std::string CreateFileName();
	std::string GetTimeString();
	tm* GetTimeStruct();

	std::string fileName;
	LogLevels logLevel;
	bool logToOuput;
};

#endif