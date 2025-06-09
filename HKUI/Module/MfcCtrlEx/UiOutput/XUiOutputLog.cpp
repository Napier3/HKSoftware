
#include "stdafx.h"
#include "XUiOutputLog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define XID_EDIT_COPY       0X7F01
#define XID_EDIT_CLEAR      0X7F02


/////////////////////////////////////////////////////////////////////////////
// CXUiOutputLog1
// long CXUiOutputLog::m_nOpenFile = 0;
// CFile* CXUiOutputLog::m_pFile = NULL;

CXUiOutputLog::CXUiOutputLog(BOOL bUseLog)
{

	if (bUseLog)
	{
		CLogPrint::Create(this);
	}
	else
	{
		CLogPrint::Create(NULL);
	}

	m_bUseLog = bUseLog;
	m_pAutoCriticSection = NULL;
}

CXUiOutputLog::~CXUiOutputLog()
{
	if (m_bUseLog)
	{
		CLogPrint::SetLog(NULL);
		CLogPrint::Release();
	}
	else
	{
		CLogPrint::Release();
	}

	if (m_pAutoCriticSection != NULL)
	{
		delete m_pAutoCriticSection;
		m_pAutoCriticSection = NULL;
	}
}

BEGIN_MESSAGE_MAP(CXUiOutputLog, CEdit)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(XID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(XID_EDIT_CLEAR, OnEditClear)
	ON_WM_WINDOWPOSCHANGING()
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CXUiOutputLog 消息处理程序

void CXUiOutputLog::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CMDIFrameWndEx *pFrame = ((CMDIFrameWndEx*)AfxGetMainWnd());

	if (pFrame == NULL)
	{
		CEdit::OnContextMenu(pWnd, point);
		return;
	}

	CRuntimeClass *pCRuntimeClass = pFrame->GetRuntimeClass();

	if (strcmp(pCRuntimeClass->m_lpszClassName, "CDialog") == 0)
	{
		CEdit::OnContextMenu(pWnd, point);
		return;
	}

	CMenu menu;		
	menu.CreatePopupMenu();

	menu.AppendMenu(MF_STRING,XID_EDIT_COPY,_T("Copy"));
	menu.AppendMenu(MF_STRING,XID_EDIT_CLEAR,_T("Clear"));

	//if (AfxGetMainWnd()->IsKindOf(RUNTIME_CLASS(CFrameWndEx)))
	{
		CMFCPopupMenu* pPopupMenu = new CMFCPopupMenu;

		if (!pPopupMenu->Create(this, point.x, point.y, (HMENU)menu.m_hMenu, FALSE, TRUE))
		{
			return;
		}

		((CMDIFrameWndEx*)AfxGetMainWnd())->OnShowPopupMenu(pPopupMenu);
		UpdateDialogControls(this, FALSE);
	}

	SetFocus();
}

void CXUiOutputLog::OnEditCopy()
{
	SetSel(0, -1, TRUE);
	Copy();
}

void CXUiOutputLog::OnEditClear()
{
	UINT nLen = GetWindowTextLength();
	SetSel(0, -1, TRUE);
	ReplaceSel(_T(""));
}

void CXUiOutputLog::OnShowMsg(UINT uCommandID)
{

}

void CXUiOutputLog::OnUpdateShowMsg(CCmdUI* pCmdUI)
{

}

void CXUiOutputLog::OnViewOutput()
{
	CDockablePane* pParentBar = DYNAMIC_DOWNCAST(CDockablePane, GetOwner());
	CMDIFrameWndEx* pMainFrame = DYNAMIC_DOWNCAST(CMDIFrameWndEx, GetTopLevelFrame());

	if (pMainFrame != NULL && pParentBar != NULL)
	{
		pMainFrame->SetFocus();
		pMainFrame->ShowPane(pParentBar, FALSE, FALSE, FALSE);
		pMainFrame->RecalcLayout();
	}
}

void CXUiOutputLog::LogString(long nLevel, const char *strMsg)
{
	CString strTemp;
	strTemp = strMsg;
	LogString(nLevel, strTemp);
}

void CXUiOutputLog::LogString(long nLevel, const CString &strMsg)
{
//	return;
	if (m_pAutoCriticSection == NULL)
	{
		XLogString(nLevel, strMsg);
	}
	else
	{
		CAutoSimpleLock oLock(m_pAutoCriticSection);
		XLogString(nLevel, strMsg);
	}
}

void CXUiOutputLog::XLogString(long nLevel, const CString &strMsg)
{
	UINT nMaxLen = GetLimitText();
	long nLen = strMsg.GetLength();
	long nTotalLen = nLen +   GetWindowTextLength();

	if (nMaxLen <= nTotalLen)
	{
		SetWindowText(_T(""));
	}

	nLen = GetWindowTextLength();
	SetSel(nLen, -1, TRUE);

	CString strTime;
	SYSTEMTIME tm;
	::GetLocalTime(&tm);
	strTime.Format(_T("%d-%d-%d %d:%d:%d-%d : "), tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond, tm.wMilliseconds);
	ReplaceSel(strTime);

	ReplaceSel(strMsg);
	ReplaceSel(_T("\r\n"));	
}
