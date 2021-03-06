// Math.cpp: CMath 的实现
#include "stdafx.h"
#include "Math.h"


// CMath


CMath::~CMath()
{
	//if (m_pExtData != nullptr)
	//{
	//	::SafeArrayDestroy(m_pExtData);
	//	m_pExtData = nullptr;
	//}
}

STDMETHODIMP CMath::Add(VARIANT lOp1, VARIANT lOp2, VARIANT* plResult)
{
	// TODO: 在此添加实现代码
	//*plResult = lOp1 + lOp2;

	HRESULT hr;
	hr = VariantChangeType(&lOp1, &lOp1, 0, VT_I4);
	if (FAILED(hr))
	{
		return hr;
	}

	hr = VariantChangeType(&lOp2, &lOp2, 0, VT_I4);
	if (FAILED(hr))
	{
		return hr;
	}

	if (plResult != nullptr)
	{
		VariantInit(plResult);
		plResult->vt = VT_I4;
		plResult->lVal = lOp1.lVal + lOp2.lVal;

		Fire_ComputationComplete(L"Result", *plResult);
	}

	return S_OK;
}

STDMETHODIMP CMath::GetExportData(SAFEARRAY** pExtData)
{
	if (nullptr == pExtData)
		return E_POINTER;

	if (*pExtData != nullptr) 
	{
		//::SafeArrayDestroy(*pExtData);
		*pExtData = nullptr;
	}

	HRESULT hr;

	if (nullptr == m_pExtData)
	{
		IRecordInfo *pRecordInfo = nullptr;
		hr = ::GetRecordInfoFromGuids(LIBID_ATLProjectTest2Lib, 1, 0, LOCALE_USER_DEFAULT, __uuidof(ExportData), &pRecordInfo);
		if (FAILED(hr))
		{
			return hr;
		}

		m_pExtData = SafeArrayCreateVectorEx(VT_RECORD, 0, 3, pRecordInfo);
		pRecordInfo->Release();

		if (nullptr == m_pExtData)
		{
			hr = Error(_T("Can not create array of ExportData structures"));
			return hr;
		}
	}
	else
	{
		SAFEARRAYBOUND rgsabound[1];
		rgsabound[0].lLbound = 0;
		rgsabound[0].cElements = 3;
		hr = SafeArrayRedim(m_pExtData, rgsabound);
		if (FAILED(hr))
		{
			return hr;
		}
	}
	*pExtData = m_pExtData;

	ExportData *pData = nullptr;
	hr = SafeArrayAccessData(*pExtData, reinterpret_cast<void**>(&pData));
	if (FAILED(hr))
	{
		return hr;
	}

	pData[0].pwstrName = SysAllocString(L"Visible");
	pData[0].varValue = CComVariant(true);
	pData[1].pwstrName = SysAllocString(L"Size");
	pData[1].varValue = CComVariant(3);
	pData[2].pwstrName = SysAllocString(L"Name");

	VARIANT var0;
	VariantInit(&var0);
	V_VT(&var0) = VT_BSTR;
	V_BSTR(&var0) = SysAllocString(L"Brighten");

	pData[2].varValue = var0;

	hr = SafeArrayUnaccessData(*pExtData);
	if (FAILED(hr))
	{
		return hr;
	}

	return S_OK;
}
