// SetConfigDlg.cpp : 实现文件
//

#include "stdafx.h"
//#include "AudioTest.h"
#include "SetConfigDlg.h"
#include "../../../AudioTest/AudioTest.h"
#include "../../../AudioTest/AudioTestDlg.h"


// CSetConfigDlg 对话框

IMPLEMENT_DYNAMIC(CSetConfigDlg, CDialog)

CSetConfigDlg::CSetConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetConfigDlg::IDD, pParent)
{

}

CSetConfigDlg::~CSetConfigDlg()
{
}

void CSetConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_STARKEY, m_ctrlStarKey);
	DDX_Control(pDX, IDC_EDIT_ENDKEY, m_ctrlEndKey);
	DDX_Control(pDX, IDC_EDIT_WAKEUP_KEY, m_ctrlWakeUpKey);
	DDX_Control(pDX, IDC_EDIT_LISTENER_TIME, m_ctrlTime);
}

BEGIN_MESSAGE_MAP(CSetConfigDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_OK, &CSetConfigDlg::OnBnClickedButtonOK)
	ON_BN_CLICKED(IDC_BUTTON_RETURN, &CSetConfigDlg::OnBnClickedButtonReturn)
END_MESSAGE_MAP()


// CSetConfigDlg 消息处理程序
void CSetConfigDlg::XUI_InitAdjust()
{
	CXUIAdjItem_Area::XUI_SetParentWnd(this);

	CXUIAdjItem_Area::XUI_OnSize();
}

BOOL CSetConfigDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	XUI_InitAdjust();

	m_ctrlStarKey.SetState(2);
	m_ctrlEndKey.SetState(2);
	m_ctrlTime.SetState(1);
	m_ctrlWakeUpKey.SetState(3);

	CDvmData* pStarKey = (CDvmData*)g_pAudioTestDlg->m_pAudioParser->m_oConfigMngr.m_oAppConfig.FindByID(CFG_STARTKEY);
	CDvmData* pEndKey = (CDvmData*)g_pAudioTestDlg->m_pAudioParser->m_oConfigMngr.m_oAppConfig.FindByID(CFG_STOPKEY);
	CDvmData* pWakeUpKey = (CDvmData*)g_pAudioTestDlg->m_pAudioParser->m_oConfigMngr.m_oAppConfig.FindByID(CFG_KEYWORD);
	CDvmData* pTime = (CDvmData*)g_pAudioTestDlg->m_pAudioParser->m_oConfigMngr.m_oAppConfig.FindByID(CFG_VOICETIME);

	if(pStarKey == NULL || pEndKey == NULL || pWakeUpKey == NULL || pTime == NULL)
	{
		return FALSE;
	}
	
	m_ctrlStarKey.SetWindowText(pStarKey->m_strValue);
	m_ctrlEndKey.SetWindowText(pEndKey->m_strValue);
	m_ctrlWakeUpKey.SetWindowText(pWakeUpKey->m_strValue);
	m_ctrlTime.SetWindowText(pTime->m_strValue);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CSetConfigDlg::OnBnClickedButtonOK()
{
	CString strStarKey(""),strEndKey(""),strWakeUp(""),strTime("");
	m_ctrlStarKey.GetWindowText(strStarKey);
	m_ctrlEndKey.GetWindowText(strEndKey);
	m_ctrlWakeUpKey.GetWindowText(strWakeUp);
	m_ctrlTime.GetWindowText(strTime);

	g_pAudioTestDlg->m_pAudioParser->m_oConfigMngr.SetConfigValue(CFG_STARTKEY,strStarKey);
	g_pAudioTestDlg->m_pAudioParser->m_oConfigMngr.SetConfigValue(CFG_STOPKEY,strEndKey);
	g_pAudioTestDlg->m_pAudioParser->m_oConfigMngr.SetConfigValue(CFG_KEYWORD,strWakeUp);
	g_pAudioTestDlg->m_pAudioParser->m_oConfigMngr.SetConfigValue(CFG_VOICETIME,strTime);

	g_pAudioTestDlg->m_pAudioParser->m_oConfigMngr.SaveConfig();
}

void CSetConfigDlg::OnBnClickedButtonReturn()
{
	g_pAudioTestDlg->ReturnNewTestUI();
}