// eventTest.cpp : �������̨Ӧ�ó������ڵ㡣
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

