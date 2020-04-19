#pragma once
#ifndef EZLOG_LOGGER_H
#define EZLOG_LOGGER_H

#ifdef EZLOG_EXPORTS
#define EZLOG_API __declspec(dllexport)
#else
#define EZLOG_API __declspec(dllimport)
#endif

#include "LogLevels.h"
#include <string>
#include <tuple>

using TimeStamp = std::tuple<std::string, std::string, std::string, std::string, std::string, std::string>;

class EZLOG_API Logger
{
public:
	Logger(LogLevels level, bool logToOutput);
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;

	void LogFatal(std::string fatal) const;
	void LogError(std::string error) const;
	void LogWarn(std::string warning) const;
	void LogInfo(std::string info) const;
	void LogDebug(std::string debugMessage) const;
	void LogTrace(std::string traceMessage) const;
	
	void SetLogLevel(LogLevels level);
	void SetLogToOutput(bool allowed);

private:
	void LogToFile(std::string& logString) const;
	void LogToOutput(std::string& logString) const;
	std::string CreateFileName();
	std::string GetTimeString() const;
	TimeStamp GetTimeStamp() const;

	std::string fileName;
	LogLevels logLevel;
	bool logToOuput;
};

#endif