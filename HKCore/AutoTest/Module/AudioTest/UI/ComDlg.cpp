// D:\WorkLiJQ\Source\AutoTest\Module\AudioTest\UI\ComDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ComDlg.h"
#include <Windows.h>
#include "../../../AudioTest/AudioTest.h"
#include "../../../AudioTest/AudioTestDlg.h"


// CComDlg 对话框

IMPLEMENT_DYNAMIC(CComDlg, CDialog)

CComDlg::CComDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CComDlg::IDD, pParent)
{
	m_bListen = false;
	m_bTestFlag = false;
}

CComDlg::~CComDlg()
{
}

void CComDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_START, m_btnListen);
	DDX_Control(pDX, IDC_BTN_SERVER, m_btnServer);
	DDX_Control(pDX, IDC_BTN_LISTENER, m_btnListener);
	DDX_Control(pDX, IDC_LIST_LOG, m_ctrlLogListBox);
	DDX_Control(pDX, IDC_STATIC_LISTENER, m_txtListener);
	DDX_Control(pDX, IDC_STATIC_SERVER, m_txtServer);
}

void CComDlg::UpdateState(int nFlag)
{
	CString strPath = _P_GetResourcePath();
	strPath += "Audio/";

	//if(g_pAudioListener->m_bStartParse)
	if(nFlag)
	{
		//m_btnListen.LoadBitmap(strPath + "停止录入.png");
		
		m_btnListen.LoadBitmap(strPath + "开始录入.png");
		m_btnListen.Invalidate();

		
		m_btnListener.LoadBitmap(strPath + "运行.png");
		m_btnListener.Invalidate();
	}
	else
	{
		//m_btnListen.LoadBitmap(strPath + "开始录入.png");
		
		m_btnListen.LoadBitmap(strPath + "停止录入.png");
		m_btnListen.Invalidate();
		
		m_btnListener.LoadBitmap(strPath + "停止.png");
		m_btnListener.Invalidate();
	}

	UpdateWindow();
}

void CComDlg::XUI_InitAdjust()
{
	CXUIAdjItem_Area::XUI_SetParentWnd(this);

	XUI_AddWnd(&m_ctrlLogListBox, 0.25, 0.5, 0, 0);
	XUI_AddWnd(&m_btnServer, 0.25, 0.5, 0, 0);
	XUI_AddWnd(&m_btnListener, 0.25, 0.5, 0, 0);
	XUI_AddWnd(&m_btnListen, 0.25, 0.5, 0, 0);
	XUI_AddWnd(&m_txtListener, 0.25, 0.5, 0, 0);
	XUI_AddWnd(&m_txtServer, 0.25, 0.5, 0, 0);

	CXUIAdjItem_Area::XUI_OnSize();
}

BEGIN_MESSAGE_MAP(CComDlg, CDialog)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BTN_START, &CComDlg::OnBnClickedBtnStart)
	ON_BN_CLICKED(IDC_BUTTON_RETURN, &CComDlg::OnBnClickedButtonReturn)
	ON_BN_CLICKED(IDC_BUTTON_TEST_STOP, &CComDlg::OnBnClickedButtonTestStop)
	ON_BN_CLICKED(IDC_BUTTON_TEST_GO, &CComDlg::OnBnClickedButtonTestGo)
	ON_BN_CLICKED(IDC_BUTTON_TEST_CLOSE, &CComDlg::OnBnClickedButtonTestClose)
END_MESSAGE_MAP()

// CComDlg 消息处理程序

BOOL CComDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	XUI_InitAdjust();

	CString strPath = _P_GetResourcePath();
	strPath += "Audio/";

	//m_btnListen.LoadBitmap(strPath + "开始录入.png");
	m_btnListen.LoadBitmap(strPath + "停止录入.png");
	m_btnListener.LoadBitmap(strPath + "停止.png");
	m_btnServer.LoadBitmap(strPath + "运行.png");

	SetBtnSize(false);

	
	return TRUE;
}

void CComDlg::OnBnClickedBtnStart()
{
	/*if(g_pAudioListener->m_bStartParse)
	{
		return;
	}*/

	//m_bListen = true;

	if(!g_pAudioListener->m_bAutioPowerFlag)
	{
		return;
	}
	if(g_pAudioTestDlg->m_pAudioParser->m_bVoiceFlag)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("【提示信息：】 正在播报语音，请稍后！"));
		return;
	}

	if(!g_pAudioListener->m_bStartParse)
	{
		//m_bListen = true;
		//m_btnListen.LoadBitmap(strPath + "开始录入.png");
		//g_pAudioListener->m_strStartKey
		g_pAudioListener->SetBtnKey(g_pAudioListener->m_strStartKey);
	}
	else
	{
		//m_bListen = false;
		//m_btnListen.LoadBitmap(strPath + "停止录入.png");
		g_pAudioListener->SetBtnKey(g_pAudioListener->m_strStopKey);
	}

//CString strPath = _P_GetResourcePath();
	//strPath += "Audio/";
	/*if(!m_bListen)
	{
		m_bListen = true;
		m_btnListen.LoadBitmap(strPath + "停止录入.png");
	}
	else
	{
		m_bListen = false;
		m_btnListen.LoadBitmap(strPath + "开始录入.png");
	}*/
}

BOOL CComDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN)
		return TRUE; 
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_ESCAPE)    
		return TRUE; 
	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CComDlg::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
}

void CComDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	XUI_OnSize(cx, cy);
}

void CComDlg::InitLogListBox(int nFlag,CString strPath)
{
	if(nFlag)
	{
		strPath += "AudioTest.txt";
		/*CString strTime; //获取系统时间
		CTime cTime; 
		cTime = CTime::GetCurrentTime();
		strTime = cTime.Format("%Y-%m-%d-%H-%M");
		strTime += _T(".txt");
		strPath += strTime;*/
		CLogPrint::CreateLogFile(strPath);
	}
}

void CComDlg::SetBtnSize(bool bFlag)
{
	CRect rcButton;
	if(!bFlag)
	{
		GetDlgItem(IDC_BUTTON_RETURN)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_TEST_STOP)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_TEST_GO)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_TEST_CLOSE)->ShowWindow(SW_HIDE);

		//CRect rcButton;
		m_btnListen.GetWindowRect(&rcButton);
		ScreenToClient(rcButton);
		m_btnListen.MoveWindow(rcButton.left,rcButton.top+25,rcButton.Width(),rcButton.Height());
		m_bTestFlag = false;
	}
	else
	{
		GetDlgItem(IDC_BUTTON_RETURN)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_TEST_STOP)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_TEST_GO)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_TEST_CLOSE)->ShowWindow(SW_SHOW);

		//CRect rcButton;
		m_btnListen.GetWindowRect(&rcButton);
		ScreenToClient(rcButton);
		m_btnListen.MoveWindow(rcButton.left,rcButton.top-25,rcButton.Width(),rcButton.Height());
		m_bTestFlag = true;
	}
	InvalidateRect(rcButton);
	m_btnListen.Invalidate();
}

void CComDlg::SetBtnState(int nTestState)
{
	if(nTestState == AUTOTEST_CREATE || nTestState == AUTOTEST_START)
	{
		GetDlgItem(IDC_BUTTON_TEST_STOP)->EnableWindow(true);
		GetDlgItem(IDC_BUTTON_TEST_GO)->EnableWindow(false);
		GetDlgItem(IDC_BUTTON_TEST_CLOSE)->EnableWindow(false);
		GetDlgItem(IDC_BUTTON_RETURN)->EnableWindow(false);
	}
	else if(nTestState == AUTOTEST_STOP)
	{
		GetDlgItem(IDC_BUTTON_TEST_STOP)->EnableWindow(false);
		GetDlgItem(IDC_BUTTON_TEST_GO)->EnableWindow(true);
		GetDlgItem(IDC_BUTTON_TEST_CLOSE)->EnableWindow(true);
		GetDlgItem(IDC_BUTTON_RETURN)->EnableWindow(false);
	}
	else if(nTestState == AUTOTEST_CLOSE || AUTOTEST_FINISH)
	{
		GetDlgItem(IDC_BUTTON_TEST_STOP)->EnableWindow(false);
		GetDlgItem(IDC_BUTTON_TEST_GO)->EnableWindow(false);
		GetDlgItem(IDC_BUTTON_TEST_CLOSE)->EnableWindow(false);
		GetDlgItem(IDC_BUTTON_RETURN)->EnableWindow(true);
	}
}

void CComDlg::OnBnClickedButtonReturn()
{
	// TODO: 在此添加控件通知处理程序代码
	if((!m_bTestFlag) || (g_pAudioListener->m_bStartParse))
	{
		return;
	}
	g_pAudioTestDlg->ReturnNewTestUI();
}

void CComDlg::OnBnClickedButtonTestStop()
{
	// TODO: 在此添加控件通知处理程序代码
	if((!m_bTestFlag) || (g_pAudioListener->m_bStartParse))
	{
		return;
	}
	g_pAudioTestDlg->StopTest();
}

void CComDlg::OnBnClickedButtonTestGo()
{
	// TODO: 在此添加控件通知处理程序代码
	if((!m_bTestFlag) || (g_pAudioListener->m_bStartParse))
	{
		return;
	}
	g_pAudioTestDlg->TestGo();
}

void CComDlg::OnBnClickedButtonTestClose()
{
	// TODO: 在此添加控件通知处理程序代码
	if((!m_bTestFlag) || (g_pAudioListener->m_bStartParse))
	{
		return;
	}
	g_pAudioTestDlg->CloseTest();
}
