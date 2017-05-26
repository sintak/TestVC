// boostTest.cpp : 定义控制台应用程序的入口点。


#include "stdafx.h"
#include <iostream>	
#include <boost/thread.hpp>
#include <boost/asio.hpp>

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

void print(const boost::system::error_code& e,
	boost::asio::deadline_timer* t)
{
	//boost::thread::sleep(boost::get_system_time() + boost::posix_time::seconds(3));  // 在主线程中使用（子线程好像也可以）
	boost::this_thread::sleep(boost::posix_time::seconds(2));  // 这个方法只能在线程中用, 在主线程中用无效.
	cout << "ddd" << endl;
	t->expires_at(t->expires_at() + boost::posix_time::seconds(4));  // 间隔时间和执行时间，最后花费时间为长度大的那个时间
	t->async_wait(boost::bind(print, boost::asio::placeholders::error, t));
}
void test1()
{
	boost::asio::io_service io;
	boost::asio::deadline_timer t(io, boost::posix_time::seconds(4));
	t.async_wait(boost::bind(print, boost::asio::placeholders::error, &t));
	io.run();
}
int main()
{
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

	test1();
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