#include "Logger.h"
#include <iostream>
#include <fstream>
#include <sstream>

using std::string;
using std::ofstream;

Logger::Logger()
{
	fileName = CreateFileName();

	ofstream ofs(fileName);
	ofs << "Log file created on " << GetLogTimeString() << std::endl;
	ofs.close();
}

void Logger::LogFatal(std::string fatal)
{
	string logString = "|FATAL|\t" + GetLogTimeString() + " | " + fatal;
	std::cout << logString << std::endl;

	ofstream ofs(fileName, std::ios::app);
	ofs << logString << std::endl;
	ofs.close();
}

void Logger::LogInfo(std::string info)
{
	string logString = "|INFO|\t" + GetLogTimeString() + " | " + info;
	std::cout << logString << std::endl;

	ofstream ofs(fileName, std::ios::app);
	ofs << logString << std::endl;
	ofs.close();
}

std::string Logger::CreateFileName()
{
	auto lt = GetTimeStruct();

	std::ostringstream oss;
	oss << lt->tm_year - 100
		<< "0" << lt->tm_mon
		<< lt->tm_mday
		<< "_"
		<< lt->tm_hour
		<< lt->tm_min
		<< lt->tm_sec;

	return "Output " + oss.str() + ".log";
}

std::string Logger::GetLogTimeString()
{
	auto lt = GetTimeStruct();

	std::ostringstream oss;
	oss << lt->tm_year - 100 << "/"
		<< "0" << lt->tm_mon << "/"
		<< lt->tm_mday
		<< " "
		<< lt->tm_hour << ":"
		<< lt->tm_min << ":"
		<< lt->tm_sec;

	return oss.str();
}

tm* Logger::GetTimeStruct()
{
	auto now = time(0);
	return localtime(&now);
}