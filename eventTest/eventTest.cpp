// eventTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "TestClass.h"
#include "eventsTester.cpp"

int main()
{
	TestClass testObj;

	testObj.execute();
	testObj.stop();
	testObj.execute();

	system("pause");

	Subject printer;
	Observer v8Handler(&printer);
	printer.NewYearComing(2015);
 	printer.updateAge(31);
	system("pause");
	return 0;
}

