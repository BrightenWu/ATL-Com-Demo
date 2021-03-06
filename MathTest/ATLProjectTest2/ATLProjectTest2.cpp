// ATLProjectTest2.cpp: DLL 导出的实现。


#include "stdafx.h"
#include "resource.h"
#include "ATLProjectTest2_i.h"
#include "dllmain.h"
#include "xdlldata.h"


using namespace ATL;

//构建进程外Com时使用
//class CATLProjectTest2Module : public ATL::CAtlExeModuleT< CATLProjectTest2Module >
//{
//public:
//	DECLARE_LIBID(LIBID_ATLProjectTest2Lib)
//	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_ATLPROJECTTEST2, "{0c78c5b3-e4a2-45af-b917-4dcaaf76267a}")
//};
//
//CATLProjectTest2Module _AtlModule;
//
//
//
////
//extern "C" int WINAPI _tWinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/,
//	LPTSTR /*lpCmdLine*/, int nShowCmd)
//{
//	return _AtlModule.WinMain(nShowCmd);
//}

//////////////////////////////////////////////////////////////////////////

// 用于确定 DLL 是否可由 OLE 卸载。
_Use_decl_annotations_
STDAPI DllCanUnloadNow(void)
{
#ifdef _MERGE_PROXYSTUB
	HRESULT hr = PrxDllCanUnloadNow();
	if (hr != S_OK)
		return hr;
#endif
	return _AtlModule.DllCanUnloadNow();
}

// 返回一个类工厂以创建所请求类型的对象。
_Use_decl_annotations_
STDAPI DllGetClassObject(_In_ REFCLSID rclsid, _In_ REFIID riid, _Outptr_ LPVOID* ppv)
{
#ifdef _MERGE_PROXYSTUB
	HRESULT hr = PrxDllGetClassObject(rclsid, riid, ppv);
	if (hr != CLASS_E_CLASSNOTAVAILABLE)
		return hr;
#endif
	return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
}

// DllRegisterServer - 向系统注册表中添加项。
_Use_decl_annotations_
STDAPI DllRegisterServer(void)
{
	// 注册对象、类型库和类型库中的所有接口
	HRESULT hr = _AtlModule.DllRegisterServer();
#ifdef _MERGE_PROXYSTUB
	if (FAILED(hr))
		return hr;
	hr = PrxDllRegisterServer();
#endif
	return hr;
}

// DllUnregisterServer - 移除系统注册表中的项。
_Use_decl_annotations_
STDAPI DllUnregisterServer(void)
{
	HRESULT hr = _AtlModule.DllUnregisterServer();
#ifdef _MERGE_PROXYSTUB
	if (FAILED(hr))
		return hr;
	hr = PrxDllRegisterServer();
	if (FAILED(hr))
		return hr;
	hr = PrxDllUnregisterServer();
#endif
	return hr;
}

// DllInstall - 按用户和计算机在系统注册表中逐一添加/移除项。
STDAPI DllInstall(BOOL bInstall, _In_opt_  LPCWSTR pszCmdLine)
{
	HRESULT hr = E_FAIL;
	static const wchar_t szUserSwitch[] = L"user";

	if (pszCmdLine != NULL)
	{
		if (_wcsnicmp(pszCmdLine, szUserSwitch, _countof(szUserSwitch)) == 0)
		{
			ATL::AtlSetPerUserRegistration(true);
		}
	}

	if (bInstall)
	{
		hr = DllRegisterServer();
		if (FAILED(hr))
		{
			DllUnregisterServer();
		}
	}
	else
	{
		hr = DllUnregisterServer();
	}

	return hr;
}


