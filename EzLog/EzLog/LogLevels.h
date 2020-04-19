#pragma once
#ifndef EZLOG_LOGLEVELS_H
#define EZLOG_LOGLEVELS_H

#ifdef EZLOG_EXPORTS
#define EZLOG_API __declspec(dllexport)
#else
#define EZLOG_API __declspec(dllimport)
#endif

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

EZLOG_API std::string LogLevelToString(LogLevels level);

#endif