// ConsoleApplication2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <map>  
#include <string>  
#include <iostream>  
#include <vector>
#include <Windows.h>
using namespace std;
typedef struct __WeightDataFlag2
{
	UINT8 unknow1 : 4;
	UINT8 isZero : 1;  // 1：当前重量为零。      0：当前重量非零。
	UINT8 isNetWeight : 1;  // 1：当前在去皮模式      0：没在去皮模式。
	UINT8 isWeightAbnormal : 1;  // 1：重量溢出，或没有开机归零。    0：重量正常且已经开机
	UINT8 unknow2 : 1;

} T__WeightDataFlag2, *PT__WeightDataFlag2;
typedef union _WeightDataFlag2
{
	UINT8 all;
	T__WeightDataFlag2 bits;
}T_WeightDataFlag2, PT_WeightDataFlag2;

#pragma pack(1)
typedef struct _WeightData
{
	UINT8 head1;
	UINT8 head2;
	UINT8 flag1;
	UINT8 sign;  // 符号：  ‘－’：重量为负。 ‘ ’：重量为正。
	char weight[6];
	UINT16 unit;
	UINT8 checkSum;
	UINT8 tail1;
	UINT8 tail2;
	T__WeightDataFlag2 flag2;
	//T_WeightDataFlag2 flag2;

} T_WeightData, *PT_WeightData;
#pragma pack()

#pragma pack(1)
typedef struct _ProtocolChangeWrap
{
	UINT8 stx;
	UINT16 cmd;
	UINT8 ext1;
	UINT8 ext2;

	static _ProtocolChangeWrap initiative() {
		_ProtocolChangeWrap wrap;
		wrap.stx = 0x3c;
		wrap.cmd = 0x50 << 8 | 0x42;
		wrap.ext1 = 0x3e;
		wrap.ext2 = 0x09;
		return wrap;
	}

	static _ProtocolChangeWrap passivity() {
		_ProtocolChangeWrap wrap;
		wrap.stx = 0x3c;
		wrap.cmd = 0x41 << 8 | 0x4c;
		wrap.ext1 = 0x3e;
		wrap.ext2 = 0x09;
		return wrap;
	}

} T_ProtocolChangeWrap, *PT_ProtocolChangeWrap;
#pragma pack()

void test(char data[], char* data2) {
	cout << data[0] << data2[1] << endl;
}

int main()
{
	// ----------------------
	// ----------------------
	// ----------------------
	// ----------------------
	char data1[2] = {'a', 'b'};
	test(data1, data1);
	// ----------------------


	T_ProtocolChangeWrap& wrap = T_ProtocolChangeWrap().initiative();
	char* buf = (char*)&wrap;
	unsigned char* buf1 = (unsigned char*)&wrap;

	unsigned char buf2[5];
	memcpy(buf2, &wrap, 5);


	T_ProtocolChangeWrap wrap1;
	wrap1.stx = 0x3c;
	wrap1.cmd = 0x41 << 8 | 0x4c;
	wrap1.ext1 = 0x3e;
	wrap1.ext2 = 0x09;
	char b[5];
	unsigned char b1[5];
	memcpy(b, &wrap1, 5);
	memcpy(b1, &wrap1, 5);

	int size = sizeof(T_ProtocolChangeWrap);
	int size1 = sizeof(T_WeightData);
	// ----------------------
	// char转string
	char a1 = 'b';
	cout << string(&a1);  // 没结束符，乱码
	// ----------------------

	map<string, bool> servicingPort;
	if (servicingPort["fdas"] == true)
	{

	}
	// ----------------------
	char data[] = { 0x01, 0x02 , 0x53 , 0x20 , 0x30 , 0x30 , 0x2E , 0x30  , 0x30 , 0x30 , 0x6B , 0x67 , 0x61 , 0x03 , 0x04 , 0x30 };
	PT_WeightData _data = (PT_WeightData)data;
	cout << sizeof(T_WeightData) <<endl;
	cout << _data->flag2.isZero << (_data->flag2.isNetWeight ? true : false) << _data->flag2.isWeightAbnormal  << endl;

	// ----------------------
	char c1[6] = { 0x30 , 0x30 , 0x2E , 0x30  , 0x30 , 0x30 };
	//char c1[] = "ABCDEF";
	char c = 0x41;
	string s1 = c1;
	cout << string(&c1[0], &c1[strlen(c1)]) << endl;  // not ok
	cout << string(&c1[0], &c1[6]) << endl;  // ok
	cout << string(c1, 6) << endl;  // ok
	cout << s1 << endl;  // not ok
	cout << c << endl;  // ok

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

