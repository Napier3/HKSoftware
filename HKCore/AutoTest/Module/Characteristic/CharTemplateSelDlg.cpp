// CharTemplateSelDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CharTemplateSelDlg.h"

#include "..\..\..\Module\Axis\AxisInterface.h"
#include "..\..\..\Module\API\GloblaDrawFunctions.h"
#include "..\XLanguageResourceAts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCharTemplateSelDlg 对话框

IMPLEMENT_DYNAMIC(CCharTemplateSelDlg, CDialog)

CCharTemplateSelDlg::CCharTemplateSelDlg(CWnd* pParent /*=NULL*/)
	: CDynDialogEx(pParent)
{
	m_pCharTemp = NULL;

}

CCharTemplateSelDlg::~CCharTemplateSelDlg()
{
}

void CCharTemplateSelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDynDialogEx::DoDataExchange(pDX);

}


BEGIN_MESSAGE_MAP(CCharTemplateSelDlg, CDynDialogEx)
	ON_NOTIFY(TVN_SELCHANGED, IDC_CHARTEMPLATESEL_TREE, &CCharTemplateSelDlg::OnTvnSelchangedTreeFolder)
END_MESSAGE_MAP()


void CCharTemplateSelDlg::CreateControls()
{
	CreateTreeCtrl(m_treeCharTemplate, CRect(5, 5, 300, 240), IDC_CHARTEMPLATESEL_TREE, this);
	CreateButton(m_btnOK, g_sLangTxt_OK/*_T("确定")*/, CRect(70, 245, 140, 266), IDOK, this);
	CreateButton(m_btnCancel, g_sLangTxt_Cancel/*_T("取消")*/, CRect(150, 245, 220, 266), IDCANCEL, this);

	m_treeCharTemplate.SetFont(g_pGlobalFont12);
	m_btnOK.SetFont(g_pGlobalFont12);
	m_btnCancel.SetFont(g_pGlobalFont12);
}


// CCharTemplateSelDlg 消息处理程序
void CCharTemplateSelDlg::InitImageList(UINT nBmpID)
{
	m_CharLibViewImages.DeleteImageList();

	CBitmap bmp;
	if (!bmp.LoadBitmap(nBmpID))
	{
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK;
	nFlags |= ILC_COLOR24;

	m_CharLibViewImages.Create(16, bmpObj.bmHeight, ILC_COLOR24, 0, 0);
	m_CharLibViewImages.Add(&bmp, RGB(255, 0, 0));

	m_treeCharTemplate.SetImageList(&m_CharLibViewImages, TVSIL_NORMAL);

}

BOOL CCharTemplateSelDlg::OnInitDialog()
{
	CDynDialogEx::OnInitDialog();

	CreateControls();
	EnableOKButton();

	MoveWindow(CRect( 0, 0, 310, 300), TRUE);
	CenterWindow();
	SetWindowText(g_sLangTxt_SelCharCurve/*_T("选择特性曲线")*/);

	m_treeCharTemplate.ShowCharLib(m_pCharLib);

	return TRUE;
}

void CCharTemplateSelDlg::OnTvnSelchangedTreeFolder(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	
	m_pCharTemp = m_treeCharTemplate.GetCurrSelChar();
	EnableOKButton();

	*pResult = 0;
}

void CCharTemplateSelDlg::EnableOKButton()
{
	UpdateData(TRUE);

	if (m_pCharTemp == NULL)
	{
		m_btnOK.EnableWindow(FALSE);
		return;
	}

	m_btnOK.EnableWindow(TRUE);
}


