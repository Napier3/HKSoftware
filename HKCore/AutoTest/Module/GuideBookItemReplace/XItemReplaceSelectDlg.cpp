// BaseKeyDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "XItemReplaceSelectDlg.h"
#include "..\..\..\Module\API\GloblaDrawFunctions.h"

// CBaseKeyDlg �Ի���

IMPLEMENT_DYNAMIC(CXItemReplaceSelectDlg, CDialog)

CXItemReplaceSelectDlg::CXItemReplaceSelectDlg(CWnd* pParent /*=NULL*/)
:CXSelectItemsDlg(pParent)
{
	
}

CXItemReplaceSelectDlg::~CXItemReplaceSelectDlg()
{
}

// CBaseKeyDlg ��Ϣ�������



BOOL CXItemReplaceSelectDlg::OnInitDialog()
{
	CXSelectItemsDlg::OnInitDialog();

// 	CRect rcDlg;
// 	GetWindowRect(&rcDlg);
// 	rcDlg.right = 160;
// 	rcDlg.bottom = 160;
// 	MoveWindow(rcDlg, TRUE);

	m_cmbMode.AddString(/*L"��Ŀ�����ȫ������Ŀ�������ӷ��ࣩ"*/g_sLangTxt_ItemClassAllSubItem);
	m_cmbMode.AddString(/*L"��Ŀ���������Ŀ���������ӷ��ࣩ"*/g_sLangTxt_ItemClassSubItem);
	m_cmbMode.SetCurSel(0);

	SetWindowText(/*_T("ѡ����Ŀ�����Լ�����Ŀѡ��ģʽ")*/g_sLangTxt_SelItemClassMode);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CXItemReplaceSelectDlg::CreateControls()    //�����ؼ�  name�� size�� ID�� this    //�������Ӹ����ؼ������ԣ����尡ʲô��
{
	//240, 290
	CRect rc(5, 5, 293, 235);
	CreateTreeCtrl(m_treeItemsAncester, rc, IDC_GBSELDLG_TREE_ITEMS, this);

	CRect rc2(5, 240, 293, 262);

	CreateComboBox_DropList(m_cmbMode, rc2, IDC_GBSELDLG_COMBO_MODE, this);

	CreateOKCancel(270);
	m_btnCancel.SetFont(g_pGlobalFont12);
	m_btnOK.SetFont(g_pGlobalFont12);
	m_treeItemsAncester.SetFont(g_pGlobalFont12);
	m_cmbMode.SetFont(g_pGlobalFont12);
}


int CXItemReplaceSelectDlg::DoModal()   //�����Ի���
{   
	CRect rect(0,0,200,185);    
	SetDlgRect(rect);
	int iRet = CDynDialogEx::DoModal();   

	return iRet;   
}   



void CXItemReplaceSelectDlg::OnOK()
{
	m_nMode = m_cmbMode.GetCurSel();

	if (m_nMode == CB_ERR)
	{
		m_nMode = 0;
	}

	CDialog::OnOK();
}

void CXItemReplaceSelectDlg::OnCancel()
{
	CDialog::OnCancel();
}

