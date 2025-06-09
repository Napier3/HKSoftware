// XSafenetXUserDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "XSafenetXUserDlg.h"
#include "..\..\Module\API\GloblaDrawFunctions.h"
#include "..\XLanguage\XLanguageResource.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// CXSafenetXUserDlg 对话框

//IMPLEMENT_DYNAMIC(CXSafenetXUserDlg, CDynDialogEx)

CXSafenetXUserDlg::CXSafenetXUserDlg(CWnd* pParent /*=NULL*/)
	: CDynDialogEx(pParent)
{
	m_bHasInitDialog = FALSE;
	m_bAddSystemButtons = FALSE;
}

CXSafenetXUserDlg::~CXSafenetXUserDlg()
{
}

void CXSafenetXUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDynDialogEx::DoDataExchange(pDX);

	if (!m_bHasInitDialog)
	{
		return;
	}

	//DDX_Control(pDX, IDOK, m_btnOK);
}


BEGIN_MESSAGE_MAP(CXSafenetXUserDlg, CDynDialogEx)
	ON_MESSAGE(WM_XUSERTCPCLIENT_CMD, &CXSafenetXUserDlg::OnXUserCmdResult)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CXSafenetXUserDlg 消息处理程序

void CXSafenetXUserDlg::OnEnChangeEditDestName()
{
	
}

/*
int CXSafenetXUserDlg::DoModal()   
{   
	CRect rectOK(96,70,96+50,70+14);   
	AddDlgControl(_T("BUTTON"), _T("确定"), STYLE_BUTTON, EXSTYLE_BUTTON, &rectOK, &m_btnOK, IDOK);   

	CRect rectCancel(154,70,154+50,70+14);   
	AddDlgControl(_T("BUTTON"), _T("取消"), STYLE_BUTTON, EXSTYLE_BUTTON, &rectCancel, NULL, IDCANCEL);   

	CRect rectTitleSrc(15,14,15+41,14+8);   
	AddDlgControl(_T("STATIC"), _T("原文件名称"), STYLE_STATIC, EXSTYLE_STATIC, &rectTitleSrc);   

	CRect rectTitleDst(7,30,7+49,14+8);   
	AddDlgControl(_T("STATIC"), _T("目标文件名称"), STYLE_STATIC, EXSTYLE_STATIC, &rectTitleDst);   

	CRect rectEditSrc(62,11,62+231,11+14);   
	AddDlgControl(_T("EDIT"), _T(""), STYLE_EDIT, EXSTYLE_EDIT, rectEditSrc, NULL, XFIDC_EDIT_SRC_NAME);   

	CRect rectEditDst(62,27,62+231,27+14);   
	AddDlgControl(_T("EDIT"), _T(""), STYLE_EDIT, EXSTYLE_EDIT, rectEditDst, NULL, XFIDC_EDIT_DEST_NAME);   

	CRect rectEditInfor(7,49,7+286,49+14);   
	AddDlgControl(_T("EDIT"), _T(""), STYLE_EDIT|ES_READONLY, EXSTYLE_EDIT, rectEditInfor, NULL, XFIDC_EDIT_INFOR);   

	int iRet = CDynDialogEx::DoModal();   

	return iRet;   
}   
*/

/*
IDD_DIALOG_STCFGFILE_EDIT DIALOGEX 0, 0, 300, 91
STYLE DS_SETFONT | DS_MODALFRAME | DS_FIXEDSYS | WS_POPUP | WS_CAPTION | WS_SYSMENU
CAPTION "修改文件名称"
FONT 8, "MS Shell Dlg", 400, 0, 0x1
	DEFPUSHBUTTON   "确定",IDOK,96,70,50,14
	PUSHBUTTON      "取消",IDCANCEL,154,70,50,14
	LTEXT           "原文件名称",IDC_STATIC,15,14,41,8
	LTEXT           "目标文件名称",IDC_STATIC,7,30,49,8
	EDITTEXT        XFIDC_EDIT_SRC_NAME,62,11,231,14,ES_AUTOHSCROLL | ES_READONLY
	EDITTEXT        XFIDC_EDIT_DEST_NAME,62,27,231,14,ES_AUTOHSCROLL
	EDITTEXT        XFIDC_EDIT_INFOR,7,49,286,14,ES_AUTOHSCROLL | ES_READONLY
*/


BOOL CXSafenetXUserDlg::OnInitDialog()
{
	CDynDialogEx::OnInitDialog();

	CreateEdit(m_edtInfor, CRect(10,10,400,30), 1916, this, EXSTYLE_EDIT, STYLE_EDIT| ES_READONLY);

	CFont *pFont = g_pGlobalFont;
	m_edtInfor.SetFont(g_pGlobalFont);

	m_bHasInitDialog = TRUE;

	MoveWindow(CRect( 0, 0, 410, 80), TRUE);
	CenterWindow();
	SetWindowText(g_sLangTxt_ServerLicense/*_T("服务器授权")*/);

	m_pSafenet_XUser->SetMsgRcvWnd(this);
	m_dwCurrXUserCmd = SAFENET_XUSER_CMD_CATALOG;
	SetTimer(XSAFENET_XUSER_TCPCLIENT_TIMER_ID, XSAFENET_XUSER_TCPCLIENT_TIMER_LONG, NULL);
	SetTimer(XSAFENET_XUSER_OVERTIMER_ID, XSAFENET_XUSER_OVERTIMER_LONG, NULL);
	m_edtInfor.SetWindowText(g_sLangTxt_ServerLicense2/*_T("从服务器获取授权信息，请稍候......")*/);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CXSafenetXUserDlg::OnOK()
{
	//CDynDialogEx::OnOK();
}

void CXSafenetXUserDlg::OnCancel()
{
	CDynDialogEx::OnCancel();
}

void CXSafenetXUserDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == XSAFENET_XUSER_TCPCLIENT_TIMER_ID)
	{
		KillTimer(XSAFENET_XUSER_TCPCLIENT_TIMER_ID);
		m_pSafenet_XUser->XUserTcpClient_Wait(m_dwCurrXUserCmd);

		CDynDialogEx::OnTimer(nIDEvent);

		if (!m_pSafenet_XUser->IsConnectSucc())
		{
			CDynDialogEx::OnCancel();
		}
	}
	else if (nIDEvent == XSAFENET_XUSER_OVERTIMER_ID)
	{
		m_pSafenet_XUser->DisconnectServer();
		CLogPrint::LogString(XLOGLEVEL_TRACE, g_sLangTxt_LicenseCommun/*_T("与授权服务器通信超时，请确保网络连接和服务器配置正确！")*/);
		KillTimer(XSAFENET_XUSER_OVERTIMER_ID);
		CDynDialogEx::OnTimer(nIDEvent);
		CDynDialogEx::OnCancel();
	}
}

HRESULT CXSafenetXUserDlg::OnXUserCmdResult(WPARAM wParam, LPARAM lParam)
{
	KillTimer(XSAFENET_XUSER_OVERTIMER_ID);
	CDvmData *pData = (CDvmData*)wParam;

	if (pData->m_strID == XUSER_CMD_HASFETURE)
	{
		m_dwCurrXUserCmd = SAFENET_XUSER_CMD_GETINFOR;
#ifdef UNICODE
		m_pSafenet_XUser->SetHasFetureID( CString_To_long(pData->m_strValue));
#else
#ifdef _DVM_VALUE_USE_CHAR_
		m_pSafenet_XUser->SetHasFetureID( _wtol(pData->m_strValue));
#else
		m_pSafenet_XUser->SetHasFetureID( atol(pData->m_strValue));
#endif
#endif

		if (m_pSafenet_XUser->HasFetureID())
		{
			SetTimer(XSAFENET_XUSER_TCPCLIENT_TIMER_ID, XSAFENET_XUSER_TCPCLIENT_TIMER_LONG, NULL);
			SetTimer(XSAFENET_XUSER_OVERTIMER_ID, XSAFENET_XUSER_OVERTIMER_LONG, NULL);
		}
		else
		{
			CDynDialogEx::OnCancel();
		}

		pData->DeleteAll();
		return 0;
	}


	if (pData->m_strID == XUSER_CMD_GETINFOR)
	{
		m_pSafenet_XUser->hasp_set_ownership(pData->GetValueByID(XUSER_CMD_PARA_ownership));
		m_pSafenet_XUser->hasp_set_develop(pData->GetValueByID(XUSER_CMD_PARA_develop));
		m_pSafenet_XUser->hasp_set_user_cop(pData->GetValueByID(XUSER_CMD_PARA_user_cop));
		m_pSafenet_XUser->hasp_set_user_name(pData->GetValueByID(XUSER_CMD_PARA_user_name));
		m_pSafenet_XUser->hasp_set_sys_name(pData->GetValueByID(XUSER_CMD_PARA_sys_name));

		m_pSafenet_XUser->hasp_set_safenet_sn(pData->GetValueByID(XUSER_CMD_PARA_safenet_sn));
		m_pSafenet_XUser->hasp_set_user_cop_sn(pData->GetValueByID(XUSER_CMD_PARA_user_cop_sn));
		m_pSafenet_XUser->hasp_set_test_apps(pData->GetValueByID(XUSER_CMD_PARA_test_apps));
		m_pSafenet_XUser->hasp_set_test(pData->GetValueByID(XUSER_CMD_PARA_test));
		m_pSafenet_XUser->hasp_set_template_authority_sn(pData->GetValueByID(XUSER_CMD_PARA_authority_sn));

		pData->DeleteAll();
		CDynDialogEx::OnOK();

		return 0;
	}

	pData->DeleteAll();
	return 0;
}

