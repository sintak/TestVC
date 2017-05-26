// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <map>
#include <winsock.h>
#include <sstream>
#include <map>
#include <queue>
//#include "a.h"
//#include "b.h"
//#include <QCoreApplication>  
#include <crtdbg.h>  
using namespace std;

void test() {}

class A
{
public:
	static const char val[];

	void test()
	{
		//IamGDI();
	}

};

class AA : A
{
	AA()
	{
		test();
		this->test();

		::test();  // global
	}
};

static int work()
{
	return  0;
}

__interface  IWorker {
};

class WorkerBase
{
public:
	virtual void work() = 0;
};

class Worker : WorkerBase
{
	
};

// 传指针还是引用
//class AAA
//{
//public:
//	static constexpr int a { 123456 };
//	static int b;
//	void test()
//	{
//		cout << "AAA test()" << endl;
//	}
//};
//int AAA::b = 111111111111;
//void pointOrRef(AAA* paaa)
//{
//	
//}
//void pointOrRef(AAA& aaa)
//{
//
//}
//const char A::val[] = { 0x36, 0x37, 0x38 };  // 使用前要初始化，否则编译不过


class BBB
{
public:
	BBB()
	{   
		// not ok
		//Count = 0;
		//ipPrinters = vector<string>();
		//mapPrinter = map<string, string>();
	}

	static int Count;
	static vector<wstring> ipPrinters;

	static map<wstring, wstring> mapPrinter;
/*
	static int GetAge()
	{
		return _age;
	}
	static void SetAge(int age)
	{
		_age = age;
	}
private:
	static int _age;
*/
};
int BBB::Count;
vector<wstring> BBB::ipPrinters;
map<wstring, wstring> BBB::mapPrinter;



void testRef(BBB& bbb)
{
	
}

enum ErrorCode
{
	OK,
	FAILD
};
void testEnum(ErrorCode& errorCode)
{
	errorCode = FAILD;
}

int glaaa;

class AAB
{
public:
	AAB(int a) {  }
};

vector<string> getVector()
{
	vector<string> va;
	va.push_back("hello");
	return va;
}
string ltos(long l)
{
	ostringstream os;
	os << l;
	string result;
	istringstream is(os.str());
	is >> result;
	return result;
}


class OtherCls
{
public:
	OtherCls() {}
	OtherCls(string comment) : comment(comment) {  }
	string comment;
};


class Person
{
public:
	Person()
	{
		
	}
	virtual void say()
	{
		this->sayHello();
	}

	
protected:
	virtual void sayHello()
	{
		cout << "sayHello. i am Person" << endl;
	}
};

class XiaoMin : public Person
{
public:
	XiaoMin(OtherCls o) : otherClsRef(o)
	{
		this->otherCls = OtherCls("otherCls");
		this->pOtherCls = new OtherCls("pOtherCls*");
	}
	void say() override {

		this->sayHello();  // sayHello. i am XiaoMin


		(Person(*this)).say();  // sayHello. i am Person
		//((Person*)this)->say();//引起循环调用了，父->子->父->子->父->子->父->子->... 错误
		Person::say();			// sayHello. i am XiaoMin
	}

	OtherCls otherCls;
	OtherCls* pOtherCls;
	OtherCls& otherClsRef;

protected:
	void sayHello() override {
		cout << "sayHello. i am XiaoMin" << endl;
		
	}

};

// ----------- log scope start

#define BBBA AAAB
#define AAAB
class LogMessageVoidify {
public:
	LogMessageVoidify() { }
	// This has to be an operator with a precedence lower than << but
	// higher than ?:
	void operator&(std::ostream&) { }
};

class DestructOutput
{
public:
	DestructOutput()
	{

	}
	~DestructOutput()
	{
		//cout << "析构输出" << endl;
		cout << this->_stream.str() << endl;
	}

	std::ostream& stream() {
		return _stream;
	}

private:
	std::ostringstream _stream;

};

//#define LOGGG() (!(true) ? (void)0 : LogMessageVoidify() & (DestructOutput().stream()))



#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

typedef int LogSeverity;
const LogSeverity LOG_VERBOSE = -1;  // This is level 1 verbosity
									 // Note: the log severities are used to index into the array of names,
									 // see log_severity_names.
const LogSeverity LOG_INFO = 0;
const LogSeverity LOG_WARNING = 1;
const LogSeverity LOG_ERROR = 2;
const LogSeverity LOG_FATAL = 3;
const LogSeverity LOG_NUM_SEVERITIES = 4;

class LogMessage {
public:
	// Used for LOG(severity).
	LogMessage(const char* file, int line, LogSeverity severity);

	// Used for CHECK_EQ(), etc. Takes ownership of the given string.
	// Implied severity = LOG_FATAL.
	LogMessage(const char* file, int line, std::string* result);

	// Used for DCHECK_EQ(), etc. Takes ownership of the given string.
	LogMessage(const char* file, int line, LogSeverity severity,
		std::string* result);

	~LogMessage();

	std::ostream& stream() { return stream_; }

private:
	LogSeverity severity_;
	std::ostringstream stream_;

	// The file and line information passed in to the constructor.
	const char* file_;
	const int line_;

#if 1//defined(OS_WIN)
	// Stores the current value of GetLastError in the constructor and restores
	// it in the destructor by calling SetLastError.
	// This is useful since the LogMessage class uses a lot of Win32 calls
	// that will lose the value of GLE and the code that called the log function
	// will have lost the thread error value when the log call returns.
	class SaveLastError {
	public:
		SaveLastError();
		~SaveLastError();

		unsigned long get_error() const { return last_error_; }

	protected:
		unsigned long last_error_;
	};

	SaveLastError last_error_;
#endif

	DISALLOW_COPY_AND_ASSIGN(LogMessage);
};

#if 1//defined(OS_WIN)
LogMessage::SaveLastError::SaveLastError() : last_error_(::GetLastError()) {
}

LogMessage::SaveLastError::~SaveLastError() {
	::SetLastError(last_error_);
}
#endif  // defined(OS_WIN)

LogMessage::LogMessage(const char* file, int line, LogSeverity severity)
	: severity_(severity), file_(file), line_(line) {
}

LogMessage::LogMessage(const char* file, int line, std::string* result)
	: severity_(LOG_FATAL), file_(file), line_(line) {
	stream_ << "Check failed: " << *result;
	delete result;
}

LogMessage::LogMessage(const char* file, int line, LogSeverity severity,
	std::string* result)
	: severity_(severity), file_(file), line_(line) {
	stream_ << "Check failed: " << *result;
	delete result;
}

LogMessage::~LogMessage() {
	stream_ << std::endl;
	std::string str_newline(stream_.str());
	//cef_log(file_, line_, severity_, str_newline.c_str());
	cout << str_newline;
}
inline int GetMinLogLevel() {
	return 0;
}

#define COMPACT_GOOGLE_LOG_EX_INFO(ClassName, ...) \
  ClassName(__FILE__, __LINE__, LOG_INFO , \
                         ##__VA_ARGS__)

#define COMPACT_GOOGLE_LOG_INFO \
  COMPACT_GOOGLE_LOG_EX_INFO(LogMessage)




#define LAZY_STREAM(stream, condition)                                  \
  !(condition) ? (void) 0 : LogMessageVoidify() & (stream)

#define LOG_STREAM(severity) COMPACT_GOOGLE_LOG_ ## severity.stream()

#define LOG_IS_ON(severity) \
	((LOG_ ## severity) >= GetMinLogLevel())

#define LOG(severity) LAZY_STREAM(LOG_STREAM(severity), LOG_IS_ON(severity))

#define LOG_IF(severity, condition) \
  LAZY_STREAM(LOG_STREAM(severity), LOG_IS_ON(severity) && (condition))


#define LOG_INFO_RECEIVER_ LOG(INFO)
#define LOG_INFO_RECEIVER(name) LOG(INFO) << "{" << name << "}"

#define LOG_INFO_RECEIVER_IF(condition) LOG_IF(INFO, condition)


#define LOG_INFO_(name, msg) LOG(INFO) << "{" << name << "}" << msg
// ----------- log scope end
void testDestructOutput() {
	LOG_INFO_RECEIVER_IF(1 == 1) << "1==1";
	LOG_INFO_RECEIVER_IF(1 == 2) << "1==2";

	std::wstring ws = L"abcdefghij";
	std::string s = "我是string内容";
	string tmp;
	int nLen = (int)ws.length();
	tmp.resize(nLen, ' ');
	DWORD dwMinSize;
	dwMinSize = WideCharToMultiByte(CP_OEMCP, NULL, ws.c_str(), -1, NULL, 0, NULL, FALSE);
	tmp.resize(dwMinSize, ' ');
	int nResult = WideCharToMultiByte(CP_OEMCP, NULL, ws.c_str(), -1, (LPSTR)tmp.c_str(), dwMinSize, NULL, FALSE);

	/*int nLen = (int)ws.length();
	tmp.resize(nLen, ' ');

	int nResult = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)ws.c_str(), nLen, (LPSTR)tmp.c_str(), nLen, NULL, NULL);*/

	LOG_INFO_RECEIVER("") << "测试LOG_INFO_RECEIVER" << s << tmp;
	LOG_INFO_("testDestructOutput", "测试LOG_INFO_");
	LOG_INFO_("testDestructOutput", "测试LOG_INFO_") << "1234";

	//LOGGG() << "abcdefg" << 123;
	//DestructOutput d;  //  [DestructOutput d();不是定义对象。是声明有一个返回T类型的d函数而已]
	cout << "testDestructOutput end" << endl;

	/*wostringstream a; a << "abcdefg" << "我是";
	cout << "";*/

}
typedef struct _RollPara {
	char rpMM;
	char rpTimes;
} T_RollPara, *PT_RollPara;

typedef struct _CutPara {
	char cp;
} T_CutPara, *PT_CutPara;

typedef struct _ZoomPara {
	char inWidth;
	char inHeight;
	char in;
	char underLine;
} T_ZoomPara, *PT_ZoomPara;
typedef struct _DevConfig {
	char roll[3];
	T_RollPara rollPara;
	char cut[3];
	T_CutPara cutPara;
	char zoom[3];
	char align[3];
	T_ZoomPara zoomPara;
	char img[8];
	char imgPrint[3];
	char cashdraw[5];
	char beep[5];
}T_DevConfig, *PT_DevConfig;
typedef struct _Printer {
	HANDLE handle;
	wstring model;
	T_DevConfig devConfig;
}T_Printer, *PT_Printer;

class PrinterBase {
public:

	static map<wstring, T_Printer> mapPrinter;
	
};
map<wstring, T_Printer> PrinterBase::mapPrinter;

char* ws2s(const wstring &wstr)
{
	int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), NULL, 0, NULL, NULL);
	char* buffer = new char[len + 1];

	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), buffer, len, NULL, NULL);
	buffer[len] = '\0';

	return buffer;
}

void decodeConfigCmd(char tmp[], const int len, wchar_t cmd[])
{
	//MessageBox(NULL, cmd.data(), L"", MB_OK | MB_SYSTEMMODAL);
	char *s = ws2s(cmd);

	const char *split = ",";
	char *stmp = strtok(s, split);

	int i = 0;

	while (stmp != NULL) {
		if (i == len)
			break;
		tmp[i] = atoi(stmp);
		i++;
		stmp = strtok(NULL, split);
	}

	stmp = nullptr;
	delete[]stmp;
	delete[]s;
}
bool s2ws(const string &str, wstring &wstr)
{
	DWORD dwMinSize;
	dwMinSize = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
	dwMinSize--;
	wstr.resize(dwMinSize, L' ');

	int nResult = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)str.c_str(), -1, (LPWSTR)wstr.c_str(), dwMinSize);

	if (nResult == 0)
	{
		return false;
	}

	return true;
}
bool ws2s(const wstring &wstr, string &str)
{
	int nLen = (int)wstr.length();
	str.resize(nLen, ' ');

	DWORD dwMinSize;
	dwMinSize = WideCharToMultiByte(CP_OEMCP, NULL, wstr.c_str(), -1, NULL, 0, NULL, FALSE);
	dwMinSize--;
	str.resize(dwMinSize, ' ');
	int nResult = WideCharToMultiByte(CP_OEMCP, NULL, wstr.c_str(), -1, (LPSTR)str.c_str(), dwMinSize, NULL, FALSE);

	if (nResult == 0)
	{
		return false;
	}

	return true;
}
int main()
{

	//_CrtSetBreakAlloc( 178 );//通过把内存id填入，可调试看到在哪里开辟的内存  

	char *mem_leak_ptr = new char[100];
	
	_CrtDumpMemoryLeaks();//打印现时已分配的(未释放的)内存 

	delete mem_leak_ptr;
	mem_leak_ptr = nullptr;
	_CrtDumpMemoryLeaks(); 

	// -----------queue
	queue<int> q;
	q.push(3);
	q.push(4);
	q.push(5);
	q.push(6);
	q.push(7);
	q.push(8);
	q.push(9);

	cout << q.front() << endl;
	cout << q.front() << endl;
	q.pop();
	cout << q.front() << endl;

	_CrtDumpMemoryLeaks();// 

	// -----------tuple
	tuple<int, int> tpl = { 3, 5 };
	cout << get<0>(tpl) << " " << get<1>(tpl) << endl;
	get<0>(tpl) = 6;	
	cout << get<0>(tpl) << " " << get<1>(tpl) << endl;
	get<0>(tpl)++;
	cout << get<0>(tpl) << " " << get<1>(tpl) << endl;

	//定义一个map</span>  
	map<string, string> mapTelDir;

	//用[]操作符可以方便快速的给map添加内容  
	mapTelDir["StarLee"] = "13813131313";
	mapTelDir["dasfs"] = "13513131313";

	//修改关键码为LiXing的值  
	//注意，这里的关键码在map里面并不存在  
	if (mapTelDir["LiXing"] != "13913131316")
	{
		mapTelDir["LiXing"] = "13513131316";
	}
	//输出  
	cout << "The5 cellhone number of LiXing is: " << mapTelDir["LiXing"] << endl;
	T_Printer pr1;
	//wchar_t tmp[32];
	//decodeConfigCmd(pr1.devConfig.roll, 3, tmp);

	PrinterBase::mapPrinter.insert(pair<wstring, T_Printer>(L"name1", pr1));
	T_Printer pr2;
	//pr2.devConfig.roll = {0x1, 0x2, 0x3};
	PrinterBase::mapPrinter.insert(pair<wstring, T_Printer>(L"name2中文", pr2));
	
	//memset(&PrinterBase::mapPrinter[L"name1"].devConfig, 0, sizeof(PrinterBase::mapPrinter[L"name1"].devConfig));
	string name1 = "name2中文";
	wstring name = L"name2中文";
	wstring tmpName;
	s2ws(name1, tmpName);
	string tmpsName;
	ws2s(name, tmpsName);
	
	wstring oName = name + L'\0';

	const wstring& nameRef = name;
	T_Printer tp = PrinterBase::mapPrinter[tmpName];

	//memset(&PrinterBase::mapPrinter[L"name2"].devConfig, 0, sizeof(PrinterBase::mapPrinter[L"name2"].devConfig));
	int c1 = sizeof(PrinterBase::mapPrinter[L"name2"].devConfig);
	int c2 = sizeof(T_DevConfig);

	T_Printer tp1 = PrinterBase::mapPrinter[L"name1"];
	T_Printer tp2 = PrinterBase::mapPrinter[L"name2"];


	std::map<wstring, int> map1;
	map1.insert(pair<wstring, int>(L"name1", 1));
	map1.insert(pair<wstring, int>(L"name2", 2));
	map1.insert(pair<wstring, int>(L"name1", 3));

	int a1 = map1[L"name1"];
	int a2 = map1[L"name2"];

	testDestructOutput();

	wstring aab= L"123456";
	cout << aab.length() << " " << aab.size() << " " << sizeof(aab) << endl;
	/*new OtherCls();
	char c[128] = "12345";
	char* cc = "12345";
	cout << sizeof(c) << ";" << c << ";" << sizeof(cc) << endl;
	strcpy_s(c, "abcdefg");
	cout << c <<endl;
	strcpy_s(c, 50, "abcdefghi");
	cout << c << ";"<<endl;*/

/*
	string ssss = "3";
	cout << typeid(ssss).name() << "  " << typeid(string).name() << endl;
*/
	//int iss = static_cast<int>(ssss);
	OtherCls o("otherClsRef");
	Person* p = new XiaoMin(o);
	p->say();
	OtherCls o1("otherClsRef1");
	XiaoMin* p1 = new XiaoMin(o1);
	cout << p1->otherCls.comment << endl;  //  正常
	//cout << p1->otherClsRef.comment << endl;  //  奔潰

	//cout << ltos(1) << " " << ltos(123) << " " << ltos(-1).data() << endl;
	///////

	//cout << (int)(unsigned char)1234 << endl;  // -46()
	//cout << (unsigned int)(unsigned char)1234 << endl;  // 4294967250

	//cout << (int)(unsigned char)123 << endl;  // 123
	//cout << (unsigned int)(unsigned char)123 << endl;  // 123


	//auto c1 = (unsigned char)-1;
	//auto c2 = (char)-1;
	//cout << (int)c1 << ":" << (int)c2 << endl;
	//cout << (unsigned char)-1 << ":" << (char)-1 << endl;

	//vector<string> va = getVector();
	//cout << va.at(0).c_str() << endl;
	//////
	//auto aab =new AAB(1);
	//cout << (new AAA())->a << endl;
	//AAA::a = 654321;
/*
	cout << AAA::a << endl;

	AAA::b = 2222222;
	cout << AAA::b << endl;*/

	/////
	//new BH();
	//auto set = Space::A::set;

	/////////
	//glaaa = 3;
	//MySpace::glaaa = 4;
	//glfun(); 

	//(new Space::A())->test();

	// IN OUT
	/*string s = "fasdf";

	BBB* bbb = new BBB;
	testRef(*bbb);
	delete bbb;

	ErrorCode errorCode = OK;
	cout << "errorCode: " << errorCode << endl;
	testEnum(errorCode);
	cout << "errorCode: " << errorCode << endl;*/
	// Interace
	//IPrint *printer = new Printer();  // 错误
	//IPrint *printer1 = new Printer1();
	//printer1->doPrintTask();
	//Printer().doPrintTask();
	//auto* pp = static_cast<Printer1*>(printer1);
		//delete printer1;

	//////////////// 传指针还是引用
	//auto paaa = new AAA();
	//pointOrRef(paaa);
	//AAA aaa;
	//pointOrRef(aaa);

	/////////////
	//BBB::Count = 4;
	//cout << "BBB:Cout = " << BBB::Count << endl;
	//
	////cout << "BBB:AGE = " << BBB::GetAge();

	//BBB::ipPrinters.push_back(L"ip1");
	//BBB::ipPrinters.push_back(L"ip2");

	//BBB::mapPrinter.insert(make_pair(L"key1", L"value1"));
	//auto result = BBB::mapPrinter.insert(make_pair(L"key2", L"value2")).second;
	//result ? cout << "插入成功" : cout << "插入失败";
	//auto result2 = BBB::mapPrinter.insert(make_pair(L"key2", L"value3")).second;
	//result2 ? cout << "插入成功" : cout << "插入失败";

	//for (auto it= BBB::ipPrinters.begin(); it != BBB::ipPrinters.end(); ++it)
	//{
	//	cout << it->c_str() << endl;
	//}
	//for (auto it = BBB::mapPrinter.begin(); it != BBB::mapPrinter.end(); ++it)
	//{
	//	cout << it->first.c_str() << ":" << (*it).second.c_str() << endl;
	//}
	//for (unsigned int i = 0; i < BBB::ipPrinters.size(); i++)
	//{
	//	auto sss = BBB::ipPrinters[i];

	//	cout << "for int i=0  : " << BBB::ipPrinters[i].c_str() << endl;
	//}

	//try
	//{
	//	cout << "BBB::ipPrinters.at(2).c_str(): " << BBB::ipPrinters.at(2).c_str() << endl;

	//}
	//catch (exception &e)
	//{
	//	cout << "输出错误，信息：" << e.what() << endl;
	//}
	//cout << "BBB::ipPrinters.at(2).c_str(): " << BBB::ipPrinters.at(1).c_str() << endl;

	//////////////
	//WorkerBase worker = new Worker();


	//////////////
	//std::cout << "hello world";

	//cout << sizeof(A::val);

	//for (auto v_element : A::val)
	//{
	//	cout << v_element << "," << endl;
	//}
	//cout << A::val;




	//vector<string> vs;
	//vs.push_back("hello vector1");
	//vs.push_back("hello vector2");

	//for (auto it = vs.begin(); it != vs.end(); ++it)
	//{
	//	cout << it->c_str() << endl;
	//}

	//for (auto it = vs.begin(); it != vs.end(); )
	//{
	//	cout << it->c_str() << endl;
	//	it = vs.erase(it);
	//}


	//for (auto it = vs.begin(); it != vs.end(); ++it)
	//{
	//	cout << it->c_str() << endl;
	//}


	//// -------
	//string arr[4] = { "hello","world","name","address" };
	//vector<string> ivec(arr, arr + 4);
	//auto cc = arr + 4;
	//cout << "cc: " << cc << cc->c_str() << endl;
	//for (vector<string>::iterator iter1 = ivec.begin(); iter1 != ivec.end(); ++iter1) {
	//	for (vector<string>::size_type sty = 0; sty != (*iter1).size(); ++sty) {
	//		//cout<<(*iter1).size()<<endl;//这句意义不明
	//		cout << (*iter1)[sty] << endl;//cout<<iter1[sty]<<endl;//应先通过迭代器寻址再使用[]算符
	//	}
	//}

	system("pause");

	//char Count;
	//std::cin >> Count;
	//return 0;
}

