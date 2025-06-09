// ViewSetsDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "ViewSetsDialog.h"

#include "..\..\..\Module\API\GloblaDrawFunctions.h"
#include "..\XLanguageResourceAts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CViewSetsDialog 对话框

// IMPLEMENT_DYNAMIC(CViewSetsDialog, CDynDialogEx)

CViewSetsDialog::CViewSetsDialog(CWnd* pParent /*=NULL*/)
	: CDynDialogEx(pParent)
{

}

CViewSetsDialog::~CViewSetsDialog()
{
}

void CViewSetsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDynDialogEx::DoDataExchange(pDX);

	if (!::IsWindow(m_treeDataset.m_hWnd))
	{
		return;
	}

	DDX_Control(pDX, IDC_TREE_DATASET_EX, m_treeDataset);
	DDX_Control(pDX, IDC_LIST_DATASET_EX, m_listDataset);
	DDX_Control(pDX, IDOK, m_btnOK);
}


BEGIN_MESSAGE_MAP(CViewSetsDialog, CDynDialogEx)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_DATASET_EX, &CViewSetsDialog::OnTvnSelchangedTreeDataset)
END_MESSAGE_MAP()


// CViewSetsDialog 消息处理程序

BOOL CViewSetsDialog::OnInitDialog()
{
	CDynDialogEx::OnInitDialog();

	CRect rcClient;
	GetClientRect(&rcClient);
	long nWidth = rcClient.Width();
	long nHeight = rcClient.Height();
	long nBtnBottom = nHeight - 5;
	long nTreeBottom = nBtnBottom - 30;
	CreateTreeCtrl(m_treeDataset, CRect(5, 5, 220, nTreeBottom), IDC_TREE_DATASET_EX, this);
	CreateListCtrl(m_listDataset, CRect(225, 5, nWidth-5, nTreeBottom), IDC_LIST_DATASET_EX, this);
	CreateButton(m_btnOK, g_sLangTxt_Close/*_T("关闭")*/, CRect(nWidth - 85, nTreeBottom+5, nWidth-5, nBtnBottom), IDOK, this);

	m_treeDataset.SetFont(g_pGlobalFont14);
	m_listDataset.SetFont(g_pGlobalFont14);
	m_btnOK.SetFont(g_pGlobalFont14);

	if (m_pDevice == NULL)
	{
		return TRUE;
	}

	CDevice *pDevice = NULL;

	if (GBCLASSID_DEVICE == m_pDevice->GetClassID())
	{
		pDevice = (CDevice *)m_pDevice;
	}
	else
	{
		pDevice = (CDevice*)m_pDevice->GetAncestor(GBCLASSID_DEVICE);
	}

	ASSERT( pDevice != NULL );

	if (pDevice == NULL)
	{
		return TRUE;
	}

	CGuideBook *pGuideBook = (CGuideBook*)m_pDevice->GetParent();
	m_treeDataset.m_bShowTestPara = TRUE;
	m_treeDataset.m_pDatasetListCtrl = &m_listDataset;

	m_listDataset.InsertColumn(0, g_sLangTxt_Index/*_T("编号")*/, LVCFMT_LEFT,40);
	m_listDataset.InsertColumn(1, g_sLangTxt_Name/*_T("名称")*/, LVCFMT_LEFT,150);
	m_listDataset.InsertColumn(2, _T("ID"), LVCFMT_LEFT,100);
	m_listDataset.InsertColumn(3, g_sLangTxt_Value/*_T("数值")*/, LVCFMT_LEFT,80);
	m_listDataset.InsertColumn(4, g_sLangTxt_Unit/*_T("单位")*/, LVCFMT_LEFT,40);
	m_listDataset.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);

	m_treeDataset.ShowDevice(pDevice, pGuideBook->GetGlobalDatas(FALSE));


	CString strTitle;
	CString strPath;
	strPath = _P_GetSystemPath();
	strPath = pGuideBook->m_strGuideBookFile.Mid(strPath.GetLength());
	long nPos = strPath.Find('\\');
	strPath = strPath.Mid(nPos+1);

	if (pGuideBook->m_strID.GetLength() > 0)
	{
		strTitle.Format(_T("%s : %s"), pGuideBook->m_strID, strPath);
	}
	else
	{
		strTitle = strPath;
	}

	SetWindowText(strTitle);


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CViewSetsDialog::OnTvnSelchangedTreeDataset(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	
	
	*pResult = 0;
}

void CViewSetsDialog::ShowDataset(CDataSet *pDataset)
{
	m_listDataset.DeleteAllItems();
	pDataset->InsertChildToListCtrl(&m_listDataset, 0);
}


int CViewSetsDialog::DoModal()   
{   
	CRect rect(0,0,450,250);   
	SetDlgRect(rect);
	int iRet = CDynDialogEx::DoModal();   

	return iRet;   
}   

void CViewSetsDialog::OnCancel()
{
	CDialog::OnCancel();
	//ShowWindow(SW_HIDE);
}

void CViewSetsDialog::OnOK()
{
	CDialog::OnOK();
	//ShowWindow(SW_HIDE);
}

