#include "stdafx.h"
#include "WzdEntrySelDlg.h"
#include "..\..\..\iSmartTestWzd\iSmartTestWzdDlg.h"
#include "../../XSttAtsTestClientImp.h"
#include "MessageDlg.h"

IMPLEMENT_DYNAMIC(CWzdEntrySelDlg, CDialog)

CWzdEntrySelDlg::CWzdEntrySelDlg(CWnd* pParent /*=NULL*/)
	: CWzdDlgBase(CWzdEntrySelDlg::IDD, pParent)
{

}

CWzdEntrySelDlg::~CWzdEntrySelDlg()
{
}

void CWzdEntrySelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_TITLE, m_txtTitle);
	DDX_Control(pDX, IDC_BTN_NEWTEST, m_btnNewTest);
	DDX_Control(pDX, IDC_BTN_OPEN, m_btnOpen);
	DDX_Control(pDX, IDC_BTN_BLUET, m_btnBluet);	//2023-06-05 huangliang  添加蓝牙按钮对象
	DDX_Control(pDX, IDC_BTN_SYSTEM, m_btnSystem);
	DDX_Control(pDX, IDC_BTN_UPDATE, m_btnUpdate);
	DDX_Control(pDX, IDC_BK, m_btnBk);
}

void CWzdEntrySelDlg::XUI_InitAdjust()
{
	CXUIAdjItem_Area::XUI_SetParentWnd(this);
	XUI_AddWnd(&m_txtTitle, 0.2, 0.1, 0.6, 0.5);
	XUI_AddWnd(&m_btnNewTest, 0.40, 0.5, 0, 0);		//2023-06-05 huangliang  修改按钮布局
	XUI_AddWnd(&m_btnBluet, 0.43, 0.5, 0, 0);	
	XUI_AddWnd(&m_btnOpen, 0.46, 0.5, 0, 0);	
	XUI_AddWnd(&m_btnSystem, 0.49, 0.5, 0, 0);
	XUI_AddWnd(&m_btnUpdate, 0.52, 0.5, 0, 0);
	XUI_AddWnd(&m_btnBk, 0, 0, 1, 1);
	CXUIAdjItem_Area::XUI_OnSize();
}

void CWzdEntrySelDlg::OnInitialUpdate()
{
	XUI_InitAdjust();
	InitUI();

	CString strIcon = _P_GetResourcePath();
	strIcon += "iSmartTestWzd/";
	m_btnNewTest.LoadImage(strIcon + "main/newtest_n.png", strIcon + "main/newtest_y.png", strIcon + "main/newtest_h.png");
	m_btnNewTest.SetImgMode(TRUE);
	m_btnOpen.LoadImage(strIcon + "main/opentest_n.png", strIcon + "main/opentest_y.png", strIcon + "main/opentest_h.png");
	m_btnOpen.SetImgMode(TRUE);

	//2023-06-05 huangliang  添加蓝牙按钮
	m_btnBluet.LoadImage(strIcon + "main/bluetooth_n.png", strIcon + "main/bluetooth_y.png", strIcon + "main/bluetooth_h.png");
	m_btnBluet.SetImgMode(TRUE);

	m_btnSystem.LoadImage(strIcon + "main/sysconfig_n.png", strIcon + "main/sysconfig_y.png", strIcon + "main/sysconfig_h.png");
	m_btnSystem.SetImgMode(TRUE);
	m_btnUpdate.LoadImage(strIcon + "main/sysupdate_n.png", strIcon + "main/sysupdate_y.png", strIcon + "main/sysupdate_h.png");
	m_btnUpdate.SetImgMode(TRUE);

	m_btnBk.LoadImage(strIcon + "bk.png", strIcon + "bk.png", strIcon + "bk.png", strIcon + "bk.png");
	m_btnBk.SetImgMode(TRUE);

	m_txtTitle.LoadImage(strIcon + "maintitle.png", strIcon + "maintitle.png", strIcon + "maintitle.png", strIcon + "maintitle.png");
	m_txtTitle.SetImgMode(TRUE);

	//stt_Start_SmartTest();
	if (IsProgramExist(_T("SmartTestCore.exe")))
	{
		return;
	}

	CString strPath;
	strPath = _P_GetInstallPath();
	strPath += _T("e-Report/Bin/");
	strPath += _T("SmartTestCore.exe");

	ExecuteFile(strPath, _T(""), _T("single"));
}

BOOL CWzdEntrySelDlg::InitUI()
{
	return TRUE;
}

BEGIN_MESSAGE_MAP(CWzdEntrySelDlg, CDialog)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_NEWTEST, &CWzdEntrySelDlg::OnBnClickedBtnNewtest)
	ON_BN_CLICKED(IDC_BTN_OPEN, &CWzdEntrySelDlg::OnBnClickedBtnOpenRecord)
	ON_BN_CLICKED(IDC_BTN_BLUET, &CWzdEntrySelDlg::OnBnClickedBtnOpenBluet)	//2023-06-05 huangliang  添加界面蓝牙按钮响应
END_MESSAGE_MAP()

void CWzdEntrySelDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	XUI_OnSize(cx, cy);
}

void CWzdEntrySelDlg::OnBnClickedBtnNewtest()
{
	g_pISmartTestWzdDlg->SetWzdMode(Wzd_Mode_CreateTest);
	g_pISmartTestWzdDlg->SetActiveDlg(DLG_STEP_Main);
	g_pISmartTestWzdDlg->InitMainCfg();
}
void CWzdEntrySelDlg::OnBnClickedBtnOpenRecord()
{
	g_pISmartTestWzdDlg->SetWzdMode(Wzd_Mode_OpenGbrpt);
	g_pISmartTestWzdDlg->SetActiveDlg(DLG_STEP_Record);
	g_pISmartTestWzdDlg->InitQueFile();
}

//2023-06-05 huangliang 打开蓝牙界面
void CWzdEntrySelDlg::OnBnClickedBtnOpenBluet()
{
	CString strTitle, strText;
	strText = _T("根据网安要求，将开启蓝牙服务，请确保已拔出网线");
	strTitle = _T("警告");
	long nRet = MessageDlg::MessageBox(strTitle, strText, MessageDlg::YESANDNO);

	if (nRet == IDCANCEL)
	{
		return;
	}

	//禁用网卡
	g_pISmartTestWzdDlg->SetNetCardState(FALSE);

	g_pISmartTestWzdDlg->SetWzdMode(Wzd_Mode_BlueToothTask);
	g_pISmartTestWzdDlg->SetActiveDlg(DLG_STEP_Bluetooth);
	g_pISmartTestWzdDlg->InitBluetooth();
}