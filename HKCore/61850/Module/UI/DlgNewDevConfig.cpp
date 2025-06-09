// DlgSmvRate.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DlgNewDevConfig.h"

#include "..\..\..\Module\System\TickCount32.h"
#include "..\..\Iec61850Config\XLanguageResourceIec_61850Cfg.h"
#include "..\..\..\Module\API\FileApi.h"

// CDlgNewDevConfig �Ի���

CDlgNewDevConfig::CDlgNewDevConfig(CWnd* pParent /*=NULL*/)
	: CDynDialogEx(pParent)
{
	m_strStaticPath = _T("");
	m_strStaticPathNew = _T("");
	m_bAutoSave = TRUE ;
}

CDlgNewDevConfig::~CDlgNewDevConfig()
{
}

void CDlgNewDevConfig::DoDataExchange(CDataExchange* pDX)
{
	CDynDialogEx::DoDataExchange(pDX);
		
	if (!m_bHasInitDialog)
	{
		return;
	}
	
	DDX_Control(pDX, IDOK, m_btnAutoConfig);//ΪIDOK
	DDX_Control(pDX, IDCANCEL, m_btnNewDevice);//ΪIDCANCEL
	DDX_Control(pDX, IECFG_IDC_BUTTON_CHOOSEPATH, m_btnBrowse);
	DDX_Text(pDX, XIDC_EDIT_PATH, m_strStaticPath);

	DDX_Text(pDX, XIDC_EDIT_PATHNEW, m_strStaticPathNew);
	DDX_Control(pDX, IECFG_IDC_BUTTON_MODPATH, m_btnModPath);
	DDX_Control(pDX, IECFG_IDC_BUTTON_AUTOSAVE, m_btnAutoSave);
}


BEGIN_MESSAGE_MAP(CDlgNewDevConfig, CDynDialogEx)
//	ON_BN_CLICKED(IECFG_IDC_BUTTON_AUTO_CONFIG, &CDlgNewDevConfig::OnBnClickedAutoConfig)
//	ON_BN_CLICKED(IECFG_IDC_BUTTON_NEW_DEVICE, &CDlgNewDevConfig::OnBnClickedNewDevice)
	ON_BN_CLICKED(IECFG_IDC_BUTTON_CHOOSEPATH, &CDlgNewDevConfig::OnBnClickedBrowse)

	ON_BN_CLICKED(IECFG_IDC_BUTTON_MODPATH, &CDlgNewDevConfig::OnBnClickedModPath)
	ON_BN_CLICKED(IECFG_IDC_BUTTON_AUTOSAVE, &CDlgNewDevConfig::OnBnClickedAutoSave)
END_MESSAGE_MAP()


// CDlgNewDevConfig ��Ϣ�������

void CDlgNewDevConfig::InitDialog()
{
	m_btnAutoConfig.EnableWindow(FALSE);
	m_btnNewDevice.EnableWindow(TRUE);
	m_btnBrowse.EnableWindow(TRUE);

	m_btnModPath.EnableWindow(FALSE);
	m_btnAutoSave.EnableWindow(FALSE);
	m_btnAutoSave.SetCheck(TRUE);
	m_editPath.EnableWindow(FALSE);
	m_editPathNew.EnableWindow(FALSE);
}


void CDlgNewDevConfig::CreateControls()
{
	CreateStatic(m_stcTitle, _T("���������ļ�·��:"), CRect(20,20,135,40), XIDC_STATIC_TITLE, this);
	CreateEdit(m_editPath,                  CRect(140,20,500,40),   XIDC_EDIT_PATH, this);
	CreateButton(m_btnBrowse, _T("���..."), CRect(520,20,580,40), IECFG_IDC_BUTTON_CHOOSEPATH, this);


	CreateStatic(m_stcNew, _T("�����õ�Ĭ��·��:"), CRect(20,50,135,70), XIDC_STATIC_NEW, this);
	CreateEdit(m_editPathNew,                  CRect(140,50,500,70),   XIDC_EDIT_PATHNEW, this);
	CreateButton(m_btnModPath, _T("����·��"), CRect(520,50,580,70), IECFG_IDC_BUTTON_MODPATH, this);

	CreateCheckBox(m_btnAutoSave, _T("ѡ���Զ��洢"),     CRect(50,90,150,110), IECFG_IDC_BUTTON_AUTOSAVE, this);
	CreateButton(m_btnAutoConfig, _T("һ����������"),     CRect(200,90,300,110), IDOK, this);
	CreateButton(m_btnNewDevice, _T("�½���װ������"), CRect(400,90,500,110), IDCANCEL, this);




	m_btnAutoConfig.SetFont(g_pGlobalFont11);
	m_btnNewDevice.SetFont(g_pGlobalFont11);
	m_btnBrowse.SetFont(g_pGlobalFont11);
	m_stcTitle.SetFont(g_pGlobalFont11);
	m_editPath.SetFont(g_pGlobalFont11);

	m_stcNew.SetFont(g_pGlobalFont11);
	m_editPathNew.SetFont(g_pGlobalFont11);
	m_btnModPath.SetFont(g_pGlobalFont11);
	m_btnAutoSave.SetFont(g_pGlobalFont11);

}


BOOL CDlgNewDevConfig::OnInitDialog()
{
	CDynDialogEx::OnInitDialog();

	CreateControls();
	InitDialog();

	MoveWindow(CRect( 0, 0, 600, 150), TRUE);
	CenterWindow();
	SetWindowText(_T("ѡ����������ļ�"));

	m_bHasInitDialog = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDlgNewDevConfig::OnOK()
{
	UpdateData(TRUE);
	CDynDialogEx::OnOK();
}

void CDlgNewDevConfig::OnCancel()
{
	UpdateData(TRUE);
	CDynDialogEx::OnCancel();
}
void CDlgNewDevConfig::OnBnClickedBrowse()
{
//	UpdateData(TRUE);
	CString strFilter = g_sLangTxt_AngLiTesterIec61850ConfigFile;
	CString strFile;
	if (! PopupOpenFileDialog(this, strFile, strFilter, _T("iecfg")) )
	{
		return;
	}
	m_strStaticPath = strFile;
	m_strStaticPathNew = strFile;
	long nPos = m_strStaticPathNew.ReverseFind('\\');
	m_strStaticPathNew = m_strStaticPathNew.Left(nPos+1);
	if (m_strStaticPathNew != _T(""))
	{
		m_btnAutoConfig.EnableWindow(TRUE);
//		m_editPathNew.EnableWindow(TRUE);
		m_btnModPath.EnableWindow(TRUE);
		m_btnAutoSave.EnableWindow(TRUE);
	}
	UpdateData(FALSE);
}

void CDlgNewDevConfig::OnBnClickedModPath()
{
	TCHAR pszBuffer[MAX_PATH];
	if (!FGetDirectory(m_hWnd, pszBuffer, _T("ѡ����������ļ���")))//ѡ�����ļ���
	{
		return;
	}

	m_strStaticPathNew = pszBuffer;
	m_strStaticPathNew += _T("\\");

	UpdateData(FALSE);

}
void CDlgNewDevConfig::OnBnClickedAutoSave()
{
	if (m_bAutoSave == TRUE)
	{
		m_bAutoSave = FALSE;
	} 
	else
	{
		m_bAutoSave = TRUE;
	}
}