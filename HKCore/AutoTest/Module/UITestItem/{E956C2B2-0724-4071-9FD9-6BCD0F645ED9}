#include "stdafx.h"
#include "UISftRsltWndDateTimeCtrl.h"
#include "../GuideBook/GbDataTypeMngr.h"
#include <locale.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


BEGIN_MESSAGE_MAP(CUISftRsltWndDateTimeCtrl, CDateTimeCtrl)
	ON_NOTIFY_REFLECT(DTN_DATETIMECHANGE, &CUISftRsltWndDateTimeCtrl::OnDtnDatetimechange)
END_MESSAGE_MAP()


CUISftRsltWndDateTimeCtrl::CUISftRsltWndDateTimeCtrl(const CString& strFormat)
{
	m_pResultWndInterface = NULL;
	m_strDateTimeFormat = strFormat;
}

CUISftRsltWndDateTimeCtrl::~CUISftRsltWndDateTimeCtrl()
{

}

void CUISftRsltWndDateTimeCtrl::OnDtnDatetimechange(NMHDR *pNMHDR, LRESULT *pResult)
{
	COleDateTime timeDest;
	GetTime(timeDest);
	
	CString strData;

#ifdef UNICODE
	_wsetlocale(LC_ALL,_T("chs"));
#endif

	strData = timeDest.Format(m_strDateTimeFormat);
	ASSERT(strData != _T(""));

	if (m_pResultWndInterface != NULL)
	{
		m_pResultWndInterface->OnResultDataChanged(strData);
	}

#ifdef UNICODE
	_wsetlocale(LC_ALL,_T("eng"));
#endif
	
	*pResult = 0;
}

void CUISftRsltWndDateTimeCtrl::InitResultDateTimeCtrl(const CString &strFormart, CString &strValue)
{
	m_strDateTimeFormat = strFormart;
	SetFormat(_T("yyyy-MM-dd HH:mm:ss"));

	//if (strValue.GetLength() > 4)
	//{
	//	COleDateTime tm;
	//	tm.ParseDateTime(strValue);
	//	SetTime(tm);
	//}
}