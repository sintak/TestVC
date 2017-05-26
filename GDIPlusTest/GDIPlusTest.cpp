// GDIPlusTest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include<windows.h>
#define ULONG_PTR ULONG
#include<gdiplus.h>//gdi+ͷ�ļ�
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
	GdiplusStartup(&pGdiToken, &gdiplusStartupInput, NULL);//��ʼ��GDI+
	HWND hWnd = ::FindWindow(NULL, L"�½��ı��ĵ�.txt - ���±�");
	HDC hDC = ::GetDC(hWnd);
	Graphics graphics(hDC);
	Pen newPen(Color(255, 0, 0), 3);//���ʣ����һ�����������ʴ�С
	while (true)
	{
		graphics.DrawRectangle(&newPen, 50, 50, 100, 60);//��һ������
		Sleep(350);
	}
	//��ѭ����������䲻����ã�ֻ������Ǹ���˼����
	GdiplusShutdown(pGdiToken);//�ر�GDI+


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