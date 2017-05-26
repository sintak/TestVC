#ifndef __AH__
#define __AH__
#pragma once
#include <string>
using namespace std;
class AH
{
public:
	static int a;
};
int AH::a;

std::string set;

void glfun() {}

namespace MySpace {
	int glaaa;
	void glfun() {}
}
namespace Space1
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

#endif  // __AH__
