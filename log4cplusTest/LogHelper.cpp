#include "StdAfx.h"
#include "LogHelper.h"
#include <windows.h>

map<string, Logger> LoggerFactory::_loggers;

void Logger::Trace(const string& msg)
{
	log4cplus::Logger logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("TRACE_MSGS"));
	LOG4CPLUS_TRACE(logger, ("{" + _name + "} " + msg).c_str());
}

void Logger::Debug(const string& msg)
{
	OutputDebugString(L"");
	log4cplus::Logger logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("DEBUG_INFO_MSGS"));
	LOG4CPLUS_DEBUG(logger, ("{" + _name + "} " + msg).c_str());

}

void Logger::Info(const string& msg)
{
	log4cplus::Logger logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("DEBUG_INFO_MSGS"));
	LOG4CPLUS_INFO(logger, ("{" + _name + "} " + msg).c_str());
}

void Logger::Warn(const string& msg)
{
	log4cplus::Logger logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("WARN_ERROR_MSGS"));
	LOG4CPLUS_WARN(logger, ("{" + _name + "} " + msg).c_str());
}

void Logger::Error(const string& msg)
{
	log4cplus::Logger logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("WARN_ERROR_MSGS"));
	LOG4CPLUS_ERROR(logger, ("{" + _name + "} " + msg).c_str());
}

void Logger::Fatal(const string& msg)
{
	log4cplus::Logger logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("FATAL_MSGS"));
	LOG4CPLUS_FATAL(logger, ("{" + _name + "} " + msg).c_str());
}

