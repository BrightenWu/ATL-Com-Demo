/************************************************************************
Programmer: Brighten Wu
Date: 2018.09.15
Issue&P.S.:
1.VARIANT varValue = CComVariant(pArray);  该方式传到VARIANT数组数据为空。
2.VB输入SAFEARRAY无法识别，返回可以。
3.VB无法识别ULONG。
4.Matlab无法识别自定义结构体。
5.VB、Matlab都无法识别存储于VARIANT的SAFEARRAY。
6.CComVariant存BSTR，vb读取出错。
7.variant存储自定义结构体(vb无法识别VT_RECORD，可以识别自定义结构数组)。
************************************************************************/

// Math.h: CMath 的声明
#pragma once
#include "resource.h"       // 主符号
#include <atlctl.h>
#include "ATLProjectTest2_i.h"
#include "_IMathEvents_CP.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif

using namespace ATL;



// CMath
class ATL_NO_VTABLE CMath :
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IMath, &IID_IMath, &LIBID_ATLProjectTest2Lib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IOleControlImpl<CMath>,
	public IOleObjectImpl<CMath>,
	public IOleInPlaceActiveObjectImpl<CMath>,
	public IViewObjectExImpl<CMath>,
	public IOleInPlaceObjectWindowlessImpl<CMath>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CMath>,
	public CProxy_IMathEvents<CMath>,
	public IObjectSafetyImpl<CMath, INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
	public CComCoClass<CMath, &CLSID_Math>,
	public CComControl<CMath>
{
public:


	CMath()
	{
		m_pExtData = nullptr;
	}

	~CMath();

DECLARE_OLEMISC_STATUS(OLEMISC_RECOMPOSEONRESIZE |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_INSIDEOUT |
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST
)

DECLARE_REGISTRY_RESOURCEID(IDR_MATH)


BEGIN_COM_MAP(CMath)
	COM_INTERFACE_ENTRY(IMath)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IID(IID_IObjectSafety, IObjectSafety)
END_COM_MAP()

BEGIN_PROP_MAP(CMath)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// 示例项
	// PROP_ENTRY_TYPE("属性名", dispid, clsid, vtType)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CMath)
	CONNECTION_POINT_ENTRY(__uuidof(_IMathEvents))
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CMath)
	CHAIN_MSG_MAP(CComControl<CMath>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// 处理程序原型: 
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		static const IID* const arr[] =
		{
			&IID_IMath,
		};

		for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
		{
			if (InlineIsEqualGUID(*arr[i], riid))
				return S_OK;
		}
		return S_FALSE;
	}

// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// IMath
public:
	HRESULT OnDraw(ATL_DRAWINFO& di)
	{
		RECT& rc = *(RECT*)di.prcBounds;
		// 将剪辑区域设置为 di.prcBounds 指定的矩形
		HRGN hRgnOld = NULL;
		if (GetClipRgn(di.hdcDraw, hRgnOld) != 1)
			hRgnOld = NULL;
		bool bSelectOldRgn = false;

		HRGN hRgnNew = CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom);

		if (hRgnNew != NULL)
		{
			bSelectOldRgn = (SelectClipRgn(di.hdcDraw, hRgnNew) != ERROR);
		}

		Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);
		SetTextAlign(di.hdcDraw, TA_CENTER|TA_BASELINE);
		LPCTSTR pszText = _T("Math");
#ifndef _WIN32_WCE
		TextOut(di.hdcDraw,
			(rc.left + rc.right) / 2,
			(rc.top + rc.bottom) / 2,
			pszText,
			lstrlen(pszText));
#else
		ExtTextOut(di.hdcDraw,
			(rc.left + rc.right) / 2,
			(rc.top + rc.bottom) / 2,
			ETO_OPAQUE,
			NULL,
			pszText,
			ATL::lstrlen(pszText),
			NULL);
#endif

		if (bSelectOldRgn)
			SelectClipRgn(di.hdcDraw, hRgnOld);

		DeleteObject(hRgnNew);

		return S_OK;
	}


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}
	STDMETHOD(Add)(VARIANT lOp1, VARIANT lOp2, VARIANT* plResult);
	STDMETHOD(GetExportData)(SAFEARRAY** pExtData);

	private:
		SAFEARRAY *m_pExtData;
};

OBJECT_ENTRY_AUTO(__uuidof(Math), CMath)
