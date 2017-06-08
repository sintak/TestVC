// boostTest.cpp : 定义控制台应用程序的入口点。


#include "stdafx.h"

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

#include <sstream>
#include <fstream>
#include <string>
#include <tchar.h>
#include <Windows.h>
#include <ShellAPI.h>
#include <winspool.h>
#include <WinSock2.h>
#include <IPHlpApi.h>
#include <stdlib.h>
#include <cctype>
#include <algorithm>
#include <list>
#include <Commdlg.h>

#include <iostream>	
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

using namespace std;
//
//void mythread(const string& s1, string& s2)
//{
//	cout << " hello,thread! " << s1  <<" : "<< s2 << endl;
//}
//
//class A
//{
//public:
//
//	void mythread1(string s1, string s2)
//	{
//		cout << " hello,thread! " << s1 << " : " << s2 << endl;
//	}
//
//	void doWork() 
//	{
//		string s2 = "def";
//		boost::thread t(boost::bind(&(A::mythread1), "abc", s2));
//		cout << " thread is over! " << endl;
//
//	}
//
//};
//int main()
//{
//	string s2 = "def";
//
//	//boost::function<void()> f(mythread);
//	//boost::function<void(string, string)> f = boost::bind(mythread, "abc", "def");
//	boost::thread t(boost::bind(mythread, "abc", s2));
//
//	//boost::thread t(f);
//	//t.join();
//	cout << " thread is over! " << endl;
//
//	(new A())->doWork();
//
//	getchar();
//
//	return 0;
//}

//class HelloWorld
//{
//public:
//    void hello(const std::string& str, int a)
//    {
//        std::cout<<str<<std::endl;
//        a++;
//        std::cout<<a;
//    }
// 
//};
//int main()
//{
//    HelloWorld obj;
//    boost::thread thrd(boost::bind(&HelloWorld::hello, &obj, "Hello World, I'm a thread!",5));
//    thrd.join();
//    system("pause");
//    return 0;
//}



//boost::function<void()> f(myFun123);
//thread t(f);
//boost::function<void(const CefV8ValueList& arguments, bool& isOK, ErrorCode& ec)> f(PrintTaskHandler::doPrintTask);
//boost::function0<void(const CefV8ValueList& arguments, bool& isOK, ErrorCode& ec)> f = boost::bind(doPrintTask, arguments, isOK, ec);
//thread t(f, arguments, isOK, ec);
//thread t(boost::bind(PrintTaskHandler::doPrintTask, arguments, isOK, ec));
//t.timed_join(boost::posix_time::seconds(3));

//boost::thread t(boost::bind(doPrintTask, arguments, isOK, ec));
//boost::thread t1(boost::bind(&PrintTaskHandler::doPrintTask, this, arguments, isOK, ec));
//t.join();
// OT => Object Type
// RT => Return Type
// A ... => Arguments
template<typename OT, typename RT, typename ... A>
struct lambda_expression {
	OT _object;
	RT(OT::*_function)(A...)const;

	lambda_expression(const OT & object)
		: _object(object), _function(&decltype(_object)::operator()) {}

	RT operator() (A ... args) const {
		return (_object.*_function)(args...);
	}
};
auto noncapture_lambda() {
	auto lambda = [](int x, int z) {
		return x + z;
	};
	return lambda_expression<decltype(lambda), int, int, int>(lambda);
}
class HelloWorld
{
public:

	void hello(const std::string& str, int a)
	{
		//auto func = +[](int *sender, int age) {};
		boost::mutex::scoped_lock lock(_mutex);

		//OutputDebugString(L"doPrintTask sleep");
		//boost::this_thread::sleep(boost::posix_time::seconds(5));
		//OutputDebugString(L"doPrintTask sleep end");

		boost::this_thread::sleep(boost::posix_time::seconds(2));


		std::cout << str << std::endl;
		a++;
		std::cout << a;
	}

	void doWork()
	{
		boost::thread thrd(boost::bind(&HelloWorld::hello, this, "Hello World, I'm a thread!", 5));

	}

private:
	boost::mutex _mutex;

};
int z = 99;
class Ob {
public:
	int a;
	Ob(int a)
	{
		this->a = a;
	}
};
void itPlus() {
}
map<string, int> gm;
class LambdaThreadTester {
public:
	void test() {
		/*int a = 3;
		int b = 4;*/
		int c = 5;
		Ob ob(13);
		/*boost::thread t([a, b](int& c) {
		c = c + 1;
		cout << a << " " << b << " " << c << endl;
		}, c);*/  // 参数引用传递，不行
		/*boost::thread t([a, b](int* c) {
			*c = *c+ 1;
			cout << a << " " << b << " " << *c << endl;
		}, &c);
		t.join();*/ // 指针方式传递可以
		//boost::thread t([this, a, b, &c](int z1, int oba) {  // int z1：非局部变量无法捕获，需要用参数传递。或者捕获复杂对象参数比较方便
		//	++c;
		//	cout << a << " " << b << " " << c << z1 << endl;
		//	this->test1();

		//	boost::this_thread::sleep(boost::posix_time::seconds(5));
		//}, z, ob.a);  // 引用捕获形式，ok
		//t.join();
		cout << c << endl;


		//map<int, int> m;
		//m.insert(std::pair<int, int>(11, 114));
		//m.insert(std::pair<int, int>(12, 115));
		//map<int, int>::iterator it = m.begin();
		//std::function<void(map<int, int>::iterator)> func = [](map<int, int>::iterator it) {  //错误？迭代器不支持多线程？
		//	cout << it->second << endl;
		//	++it;
		//	cout << it->second << endl;
		//};
		////func();
		//boost::thread t2(func, it);

		map<string, int>::iterator gmIt = gm.find("27");

		gm["12"] = 33;
		gm["13"] = 44;
		gm["14"] = 55;

		for (int i = 0; i < 200; i++)
		{
			boost::thread t3([]() {
				cout << gm["12"] << gm["13"] << endl;
			});

		}



		/*boost::thread t1([&it]() mutable {
			cout << it->second << endl;
			++it;
			cout << it->second << endl;
		});*/
	}

	void test1() {
		cout << "I am test1" << endl;
	}

	void test2() {
		cout << "I am test2" << endl;
	}
};

//void print(const boost::system::error_code& e,
//	boost::asio::deadline_timer* t)
//{
//	//boost::thread::sleep(boost::get_system_time() + boost::posix_time::seconds(3));  // 在主线程中使用（子线程好像也可以）
//	boost::this_thread::sleep(boost::posix_time::seconds(2));  // 这个方法只能在线程中用, 在主线程中用无效.
//	cout << "ddd" << endl;
//	t->expires_at(t->expires_at() + boost::posix_time::seconds(4));  // 间隔时间和执行时间，最后花费时间为长度大的那个时间
//	t->async_wait(boost::bind(print, boost::asio::placeholders::error, t));
//}
//void test1()
//{
//
//	boost::asio::io_service io;
//	boost::asio::deadline_timer t(io, boost::posix_time::seconds(4));
//	t.async_wait(boost::bind(print, boost::asio::placeholders::error, &t));
//	io.run();
//
//}


int main()
{

	boost::asio::io_service io;
	boost::asio::serial_port sp(io, "COM2");

	boost::thread t([]() {
		LambdaThreadTester lt;
		lt.test();
	});

	//HelloWorld hw;
	//hw.doWork();
	//hw.doWork();

	////boost::this_thread::sleep(boost::posix_time::seconds(1));
	////(new HelloWorld())->doWork();
	//system("pause");
/*
	boost::asio::io_service io;
	boost::asio::deadline_timer timer(io, boost::posix_time::seconds(5));

	timer.async_wait(&print);
	io.run();*/

	//test1();
	system("pause");
	return 0;
}
//
//const int BUF_SIZE = 10;
//const int ITERS = 100;
//boost::mutex io_mutex;
//class buffer
//{
//public:
//	typedef boost::mutex::scoped_lock
//		scoped_lock;
//	buffer()
//		: p(0), c(0), full(0)
//	{
//	}
//	void put(int m)
//	{
//		scoped_lock lock(mutex);
//		if (full == BUF_SIZE)
//		{
//			{
//				boost::mutex::scoped_lock
//					lock(io_mutex);
//				std::cout <<
//					"Buffer is full. Waiting..."
//					<< std::endl;
//			}
//			while (full == BUF_SIZE)
//				cond.wait(lock);
//		}
//		buf[p] = m;
//		p = (p + 1) % BUF_SIZE;
//		++full;
//		cond.notify_one();
//	}
//	int get()
//	{
//		scoped_lock lk(mutex);
//		if (full == 0)
//		{
//			{
//				boost::mutex::scoped_lock
//					lock(io_mutex);
//				std::cout <<
//					"Buffer is empty. Waiting..."
//					<< std::endl;
//			}
//			while (full == 0)
//				cond.wait(lk);
//		}
//		int i = buf[c];
//		c = (c + 1) % BUF_SIZE;
//		--full;
//		cond.notify_one();
//		return i;
//	}
//private:
//	boost::mutex mutex;
//	boost::condition cond;
//	unsigned int p, c, full;
//	int buf[BUF_SIZE];
//};
//buffer buf;
//void writer()
//{
//	for (int n = 0; n < ITERS; ++n)
//	{
//		{
//			boost::mutex::scoped_lock
//				lock(io_mutex);
//			std::cout << "sending: "
//				<< n << std::endl;
//		}
//		buf.put(n);
//	}
//}
//void reader()
//{
//	for (int x = 0; x < ITERS; ++x)
//	{
//		int n = buf.get();
//		{
//			boost::mutex::scoped_lock
//				lock(io_mutex);
//			std::cout << "received: "
//				<< n << std::endl;
//		}
//	}
//}