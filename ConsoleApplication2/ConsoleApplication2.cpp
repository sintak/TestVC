// ConsoleApplication2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

class TT
{
public:
	string name;
};

class A
{
public:
	A()
	{
		this->name = "fds";
	}
private:
	string name;
};

class AA : A
{
public:
	AA()
	{
		
	}
};

int main()
{
	new AA();

    return 0;
}

