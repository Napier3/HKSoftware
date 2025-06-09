// Expression.cpp : CExpression 的实现

#include "stdafx.h"
#include "Expression.h"


// CExpression


STDMETHODIMP CExpression::SetExpression(BSTR bstrExpression, LONG* pnReturn)
{
	// TODO: 在此添加实现代码
	*pnReturn = m_oExpression.SetAtlExpression(bstrExpression);
	return S_OK;
}

STDMETHODIMP CExpression::GetSyntaxs(BSTR* pbstrSyntaxs)
{
	// TODO: 在此添加实现代码
	CComBSTR bstrSyntaxs("");
	CAtlScriptSyntaxs* pScripts = m_oExpression.GetScriptSyntaxs();
	LONG nCount = pScripts->GetCount();
	CAtlScriptSyntax* pScript = NULL;
	for (int i=0;i<nCount;i++)
	{
		pScript = pScripts->GetItem(i);
		if (pScript!=NULL)
		{
			bstrSyntaxs+=pScript->m_strSyntaxError+"\n";
		}
	}
	*pbstrSyntaxs = bstrSyntaxs.Copy();
	return S_OK;
}

STDMETHODIMP CExpression::GetSyntaxsCount(LONG* pnSyntaxs)
{
	// TODO: 在此添加实现代码
	CAtlScriptSyntaxs* pScripts = m_oExpression.GetScriptSyntaxs();
	*pnSyntaxs = pScripts->GetCount();
	return S_OK;
}

STDMETHODIMP CExpression::GetResult(DOUBLE* pdResult)
{
	// TODO: 在此添加实现代码
	DOUBLE dValue;
	m_oExpression.Value(dValue);
	*pdResult = dValue;
	return S_OK;
}

STDMETHODIMP CExpression::AttachConstVariables(IDispatch* pVariables, LONG* pnReturn)
{
	// TODO: 在此添加实现代码
	m_oExpression.AttachConstVariables(pVariables);
	return S_OK;
}

STDMETHODIMP CExpression::AttachVariables(IDispatch* pVariables, LONG* pnReturn)
{
	// TODO: 在此添加实现代码
	m_oExpression.AttachTempVariables(pVariables);
	return S_OK;
}
