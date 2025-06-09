// BaseKeyDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "XSelectItemsDlg.h"
#include "..\..\Module\API\GloblaDrawFunctions.h"

// CBaseKeyDlg �Ի���

IMPLEMENT_DYNAMIC(CXSelectItemsDlg, CDialog)

CXSelectItemsDlg::CXSelectItemsDlg(CWnd* pParent /*=NULL*/)
:CDynDialogEx(pParent)
{
	m_pCurrSelObj = NULL;
}

CXSelectItemsDlg::~CXSelectItemsDlg()
{
}

void CXSelectItemsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CXSelectItemsDlg, CDialog)
	ON_NOTIFY(TVN_SELCHANGED, IDC_GBSELDLG_TREE_ITEMS, &CXSelectItemsDlg::OnTvnSelchangedTreeItems)
END_MESSAGE_MAP()


// CBaseKeyDlg ��Ϣ�������



BOOL CXSelectItemsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CreateControls();  //�����ؼ�
	CenterWindow();

	CExBaseList oListParent;
	m_pTestItem->GetAllAncestor(&oListParent, GBCLASSID_DEVICE);
	CString strPrev, strText;
	HTREEITEM hItem;
	POS pos = oListParent.GetHeadPosition();
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = oListParent.GetNext(pos);
		strText = strPrev + pObj->m_strName;
		hItem = m_treeItemsAncester.InsertItem(strText);
		m_treeItemsAncester.SetItemData(hItem, (DWORD)pObj);
		strPrev += _T("**");
	}

	oListParent.RemoveAll();

// 	CRect rcDlg;
// 	GetWindowRect(&rcDlg);
// 	rcDlg.right = 160;
// 	rcDlg.bottom = 160;
// 	MoveWindow(rcDlg, TRUE);

	EnableButtons();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CXSelectItemsDlg::CreateControls()    //�����ؼ�  name�� size�� ID�� this    //�������Ӹ����ؼ������ԣ����尡ʲô��
{
	//240, 290
	CRect rc(5, 5, 293, 262);
	CreateTreeCtrl(m_treeItemsAncester, rc, IDC_GBSELDLG_TREE_ITEMS, this);
	
	CreateOKCancel(270);

	m_btnCancel.SetFont(g_pGlobalFont12);
	m_btnOK.SetFont(g_pGlobalFont12);
	m_treeItemsAncester.SetFont(g_pGlobalFont12);

}

void CXSelectItemsDlg::CreateOKCancel(long nTopPos)
{
	CRect rc;
	rc.top = nTopPos;
	rc.left = 15;
	rc.right = 100;
	rc.bottom = nTopPos + 25;

	CreateButton(m_btnOK, _T("ȷ��"), rc, IDOK, this);

	rc.left = 110;
	rc.right = 195;
	CreateButton(m_btnCancel, _T("ȡ��"), rc, IDCANCEL, this);

}



int CXSelectItemsDlg::DoModal()   //�����Ի���
{   
	CRect rect(0,0,200,185);    
	SetDlgRect(rect);
	int iRet = CDynDialogEx::DoModal();   

	return iRet;   
}   



void CXSelectItemsDlg::OnOK()
{
	CDialog::OnOK();
}

void CXSelectItemsDlg::OnCancel()
{
	CDialog::OnCancel();
}

 void CXSelectItemsDlg::EnableButtons()
 {
	m_btnOK.EnableWindow(m_pCurrSelObj != NULL);
 }

void CXSelectItemsDlg::OnTvnSelchangedTreeItems(NMHDR *pNMHDR, LRESULT *pResult)
{
	HTREEITEM hSel = m_treeItemsAncester.GetSelectedItem();

	if (hSel != NULL)
	{
		m_pCurrSelObj = (CExBaseObject*)m_treeItemsAncester.GetItemData(hSel);
	}
	else
	{
		m_pCurrSelObj = NULL;
	}

	EnableButtons();
}

