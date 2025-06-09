// XFolderAddDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "XFolderAddDlg.h"
#include "..\..\Module\API\GloblaDrawFunctions.h"
#include "..\XLanguage\XLanguageMngr.h"
#include "..\XLanguage\XLangWndAdjust.h"

// CXFolderAddDlg 对话框

//IMPLEMENT_DYNAMIC(CXFolderAddDlg, CDynDialogEx)

CXFolderAddDlg::CXFolderAddDlg(CWnd* pParent /*=NULL*/)
	: CDynDialogEx(pParent)
	, m_strDestFolderName(_T(""))
	, m_strInfor(_T(""))
{
	m_pSrcFolder = NULL;
}

CXFolderAddDlg::~CXFolderAddDlg()
{
}

void CXFolderAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CDynDialogEx::DoDataExchange(pDX);

	if (!m_bHasInitDialog)
	{
		return;
	}

	DDX_Text(pDX, XFIDC_EDIT_DEST_NAME, m_strDestFolderName);
	DDX_Text(pDX, XFIDC_EDIT_INFOR, m_strInfor);
}


BEGIN_MESSAGE_MAP(CXFolderAddDlg, CDynDialogEx)
	ON_EN_CHANGE(XFIDC_EDIT_DEST_NAME, &CXFolderAddDlg::OnEnChangeEditDestName)
END_MESSAGE_MAP()


// CXFolderAddDlg 消息处理程序

void CXFolderAddDlg::OnEnChangeEditDestName()
{
	EnableOkButton();
}

void CXFolderAddDlg::xlang_InitAndAdjust()
{
	if (xlang_IsCurrXLanguageChinese())
	{
		return;
	}
    m_stcDstFileName.SetLanguageID(g_sLangTxt_TgetFileNm);
	m_btnOK.SetLanguageID(g_sLangTxt_OK);
	m_btnCancel.SetLanguageID(g_sLangTxt_Cancel);

	CXLangWndAdjMngr oWndAdjMngr;  
	oWndAdjMngr.RegisterCols();
	oWndAdjMngr.RegisterXCol(&m_stcDstFileName);
	oWndAdjMngr.RegisterCol();
	oWndAdjMngr.RegisterWnd(&m_edtDestFileName);
	/*oWndAdjMngr.RegisterCols();*/
	oWndAdjMngr.RegisterXCol(&m_btnOK);
	oWndAdjMngr.RegisterXCol(&m_btnCancel);



	oWndAdjMngr.Adjust(this, TRUE);
}

BOOL CXFolderAddDlg::OnInitDialog()
{
	CDynDialogEx::OnInitDialog();

	m_stcDstFileName.CreateEx(EXSTYLE_STATIC, _T("STATIC"),g_sLangTxt_TgetFileNm/*_T("目标文件名称")*/, STYLE_STATIC, CRect(10,10,100,30), this, XFIDC_TITLE_DEST_NAME); 
	m_edtDestFileName.CreateEx(EXSTYLE_EDIT, _T("EDIT"), _T(""), STYLE_EDIT, CRect(110,10,400,30), this, XFIDC_EDIT_DEST_NAME); 
	m_edtInfor.CreateEx(EXSTYLE_EDIT, _T("EDIT"), _T(""), STYLE_EDIT|ES_READONLY, CRect(10,40,400,60), this, XFIDC_EDIT_INFOR); 

	m_btnOK.CreateEx(EXSTYLE_BUTTON, _T("BUTTON"), g_sLangTxt_OK/*_T("确定")*/, STYLE_BUTTON, CRect(60,70,110,95), this, IDOK); 
	m_btnCancel.CreateEx(EXSTYLE_BUTTON, _T("BUTTON"), g_sLangTxt_Cancel/*_T("取消")*/, STYLE_BUTTON, CRect(120,70,180,95), this, IDCANCEL); 

	CFont *pFont = g_pGlobalFont;
	m_stcDstFileName.SetFont(pFont);
	m_edtDestFileName.SetFont(pFont);
	m_edtInfor.SetFont(pFont);
	m_btnOK.SetFont(pFont);
	m_btnCancel.SetFont(pFont);

	MoveWindow(CRect( 0, 0, 410, 125), TRUE);
	CenterWindow();
	SetWindowText(g_sLangTxt_NewFolder/*_T("新建文件夹")*/);

	xlang_InitAndAdjust();
	EnableOkButton();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CXFolderAddDlg::EnableOkButton()
{
	if (m_pSrcFolder == NULL)
	{
		m_btnOK.EnableWindow(FALSE);
		return;
	}

	UpdateData(TRUE);

	if (m_strDestFolderName.GetLength() == 0)
	{
		m_btnOK.EnableWindow(FALSE);
		return;
	}

	if (m_pSrcFolder->FindByID(m_strDestFolderName) != NULL)
	{
		m_strInfor.Format(g_sLangTxt_ExiSaNameFile/*_T("存在同名称的文件夹【%s】")*/, m_strDestFolderName);
		m_btnOK.EnableWindow(FALSE);
	}
	else
	{
		m_strInfor.Empty();
		m_btnOK.EnableWindow(TRUE);
	}

	UpdateData(FALSE);
}

void CXFolderAddDlg::OnOK()
{
	UpdateData(TRUE);

	if (!xfile_CheckFileName(m_strDestFolderName, this))
	{
		return;
	}

	CDynDialogEx::OnOK();
}
