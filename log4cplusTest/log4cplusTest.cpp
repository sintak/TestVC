// log4cplusTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

#include <log4cplus/logger.h>  
#include <log4cplus/fileappender.h>  
#include <log4cplus/consoleappender.h>  
#include <log4cplus/layout.h>  
#include <log4cplus/ndc.h>  
#include <log4cplus/helpers/loglog.h>  
#include <log4cplus/loggingmacros.h>  
#include <log4cplus/configurator.h>
#include "LogHelper.h"
#include <windows.h>
#define CONNNN(s1, s2) "[]"+ s1   + "[ ]"##s2

#define LOGGER_INIT()    \
	log4cplus::initialize();    \
	log4cplus::PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT("urconfig.properties"));


#define ADDITION_OUTPUT(name, msg)    \
	stringstream ss;    \
	ss << "{"<< name << "}" << msg;    \
	string str = ss.str(); \
	wstring wstr;  \
	DWORD dwMinSize;    \
	dwMinSize = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);    \
	wstr.resize(dwMinSize, L' ');    \
	MultiByteToWideChar(CP_ACP, 0, (LPCSTR)str.c_str(), -1, (LPWSTR)wstr.c_str(), dwMinSize); \
	OutputDebugString(wstr.c_str());


#define LOG_PATTERN

//#define LOG_DEBUG(msg)      \
//		ADDITION_OUTPUT(msg); \
//		log4cplus::Logger logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("DEBUG_INFO_MSGS"));  \
//		LOG4CPLUS_DEBUG(logger, ("{" + std::string(typeid(this).name()) + "} " + msg).c_str()); 

#define LOG_DEBUG(name, msg)      \
		ADDITION_OUTPUT(name, msg); \
		log4cplus::Logger logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("DEBUG_INFO_MSGS"));  \
		LOG4CPLUS_DEBUG(logger, ("{" + std::string(name) + "} " + msg).c_str()); 

#define LOG_INFO LOG_DEBUG
	

class ABAB
{
public:
	void test()
	{
		//string name;
		//log4cplus::Logger logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("DEBUG_INFO_MSGS")); 
		//LOG4CPLUS_DEBUG(logger, name.c_str());

		//string s;

		LOG_DEBUG(typeid(this).name(),"测试输出");

	}
};

int main()
{
	/*string s = "abc";
	const char* ss = "aabbcc";
	cout << CONNNN(string(ss), "efg");
	cout << CONNNN(s, "efg");*/

	//const std::wstring file_name = _T("log.txt");

	//log4cplus::initialize();

	//log4cplus::helpers::LogLog::getLogLog()->setInternalDebugging(true);

	//log4cplus::SharedAppenderPtr append_1(new log4cplus::FileAppender((file_name), std::ios::trunc, true));
	//append_1->setName(LOG4CPLUS_TEXT("main"));

	//log4cplus::SharedAppenderPtr pConsoleAppender(new log4cplus::ConsoleAppender());

	//log4cplus::Logger::getRoot().addAppender(append_1);
	//log4cplus::Logger::getRoot().addAppender(pConsoleAppender);

	//// %d{%m/%d/%y %H:%M:%S,%Q} [%t] %-5p - %m%n
	//std::auto_ptr<log4cplus::Layout> pPatternLayout(new log4cplus::PatternLayout(_T("%d{%y-%m-%d %H:%M:%S,%Q} [%t] %-5p - %m [%l]%n")));
	//append_1->setLayout(pPatternLayout);

	//log4cplus::Logger root = log4cplus::Logger::getRoot();

	//root.setLogLevel(log4cplus::ALL_LOG_LEVEL);

	//LOG4CPLUS_TRACE(log4cplus::Logger::getRoot(), "ABC");

	//LOG4CPLUS_TRACE(Logger::getRoot(), "info")
	//LOG4CPLUS_DEBUG(Logger::getRoot(), "info")
	//LOG4CPLUS_INFO(Logger::getRoot(), "info")
	//LOG4CPLUS_WARN(Logger::getRoot(), "info")
	//LOG4CPLUS_ERROR(Logger::getRoot(), "info")
	//LOG4CPLUS_FATAL(Logger::getRoot(), "info")

	//    

	log4cplus::initialize();
	log4cplus::PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT("urconfig.properties"));

	//ABAB().test();

	////入root的logger写入记录
	//log4cplus::Logger root = log4cplus::Logger::getRoot();
	//LOG4CPLUS_FATAL(root, "向all_msgs.log文件中写入信息，因为向root，自动往所有的字文件写入!");

	////只向log4cplus.logger.trace_msgs      = TRACE,TRACE_MSGS对应的
	////log4cplus.appender.TRACE_MSGS文件写入日志
	//log4cplus::Logger logger1 = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("TRACE_MSGS"));
	//LOG4CPLUS_TRACE(logger1, "只向all_msgs.log或trace_msgs.log文件写入日志!");

	//log4cplus::Logger logger2 = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("DEBUG_INFO_MSGS"));
	//LOG4CPLUS_DEBUG(logger2, "只向all_msgs.log或debug_info_msgs.log文件写入日志!");
	//LOG4CPLUS_INFO(logger2, "只向all_msgs.log或debug_info_msgs.log文件写入日志!");

	//log4cplus::Logger logger3 = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("WARN_ERROR_MSGS"));
	//LOG4CPLUS_WARN(logger3, "只向all_msgs.log或warn_error_msgs.log文件写入日志!");
	//LOG4CPLUS_ERROR(logger3, "只向all_msgs.log或warn_error_msgs.log文件写入日志!");

	log4cplus::Logger logger4 = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("FATAL_MSGS"));
	LOG4CPLUS_DEBUG(logger4, "只向all_msgs.log或fatal_msgs.log文件写入日志! FATAL");
	LOG4CPLUS_FATAL(logger4, "只向all_msgs.log或fatal_msgs.log文件写入日志!");

	//log4cplus::Logger logger2 = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("debug_msgs"));
	//LOG4CPLUS_DEBUG(logger2, "只向all_msgs.log文件或控制台写入日志!");


	/*std::cout << typeid(log4cplus::Logger).name() << " " << typeid(log4cplus::Logger).raw_name() << endl;


	Logger* lll = LoggerFactory::getLogger("ClassName");
	Logger* lll2 = LoggerFactory::getLogger("ClassName2");
	Logger* llll = LoggerFactory::getLogger("ClassName");

	lll->Debug("lll使用LoggerFactory");
	lll2->Debug("lll2使用LoggerFactory");
	Logger LLL2 = *lll2;

	A* aa = new BB;
	aa->test();
	(new BB())->test();*/


	return 0;
}

