/*
© Copyright 2020 carlthecoder@outlook.com

This file is part of EzLog.
EzLog is free software : you can redistribute it and /or modify
it under the terms of the Lesser GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

EzLog is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with EzLog. If not, see < https://www.gnu.org/licenses/lgpl-3.0.txt >
*/

#include "Logger.h"
#include <ctime>
#include <iostream>
#include <fstream>

using std::string;
using std::ofstream;

Logger::Logger(LogLevels level, bool logToOutput)
	:
	logLevel(level),
	logToOuput(logToOutput)
{
	fileName = CreateFileName();

	ofstream ofs(fileName);
	ofs << "Log file created on " << GetTimeString() << std::endl;
	ofs.close();
}

void Logger::LogFatal(std::string fatal) const
{
	if (logLevel == LogLevels::Off || logLevel < LogLevels::Fatal)
	{
		return;
	}
	string logString = "|FATAL|\t" + GetTimeString() + " | " + fatal;
	LogToFile(logString);
}

void Logger::LogError(std::string error) const
{
	if (logLevel == LogLevels::Off || logLevel < LogLevels::Error)
	{
		return;
	}
	string logString = "|ERROR|\t" + GetTimeString() + " | " + error;
	LogToFile(logString);
}

void Logger::LogWarn(std::string warning) const
{
	if (logLevel == LogLevels::Off || logLevel < LogLevels::Warn)
	{
		return;
	}
	string logString = "|WARN|\t" + GetTimeString() + " | " + warning;
	LogToFile(logString);
}

void Logger::LogInfo(std::string info) const
{
	if (logLevel == LogLevels::Off || logLevel < LogLevels::Info)
	{
		return;
	}
	string logString = "|INFO|\t" + GetTimeString() + " | " + info;
	LogToFile(logString);
}

void Logger::LogDebug(std::string debugMessage) const
{
	if (logLevel == LogLevels::Off || logLevel < LogLevels::Debug)
	{
		return;
	}
	string logString = "|DEBUG|\t" + GetTimeString() + " | " + debugMessage;
	LogToFile(logString);
}

void Logger::LogTrace(std::string traceMessage) const
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
}

void Logger::SetLogToOutput(bool allowed)
{
	logToOuput = allowed;
}

void Logger::LogToFile(std::string& logString) const
{
	ofstream ofs(fileName, std::ios::app);
	ofs << logString << std::endl;
	ofs.close();

	LogToOutput(logString);
}

void Logger::LogToOutput(std::string& logString) const
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

std::string Logger::GetTimeString() const
{
	auto [year, month, day, hour, min, sec] = GetTimeStamp();

	return day + "/" + month + "/" + year + " " + hour + ":" + min + ":" + sec;
}

TimeStamp Logger::GetTimeStamp() const
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