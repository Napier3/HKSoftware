#include "StdAfx.h"
#include "ListBoxLog.h"

CListBoxLog::CListBoxLog(void)
{
	CLogPrint::Create(this);
}

CListBoxLog::~CListBoxLog(void)
{
	CLogPrint::SetLog(NULL);
	CLogPrint::Release();
}

void CListBoxLog::LogString(long nLevel, const CString &strMsg)
{
	if(!m_hWnd)
	{
		return;
	}
	
	//AddString(strMsg);
	if(nLevel == XLOGLEVEL_WARNING)
	{
		return;
	}
	long nCount = GetCount();
	InsertString(nCount,strMsg);

	SetTopIndex(nCount-1);
	

// 	if (nCount > 200)
// 	{
// 		long nIndex=0;
// 		for (nIndex=0; nIndex < nCount-200; nIndex++)
// 		{
// 			DeleteString(0);
// 		}
// 	}
// 
// 	nCount = GetCount();
// 	SetTopIndex(nCount-1);
}
