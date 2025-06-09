// DlgSmvRate.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DlgExportWRep.h"

CDlgExportWRep::CDlgExportWRep(CWnd* pParent /*=NULL*/)
	: CDynDialogEx(pParent)
{
	m_bCheckSchema = TRUE ;
	m_bCheckDataTypeTmp = TRUE ;
	m_bCheckAppModel = TRUE ;
	m_bCheckVirCircuit = TRUE ;
}

CDlgExportWRep::~CDlgExportWRep()
{
}

void CDlgExportWRep::DoDataExchange(CDataExchange* pDX)
{
	CDynDialogEx::DoDataExchange(pDX);
		
	if (!m_bHasInitDialog)
	{
		return;
	}
	
	DDX_Control(pDX, IDOK, m_btnOk);//ΪIDOK
	DDX_Control(pDX, IDCANCEL, m_btnCancel);//ΪIDCANCEL
	DDX_Control(pDX, EXPORTREP_IDC_BUTTON_SCHEMA, m_btnSchema);
	DDX_Control(pDX, EXPORTREP_IDC_BUTTON_DATATYPETMP, m_btnDataTypeTmp);
	DDX_Control(pDX, EXPORTREP_IDC_BUTTON_APPMODEL, m_btnAppModel);
	DDX_Control(pDX, EXPORTREP_IDC_BUTTON_VIRCIRCUIT, m_btnVirCircuit);
}


BEGIN_MESSAGE_MAP(CDlgExportWRep, CDynDialogEx)
 	ON_BN_CLICKED(EXPORTREP_IDC_BUTTON_SCHEMA, &CDlgExportWRep::OnBnClickedCheckSchema)
	ON_BN_CLICKED(EXPORTREP_IDC_BUTTON_DATATYPETMP, &CDlgExportWRep::OnBnClickedCheckDataTypeTmp)
	ON_BN_CLICKED(EXPORTREP_IDC_BUTTON_APPMODEL, &CDlgExportWRep::OnBnClickedCheckAppModel)
	ON_BN_CLICKED(EXPORTREP_IDC_BUTTON_VIRCIRCUIT, &CDlgExportWRep::OnBnClickedCheckVirCircuit)
END_MESSAGE_MAP()


// CDlgExportWRep ��Ϣ�������

void CDlgExportWRep::InitDialog()
{
	m_btnOk.EnableWindow(TRUE);
	m_btnCancel.EnableWindow(TRUE);
	m_btnSchema.EnableWindow(TRUE);
	m_btnSchema.SetCheck(TRUE);
	m_btnDataTypeTmp.EnableWindow(TRUE);
	m_btnDataTypeTmp.SetCheck(TRUE);
	m_btnAppModel.EnableWindow(TRUE);
	m_btnAppModel.SetCheck(TRUE);
	m_btnVirCircuit.EnableWindow(TRUE);
	m_btnVirCircuit.SetCheck(TRUE);
}


void CDlgExportWRep::CreateControls()
{
	CreateCheckBox(m_btnSchema, _T("����Schema�﷨�����"),     CRect(50,20,320,40), EXPORTREP_IDC_BUTTON_SCHEMA, this);
	CreateCheckBox(m_btnDataTypeTmp, _T("����DL/T860��������ģ�������"),     CRect(50,50,320,70), EXPORTREP_IDC_BUTTON_DATATYPETMP, this);
	CreateCheckBox(m_btnAppModel, _T("���湤��Ӧ��ģ�͹淶�Լ����"),     CRect(50,80,320,100), EXPORTREP_IDC_BUTTON_APPMODEL, this);
	CreateCheckBox(m_btnVirCircuit, _T("�������·�淶�Լ����"),     CRect(50,110,320,130), EXPORTREP_IDC_BUTTON_VIRCIRCUIT, this);
	CreateButton(m_btnOk, _T("ȷ��"),     CRect(60,150,130,170), IDOK, this);
	CreateButton(m_btnCancel, _T("ȡ��"), CRect(190,150,260,170), IDCANCEL, this);

	m_btnSchema.SetFont(g_pGlobalFont11);
	m_btnDataTypeTmp.SetFont(g_pGlobalFont11);
	m_btnAppModel.SetFont(g_pGlobalFont11);
	m_btnVirCircuit.SetFont(g_pGlobalFont11);
	m_btnOk.SetFont(g_pGlobalFont11);
	m_btnCancel.SetFont(g_pGlobalFont11);
}


BOOL CDlgExportWRep::OnInitDialog()
{
	CDynDialogEx::OnInitDialog();

	CreateControls();
	InitDialog();

	MoveWindow(CRect( 0, 0, 320, 220), TRUE);
	CenterWindow();
	SetWindowText(_T("ѡ�񵼳��ı������"));

	m_bHasInitDialog = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDlgExportWRep::OnOK()
{
	UpdateData(TRUE);
	CDynDialogEx::OnOK();
}

void CDlgExportWRep::OnCancel()
{
	UpdateData(TRUE);
	CDynDialogEx::OnCancel();
}

void CDlgExportWRep::OnBnClickedCheckSchema()
{
	if (m_bCheckSchema == TRUE)
	{
		m_bCheckSchema = FALSE;
	} 
	else
	{
		m_bCheckSchema = TRUE;
	}
}

void CDlgExportWRep::OnBnClickedCheckDataTypeTmp()
{
	if (m_bCheckDataTypeTmp == TRUE)
	{
		m_bCheckDataTypeTmp = FALSE;
	} 
	else
	{
		m_bCheckDataTypeTmp = TRUE;
	}
}

void CDlgExportWRep::OnBnClickedCheckAppModel()
{
	if (m_bCheckAppModel == TRUE)
	{
		m_bCheckAppModel = FALSE;
	} 
	else
	{
		m_bCheckAppModel = TRUE;
	}
}

void CDlgExportWRep::OnBnClickedCheckVirCircuit()
{
	if (m_bCheckVirCircuit == TRUE)
	{
		m_bCheckVirCircuit = FALSE;
	} 
	else
	{
		m_bCheckVirCircuit = TRUE;
	}
}