// SttTestAppIPConfigDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SttTestAppIPConfigDlg.h"
#include "..\..\SttCmd\SttParas.h"
#include "..\..\SttGlobalDef.h"

#define STT_STC_TESTAPP_DEVICEIP		0x000002060
#define STT_EDIT_TESTAPP_DEVICEIP		0x000002061
#define STT_STC_TESTAPP_DEVICEMASK		0x000002062
#define STT_EDIT_TESTAPP_DEVICEMASK		0x000002063
#define STT_BTN_OK		0x000002060
#define STT_BTN_CANCEL	0x000002061


// CSttTestAppIPConfigDlg 对话框

//IMPLEMENT_DYNAMIC(CSttTestAppIPConfigDlg, CDialog)

CSttTestAppIPConfigDlg::CSttTestAppIPConfigDlg(CDataGroup *pDvGroup,CWnd* pParent /*=NULL*/)
//	: CDialog(CSttTestAppIPConfigDlg::IDD, pParent)
	: CDynDialogEx(pParent)
{
	m_pDvGroup = pDvGroup;
	m_pGlobalFont11 = font_CreateNew(g_lfGlobalFont11, -11);
}

CSttTestAppIPConfigDlg::~CSttTestAppIPConfigDlg()
{
	if (m_pGlobalFont11 != NULL)
	{
		delete m_pGlobalFont11;
	}
}

void CSttTestAppIPConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDynDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSttTestAppIPConfigDlg, CDynDialogEx)
	ON_BN_CLICKED(STT_BTN_OK, &CSttTestAppIPConfigDlg::OnBtnClickOK)
	ON_BN_CLICKED(STT_BTN_CANCEL, &CSttTestAppIPConfigDlg::OnBtnClickCancel)
END_MESSAGE_MAP()


// CSttTestAppIPConfigDlg 消息处理程序

BOOL CSttTestAppIPConfigDlg::OnInitDialog()
{
	CDynDialogEx::OnInitDialog();

	CreateStatic(m_stcDeviceIP,_T("IP："), CRect(10,20,50,45), STT_STC_TESTAPP_DEVICEIP, this);
	m_ctrlDeviceIP.Create(WS_TABSTOP | WS_CHILD | WS_VISIBLE, CRect(50,20,230,45), this, STT_EDIT_TESTAPP_DEVICEIP); 
	CreateStatic(m_stcDeviceMask,_T("子网掩码："), CRect(250,20,340,45), STT_STC_TESTAPP_DEVICEMASK, this);
	m_ctrlDeviceMask.Create(WS_TABSTOP | WS_CHILD | WS_VISIBLE, CRect(340,20,520,45), this, STT_EDIT_TESTAPP_DEVICEMASK); 
	CreateButton(m_btnCancel,_T("取消"), CRect(180,215,260,240), STT_BTN_CANCEL, this);
	CreateButton(m_btnOK,_T("确定"), CRect(270,215,350,240), STT_BTN_OK, this);

	m_stcDeviceIP.SetFont(g_pGlobalFont12);
	m_ctrlDeviceIP.SetFont(g_pGlobalFont12);
	m_stcDeviceMask.SetFont(g_pGlobalFont12);
	m_ctrlDeviceMask.SetFont(g_pGlobalFont12);
	m_btnCancel.SetFont(g_pGlobalFont12);
	m_btnOK.SetFont(g_pGlobalFont12);

	if (m_pDvGroup != NULL)
	{
		CDataGroup *pDvIPGroup = m_pDvGroup->FindByDataType(STT_SYS_DATA_ID_DeviceIP);
		if (pDvIPGroup != NULL)
		{
			CString strIP=_T(""),strMask=_T("");
			stt_GetDataValueByID(pDvIPGroup, STT_SYS_DATA_ID_IP, strIP);
			stt_GetDataValueByID(pDvIPGroup, STT_SYS_DATA_ID_mask, strMask);
			m_ctrlDeviceIP.SetWindowText(strIP);
			m_ctrlDeviceMask.SetWindowText(strMask);
		}	
	}
	
	MoveWindow(CRect( 0, 0, 530, 280), TRUE);
	CenterWindow();
	SetWindowText(_T("测试仪IP配置"));

	return TRUE;
}

void CSttTestAppIPConfigDlg::OnBtnClickOK()
{
	CString strIP=_T(""),strMask=_T("");
	m_ctrlDeviceIP.GetWindowText(strIP);
	m_ctrlDeviceMask.GetWindowText(strMask);

	if (strIP.IsEmpty() || strMask.IsEmpty())
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("IP和子网掩码不能为空"));
		return;
	}

	m_strDeviceIP = strIP;
	m_strDeviceMask = strMask;

	CDynDialogEx::OnOK();	
}

void CSttTestAppIPConfigDlg::OnBtnClickCancel()
{
	CDynDialogEx::OnCancel();	
}
