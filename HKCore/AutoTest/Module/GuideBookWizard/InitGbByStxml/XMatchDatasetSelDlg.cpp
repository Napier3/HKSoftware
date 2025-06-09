// XMatchDatasetSelDlg.cpp: implementation of the CXMatchDatasetSelDlg class.    
//    
//////////////////////////////////////////////////////////////////////    

#include "stdafx.h"    
#include "XMatchDatasetSelDlg.h"   
#include "..\..\..\..\Module\API\GloblaDrawFunctions.h"
#include "..\..\..\Module\GuideBook\GuideBookDefine.h"

#ifdef _DEBUG    
#undef THIS_FILE    
static char THIS_FILE[]=__FILE__;   
#define new DEBUG_NEW    
#endif    

#define IDC_LIST_DATASET 1600    
#define IDC_EDIT_DATAVALUE 1601    
//////////////////////////////////////////////////////////////////////    
// Construction/Destruction    
//////////////////////////////////////////////////////////////////////    

CXMatchDatasetSelDlg::CXMatchDatasetSelDlg(CXMatchRefObjectSelEdit *pEdit, CWnd* pParent /*= NULL*/)   
: CDynDialogEx(pParent)   
{   
	m_pEdit = pEdit;
	m_bAddSystemButtons = FALSE;   
}   

CXMatchDatasetSelDlg::~CXMatchDatasetSelDlg()   
{   
	m_oListDataset.RemoveAll();
}   

void CXMatchDatasetSelDlg::ResetDatasetList()
{
	m_oListDataset.RemoveAll();
	ShowDatasetTree();
}

void CXMatchDatasetSelDlg::AddDataset(CExBaseObject *pDataset)
{
	if (m_oListDataset.Find(pDataset) == NULL)
	{
		m_oListDataset.AddTail(pDataset);
		InsertDataset((CExBaseList*)pDataset, TVI_ROOT);
	}
}

void CXMatchDatasetSelDlg::ShowDatasetTree()
{
	m_treeDataset.DeleteAllItems();
	POS pos = m_oListDataset.GetHeadPosition();
	CExBaseList *pDataset = NULL;

	m_treeDataset.InsertItem(_T("-----------------------"), TVI_ROOT);

	while (pos != NULL)
	{
		pDataset = (CExBaseList*)m_oListDataset.GetNext(pos);
		InsertDataset(pDataset, TVI_ROOT);
	}
}

void CXMatchDatasetSelDlg::InsertDataset(CExBaseList *pDataset, HTREEITEM hParent)
{
	POS posData = pDataset->GetHeadPosition();
	CExBaseObject *pData = NULL;
	HTREEITEM hData = NULL;
	HTREEITEM hDataset = NULL;

	hDataset = m_treeDataset.InsertItem(pDataset->m_strName, TVI_ROOT);
	m_treeDataset.SetItemData(hDataset, (DWORD)pDataset);

	while (posData != NULL)
	{
		pData = (CExBaseObject *)pDataset->GetNext(posData);
		hData = m_treeDataset.InsertItem(pData->m_strName, hDataset);
		m_treeDataset.SetItemData(hData, (DWORD)pData);
	}

	m_treeDataset.Expand(hDataset, TVE_EXPAND);
}

BEGIN_MESSAGE_MAP(CXMatchDatasetSelDlg, CDynDialogEx)   
	//{{AFX_MSG_MAP(CXMatchDatasetSelDlg)    
	//}}AFX_MSG_MAP   
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_DATASET, &CXMatchDatasetSelDlg::OnNMDblclkTreeDataset)
END_MESSAGE_MAP()   



void CXMatchDatasetSelDlg::OnNMDblclkTreeDataset(NMHDR *pNMHDR, LRESULT *pResult)
{
	HTREEITEM hSel = m_treeDataset.GetSelectedItem();

	if (hSel == NULL || m_pEdit == NULL)
	{
		return;
	}

	CExBaseObject *pSel = (CExBaseObject*)m_treeDataset.GetItemData(hSel);

	if (pSel == NULL)
	{
		m_pEdit->SetMatchRefData(pSel);
	}
	else
	{
		if (pSel->GetClassID() == GBCLASSID_DATAOBJ)
		{
			m_pEdit->SetMatchRefData(pSel);
		}
	}

	*pResult = 0;
}

BOOL CXMatchDatasetSelDlg::OnInitDialog()   
{   
	BOOL bRet = CDynDialogEx::OnInitDialog();   

	//SetWindowPos(NULL, 0, 0, 190, 190, SWP_SHOWWINDOW);
	CRect rc;
	GetClientRect(&rc);
	
	CreateTreeCtrl(m_treeDataset, rc, IDC_LIST_DATASET, this);
	m_treeDataset.SetFont(g_pGlobalFont14);

	return bRet;   
}   

int CXMatchDatasetSelDlg::DoModal()   
{   
	CRect rect(0,0,250,300);   
	SetDlgRect(rect);
//	AddDlgControl(_T("LISTBOX"), _T("ListboxText"), STYLE_LISTBOX, EXSTYLE_LISTBOX, &rect, &m_lstBox, IDC_LIST_DATAS);   
	int iRet = CDynDialogEx::DoModal();   

	return iRet;   
}   

 void CXMatchDatasetSelDlg::OnCancel()
 {
	 //CDialog::OnCancel()
	ShowWindow(SW_HIDE);
 }

 void CXMatchDatasetSelDlg::OnOK()
 {
	//CDialog::OnOK()
	ShowWindow(SW_HIDE);
 }



//////////////////////////////////////////////////////////////////////////
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

 //////////////////////////////////////////////////////////////////////    
 // Construction/Destruction    
 //////////////////////////////////////////////////////////////////////    

 CXMatchDataObjEditDlg::CXMatchDataObjEditDlg(CWnd* pParent /*= NULL*/)   
	 : CDynDialogEx(pParent)   
 {   
	 m_bAddSystemButtons = FALSE;   
 }   

 CXMatchDataObjEditDlg::~CXMatchDataObjEditDlg()   
 {   
	 
 }   

 BEGIN_MESSAGE_MAP(CXMatchDataObjEditDlg, CDynDialogEx)   
	 //{{AFX_MSG_MAP(CXMatchDataObjEditDlg)    
	 //}}AFX_MSG_MAP   
 END_MESSAGE_MAP()   


 BOOL CXMatchDataObjEditDlg::OnInitDialog()   
 {   
	 BOOL bRet = CDynDialogEx::OnInitDialog();   

	 //SetWindowPos(NULL, 0, 0, 190, 190, SWP_SHOWWINDOW);
	 CRect rc;
	 GetClientRect(&rc);

	 CreateEdit(m_editValue, CRect(12, 12, 195, 34), IDC_EDIT_DATAVALUE, this);
	 CreateButton(m_btnOK, _T("确定"), CRect(212, 12, 284, 34), IDOK, this);
	 CreateButton(m_btnCancel, _T("取消"), CRect(295, 12, 368, 34), IDOK, this);
	m_editValue.SetWindowText(m_strValue);
	SetWindowText(m_strDataName);

	m_editValue.SetFont(g_pGlobalFont14);
	m_btnOK.SetFont(g_pGlobalFont14);
	m_btnCancel.SetFont(g_pGlobalFont14);

	 return bRet;   
 }   

 int CXMatchDataObjEditDlg::DoModal()   
 {   
	 CRect rect(0,0,252,28);   
	 SetDlgRect(rect);
	 //	AddDlgControl(_T("LISTBOX"), _T("ListboxText"), STYLE_LISTBOX, EXSTYLE_LISTBOX, &rect, &m_lstBox, IDC_LIST_DATAS);   
	 int iRet = CDynDialogEx::DoModal();   

	 return iRet;   
 }   

 void CXMatchDataObjEditDlg::OnCancel()
 {
	 CDialog::OnCancel();
 }

 void CXMatchDataObjEditDlg::OnOK()
 {
	 m_editValue.GetWindowText(m_strValue);
	 
	 CDialog::OnOK();
 }
