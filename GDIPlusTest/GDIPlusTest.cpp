// GDIPlusTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include<windows.h>
#define ULONG_PTR ULONG
#include<gdiplus.h>//gdi+头文件
#include <string>
#include <iostream>
using namespace std;
using namespace Gdiplus;
#pragma comment(lib,"gdiplus.lib")


#define PRINTER_NAME "Aibao A-5801"  

void Print();

int main()
{

	// print
	Print();

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR pGdiToken;
	GdiplusStartup(&pGdiToken, &gdiplusStartupInput, NULL);//初始化GDI+
	HWND hWnd = ::FindWindow(NULL, L"新建文本文档.txt - 记事本");
	HDC hDC = ::GetDC(hWnd);
	Graphics graphics(hDC);
	Pen newPen(Color(255, 0, 0), 3);//画笔，最后一个参数，画笔大小
	while (true)
	{
		graphics.DrawRectangle(&newPen, 50, 50, 100, 60);//画一个矩形
		Sleep(350);
	}
	//死循环，下面这句不会调用，只是想把那个意思表明
	GdiplusShutdown(pGdiToken);//关闭GDI+


	return 0;
}

void Print()
{
	std::string hello = "!!! Hello Printer !!!\f";
	HANDLE hPrinter = NULL;
	DOC_INFO_1 DocInfo;
	DWORD      dwJob;
	DWORD      dwBytesWritten = 0L;

	if (OpenPrinter((LPTSTR)_T(PRINTER_NAME), &hPrinter, NULL)) {
		cout << "printer opened" << endl;
		DocInfo.pDocName = (LPTSTR)_T("My Document");
		DocInfo.pOutputFile = NULL;
		DocInfo.pDatatype = (LPTSTR)_T("RAW");
		dwJob = StartDocPrinter(hPrinter, 1, (LPBYTE)&DocInfo);
		if (dwJob != 0) {
			cout << "Print job open" << endl;
			if (StartPagePrinter(hPrinter)) {
				cout << "Page started" << endl;
				// Send the data to the printer.  
				if (WritePrinter(hPrinter, (void*)hello.c_str(), hello.length(), &dwBytesWritten)) {
					if (dwBytesWritten == hello.length()) { cout << "Message sent to printer" << endl; }
				}
				EndPagePrinter(hPrinter);
				cout << "Page Closed" << endl;
			}
			// Inform the spooler that the document is ending.  
			EndDocPrinter(hPrinter);
			cout << "Print job open" << endl;
		}
		else {
			cout << "Could not create print job" << endl;
		}
		// Close the printer handle.  
		ClosePrinter(hPrinter);
		cout << "printer closed" << endl;
	}
	else {
		cout << "Could not open Printer" << endl;
	}
	cout << "done";
}