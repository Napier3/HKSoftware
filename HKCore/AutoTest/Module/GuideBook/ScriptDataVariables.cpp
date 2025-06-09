#include "StdAfx.h"
#include "ScriptDataVariables.h"
#include "../XLanguageResourceAts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CScriptDataVariable::CScriptDataVariable(UINT nType, const CString &strVar, LPVOID pValue)
{
	m_strID = strVar;
	m_nType = nType;
	m_pVariableValue = pValue;
}

CScriptDataVariable::~CScriptDataVariable()
{
	if (m_pVariableValue != NULL)
	{
		free(m_pVariableValue);
	}
}

CScriptDataVariables::CScriptDataVariables(void)
{
	
}

CScriptDataVariables::~CScriptDataVariables(void)
{

}

void CScriptDataVariables::AddScriptDataVariable(UINT nType, const CString &strVar, LPVOID pValue)
{
	CScriptDataVariable *pVariable = (CScriptDataVariable*)FindByID(strVar);
	
	if (pVariable != NULL)
	{
		if (pVariable->m_nType != nType)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_DiffTypeData/*L"变量[%s]存在不同类型数据类型定义"*/, strVar);
		}

		pVariable->m_nType = nType;
		pVariable->SetValue(pValue);
	}
	else
	{
		pVariable = new CScriptDataVariable(nType, strVar, pValue);
		pVariable->SetParent(this);
		AddTail(pVariable);
	}
}

