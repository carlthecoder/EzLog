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

#include "LogLevels.h"

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

		default:
			return "Off";
	}
}