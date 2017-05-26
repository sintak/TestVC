// exceptionTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

//customized exception class 'myException'    
class myException :public exception
{
public:
	const char* what()const throw()
	{
		return "ERROR! Don't divide a number by integer zero.\n";
	}
};
void check(int y) //any type of exception is permitted    
{
	if (y == 0) throw myException();
}
void myUnexpected()
{
	cout << "Unexpected exception caught!\n";
	system("pause");
	exit(-1);
}
void myTerminate() //##1 set it be the terminate handler    
{
	cout << "Unhandler exception!\n";
	system("pause");
	exit(-1);
}
//entry of the application    
int main()
{
	unexpected_handler oldHandler = set_unexpected(myUnexpected);
	terminate_handler preHandler = set_terminate(myTerminate);
	int x = 100, y = 0;
	try
	{
		check(y);
		cout << x / y;
	}
	catch (int &e) //no catch sentence matches the throw type    
	{
		cout << e << endl;
	}
	system("pause");
	return 0;
}

//
//class A
//{
//public:
//	void test()
//	{
//		try
//		{
//			cout << "cccccc" << endl;
//			throw exception("cccccc");
//
//		}
//		catch (...)
//		{
//		}
//
//
//		try
//		{
//			// malloc1
//			//throw exception();
//			cout << "malloc1" << endl;
//			try
//			{
//				// do2
//				throw exception();
//				cout << "do2" << endl;
//			}
//			catch (...)
//			{
//			}
//
//			// free1
//			cout << "free1" << endl;
//		}
//		catch (...)
//		{
//		}
//
//		cout << "end" << endl;
//
//	}
//};
//
//int main()
//{
//	string a = "fasdfas";
//	cout << a.size() << " " << a.length() << endl;
//
//	A().test();
//
//	try
//	{
//
//		int a = 0;
//		//int b = 3 / a;
//		throw exception("aaaaaaaaaaa");
//	}
//	catch (const std::exception& e)
//	{
//		cout << e.what() << endl;
//	}
//	catch(...)  // 漏掉的异常才来到这里
//	{
//		cout << "bbbbb" << endl;
//
//	}
//
//	/*__try
//	{
//
//	}
//	__finally
//	{
//		
//	}*/
//	
//	//try
//	//{
//	//	// malloc1
//	//	cout << "mallco1" << endl;
//	//	__try
//	//	{
//	//		// do2
//	//		cout << "do2" << endl;
//
//	//	}
//	//	__finally
//	//	{
//	//		// free1
//	//		cout << "free1" << endl;
//
//	//	}
//	//}
//	//catch (...)
//	//{
//	//}
//
//	/*__try
//	{
//
//	}
//	__except (1)
//	{
//	}*/
//
//	//domain_error
//	system("pause");
//    return 0;
//}
//
