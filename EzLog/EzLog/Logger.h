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

#pragma once
#ifndef EZLOG_LOGGER_H
#define EZLOG_LOGGER_H

#ifdef EZLOG_EXPORTS
#define EZLOG_API __declspec(dllexport)
#else
#define EZLOG_API __declspec(dllimport)
#endif

#include "LogLevel.h"
#include "TimeStamp.h"

class EZLOG_API Logger
{
public:
	Logger() = default;
	~Logger();
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;

	void Initialize(LogLevel level = LogLevel::Trace, bool consoleLogging = true, const char* fileName = "Output.log", const char* dirPath = "Log");
	
	void SetLogLevel(LogLevel level);
	void ToggleConsoleLogging(bool allowed);

	void LogFatal(const char* fatal) const;
	void LogError(const char* error) const;
	void LogWarn(const char* warning) const;
	void LogInfo(const char* info) const;
	void LogDebug(const char* debugMessage) const;
	void LogTrace(const char* traceMessage) const;	

private:
	char* filePath = nullptr;
	char* timeString = nullptr;
	bool consoleLogging = true;
	LogLevel logLevel = LogLevel::Trace;

	void LogToFile(const char* logString) const;
	void LogToConsole(const char* logString) const;

	void CreateFilePath(const char* dirPath, const char* fileName);
	void CreateTimeString();
	TimeStamp GetTimeStamp() const;
};

#endif