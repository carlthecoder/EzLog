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

#pragma once
#ifndef EZLOG_LOGGER_H
#define EZLOG_LOGGER_H

#ifdef EZLOG_EXPORTS
#define EZLOG_API __declspec(dllexport)
#else
#define EZLOG_API __declspec(dllimport)
#endif

#include "LogLevels.h"
#include <tuple>
#include <string>

using TimeStamp = std::tuple<std::string, std::string, std::string, std::string, std::string, std::string>;

class EZLOG_API Logger
{
public:
	Logger(LogLevels level = LogLevels::Trace, bool logToOutput = true, std::string dirPath = "Logs", std::string fileName = "output");
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
	std::string CreateFileName(std::string fileName);
	std::string GetTimeString() const;
	TimeStamp GetTimeStamp() const;

	std::string filename;
	LogLevels logLevel;
	bool logToOuput;
	std::string directory;
};

#endif