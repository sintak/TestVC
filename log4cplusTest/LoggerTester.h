#pragma once
#include "LogHelper.h"

class LoggerTester
{
public:
	void test()
	{
		//this->_logger （static const对象点不出方法？）
			
	}
private:
	static const Logger _logger;
};
