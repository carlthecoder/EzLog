#pragma once
#ifndef EZLOG_LOGLEVELS_H
#define EZLOG_LOGLEVELS_H

#include <string>

enum class LogLevels
{
	Off,
	Fatal,
	Error,
	Warn,
	Info,
	Debug,
	Trace
};

std::string LogLevelToString(LogLevels level)
{
	switch (level)
	{
		case LogLevels::Off:
			return "Off";
			
		case LogLevels::Fatal:
			return "Fatal";
			
		case LogLevels::Error:
			return "Error";

		case LogLevels::Warn:
			return "Warn";

		case LogLevels::Info:
			return "Info";

		case LogLevels::Debug:
			return "Debug";

		case LogLevels::Trace:
			return "Trace";
	}
}

#endif