// containerTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "TC_ThreadQueue.h"

int main()
{
	TC_ThreadQueue<int> q;
	q.push_back(3);
	q.push_back(5);
	

    return 0;
}

