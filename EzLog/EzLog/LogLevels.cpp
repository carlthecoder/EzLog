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