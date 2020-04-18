#include "Logger.h"
#include <iostream>
#include <fstream>
#include <sstream>

using std::string;
using std::ofstream;

Logger::Logger()
	:
	logLevel(LogLevels::Off),
	logToOuput(false)
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
	LogToFile(logString);
}

void Logger::LogError(std::string error)
{
	if (logLevel == LogLevels::Off || logLevel < LogLevels::Error)
	{
		return;
	}
	string logString = "|ERROR|\t" + GetTimeString() + " | " + error;
	LogToFile(logString);
}

void Logger::LogWarn(std::string warning)
{
	if (logLevel == LogLevels::Off || logLevel < LogLevels::Warn)
	{
		return;
	}
	string logString = "|WARN|\t" + GetTimeString() + " | " + warning;
	LogToFile(logString);
}

void Logger::LogInfo(std::string info)
{
	if (logLevel == LogLevels::Off || logLevel < LogLevels::Info)
	{
		return;
	}
	string logString = "|INFO|\t" + GetTimeString() + " | " + info;
	LogToFile(logString);
}

void Logger::LogDebug(std::string debugMessage)
{
	if (logLevel == LogLevels::Off || logLevel < LogLevels::Debug)
	{
		return;
	}
	string logString = "|DEBUG|\t" + GetTimeString() + " | " + debugMessage;
	LogToFile(logString);
}

void Logger::LogTrace(std::string traceMessage)
{
	if (logLevel == LogLevels::Off || logLevel < LogLevels::Trace)
	{
		return;
	}
	string logString = "|TRACE|\t" + GetTimeString() + " | " + traceMessage;
	LogToFile(logString);
}

void Logger::SetLogLevel(LogLevels level)
{
	logLevel = level;
	LogInfo("LogLevel set to " + LogLevelToString(level));
}

void Logger::SetLogToOuput(bool allowed)
{
	logToOuput = allowed;
}

void Logger::LogToFile(std::string& logString)
{
	ofstream ofs(fileName, std::ios::app);
	ofs << logString << std::endl;
	ofs.close();

	LogToOutput(logString);
}

void Logger::LogToOutput(std::string& logString)
{
	if (logToOuput)
	{
		std::cout << logString << std::endl;
	}	
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