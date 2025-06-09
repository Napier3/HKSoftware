// Equation.cpp : CEquation 的实现

#include "stdafx.h"
#include "Equation.h"


// CEquation


STDMETHODIMP CEquation::GetCount(LONG* pnCount)
{
	// TODO: 在此添加实现代码
	*pnCount = m_oEquation.GetKeyCount();
	return S_OK;
}

STDMETHODIMP CEquation::GetItem(LONG nIndex, IDispatch** pIEquationKey)
{
	// TODO: 在此添加实现代码
	CWEqtnKey *pKey = NULL;
	HRESULT nResult = S_OK;

	pKey = m_oEquation.FindEquationKey(nIndex);

	if (pKey != NULL)
	{
		CComObject<CEquationKey> *pEquationKey = NULL;
		CComObject<CEquationKey>::CreateInstance(&pEquationKey);
		pEquationKey->AttachEqtnKey(pKey);
		pEquationKey->QueryInterface(IID_IDispatch, (void**)pIEquationKey);
	}
	else
	{
		nResult = S_FALSE;
	}
	return S_OK;
}

STDMETHODIMP CEquation::GetKeyValue(LONG nIndex, BSTR* pbstrValue)
{
	// TODO: 在此添加实现代码
	CWEqtnKey *pKey = NULL;
	pKey = m_oEquation.FindEquationKey(nIndex);

	if (pKey != NULL)
	{
		*pbstrValue = pKey->m_strKeyValue.Copy();
	}
	else
	{
		pbstrValue = NULL;
	}
return S_OK;
}

STDMETHODIMP CEquation::SetKeyValue(LONG nIndex, BSTR bstrValue)
{
	// TODO: 在此添加实现代码
	CWEqtnKey *pKey = NULL;
	pKey = m_oEquation.FindEquationKey(nIndex);

	if (pKey != NULL)
	{
		pKey->SetKeyValue(bstrValue);
	}
	return S_OK;
}

STDMETHODIMP CEquation::GetLong(BSTR bstrKeyName, LONG nDefaultVal, LONG* pnVal)
{
	// TODO: 在此添加实现代码
	if (m_oEquation.ParseLong(bstrKeyName, pnVal))
	{
	}
	else
	{
		*pnVal = nDefaultVal;
	}
	return S_OK;
}

STDMETHODIMP CEquation::GetFloat(BSTR bstrKeyName, FLOAT fDefaultVal, FLOAT* pfVal)
{
	// TODO: 在此添加实现代码
	if (m_oEquation.ParseFloat(bstrKeyName, pfVal))
	{
	}
	else
	{
		*pfVal = fDefaultVal;
	}

	return S_OK;
}

STDMETHODIMP CEquation::GetString(BSTR bstrKeyName, BSTR bstrDefaultVal, BSTR* pbstrVal)
{
	// TODO: 在此添加实现代码
	CComBSTR bstr;
	if (m_oEquation.ParseString(bstrKeyName, bstr))
	{
		*pbstrVal = bstr.Copy();
	}
	else
	{
		if (bstrDefaultVal != NULL)
		{
			*pbstrVal = ::SysAllocStringLen(bstrDefaultVal, ::SysStringLen(bstrDefaultVal));
		}
	}
	return S_OK;
}

STDMETHODIMP CEquation::GetDouble(BSTR bstrKeyName, DOUBLE dDefaultVal, DOUBLE* pdVal)
{
	// TODO: 在此添加实现代码
	if (m_oEquation.ParseDouble(bstrKeyName, pdVal))
	{
	}
	else
	{
		*pdVal = dDefaultVal;
	}
	return S_OK;
}

STDMETHODIMP CEquation::SetEquation(BSTR bstrEquation, LONG* pnCount)
{
	// TODO: 在此添加实现代码
	m_oEquation.InitBuffer(bstrEquation);
	*pnCount = m_oEquation.GetKeyCount();
	return S_OK;
}

STDMETHODIMP CEquation::GetEquation(BSTR* pbstrEquation)
{
	// TODO: 在此添加实现代码
	m_oEquation.GetEquationData(pbstrEquation);
	return S_OK;
}

STDMETHODIMP CEquation::SetKeyValueByName(BSTR bstrKeyName, BSTR bstrKeyValue, LONG AddNew)
{
	// TODO: 在此添加实现代码
	if (m_oEquation.SetKeyValue(bstrKeyName, bstrKeyValue, AddNew))
	{
		return S_OK;
	}
	else
	{
		return S_FALSE;
	}
	
}

STDMETHODIMP CEquation::SetKeyValueByEquation(BSTR bstrEquation, LONG nAddNew)
{
	// TODO: 在此添加实现代码
	m_oEquation.SetKeyValueEx(bstrEquation,nAddNew);
	return S_OK;
}

STDMETHODIMP CEquation::FreeAllKeys(void)
{
	// TODO: 在此添加实现代码
	m_oEquation.FreeAllKeys();
	return S_OK;
}

STDMETHODIMP CEquation::IsKeyExist(BSTR bstrKeyName, LONG* pnExist)
{
	// TODO: 在此添加实现代码
	CWEqtnKey* pEqtKey = m_oEquation.FindEquationKey(bstrKeyName);
	if (pEqtKey==NULL)
	{
		*pnExist=0;
	}
	else
	{
		*pnExist=1;
	}
	return S_OK;
}

STDMETHODIMP CEquation::StringSerialize(IDispatch* pIStringBuffer)
{
	// TODO: 在此添加实现代码

	return S_OK;
}

STDMETHODIMP CEquation::BinarySerialize(IDispatch* pIBinaryBuffer)
{
	// TODO: 在此添加实现代码

	return S_OK;
}
