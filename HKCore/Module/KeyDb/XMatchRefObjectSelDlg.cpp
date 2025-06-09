// XMatchRefObjectSelDlg.cpp: implementation of the CXMatchRefObjectSelDlg class.    
//    
//////////////////////////////////////////////////////////////////////    

#include "stdafx.h"    
#include "XMatchRefObjectSelDlg.h"   
#include "XMatchEditGridCtrlBase.h"
#include "..\API\GloblaDrawFunctions.h"

#ifdef _DEBUG    
#undef THIS_FILE    
static char THIS_FILE[]=__FILE__;   
#define new DEBUG_NEW    
#endif    

#define IDC_LIST_DATAS 1600    
//////////////////////////////////////////////////////////////////////    
// Construction/Destruction    
//////////////////////////////////////////////////////////////////////    

CXMatchRefObjectSelDlg::CXMatchRefObjectSelDlg(CXMatchRefObjectSelEdit *pEdit, CWnd* pParent /*= NULL*/)   
: CDynDialogEx(pParent)   
{   
	m_pEdit = pEdit;
	m_bAddSystemButtons = FALSE;   
}   

CXMatchRefObjectSelDlg::~CXMatchRefObjectSelDlg()   
{   
}   

BEGIN_MESSAGE_MAP(CXMatchRefObjectSelDlg, CDynDialogEx)   
	//{{AFX_MSG_MAP(CXMatchRefObjectSelDlg)    
	ON_LBN_DBLCLK(IDC_LIST_DATAS, OnDblclkList)   
	//}}AFX_MSG_MAP    
END_MESSAGE_MAP()   

BOOL CXMatchRefObjectSelDlg::OnInitDialog()   
{   
	BOOL bRet = CDynDialogEx::OnInitDialog();   

	//SetWindowPos(NULL, 0, 0, 190, 190, SWP_SHOWWINDOW);
	CRect rc;
	GetClientRect(&rc);
	
	if( m_lstBox.Create(WS_CHILD|WS_VISIBLE|WS_VSCROLL|LBS_NOTIFY,rc,this,IDC_LIST_DATAS))
	{
		//m_lstBox.ModifyStyleEx(0, EXSTYLE_LISTBOX, SWP_SHOWWINDOW);
		//m_lstBox.AddString(_T("First String"));   
		//m_lstBox.AddString(_T("Second String"));   
		CFont *pFont = GetFont();
		m_lstBox.SetFont(g_pGlobalFont14);
	}

	return bRet;   
}   

void CXMatchRefObjectSelDlg::ShowExBaseList(CExBaseList *pListDatas, BOOL bAddEmpty, BOOL bShowID)
{
	long nTopIndex = m_lstBox.GetTopIndex();
	long nSelIndex = m_lstBox.GetCurSel();
	m_lstBox.SetFont(g_pGlobalFont14);

	ASSERT (pListDatas != NULL);
	m_lstBox.ResetContent();

	if (bAddEmpty)
	{
		long nIndex = m_lstBox.AddString(_T(""));
		m_lstBox.SetItemData(nIndex, 0);
	}

	if (pListDatas == NULL)
	{
		return;
	}

	if (bShowID)
	{
		POS pos = pListDatas->GetHeadPosition();
		CExBaseObject *p = NULL;
		CString strText;
		long nIndex = 0;

		while (pos != NULL)
		{
			p = pListDatas->GetNext(pos);
			strText.Format(_T("%s[%s]"), p->m_strName, p->m_strID);
			nIndex = m_lstBox.AddString(strText);
			m_lstBox.SetItemDataPtr(nIndex, p);
		}
	}
	else
	{
		pListDatas->InsertChildreListBox(&m_lstBox);
	}
	
	m_lstBox.SetCurSel(nSelIndex);
	m_lstBox.SetTopIndex(nTopIndex);
}

int CXMatchRefObjectSelDlg::DoModal()   
{   
	CRect rect(0,0,300,200);   
	SetDlgRect(rect);
//	AddDlgControl(_T("LISTBOX"), _T("ListboxText"), STYLE_LISTBOX, EXSTYLE_LISTBOX, &rect, &m_lstBox, IDC_LIST_DATAS);   
	int iRet = CDynDialogEx::DoModal();   

	return iRet;   
}   

 void CXMatchRefObjectSelDlg::OnCancel()
 {
	 //CDialog::OnCancel()
	ShowWindow(SW_HIDE);
 }

 void CXMatchRefObjectSelDlg::OnOK()
 {
	//CDialog::OnOK()
	ShowWindow(SW_HIDE);
 }

void CXMatchRefObjectSelDlg::OnDblclkList()    
{   
	CString strBuf;   
	int nIndex = m_lstBox.GetCurSel();   

	if (nIndex == LB_ERR)
	{
		return;
	}

	CExBaseObject *pSel = (CExBaseObject*)m_lstBox.GetItemDataPtr(nIndex);
	//CXMatchEditGridCtrlBase *pXMatchGrid = (CXMatchEditGridCtrlBase*)GetParent();
	//pXMatchGrid->SetMatchRefData(pSel);

	if (m_pEdit != NULL)
	{
		m_pEdit->SetMatchRefData(pSel);
	}

	//AfxMessageBox(strBuf);   
	//OnOK();   
}  