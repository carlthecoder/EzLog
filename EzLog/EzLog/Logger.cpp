#include "Logger.h"
#include <ctime>
#include <iostream>
#include <fstream>

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
		std::clog << logString << std::endl;
	}	
}

std::string Logger::CreateFileName()
{
	auto [year, month, day, hour, min, sec] = GetTimeStamp();

	auto fileTime = year + month + day + "_" + hour + min + sec;

	return "Output " + fileTime + ".log";
}

std::string Logger::GetTimeString()
{
	auto [year, month, day, hour, min, sec] = GetTimeStamp();

	return day + "/" + month + "/" + year + " " + hour + ":" + min + ":" + sec;
}

TimeStamp Logger::GetTimeStamp()
{
	auto now = time(0);
	auto lt = localtime(&now);

	string year = std::to_string(lt->tm_year - 100);
	string month = std::to_string(lt->tm_mon);
	string day = std::to_string(lt->tm_mday);
	month = lt->tm_mon < 10 ? "0" + month : month;
	day = lt->tm_mday < 10 ? "0" + day : day;

	string hour = std::to_string(lt->tm_hour);
	string min = std::to_string(lt->tm_min);
	hour = lt->tm_hour < 10 ? "0" + hour : hour;
	string sec = std::to_string(lt->tm_sec);
	min = lt->tm_min < 10 ? "0" + min : min;
	sec = lt->tm_sec < 10 ? "0" + sec : sec;

	return std::make_tuple(year, month, day, hour, min, sec);
}