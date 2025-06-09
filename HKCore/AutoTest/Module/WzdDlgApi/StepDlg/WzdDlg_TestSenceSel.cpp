#include "stdafx.h"
#include "WzdMainDlg.h"
#include "WzdDlg_TestSenceSel.h"
#include "MessageDlg.h"

IMPLEMENT_DYNAMIC(CWzdDlg_TestSenceSel, CDialog)

CWzdDlg_TestSenceSel::CWzdDlg_TestSenceSel(CWnd* pParent /*=NULL*/)
	: CWzdDlgBase(CWzdDlg_TestSenceSel::IDD, pParent)
{
	m_editSCD.SetBorderColor(g_crBlue);
	m_editFile.SetBorderColor(g_crBlue);
	m_strSelectPDF = _T("0");
}

CWzdDlg_TestSenceSel::~CWzdDlg_TestSenceSel()
{
}

void CWzdDlg_TestSenceSel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_UESR, m_txtUser);
	DDX_Control(pDX, IDC_CBB_USER, m_cbbUser);
	DDX_Control(pDX, IDC_STATIC_CFG, m_txtCfg);
	DDX_Control(pDX, IDC_STATIC_LV, m_txtLv);
	DDX_Control(pDX, IDC_CBB_LV, m_cbbLv);
	DDX_Control(pDX, IDC_STATIC_TYPE, m_txtType);
	DDX_Control(pDX, IDC_CBB_TYPE, m_cbbType);
	DDX_Control(pDX, IDC_STATIC_FACTORY, m_txtFactory);
	DDX_Control(pDX, IDC_CBB_FACTORY, m_cbbFactory);
	DDX_Control(pDX, IDC_STATIC_COMM, m_txtComm);
	DDX_Control(pDX, IDC_CBB_COMM, m_cbbComm);
	DDX_Control(pDX, IDC_STATIC_TESTTYPE, m_txtTestType);
	DDX_Control(pDX, IDC_STATIC_SCD, m_txtSCD);
	DDX_Control(pDX, IDC_EDIT_SCD, m_editSCD);
	DDX_Control(pDX, IDC_BTN_SCD, m_btnSCD);
	DDX_Control(pDX, IDC_STATIC_FILE, m_txtFile);
	DDX_Control(pDX, IDC_CB_FILE, m_cbFile);
	DDX_Control(pDX, IDC_EDIT_FILE, m_editFile);
	DDX_Control(pDX, IDC_BTN_FILE, m_btnFile);
	DDX_Control(pDX, IDC_CBB_SITETYPE, m_cbbSubstationType);
	DDX_Control(pDX, IDC_CBB_TESTTYPE, m_cbbTestType);
}

BOOL CWzdDlg_TestSenceSel::InitUI(CDataGroup* pDataGroup)
{
	m_pDataCfg = pDataGroup;

	CDvmData* pUserFactory = ParseUIXml(pDataGroup, SENCESEL_USERFACTORY);
	CDvmData* pSubstation = ParseUIXml(pDataGroup, SENCESEL_SUBSTATION);
	CDvmData* pVolLevel = ParseUIXml(pDataGroup, SENCESEL_VOLTLEVEL);
	CDvmData* pDeviceType = ParseUIXml(pDataGroup, SENCESEL_DEVICETYPE);
	CDvmData* pDeviceCommond = ParseUIXml(pDataGroup, SENCESEL_DEVICECOMMOND);
	CDvmData* pTestType = ParseUIXml(pDataGroup, SENCESEL_TESTTYPE);
	CDvmData* pSCDChoose = ParseUIXml(pDataGroup, SENCESEL_SCDCHOOSE);
	CDvmData* pSetFileChoose = ParseUIXml(pDataGroup, SENCESEL_SETFILECHOOSE);
	CDvmData* pFactory = ParseUIXml(pDataGroup, SENCESEL_FACTORY);
	BOOL bParseRes = pUserFactory && pSubstation && pVolLevel && pDeviceType
		&& pDeviceCommond && pTestType && pSCDChoose && pSetFileChoose && pFactory;
	if(bParseRes == FALSE)
	{
		return FALSE;
	}

	XmlToUI(&m_cbbUser, pUserFactory);

	XmlToUI(&m_cbbLv, pVolLevel);
	OnCbnSelchangeCbbUser();
	XmlToUI(&m_cbbType, pDeviceType);
	OnCbnSelchangeCbbCfg();
	XmlToUI(&m_cbbComm, pDeviceCommond);
	OnCbnSelchangeCbbComm();
	XmlToUI(&m_cbbFactory, pFactory);
	OnCbnSelChangeCbbFactory();
	XmlToUI(&m_cbbSubstationType, pSubstation);
	OnCbnSelchangeCbbSitetype();
	XmlToUI(&m_cbbTestType, pTestType);
	OnCbnSelchangeCbbTesttype();

	XmlToUI(&m_editSCD, pSCDChoose, &m_cbFile);
	XmlToUI(&m_editFile, pSetFileChoose);

	EnableFile(m_cbFile.GetCheck());

	return TRUE;
}

void CWzdDlg_TestSenceSel::EnableSCD(BOOL bEnable)
{
 	m_editSCD.EnableWindow(bEnable);
 	m_btnSCD.SetEnabled(bEnable);
 	GetParentWnd()->SendMessage(WM_SENCESEL_CHANGE, IsIEDDevice(), m_cbFile.GetCheck());
}

void CWzdDlg_TestSenceSel::EnableFile(BOOL bEnable)
{
	m_editFile.EnableWindow(bEnable);
	m_btnFile.SetEnabled(bEnable);
	GetParentWnd()->SendMessage(WM_SENCESEL_CHANGE, IsIEDDevice(), m_cbFile.GetCheck());
}

void CWzdDlg_TestSenceSel::OnInitialUpdate()
{
	XUI_InitAdjust();
}

BOOL CWzdDlg_TestSenceSel::IsIEDDevice()
{
	return m_cbbSubstationType.GetCurSel() == 1;
}

void CWzdDlg_TestSenceSel::XUI_InitAdjust()
{
	CXUIAdjItem_Area::XUI_SetParentWnd(this);
 	XUI_AddWnd(&m_txtUser, 0, 0, 0, 0);
	XUI_AddWnd(&m_cbbUser, 0, 0, 0.5, 0);

	XUI_AddWnd(&m_cbbSubstationType, 0, 0, 0.5, 0);
	XUI_AddWnd(&m_txtCfg, 0, 0, 0, 0);

	XUI_AddWnd(&m_txtLv, 0, 0, 0, 0);
	XUI_AddWnd(&m_cbbLv, 0, 0, 0.5, 0);

	XUI_AddWnd(&m_txtType, 0, 0, 0, 0);
	XUI_AddWnd(&m_cbbType, 0, 0, 0.5, 0);

	XUI_AddWnd(&m_txtFactory, 0, 0, 0, 0);
	XUI_AddWnd(&m_cbbFactory, 0, 0, 0.5, 0);

	XUI_AddWnd(&m_txtComm, 0, 0, 0, 0);
	XUI_AddWnd(&m_cbbComm, 0, 0, 0.5, 0);

	XUI_AddWnd(&m_txtTestType, 0, 0, 0, 0);
	XUI_AddWnd(&m_cbbTestType, 0, 0, 0.5, 0);

	XUI_AddWnd(&m_txtSCD, 0, 0, 0, 0);
	XUI_AddWnd(&m_editSCD, 0, 0, 1, 0);
	XUI_AddWnd(&m_btnSCD, 1, 0, 0, 0);

	XUI_AddWnd(&m_txtFile, 0, 0, 0, 0);
	XUI_AddWnd(&m_cbFile, 0, 0, 0, 0);
	XUI_AddWnd(&m_editFile, 0, 0, 1, 0);
	XUI_AddWnd(&m_btnFile, 1, 0, 0, 0);

	CXUIAdjItem_Area::XUI_OnSize();
}

BOOL CWzdDlg_TestSenceSel::DoNext()
{	
	if(m_editFile.IsWindowEnabled())
	{
		CString strText;
		m_editFile.GetWindowText(strText);
		if(!strText.GetLength())
		{
			MessageDlg::MessageBox("错误", "没有选择定值单文件！", MessageDlg::ERRYES);
			return FALSE;
		}
	}

	if(m_editSCD.IsWindowEnabled())
	{
		CString strText;
		m_editSCD.GetWindowText(strText);
		if(!strText.GetLength())
		{
			MessageDlg::MessageBox("错误", "没有选择SCD文件！", MessageDlg::ERRYES);
			return FALSE;
		}
	}

	if(m_strGbFile.MakeLower() != g_pWzdMainDlg->m_oGuideBook.m_strGbXmlFile)
	{
		GetParentWnd()->SendMessage(WM_MAIN_ENABLE_NEXT, 0, 0);
		GetParentWnd()->SendMessage(WM_MAIN_ENABLE_PREV, 0, 0);

		g_pWzdMainDlg->m_oGuideBook.OpenXMLFile(m_strGbFile);
		g_pWzdMainDlg->m_strGuideBookIecfgFile = ParseFileName(g_pWzdMainDlg->m_oGuideBook.m_strIecfgFile);

		GetParentWnd()->SendMessage(WM_MAIN_ENABLE_NEXT, 0, 1);
		GetParentWnd()->SendMessage(WM_MAIN_ENABLE_PREV, 0, 1);
	}

	//20230609 huangliang 
	g_pWzdMainDlg->m_oGuideBook.UpdateGlobalDifferentData(_T("SelectPDF"), _T("选择定值单"), _T("number"), m_strSelectPDF);
	g_pWzdMainDlg->m_oGuideBook.UpdateGlobalDifferentData(_T("RelayProduction"), _T("RelayProduction"), _T("string"), g_pWzdMainDlg->GetFactory());
	g_pWzdMainDlg->SetRecv0x92DataInGlobal();
	return TRUE;
}

void CWzdDlg_TestSenceSel::SetGbFile(const CString& strFile)
{
	m_strGbFile = strFile;
}

BEGIN_MESSAGE_MAP(CWzdDlg_TestSenceSel, CDialog)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CB_FILE, &CWzdDlg_TestSenceSel::OnBnClickedCbFile)
	ON_BN_CLICKED(IDC_BTN_SCD, &CWzdDlg_TestSenceSel::OnBnClickedBtnScd)
	ON_BN_CLICKED(IDC_BTN_FILE, &CWzdDlg_TestSenceSel::OnBnClickedBtnFile)
	ON_CBN_SELCHANGE(IDC_CBB_LV, &CWzdDlg_TestSenceSel::OnCbnSelchangeCbbCfg)
	ON_CBN_SELCHANGE(IDC_CBB_TYPE, &CWzdDlg_TestSenceSel::OnCbnSelchangeCbbCfg)
	ON_CBN_SELCHANGE(IDC_CBB_COMM, &CWzdDlg_TestSenceSel::OnCbnSelchangeCbbComm)
	ON_CBN_SELCHANGE(IDC_CBB_FACTORY, &CWzdDlg_TestSenceSel::OnCbnSelChangeCbbFactory)
	ON_CBN_SELCHANGE(IDC_CBB_USER, &CWzdDlg_TestSenceSel::OnCbnSelchangeCbbUser)
	ON_CBN_SELCHANGE(IDC_CBB_TESTTYPE, &CWzdDlg_TestSenceSel::OnCbnSelchangeCbbTesttype)
	ON_CBN_SELCHANGE(IDC_CBB_DEVICETYPE, &CWzdDlg_TestSenceSel::OnCbnSelchangeCbbSitetype)
END_MESSAGE_MAP()

void CWzdDlg_TestSenceSel::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	XUI_OnSize(cx, cy);
}

void CWzdDlg_TestSenceSel::OnBnClickedCbFile()
{
 	EnableFile(m_cbFile.GetCheck());

	//20230817 huangliang 新增是否勾选定值单
	m_strSelectPDF = _T("0");
	if(m_cbFile.GetCheck())
		m_strSelectPDF = _T("1");	
}

void CWzdDlg_TestSenceSel::OnBnClickedBtnScd()
{
	CFileDialog oDlg(TRUE, NULL, NULL, OFN_FORCESHOWHIDDEN, "SCD文件(*.scd)|*.scd||", this);
	if(oDlg.DoModal() == IDOK)
	{
		CString strName = oDlg.GetPathName();
		m_editSCD.SetWindowText(oDlg.GetFileName());	//20230824 huangliang 仅显示文件名称
		GetParentWnd()->SendMessage(WM_OPEN_SCL_FILE, 0, (LPARAM)strName.GetString());
		//g_pWzdMainDlg->OnOpenSclFile(0, (LPARAM)strName.GetString());
	}
}

void CWzdDlg_TestSenceSel::OnBnClickedBtnFile()
{
	CFileDialog oDlg(TRUE, NULL, NULL, OFN_FORCESHOWHIDDEN, "XML文件(*.xml)|*.xml|PDF文件(*.pdf)|*.pdf||", this);
	if(oDlg.DoModal() == IDOK)
	{
		CString strName = oDlg.GetPathName();
		m_editFile.SetWindowText(strName);
		BOOL bIsXml = oDlg.GetFileExt() == "xml";
		GetParentWnd()->SendMessage(WM_SENSESEL_FILE, bIsXml, (LPARAM)strName.GetString());
	}
}

void CWzdDlg_TestSenceSel::OnCbnSelchangeCbbComm()
{
	CString strText;
	m_cbbComm.GetWindowText(strText);
	if(strText.Find("MMS") != -1)
	{
		strText = "MMS";
	}
	else if(strText.Find("CMS") != -1)
	{
		strText = "CMS";
	}
	else
	{
		strText = "";
	}
	GetParentWnd()->SendMessage(WM_SENCESEL_COMM, 0, (LPARAM)strText.GetString());
}

void CWzdDlg_TestSenceSel::OnCbnSelChangeCbbFactory()
{
	CString strFactory;
	m_cbbFactory.GetWindowText(strFactory);
	GetParentWnd()->SendMessage(WM_SENCESEL_COMM, (WPARAM)strFactory.GetString(), 0);
}

void CWzdDlg_TestSenceSel::OnCbnSelchangeCbbCfg()
{
	CString strVolt, strType;
	m_cbbLv.GetWindowText(strVolt);
	m_cbbType.GetWindowText(strType);
	GetParentWnd()->SendMessage(WM_SENCESEL_CFG, (WPARAM)strVolt.GetString(), (LPARAM)strType.GetString());
}

void CWzdDlg_TestSenceSel::OnCbnSelchangeCbbUser()
{
	CString strUser;
	m_cbbUser.GetWindowText(strUser);
	GetParentWnd()->SendMessage(WM_USER_CHANGE, 0, (LPARAM)strUser.GetString());
}

void CWzdDlg_TestSenceSel::OnCbnSelchangeCbbTesttype()
{
	CString strText;
	m_cbbTestType.GetWindowText(strText);
	GetParentWnd()->SendMessage(WM_SENCESEL_TEST, 0, (LPARAM)strText.GetString());
}

void CWzdDlg_TestSenceSel::OnCbnSelchangeCbbSitetype()
{
	CString strText;
	m_cbbSubstationType.GetWindowText(strText);
	if(m_cbbSubstationType.GetCurSel())
	{
		EnableSCD(TRUE);
	}
	else
	{
		EnableSCD(FALSE);
	}
}
