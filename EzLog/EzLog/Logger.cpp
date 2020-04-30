/*
Copyright © 2020 Carl Claessens

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
#include <filesystem>
#include <cstdio>
#include <sstream>

using std::ofstream;
using std::stringstream;

Logger::~Logger()
{
	if (filePath)
	{
		delete[] filePath;
		filePath = nullptr;
	}

	if (timeString)
	{
		delete[] timeString;
		timeString = nullptr;
	}

	if (outputString)
	{
		delete[] outputString;
		outputString = nullptr;
	}
}

void Logger::Initialize(LogLevel level, bool logToConsole, const char* fileName, const char* dirPath)
{
	logLevel = level;
	this->consoleLogging = logToConsole;
	std::filesystem::create_directory(dirPath);

	CreateFilePath(dirPath, fileName);

	ofstream ofs(filePath);
	ofs << "EzLog v1.0" << std::endl
		<< "----------" << std::endl;
	ofs.close();
}

void Logger::SetLogLevel(LogLevel level)
{
	logLevel = level;
}

void Logger::ToggleConsoleLogging(bool onOff)
{
	consoleLogging = onOff;
}

void Logger::LogFatal(const char* fatal)
{
	if (logLevel == LogLevel::Off || logLevel < LogLevel::Fatal)
	{
		return;
	}

	FormatAndLog("|FATAL|\t", fatal);
}

void Logger::LogError(const char* error)
{
	if (logLevel == LogLevel::Off || logLevel < LogLevel::Error)
	{
		return;
	}

	FormatAndLog("|ERROR|\t", error);
}

void Logger::LogWarn(const char* warning)
{
	if (logLevel == LogLevel::Off || logLevel < LogLevel::Warn)
	{
		return;
	}

	FormatAndLog("|WARN|\t", warning);
}

void Logger::LogInfo(const char* info)
{
	if (logLevel == LogLevel::Off || logLevel < LogLevel::Info)
	{
		return;
	}

	FormatAndLog("|INFO|\t", info);
}

void Logger::LogDebug(const char* debug)
{
	if (logLevel == LogLevel::Off || logLevel < LogLevel::Debug)
	{
		return;
	}

	FormatAndLog("|DEBUG|\t", debug);
}

void Logger::LogTrace(const char* trace)
{
	if (logLevel == LogLevel::Off || logLevel < LogLevel::Trace)
	{
		return;
	}

	FormatAndLog("|TRACE|\t", trace);
}

void Logger::CreateFilePath(const char* dirPath, const char* fileName)
{
	auto size = strlen(dirPath) + strlen(fileName) + 2;
	filePath = new char[size] {};

	strcat(filePath, dirPath);
	strcat(filePath, "\\");
	strcat(filePath, fileName);
}

void Logger::CreateTimeString()
{
	auto ts = GetTimeStamp();

	std::stringstream ss;
	ss << ts.year << "_" << ts.month << "_" << ts.day
		<< " " << ts.hour << "_" << ts.min;

	auto time = ss.str().c_str();
	delete[] timeString;
	timeString = new char[strlen(time)] {};

	strcpy(timeString, time);
}

TimeStamp Logger::GetTimeStamp() const
{
	auto now = time(0);
	auto lt = localtime(&now);

	TimeStamp stamp;

	stamp.day = lt->tm_mday;
	stamp.month = lt->tm_mon;
	stamp.year = lt->tm_year % 100;
	stamp.hour = lt->tm_hour;
	stamp.min = lt->tm_min;
	stamp.sec = lt->tm_sec;

	return stamp;
}

void Logger::FormatAndLog(const char* levelLabel, const char* output)
{
	ClearOutputString();

	auto len1 = strlen(levelLabel);
	auto len2 = strlen(output);
	outputString = new char[len1 + len2 + 1] {};

	strcat(outputString, levelLabel);
	strcat(outputString, output);

	LogToFile(outputString);

	if (consoleLogging)
	{
		LogToConsole(outputString);
	}
}

void Logger::ClearOutputString()
{
	if (outputString)
	{
		delete[] outputString;
		outputString = nullptr;
	}
}

void Logger::LogToFile(const char* logString) const
{
	ofstream ofs(filePath, std::ios::app);
	ofs << logString << '\n';
	ofs.close();
}

void Logger::LogToConsole(const char* logString) const
{
	std::cout << logString << '\n';
}