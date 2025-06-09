// D:\WorkLiJQ\Source\AutoTest\Module\AudioTest\UI\MainDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MainDlg.h"
#include "../../../AudioTest/AudioTest.h"
#include "../../../AudioTest/AudioTestDlg.h"
// CMainDlg 对话框

IMPLEMENT_DYNAMIC(CMainDlg, CDialog)

CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMainDlg::IDD, pParent)
{
	
}

CMainDlg::~CMainDlg()
{
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_TITLE, m_static);
	DDX_Control(pDX, IDC_BTN_NEWTEST, m_btnNewTest);
	DDX_Control(pDX, IDC_BTN_TESTRECORD, m_btnTestRecord);
	DDX_Control(pDX, IDC_BTN_SYSTEMSET, m_btnSystem);
	DDX_Control(pDX, IDC_BTN_QUITSYSTEM, m_btnQuit);
}


BEGIN_MESSAGE_MAP(CMainDlg, CDialog)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BTN_NEWTEST, &CMainDlg::OnBnClickedBtnNewtest)
	ON_BN_CLICKED(IDC_BTN_SYSTEMSET, &CMainDlg::OnBnClickedBtnSetSystem)
	ON_BN_CLICKED(IDC_BTN_QUITSYSTEM, &CMainDlg::OnBnClickedBtnQuitsystem)
END_MESSAGE_MAP()


// CMainDlg 消息处理程序


BOOL CMainDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString strPath = _P_GetResourcePath();
	strPath += "Audio/";

	m_btnNewTest.LoadBitmap(strPath + "新建测试.png");
	m_btnTestRecord.LoadBitmap(strPath + "测试记录.png");
	m_btnSystem.LoadBitmap(strPath + "系统设置.png");
	m_btnQuit.LoadBitmap(strPath + "退出系统.png");

	m_font.CreatePointFont(170, _T("Microsoft Sans Serif"));
	m_static.SetFont(&m_font);

	XUI_InitAdjust();

	return TRUE;  
}

void CMainDlg::XUI_InitAdjust()
{
	CXUIAdjItem_Area::XUI_SetParentWnd(this);

	XUI_AddWnd(&m_static, 0, 0.5, 1, 0);
	XUI_AddWnd(&m_btnNewTest, 0.25, 1, 0, 0);
	XUI_AddWnd(&m_btnTestRecord, 0.4, 1, 0, 0);
	XUI_AddWnd(&m_btnSystem, 0.6, 1, 0, 0);
	XUI_AddWnd(&m_btnQuit, 0.75, 1, 0, 0);

	CXUIAdjItem_Area::XUI_OnSize();
}

BOOL CMainDlg::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
}

void CMainDlg::OnBnClickedBtnNewtest()
{
	// TODO: 在此添加控件通知处理程序代码
	if(g_pAudioListener->m_bStartParse)
	{
		return;
	}
	g_pAudioTestDlg->OpenNewTestUI();
	g_pAudioListener->m_nWholeFlag = Flag_TipWord;
	g_pAudioListener->m_nTipWordFlag = Flag_TW_Question;
	CString strTipId = "CheckType";
	if(g_pAudioListener == NULL || g_pAudioListener->m_pAudioParser == NULL)
	{
		return;
	}
	g_pAudioListener->m_pAudioParser->m_oConfigMngr.m_oMatchWords.GetCurrentTipWord(strTipId,Flag_Flow_OK);
}

void CMainDlg::OnBnClickedBtnQuitsystem()
{
	if(g_pAudioListener->m_bStartParse)
	{
		return;
	}

	if(!g_pAudioTestDlg->m_bIsAudioFlag)
	{
		int nRet = MessageBox(("确定要退出系统吗？"),("退出系统"),MB_YESNO | MB_ICONWARNING);
		if(nRet == IDYES)
		{
			DestroyWindow();
			exit(0);
		}
	}
	else
	{
		DestroyWindow();
		exit(0);
	}
	g_pAudioTestDlg->m_bIsAudioFlag = false;
	
	return;
}

void CMainDlg::OnBnClickedBtnSetSystem()
{
	g_pAudioTestDlg->SetSetSystem(NULL);
}

void CMainDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	XUI_OnSize(cx, cy);
}