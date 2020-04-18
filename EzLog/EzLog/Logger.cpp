#include "Logger.h"
#include <iostream>
#include <fstream>
#include <sstream>

using std::string;
using std::ofstream;

Logger::Logger()
	:
	logLevel(LogLevels::Off)
{
	fileName = CreateFileName();

	ofstream ofs(fileName);
	ofs << "Log file created on " << GetTimeString() << std::endl;
	ofs.close();
}

void Logger::LogFatal(std::string fatal)
{
	if (logLevel == LogLevels::Off || logLevel < LogLevels::Fatal)
	{
		return;
	}
	string logString = "|FATAL|\t" + GetTimeString() + " | " + fatal;
	LogInternal(logString);
}

void Logger::LogError(std::string error)
{
	if (logLevel == LogLevels::Off || logLevel < LogLevels::Error)
	{
		return;
	}
	string logString = "|ERROR|\t" + GetTimeString() + " | " + error;
	LogInternal(logString);
}

void Logger::LogWarn(std::string warning)
{
	if (logLevel == LogLevels::Off || logLevel < LogLevels::Warn)
	{
		return;
	}
	string logString = "|WARN|\t" + GetTimeString() + " | " + warning;
	LogInternal(logString);
}

void Logger::LogInfo(std::string info)
{
	if (logLevel == LogLevels::Off || logLevel < LogLevels::Info)
	{
		return;
	}
	string logString = "|INFO|\t" + GetTimeString() + " | " + info;
	LogInternal(logString);
}

void Logger::LogDebug(std::string debugMessage)
{
	if (logLevel == LogLevels::Off || logLevel < LogLevels::Debug)
	{
		return;
	}
	string logString = "|DEBUG|\t" + GetTimeString() + " | " + debugMessage;
	LogInternal(logString);
}

void Logger::LogTrace(std::string traceMessage)
{
	if (logLevel == LogLevels::Off || logLevel < LogLevels::Trace)
	{
		return;
	}
	string logString = "|TRACE|\t" + GetTimeString() + " | " + traceMessage;
	LogInternal(logString);
}

LogLevels Logger::GetLogLevel()
{
	return logLevel;
}

void Logger::SetLogLevel(LogLevels level)
{
	logLevel = level;
}

void Logger::LogInternal(std::string& logString)
{
	std::cout << logString << std::endl;
	ofstream ofs(fileName, std::ios::app);
	ofs << logString << std::endl;
	ofs.close();
}

std::string Logger::CreateFileName()
{
	auto lt = GetTimeStruct();

	std::ostringstream oss;
	oss << lt->tm_year - 100
		<< "0" << lt->tm_mon
		<< lt->tm_mday
		<< "_"
		<< lt->tm_hour
		<< lt->tm_min
		<< lt->tm_sec;

	return "Output " + oss.str() + ".log";
}

std::string Logger::GetTimeString()
{
	auto lt = GetTimeStruct();

	std::ostringstream oss;
	oss << lt->tm_year - 100 << "/"
		<< "0" << lt->tm_mon << "/"
		<< lt->tm_mday
		<< " "
		<< lt->tm_hour << ":"
		<< lt->tm_min << ":"
		<< lt->tm_sec;

	return oss.str();
}

tm* Logger::GetTimeStruct()
{
	auto now = time(0);
	return localtime(&now);
}