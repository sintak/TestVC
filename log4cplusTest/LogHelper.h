#pragma once
#include <string>

#include  <log4cplus/logger.h>  
#include  <log4cplus/fileappender.h>  
#include  <log4cplus/consoleappender.h>  
#include  <log4cplus/layout.h>  
#include  <log4cplus/ndc.h>  
#include  <log4cplus/helpers/loglog.h>  
#include  <log4cplus/loggingmacros.h>  
#include <log4cplus/configurator.h>
#include <iostream>


#define LOG_DEBUG1(loggerFake, msg)   \
	log4cplus::Logger logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("DEBUG_INFO_MSGS"));  \
	LOG4CPLUS_DEBUG(logger, ("{" + loggerFake._name + "} " + msg).c_str());

#define LOG_DEBUG2(name, msg)   \
	log4cplus::Logger logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("DEBUG_INFO_MSGS"));  \
	LOG4CPLUS_DEBUG(logger, msg);



using namespace std;
class LogHelper
{
};

class Logger
{
public:
	Logger(const std::string& name) : _name(name)
	{
		log4cplus::initialize();
		log4cplus::PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT("urconfig.properties"));

		cout << "Logger:" << endl;
		cout << typeid(this).name() << endl;
		cout << typeid(Logger).name() << endl;
	}
	virtual ~Logger() {}
	virtual void Trace(const string& msg);
	virtual void Debug(const string& msg);
	virtual void Info(const string& msg);
	virtual void Warn(const string& msg);
	virtual void Error(const string& msg);
	virtual void Fatal(const string& msg);

private:
	std::string _name;
};

class A
{
public:
	void test()
	{
		test1();
	}
	virtual void test1()
	{

	}
	
};
class BB : public A
{
public:
	void test1() override
	{

		cout << typeid(this).name() << endl;
		cout << typeid(BB).name() << endl;
	}
};

class LoggerFactory
{
public:
	virtual ~LoggerFactory()
	{
	}

	static Logger* getLogger()
	{
		return getLogger("");
	}

	static Logger* getLogger(const char* name)
	{
		return getLogger(std::string(name));
	}

	static Logger* getLogger(const std::string& name)
	{
		map<string, Logger>::iterator it = _loggers.find(name);
		if (it != _loggers.end())
		{
			return &it->second;
		}
		else
		{
			_loggers.insert(std::pair<string, Logger>(name, Logger(name)));
			map<string, Logger>::iterator it = _loggers.find(name);
			if (it != _loggers.end())
			{
				return &it->second;
			}
			else
			{
				return nullptr;
			}
		}
	}

private:
	static map<string, Logger> _loggers;

};
