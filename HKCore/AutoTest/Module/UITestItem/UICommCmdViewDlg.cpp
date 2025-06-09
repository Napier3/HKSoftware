// UICommCmdViewDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "UICommCmdViewDlg.h"
#include "../TestControl/TestControlWnd.h"
#include "../../../Module/api/GloblaDrawFunctions.h"

#include "CommCmdGrid_Analogs.h"
#include "..\TCtrlCntrConfig.h"
// CUICommCmdViewDlg 对话框

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BOOL atsrpc_IsSmartTestRpc();

#ifdef _UITEST_USE_DIALOGEX
#else
IMPLEMENT_DYNAMIC(CUICommCmdViewDlg, CDialog)
#endif

CUICommCmdViewDlg::CUICommCmdViewDlg(CWnd* pParent /*=NULL*/)
//: CDialog(CUICommCmdViewDlg::IDD, pParent)
{
	m_bEnterTimeTrigger = FALSE;
	m_pTestCtrlWndRef = NULL;
	m_nIDEvent = 0;
	m_pParentWnd = pParent;
}

CUICommCmdViewDlg::~CUICommCmdViewDlg()
{

}

void CUICommCmdViewDlg::DoDataExchange(CDataExchange* pDX)
{
#ifdef _UITEST_USE_DIALOGEX
	CDynDialogEx::DoDataExchange(pDX);
#else
	CDialog::DoDataExchange(pDX);
#endif
}

#ifdef _UITEST_USE_DIALOGEX
BEGIN_MESSAGE_MAP(CUICommCmdViewDlg, CDynDialogEx)
#else
BEGIN_MESSAGE_MAP(CUICommCmdViewDlg, CDialog)
#endif
	ON_WM_CLOSE()
	ON_WM_CHAR()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CUICommCmdViewDlg 消息处理程序

void CUICommCmdViewDlg::OnCancel()
{
}

void CUICommCmdViewDlg::OnOK()
{
}

void CUICommCmdViewDlg::OnClose()
{
	if (m_pTestCtrlWndRef == NULL)
	{
		return;
	}

	if (m_nIDEvent == 0)
	{
		return;
	}

	SHORT nState = ::GetKeyState(VK_CONTROL);

	if ((nState & 0xFF00) > 0)
	{
		((CTestControlWnd*)m_pTestCtrlWndRef)->FireOnTimer(m_nIDEvent);
		m_nIDEvent = 0;
	}
}

BOOL CUICommCmdViewDlg::OnInitDialog()
{
#ifdef _UITEST_USE_DIALOGEX
	CDynDialogEx::OnInitDialog();
#else
	CDialog::OnInitDialog();
#endif

	CRect rcClient;
	GetClientRect(rcClient);
	rcClient.right =rcClient.left +  450;
	rcClient.DeflateRect(4,4,4,4);
	m_gridAttr.CreateGrid(this, rcClient, 0x940);
	CRect rcView;
	m_gridAttr.GetViewRect(&rcView);
	rcView.bottom += 20;
	long nHeight = rcClient.Height() - rcView.Height();
	m_gridAttr.ShowWindow(SW_SHOW);
	CenterWindow();

	CRect rcItem;
	nHeight = m_gridAttr.GetItemRect(0, &rcItem, LVIR_BOUNDS);
	nHeight = rcItem.Height() * 11;
	nHeight += 12;

	CRect rcDlg;
	GetWindowRect(rcDlg);
	rcDlg.right = rcDlg.left + 450;
	nHeight = rcClient.Height() - nHeight;
	rcDlg.bottom -= nHeight;
	rcDlg.bottom += 24;
	MoveWindow(rcDlg, FALSE);
	CenterWindow();

	rcClient.bottom -= nHeight;
	m_gridAttr.MoveWindow(rcClient, FALSE);
	rcClient.top = rcClient.bottom+4;
	rcClient.bottom += 20;
	CreateStatic(m_wndTimerText, _T(""),  rcClient,  0x941, this);
	m_wndTimerText.SetFont(g_pGlobalFont11);

	return TRUE;
}

void CUICommCmdViewDlg::InitTestItem(CCommCmd* pTestItemCommCmd, const CString &strTitle)
{
	try
	{
		m_strGuideBookTitle = strTitle;
		m_gridAttr.ShowCommCmdAttr(pTestItemCommCmd);

		if (m_strGuideBookTitle.GetLength() > 0)
		{
			m_gridAttr.ShowAttr(_T(""), m_strGuideBookTitle);
		}

		if (g_bShowTestWndTop)
		{
			if ( (!CTCtrlCntrConfig::IsShowTestSpyWnd()) && atsrpc_IsSmartTestRpc())
			{
				if (IsWindowVisible())
				{
					ShowWindow(SW_HIDE);
				}
			}
			else
			{
				ShowWindow(SW_SHOW);
			}
		}
		else
		{
			ShowWindow(SW_HIDE);
		}
	}
	catch (...)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR,_T("CUICommCmdViewDlg::InitTestItem:  error"));
	}

	m_nTimerLong = 0;
}

void CUICommCmdViewDlg::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

#ifdef _UITEST_USE_DIALOGEX
	CDynDialogEx::OnChar(nChar, nRepCnt, nFlags);
#else
	CDialog::OnChar(nChar, nRepCnt, nFlags);
#endif
}

void CUICommCmdViewDlg::ShowCommMessage(const CString &strMsg, BOOL bCreateTimer)
{
	try
	{
		m_strCmdMessage = strMsg;

		if (bCreateTimer)
		{
			SetTimer(TIMER_COMMMESSAGE, 1000, NULL);
		}
		else
		{
			KillTimer(TIMER_COMMMESSAGE);
		}

		SetWindowText(m_strCmdMessage);
	}
	catch (...)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR,_T("CUICommCmdViewDlg::ShowCommMessage:  error"));
	}

	m_nTimerLong = 0;
}

void CUICommCmdViewDlg::ShowCommViewDlg(DWORD dwShow)
{
	try
	{
		//2020-06-21  lijunqing 忘记为什么要增加IsShowTestSpyWnd了
		ShowWindow(dwShow);

		if (SW_HIDE == dwShow)
		{
			m_bEnterTimeTrigger = FALSE;
		}
	}
	catch (...)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR,_T("CUICommCmdViewDlg::ShowCommViewDlg:  error"));
	}

}

void CUICommCmdViewDlg::Gbs_EnterTimeTrigger()
{
	m_bEnterTimeTrigger = TRUE;
}

CString CUICommCmdViewDlg::GetTimerString()
{
	CString strTime;

	if (m_nTimerLong > 3600)
	{
			long nHour = m_nTimerLong / 3600;
			long nMinute = (m_nTimerLong - nHour * 3600) / 60;
			long nSecond = m_nTimerLong % 60;
			strTime.Format(_T("%d:%d:%d"), nHour, nMinute, nSecond);
	}
	else if (m_nTimerLong > 60)
	{
		long nMinute = m_nTimerLong  / 60;
		long nSecond = m_nTimerLong % 60;
		strTime.Format(_T("%d:%d"), nMinute, nSecond);
	}
	else
	{
		strTime.Format(_T("%d"), m_nTimerLong);
	}

	return strTime;
}

void CUICommCmdViewDlg::InitTestItem(long nMaxCount, long nCurrIndex, long nTimerLong)
{
	try
	{
		CString strText;

		if (nMaxCount > 0)
		{
			strText.Format(_T("%d / %d"), nCurrIndex, nMaxCount);
			m_gridAttr.ShowAttr(_T("数据处理进度"), strText, COMMCMD_ATTR_ROW_MAXREAD);
			m_gridAttr.ShowAttr(_T("时间间隔"), nTimerLong, COMMCMD_ATTR_ROW_TIMEGAP);
		}
		else
		{
			m_gridAttr.ShowAttr(_T(""), _T(""), COMMCMD_ATTR_ROW_MAXREAD);
			m_gridAttr.ShowAttr(_T(""), _T(""), COMMCMD_ATTR_ROW_TIMEGAP);
		}
	}
	catch (...)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR,_T("CUICommCmdViewDlg::InitTestItem:  error"));
	}

}

void CUICommCmdViewDlg::OnTimer(UINT_PTR nIDEvent)
{
	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, L"TestControlWnd::OnTimer(%d)", nIDEvent);
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	m_nTimerLong++;

	if (TIMER_COMMMESSAGE == nIDEvent)
	{
		CString strTitle;

		if (m_bEnterTimeTrigger)
		{
			SYSTEMTIME tmSys;
			::GetLocalTime(&tmSys);
			strTitle.Format(_T("%s : %s       %d:%d:%d"), m_strCmdMessage, GetTimerString()
				, tmSys.wHour, tmSys.wMinute, tmSys.wSecond);
		}
		else
		{
			strTitle.Format(_T("%s : %s"), m_strCmdMessage, GetTimerString());
		}

		//strTitle.Format(_T("%s:%s : %d"), m_strGuideBookTitle, m_strCmdMessage, m_nTimerLong * 1000);
		m_wndTimerText.SetWindowText(strTitle);
	}

#ifdef _UITEST_USE_DIALOGEX
	CDynDialogEx::OnTimer(nIDEvent);
#else
	CDialog::OnTimer(nIDEvent);
#endif
}
