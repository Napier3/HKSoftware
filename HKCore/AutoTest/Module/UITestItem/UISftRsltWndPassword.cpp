#include "stdafx.h"
#include "UISftRsltWndPassword.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CUISftRsltWndPassword::CUISftRsltWndPassword()
{
	m_pEditPsw = NULL;
	m_pEditUserName = NULL;
	m_nTimerID = -1;
	m_strUserID = L"a001";
}

CUISftRsltWndPassword::~CUISftRsltWndPassword()
{
	if (m_pEditPsw != NULL)
	{
		delete m_pEditPsw;
		m_pEditPsw = NULL;
	}

	if (m_pEditUserName != NULL)
	{
		delete m_pEditUserName;
		m_pEditUserName = NULL;
	}
}

BEGIN_MESSAGE_MAP(CUISftRsltWndPassword, CStatic)
	ON_WM_CREATE()
	ON_WM_TIMER()
END_MESSAGE_MAP()

int CUISftRsltWndPassword::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	return 0;
}

void CUISftRsltWndPassword::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_nTimerID == nIDEvent)
	{
		CString strText;
		CString strUserName;
		m_pEditPsw->GetWindowText(strText);
		BOOL bPswTrue = FALSE;


		if (m_pResultWndInterface != NULL)
		{
			if (m_strUserID == L"a001")
			{
				if (strText == L"12345")
				{
					bPswTrue = TRUE;
				}
				else
				{
				}
			}
			else if (m_strUserID == L"b001")
			{
				if (strText == L"23456")
				{
					bPswTrue = TRUE;
				}
				else
				{
				}
			}
			else
			{
			}

			if (bPswTrue)
			{
				m_pEditUserName->SetWindowText(m_strUserID);				
				m_pResultWndInterface->OnResultDataChanged(m_strUserID);
			}
			else
			{
				m_pResultWndInterface->OnResultDataChanged(_T(""));
				m_pEditUserName->SetWindowText(_T(""));
			}
		}
	}
	CStatic::OnTimer(nIDEvent);
}

void CUISftRsltWndPassword::AdjustWnd()
{
	if ( m_pEditPsw != NULL && m_pEditUserName != NULL )
	{
		CRect rcMain;
		GetWindowRect(&rcMain);
		CRect rcEdit(0,0,0,0);
		rcEdit.right = rcMain.Width() / 2;
		rcEdit.bottom = rcMain.Height() - 2;

		m_pEditPsw->MoveWindow(rcEdit);

		rcEdit.left = rcEdit.right;
		rcEdit.right += rcEdit.right;
		m_pEditUserName->MoveWindow(rcEdit);
	}
}

void CUISftRsltWndPassword::InitPassWord(const CString &strInterfaceCall, const CString &strUserName, long &nID)
{
	//m_oBuffer.ParseInterfaceCall(strInterfaceCall);
	m_strUserName = strUserName;

	//m_strUserID = m_oBuffer.m_pszInterfaceMethodID;

	if ( m_pEditPsw != NULL && m_pEditUserName != NULL )
	{
		m_pEditPsw->SetWindowText(_T(""));
		m_pEditUserName->SetWindowText(strUserName);
	}
	else
	{
		CRect rcMain;
		GetWindowRect(&rcMain);
		CRect rcEdit(0,0,0,0);
		rcEdit.right = rcMain.Width() / 2;
		rcEdit.bottom = rcMain.Height() - 2;

		m_pEditPsw = new CEdit();
		m_pEditPsw->CreateEx(WS_EX_CLIENTEDGE, _T("Edit"), _T(""), WS_CHILD|WS_VISIBLE|ES_LEFT|ES_AUTOHSCROLL | ES_PASSWORD
			, rcEdit, this, nID++);
		m_pEditPsw->EnableWindow(TRUE);

		rcEdit.left = rcEdit.right+5;
		rcEdit.right += rcEdit.right;
		m_pEditUserName = new CEdit();
		m_pEditUserName->CreateEx(WS_EX_CLIENTEDGE, _T("Edit"), _T(""), WS_CHILD|WS_VISIBLE|ES_LEFT|ES_AUTOHSCROLL | ES_READONLY
			, /*rcWnd*/rcEdit, this, nID++);
		m_pEditUserName->EnableWindow(TRUE);
	}

	if (m_nTimerID == -1)
	{
		m_nTimerID = SetTimer(2, 200, NULL);
	}
}