#include "stdafx.h"
#include "SttMacroXmlKeys.h"

CMacroXmlKeys *CMacroXmlKeys::g_pMacroXmlKeys = NULL;
long CMacroXmlKeys::g_nRef = 0;

CMacroXmlKeys::CMacroXmlKeys(void)
{
	m_strParaKey = L"data";
	m_strParaUnitKey = L"unit";
	m_strParaDataTypeKey = L"data-type";
	m_strParaValueKey = L"value";
	m_strParaDefValueKey = L"default";
	m_strRemarkKey = L"remark";
	m_strParasFormatKey = L"format";

	m_strTestMacrosKey = L"macros";
	m_strProgIDKey = L"prog-id";
	m_strTestMacroKey = L"macro";
	m_strPxAppTypeKey = L"type";
	m_strFaultParasKey = L"fault-paras";
	m_strSysParasKey = L"sys-paras";
	m_strResultsKey = L"results";
	m_strSearchResultsKey = L"search-results";
	m_strUiDllFileKey = L"ui-dll-file";
	m_strFaultParasExKey = L"fault-paras-ex";
	m_strParaGroupKey = L"group";
	m_strCreateGroupKey = L"create-group";
	m_strResultExKey = L"results-ex";
	m_strParasKey = L"paras";
}

CMacroXmlKeys::~CMacroXmlKeys(void)
{
}

CMacroXmlKeys *CMacroXmlKeys::Create()
{
	g_nRef++;
	if (g_nRef == 1)
	{
		g_pMacroXmlKeys = new CMacroXmlKeys();
	}

	return g_pMacroXmlKeys;
}

void CMacroXmlKeys::Release()
{
	g_nRef--;
	if (g_nRef == 0)
	{
		delete g_pMacroXmlKeys;
	}
}
