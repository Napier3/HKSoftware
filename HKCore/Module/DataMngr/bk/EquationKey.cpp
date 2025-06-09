// EquationKey.cpp : CEquationKey ��ʵ��

#include "stdafx.h"
#include "EquationKey.h"


// CEquationKey


STDMETHODIMP CEquationKey::get_Name(BSTR* pVal)
{
	// TODO: �ڴ����ʵ�ִ���
	if (m_pEqtnKey == NULL)
	{
		return S_FALSE;
	}
	else
	{
		*pVal = m_pEqtnKey->m_strKeyName.Copy();
		return S_OK;
	}
	return S_OK;
}

STDMETHODIMP CEquationKey::get_Value(BSTR* pVal)
{
	// TODO: �ڴ����ʵ�ִ���
	if (m_pEqtnKey == NULL)
	{
		return S_FALSE;
	}
	else
	{
		*pVal = m_pEqtnKey->m_strKeyValue.Copy();
		return S_OK;
	}
	return S_OK;
}

STDMETHODIMP CEquationKey::put_Value(BSTR newVal)
{
	// TODO: �ڴ����ʵ�ִ���
	if (m_pEqtnKey == NULL)
	{
		return S_FALSE;
	}
	else
	{
		m_pEqtnKey->m_strKeyValue = newVal;
		return S_OK;
	}
	return S_OK;
}
