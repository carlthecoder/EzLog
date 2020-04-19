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