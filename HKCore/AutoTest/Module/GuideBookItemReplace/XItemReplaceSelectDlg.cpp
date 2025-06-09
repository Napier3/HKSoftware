// BaseKeyDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "XItemReplaceSelectDlg.h"
#include "..\..\..\Module\API\GloblaDrawFunctions.h"

// CBaseKeyDlg 对话框

IMPLEMENT_DYNAMIC(CXItemReplaceSelectDlg, CDialog)

CXItemReplaceSelectDlg::CXItemReplaceSelectDlg(CWnd* pParent /*=NULL*/)
:CXSelectItemsDlg(pParent)
{
	
}

CXItemReplaceSelectDlg::~CXItemReplaceSelectDlg()
{
}

// CBaseKeyDlg 消息处理程序



BOOL CXItemReplaceSelectDlg::OnInitDialog()
{
	CXSelectItemsDlg::OnInitDialog();

// 	CRect rcDlg;
// 	GetWindowRect(&rcDlg);
// 	rcDlg.right = 160;
// 	rcDlg.bottom = 160;
// 	MoveWindow(rcDlg, TRUE);

	m_cmbMode.AddString(/*L"项目分类的全部子项目（包含子分类）"*/g_sLangTxt_ItemClassAllSubItem);
	m_cmbMode.AddString(/*L"项目分类的子项目（不包含子分类）"*/g_sLangTxt_ItemClassSubItem);
	m_cmbMode.SetCurSel(0);

	SetWindowText(/*_T("选择项目分类以及子项目选择模式")*/g_sLangTxt_SelItemClassMode);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CXItemReplaceSelectDlg::CreateControls()    //创建控件  name、 size、 ID、 this    //继续增加各个控件的属性，字体啊什么的
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


int CXItemReplaceSelectDlg::DoModal()   //弹出对话框
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

