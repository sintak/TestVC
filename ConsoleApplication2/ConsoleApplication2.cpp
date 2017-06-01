// ConsoleApplication2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <map>  
#include <string>  
#include <iostream>  
#include <vector>
using namespace std;

int main()
{
	// ----------------------
	map<string, vector<int>> m1;
	map<string, vector<int>>::iterator m1It = m1.find("11");
	if (m1It != m1.end())
	{
		m1It->second.push_back(1177);
	}
	else
	{
		//m1.insert(std::pair<string, vector<int>>("11", 1177)); // 1177个元素，不是一个为1177的元素
		vector<int> v1;
		v1.push_back(1178);
		m1.insert(std::pair<string, vector<int>>("11", v1));
	}
	m1["22"].push_back(2288);  // 推荐这种方法
	m1["22"].push_back(2289);

	// ----------------------
	map<string, bool> printerState;
	//printerState.insert(std::pair<string, bool>("123", true));
	//printerState.insert(std::pair<string, bool>("123", false));
	printerState["123"] = false;
	printerState["123"] = true;
	printerState["123"] = false;
	printerState["456"] = false;
	printerState["78.1"] = true;
	bool state = printerState["fsdgda"];

	// ----------------------
	vector<int> ve;

	// ----------------------
	multimap<int, int> a;
	a.insert(pair<int, int>(1, 11));
	a.insert(pair<int, int>(1, 11));
	a.insert(pair<int, int>(1, 12));
	a.insert(pair<int, int>(1, 13));
	a.insert(pair<int, int>(2, 21));
	a.insert(pair<int, int>(2, 22));
	a.insert(pair<int, int>(3, 31));
	a.insert(pair<int, int>(3, 32));
	a.insert(pair<int, int>(1, 41));
	multimap<int, int>::iterator p_map;
	pair<multimap<int, int>::iterator, multimap<int, int>::iterator> ret;
	
	for (p_map = a.begin(); p_map != a.end();)
	{
		cout << p_map->first << " =>";
		ret = a.equal_range(p_map->first);
		for (p_map = ret.first; p_map != ret.second; ++p_map)
			cout << "" << p_map->second;//(*p_map).second; 一样的貌似。。。
		cout << endl;
	}
	system("pause");
    return 0;
}

