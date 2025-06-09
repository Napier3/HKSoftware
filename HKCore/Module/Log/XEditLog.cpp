
#include "stdafx.h"
#include "XEditLog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CXEditLog* CXEditLog::g_pXEditLog = NULL;
long CXEditLog::g_nXEditLogRef = 0;


CXEditLog::CXEditLog()
{
	
}

CXEditLog::~CXEditLog()
{
	Detach();
}

void CXEditLog::Attach(HWND hWnd)
{
	Detach();
	m_wndEdit.Attach(hWnd);
}

void CXEditLog::Detach()
{
	if (m_wndEdit.m_hWnd != NULL)
	{
		m_wndEdit.Detach();
	}
}

void CXEditLog::Create()
{
	g_nXEditLogRef++;

	if (g_nXEditLogRef == 1)
	{
		g_pXEditLog = new CXEditLog();
	}
}

void CXEditLog::Release()
{
	g_nXEditLogRef--;

	if (g_nXEditLogRef == 0)
	{
		delete g_pXEditLog;
		g_pXEditLog = NULL;
	}
}

void CXEditLog::AttachLogWnd(unsigned long hLogWnd)
{
	ASSERT(g_pXEditLog != NULL);

	if (g_pXEditLog != NULL)
	{
		g_pXEditLog->Attach((HWND)hLogWnd);
	}
}

void CXEditLog::LogString(long nLevel, const CString &strLog, BOOL bTime)
{
	if (g_pXEditLog != NULL)
	{
		g_pXEditLog->In_LogString(nLevel, strLog, bTime);
	}
}

void CXEditLog::In_LogString(long nLevel, const CString &strLog, BOOL bTime)
{
	if (!::IsWindow(m_wndEdit.m_hWnd))
	{
		//CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("for debug ----1"));
		//::MessageBox(NULL, _T("CXEditLog， 不是窗口！"), _T("提示"), MB_OK);
		return;
	}

	UINT nMaxLen = m_wndEdit.GetLimitText();
	long nLen = strLog.GetLength();
	long nWndTextLen = ::SendMessage(m_wndEdit.m_hWnd, WM_GETTEXTLENGTH, 0, 0); 
	long nTotalLen = nLen +   nWndTextLen;

	if (nMaxLen <= nTotalLen)
	{
		m_wndEdit.SetWindowText(_T(""));
	}

	m_wndEdit.SetSel(-1, -1, TRUE);

	if (bTime)
	{
		CString strTime;
		SYSTEMTIME tm;
		::GetLocalTime(&tm);
		strTime.Format(_T("%d-%d-%d %d:%d:%d-%d : "), tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond, tm.wMilliseconds);
		m_wndEdit.ReplaceSel(strTime);
	}
	
	m_wndEdit.ReplaceSel(strLog);
	m_wndEdit.ReplaceSel(_T("\r\n"));	
}

