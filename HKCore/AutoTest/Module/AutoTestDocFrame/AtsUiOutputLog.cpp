
#include "stdafx.h"
#include "AtsUiOutputLog.h"

#include "..\TestControl/TCtrlCntrBaseApp.h"
#include "..\..\Module\XLanguage\XLangMenu.h"
#include "..\..\..\Module\Log\XEditLog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define XID_EDIT_COPY       0X7F01
#define XID_EDIT_CLEAR      0X7F02


/////////////////////////////////////////////////////////////////////////////
// CAtsUiOutputLog1
// long CAtsUiOutputLog::m_nOpenFile = 0;
// CFile* CAtsUiOutputLog::m_pFile = NULL;

CAtsUiOutputLog::CAtsUiOutputLog(BOOL bUseLog)
{
	if (bUseLog)
	{
		CLogPrint::Create(this);
		CreateTestTempFile();
	}

	m_bUseLog = bUseLog;
}

CAtsUiOutputLog::~CAtsUiOutputLog()
{
	if (m_bUseLog)
	{
		CLogPrint::SetLog(NULL);
		CLogPrint::Release();
	}
}

BEGIN_MESSAGE_MAP(CAtsUiOutputLog, CEdit)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(XID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(XID_EDIT_CLEAR, OnEditClear)
	ON_WM_WINDOWPOSCHANGING()
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CAtsUiOutputLog 消息处理程序

void CAtsUiOutputLog::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	CMenu menu;		
	menu.CreatePopupMenu();

	menu.AppendMenu(MF_STRING,XID_EDIT_COPY,g_sLangTxt_Copy);
	menu.AppendMenu(MF_STRING,XID_EDIT_CLEAR,g_sLangTxt_Clear);

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

void CAtsUiOutputLog::OnEditCopy()
{
	SetSel(0, -1, TRUE);
	Copy();
}

void CAtsUiOutputLog::OnEditClear()
{
	UINT nLen = GetWindowTextLength();
	SetSel(0, -1, TRUE);
	ReplaceSel(_T(""));
}

void CAtsUiOutputLog::OnShowMsg(UINT uCommandID)
{

}

void CAtsUiOutputLog::OnUpdateShowMsg(CCmdUI* pCmdUI)
{

}

void CAtsUiOutputLog::OnViewOutput()
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

void CAtsUiOutputLog::CreateTestTempFile()
{
	CTCtrlCntrBaseApp *pApp = g_theTCtrlCntrApp;
	CTCtrlCntrConfig* pCtrlCfg = pApp->GetCntrConfig();

	if (pCtrlCfg->m_nWriteTestTempFile == 1)
	{
		CLogPrint::CreateLogFile();
	}
	else
	{
		CLogPrint::CloseLogFile();
	}
}

void CAtsUiOutputLog::LogString(long nLevel, const char *strMsg)
{
	CString strTemp;
	strTemp = strMsg;
	LogString(nLevel, strTemp);
}

void CAtsUiOutputLog::LogString(long nLevel, const CString &strMsg)
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

	//shaolei 20220516
	CXEditLog::LogString(nLevel, strMsg, TRUE);

// 	if (m_pFile != NULL)
// 	{
// 		CString strText;
// 		strText.Format(_T("%s%s\r\n"), strTime, strMsg);
// 		char *pText = NULL;
// 		CString_to_char(strText, &pText);
// 		m_pFile->Write(pText, strlen(pText));
// 		delete pText;
// 	}
}
