// MathTest.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <atlbase.h>
#include <vector>
#include "../ATLProjectTest2/ATLProjectTest2_i.h"
#include "../ATLProjectTest2/ATLProjectTest2_i.c"
//#import "ATLProjectTest2.tlb"

int main()
{
	//初始化COM库
	if (CoInitializeEx(NULL, COINIT_MULTITHREADED) != S_OK)
	{
		std::cout << "Fail to Initialize COM" << std::endl;
		return -1;
	}

	CComPtr<IMath> PMath;
	HRESULT hr = CoCreateInstance(CLSID_Math, NULL, CLSCTX_SERVER, IID_IMath, (void * *)&PMath);
	if (FAILED(hr))
	{
		std::cout << "Failed to create server instance" << std::endl;
		return -1;
	}

	CComVariant lResult;
	PMath->Add(CComVariant(100), CComVariant(200), &lResult);

	std::cout << "Test Result :" << lResult.lVal << std::endl;

	SAFEARRAY *pArray = nullptr;
	PMath->GetExportData(&pArray);
	if (nullptr == pArray)
	{
		return -1;
	}

	ExportData *pData;
	hr = SafeArrayAccessData(pArray, (void**)(&pData));
	if (FAILED(hr))
	{
		return hr;
	}

	LONG lLbound = 0;
	LONG lUbound = 0;
	hr = SafeArrayGetLBound(pArray, 1, &lLbound);
	if (FAILED(hr))
	{
		return hr;
	}

	hr = SafeArrayGetUBound(pArray, 1, &lUbound);
	if (FAILED(hr))
	{
		return hr;
	}

	LONG lCount = lUbound - lLbound + 1;

	std::vector<ExportData> vData(lCount);

	for (LONG l = 0; l < lCount; l++)
	{
		vData[l] = pData[l];
	}

	hr = SafeArrayUnaccessData(pArray);
	if (FAILED(hr))
	{
		return hr;
	}

	//SafeArrayDestroyData(pArray);

	CoUninitialize();

	int t = 0;
	std::cin >> t;
    return 0;
}

