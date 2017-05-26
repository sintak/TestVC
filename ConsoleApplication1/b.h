#ifndef __BH__
#define __BH__
#pragma once
#include "a.h"
#include <string>

class BH
{
public:
	static int a;

};
int BH::a;

namespace Space
{
	class A
	{
	public:
		static int glaaa;
		static std::string set;
		void test()
		{
			glfun();
			MySpace::glfun();
		}
	};
	int A::glaaa = 123;
	std::string A::set;

	int glaaa;
}
#endif
