#include "stdafx.h"
#include "UISftRsltWndMultiSel.h"
#include "UISftRsltWndInterface.h"
#include "../GuideBook/GbDataTypeMngr.h"
#include "../../../Module/AtlMemBuffer/WBufferBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CUISftRsltWndMultiSel::CUISftRsltWndMultiSel()
{

}

CUISftRsltWndMultiSel::CUISftRsltWndMultiSel(const CString& strFormat)
{
	m_pResultWndInterface = NULL;
	m_strFormat = strFormat;
}

CUISftRsltWndMultiSel::~CUISftRsltWndMultiSel()
{
}

BEGIN_MESSAGE_MAP(CUISftRsltWndMultiSel, CCheckListBox)
ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

void CUISftRsltWndMultiSel::InitMultiSel(const CString& strFormat,const CString& strValue)
{
// 	ResetContent();
// 	long nCount = 0;
// 	long nIndex = 0;
// 
// 	m_strFormat = strFormat;
// 	CDataType* oDataType = (CDataType*)CGbDataTypeMngr::GetSafetyComboDataTypes()->FindByID(m_strFormat);
// 	ASSERT(oDataType != NULL);
// 
// 	nCount = oDataType->GetCount();
// 
// 	for(long i=0;i<nCount;i++)
// 	{
// 		CDataTypeValue* oValue = (CDataTypeValue*)oDataType->GetAtIndex(i);
// 		AddString(oValue->m_strName);
// 	}
// 
// 	CWBufferBase oBuffer;
// 	BSTR bstrValue = strValue.AllocSysString();
// 	oBuffer.InitBuffer(bstrValue);
// 	WCHAR pszBuffer[MAX_PATH];
// #ifdef _UNICODE
// 	lstrcpy(pszBuffer,g_strMultiComboSeparator);
// 	nCount = lstrlen(pszBuffer);
// #else
// 	wcscpy(pszBuffer,g_strMultiComboSeparator);
// 	nCount = wcslen(pszBuffer);
// #endif
// 
// 
// 	for(nIndex = 0;nIndex<nCount;nIndex++)
// 	{
// 		oBuffer.FormatBuffer(pszBuffer[nIndex]);
// 	}
// 
// 	oBuffer.ResetPointer();
// 	WCHAR* pTemp = oBuffer.GetString();
// 
// 	while(oBuffer.IsPoiterInBuffer(pTemp))
// 	{
// 		nIndex = FindString(-1,pTemp);
// 		if(nIndex != LB_ERR)
// 		{
// 			SetCheck(nIndex,1);
// 		}
// 
// 		oBuffer.NextString();
// 		pTemp = oBuffer.GetString();
// 	}
// 
// 	
// 	if (m_pResultWndInterface != NULL)
// 	{
// 		m_pResultWndInterface->OnResultDataChanged(strValue);
// 	}
// 
// 	::SysFreeString(bstrValue);
}

void CUISftRsltWndMultiSel::OnLButtonUp(UINT nFlags, CPoint point)
{
	long nCount = 0;
	long nSelCount = 0;
	long nIndex = 0;
	nCount = this->GetCount();
	CString strData;
	CString strTemp;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		if (GetCheck(nIndex))
		{
			nSelCount++;
			GetText(nIndex, strTemp);
			strData += strTemp;
			strData += g_strMultiComboSeparator;
		}
	}

	if (m_pResultWndInterface != NULL)
	{
		m_pResultWndInterface->OnResultDataChanged(strData);
	}

	CCheckListBox::OnLButtonUp(nFlags, point);
}