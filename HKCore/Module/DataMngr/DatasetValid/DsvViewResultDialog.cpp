// DsvViewResultDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "DsvViewResultDialog.h"

#include "..\..\..\Module\API\GloblaDrawFunctions.h"
#include "..\..\XLanguage\XLanguageResource.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// CDsvViewResultDialog 对话框

// IMPLEMENT_DYNAMIC(CDsvViewResultDialog, CDynDialogEx)

CDsvViewResultDialog::CDsvViewResultDialog(CWnd* pParent /*=NULL*/)
	: CDynDialogEx(pParent)
{
	m_pDsvScript  = NULL;
	m_pDsvDataset = NULL;
	m_nImageList = 0;
}

CDsvViewResultDialog::~CDsvViewResultDialog()
{
}

void CDsvViewResultDialog::DoDataExchange(CDataExchange* pDX)
{
	CDynDialogEx::DoDataExchange(pDX);

	if (!::IsWindow(m_treeDataset.m_hWnd))
	{
		return;
	}

	DDX_Control(pDX, IDC_TREE_DSV_VIEW, m_treeDataset);
	DDX_Control(pDX, IDC_LIST_DSV_VIEW, m_listDataset);
	DDX_Control(pDX, IDOK, m_btnOK);
}


BEGIN_MESSAGE_MAP(CDsvViewResultDialog, CDynDialogEx)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_DSV_VIEW, &CDsvViewResultDialog::OnTvnSelchangedTreeDataset)
END_MESSAGE_MAP()


// CDsvViewResultDialog 消息处理程序

BOOL CDsvViewResultDialog::OnInitDialog()
{
	CDynDialogEx::OnInitDialog();

	CRect rcClient;
	GetClientRect(&rcClient);
	long nWidth = rcClient.Width();
	long nHeight = rcClient.Height();
	long nBtnBottom = nHeight - 5;
	long nTreeBottom = nBtnBottom - 30;
	CreateTreeCtrl(m_treeDataset, CRect(5, 5, 220, nTreeBottom), IDC_TREE_DSV_VIEW, this);
	m_listDataset.Create(CRect(225, 5, nWidth-5, nTreeBottom), this, IDC_LIST_DSV_VIEW);
	CreateButton(m_btnOK, g_sLangTxt_Close/*_T("关闭")*/, CRect(nWidth - 85, nTreeBottom+5, nWidth-5, nBtnBottom), IDOK, this);

	m_listDataset.InitGrid();

	m_treeDataset.SetFont(g_pGlobalFont12);
	m_listDataset.SetFont(g_pGlobalFont12);
	m_btnOK.SetFont(g_pGlobalFont12);

	if (m_pDsvDataset == NULL || m_pDsvScript == NULL)
	{
		return TRUE;
	}

	m_treeDataset.SetImageListBmp(m_nImageList);
	m_treeDataset.m_pDatasetListCtrl = &m_listDataset;
	ViewDsvScriptResult(m_pDsvScript, m_pDsvDataset);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDsvViewResultDialog::OnTvnSelchangedTreeDataset(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	
	
	*pResult = 0;
}

void CDsvViewResultDialog::ViewDsvScriptResult(CDsvScript *pDsvScript, CDvmDataset *pDsvDataset)
{
	m_treeDataset.DeleteAllItems();

	m_treeDataset.ShowDsvScript(pDsvScript);
	m_listDataset.ShowDatas(pDsvDataset);
}


int CDsvViewResultDialog::DoModal()   
{   
	CRect rect(0,0,450,250);   
	SetDlgRect(rect);
	int iRet = CDynDialogEx::DoModal();   

	return iRet;   
}   

void CDsvViewResultDialog::OnCancel()
{
	CDialog::OnCancel();
	//ShowWindow(SW_HIDE);
}

void CDsvViewResultDialog::OnOK()
{
	CDialog::OnOK();
	//ShowWindow(SW_HIDE);
}

