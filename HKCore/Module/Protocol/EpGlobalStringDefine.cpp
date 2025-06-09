// EpGlobalDefine.cpp
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EpGlobalStringDefine.h"
#include "EpAnalyseMngr.h"


CEpAnalyseMngr g_oEpAnalyseMngr;

void Ep_InitGetFrameAnalyse()
{
	CEpAnalyseStringXmlRWKeys::Create();

	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("AnalyseString.xml");
	g_oEpAnalyseMngr.DeleteAll();
	g_oEpAnalyseMngr.OpenXmlFile(strFile, CEpAnalyseStringXmlRWKeys::CEpAnalyseMngrKey(), CEpAnalyseStringXmlRWKeys::g_pXmlKeys);

	CEpAnalyseStringXmlRWKeys::Release();
}

CString Ep_GetFrameAnalyseString(const CString &strID)
{
	CEpAnalyseString *pString = (CEpAnalyseString*)g_oEpAnalyseMngr.FindByID(strID);

	if (pString == NULL)
	{
		return strID;
	}
	else
	{
		return pString->m_strString;
	}
}

CString Ep_GetFrameAnalyseStringValue(const CString &strID, const CString &strValue)
{
	CEpAnalyseString *pString = (CEpAnalyseString*)g_oEpAnalyseMngr.FindByID(strID);

	if (pString == NULL)
	{
		return strValue;
	}
	else
	{
		CEpAnalyseStringVal *pVal = pString->FindByValue(strValue);

		if (pVal != NULL)
		{
			return pVal->m_strName;
		}
		else
		{
			return strValue;
		}
	}
}
// 
// CString Ep_GetFrameAnalyseStringValue(const CString &strID, long nValue)
// {
// 	CEpAnalyseString *pString = (CEpAnalyseString*)g_oEpAnalyseMngr.FindByID(strID);
// 
// 	if (pString == NULL)
// 	{
// 		CString strValue;
// 		strValue.Format(_T("%d"), nValue);
// 		return strValue;
// 	}
// 	else
// 	{
// 		CEpAnalyseStringVal *pVal = pString->FindByValue(nValue);
// 
// 		if (pVal != NULL)
// 		{
// 			return pVal->m_strName;
// 		}
// 		else
// 		{
// 			CString strValue;
// 			strValue.Format(_T("%d"), nValue);
// 			return strValue;
// 		}
// 	}
// }
