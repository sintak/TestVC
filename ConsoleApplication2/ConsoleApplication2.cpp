// ConsoleApplication2.cpp : �������̨Ӧ�ó������ڵ㡣
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

