// ConsoleApplication2.cpp : �������̨Ӧ�ó������ڵ㡣
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
	UINT8 isZero : 1;  // 1����ǰ����Ϊ�㡣      0����ǰ�������㡣
	UINT8 isNetWeight : 1;  // 1����ǰ��ȥƤģʽ      0��û��ȥƤģʽ��
	UINT8 isWeightAbnormal : 1;  // 1�������������û�п������㡣    0�������������Ѿ�����
	UINT8 unknow2 : 1;

} T__WeightDataFlag2, *PT__WeightDataFlag2;
typedef union _WeightDataFlag2
{
	UINT8 all;
	T__WeightDataFlag2 bits;
}T_WeightDataFlag2, PT_WeightDataFlag2;
typedef struct _WeightData
{
	UINT8 head1;
	UINT8 head2;
	UINT8 flag1;
	UINT8 sign;  // ���ţ�  ������������Ϊ���� �� ��������Ϊ����
	char weight[6];
	UINT16 unit;
	UINT8 checkSum;
	UINT8 tail1;
	UINT8 tail2;
	T__WeightDataFlag2 flag2;
	//T_WeightDataFlag2 flag2;

} T_WeightData, *PT_WeightData;

int main()
{
	// ----------------------
	// ----------------------
	// ----------------------
	// ----------------------
	// ----------------------
	// ----------------------
	// charתstring
	char a1 = 'b';
	cout << string(&a1);
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
		//m1.insert(std::pair<string, vector<int>>("11", 1177)); // 1177��Ԫ�أ�����һ��Ϊ1177��Ԫ��
		vector<int> v1;
		v1.push_back(1178);
		m1.insert(std::pair<string, vector<int>>("11", v1));
	}
	m1["22"].push_back(2288);  // �Ƽ����ַ���
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
			cout << "" << p_map->second;//(*p_map).second; һ����ò�ơ�����
		cout << endl;
	}
	system("pause");
    return 0;
}

