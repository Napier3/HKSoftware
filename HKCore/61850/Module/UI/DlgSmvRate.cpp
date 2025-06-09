// DlgSmvRate.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DlgSmvRate.h"

#include "..\..\..\Module\System\TickCount32.h"

// CDlgSmvRate �Ի���

CDlgSmvRate::CDlgSmvRate(CWnd* pParent /*=NULL*/)
	: CDynDialogEx(pParent)
{
	m_bEditAll = 0;
	m_pCloneIecCfgSmvRates = NULL;
}

CDlgSmvRate::~CDlgSmvRate()
{
	if (m_pCloneIecCfgSmvRates != NULL)
	{
		delete m_pCloneIecCfgSmvRates;
		m_pCloneIecCfgSmvRates = NULL;
	}
}

void CDlgSmvRate::DoDataExchange(CDataExchange* pDX)
{
	CDynDialogEx::DoDataExchange(pDX);
		
	if (!m_bHasInitDialog)
	{
		return;
	}
	
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
}


BEGIN_MESSAGE_MAP(CDlgSmvRate, CDynDialogEx)

END_MESSAGE_MAP()


// CDlgSmvRate ��Ϣ�������
void CDlgSmvRate::InitIecCfgSmvRates(CIecCfgSmvRates *pIecCfgSmvRates)
{
	m_pCloneIecCfgSmvRates = (CIecCfgSmvRates *)pIecCfgSmvRates->Clone();
}

void CDlgSmvRate::InitDialog()
{
	ShowSmvRate();

	m_btnOK.EnableWindow(TRUE);
	m_btnCancel.EnableWindow(TRUE);
}

void CDlgSmvRate::ShowSmvRate()
{
	m_grid.ShowDatas(m_pCloneIecCfgSmvRates);
}

void CDlgSmvRate::SaveSmvRate()
{
	
}


void CDlgSmvRate::CreateControls()
{
	m_grid.Create(CRect(10, 10, 354, 280), this, IECFG_IDC_GRID_SMVRATE);
	m_grid.InitGrid();

	CreateButton(m_btnOK, _T("ȷ��"),     CRect(200,284,272,305), IDOK, this);
	CreateButton(m_btnCancel, _T("ȡ��"), CRect(280,284,354,305), IDCANCEL, this);
	CreateCheckBox(m_btnCheckAll, _T("�޸�ȫ������"), CRect(10,284,105,305), IECFG_IDC_BUTTON_CHK_ALL, this);

	m_btnOK.SetFont(g_pGlobalFont11);
	m_btnCancel.SetFont(g_pGlobalFont11);
	m_btnCheckAll.SetFont(g_pGlobalFont11);
	m_grid.SetFont(g_pGlobalFont11);
}


BOOL CDlgSmvRate::OnInitDialog()
{
	CDynDialogEx::OnInitDialog();

	CreateControls();
	InitDialog();

	MoveWindow(CRect( 0, 0, 370, 340), TRUE);
	CenterWindow();
	SetWindowText(_T("������������"));

	m_bHasInitDialog = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDlgSmvRate::OnOK()
{
	UpdateData(TRUE);
	
	m_bEditAll = m_btnCheckAll.GetCheck();

	CDynDialogEx::OnOK();
}

void CDlgSmvRate::OnCancel()
{
	
	CDynDialogEx::OnCancel();
}
