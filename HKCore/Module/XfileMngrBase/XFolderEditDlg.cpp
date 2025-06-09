// XFolderEditDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "XFolderEditDlg.h"
#include "..\..\Module\API\GloblaDrawFunctions.h"
#include "..\XLanguage\XLanguageMngr.h"
#include "..\XLanguage\XLangWndAdjust.h"

// CXFolderEditDlg 对话框

//IMPLEMENT_DYNAMIC(CXFolderEditDlg, CDynDialogEx)

CXFolderEditDlg::CXFolderEditDlg(CWnd* pParent /*=NULL*/)
	: CDynDialogEx(pParent)
	, m_strSrcFolderName(_T(""))
	, m_strDestFolderName(_T(""))
	, m_strInfor(_T(""))
{
	m_pSrcFolder = NULL;
	m_bAddSystemButtons = FALSE;
}

CXFolderEditDlg::~CXFolderEditDlg()
{
}

void CXFolderEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDynDialogEx::DoDataExchange(pDX);

	if (!m_bHasInitDialog)
	{
		return;
	}

	DDX_Text(pDX, XFIDC_EDIT_SRC_NAME, m_strSrcFolderName);
	DDX_Text(pDX, XFIDC_EDIT_DEST_NAME, m_strDestFolderName);
	DDX_Text(pDX, XFIDC_EDIT_INFOR, m_strInfor);
	//DDX_Control(pDX, IDOK, m_btnOK);
}


BEGIN_MESSAGE_MAP(CXFolderEditDlg, CDynDialogEx)
	ON_EN_CHANGE(XFIDC_EDIT_DEST_NAME, &CXFolderEditDlg::OnEnChangeEditDestName)
END_MESSAGE_MAP()


// CXFolderEditDlg 消息处理程序

void CXFolderEditDlg::OnEnChangeEditDestName()
{
	EnableOkButton();
}

void CXFolderEditDlg::xlang_InitAndAdjust()
{
	if (xlang_IsCurrXLanguageChinese())
	{
		return;
	}
	m_stcSrcFileName.SetLanguageID(g_sLangTxt_OrgnFileNm);
	m_stcDstFileName.SetLanguageID(g_sLangTxt_TgetFileNm);
	m_btnOK.SetLanguageID(g_sLangTxt_OK );
	m_btnCancel.SetLanguageID(g_sLangTxt_Cancel );

	CXLangWndAdjMngr oWndAdjMngr;  
	oWndAdjMngr.RegisterCols();
	oWndAdjMngr.RegisterCol();
	oWndAdjMngr.RegisterCols();
	oWndAdjMngr.RegisterXCol(&m_stcSrcFileName);
	oWndAdjMngr.RegisterCols();
	oWndAdjMngr.RegisterXCol(&m_stcDstFileName);
	oWndAdjMngr.RegisterCol();
	oWndAdjMngr.RegisterWnd(&m_edtSrcFileName);
	oWndAdjMngr.RegisterWnd(&m_edtDestFileName);
	/*oWndAdjMngr.RegisterCols();*/
	oWndAdjMngr.RegisterXCol(&m_btnOK);
	oWndAdjMngr.RegisterXCol(&m_btnCancel);



	oWndAdjMngr.Adjust(this, TRUE);
}
BOOL CXFolderEditDlg::OnInitDialog()
{
	CDynDialogEx::OnInitDialog();

	m_stcSrcFileName.CreateEx(EXSTYLE_STATIC, _T("STATIC"), g_sLangTxt_OrgnFileNm/*_T("原文件名称")*/, STYLE_STATIC, CRect(10,10,100,30), this, XFIDC_TITLE_SRC_NAME); 
	m_edtSrcFileName.CreateEx(EXSTYLE_EDIT, _T("EDIT"), _T(""), STYLE_EDIT| ES_READONLY, CRect(110,10,400,30), this, XFIDC_EDIT_SRC_NAME); 

	m_stcDstFileName.CreateEx(EXSTYLE_STATIC, _T("STATIC"), g_sLangTxt_TgetFileNm/*_T("目标文件名称")*/, STYLE_STATIC, CRect(10,40,100,60), this, XFIDC_TITLE_DEST_NAME); 
	m_edtDestFileName.CreateEx(EXSTYLE_EDIT, _T("EDIT"), _T(""), STYLE_EDIT, CRect(110,40,400,60), this, XFIDC_EDIT_DEST_NAME); 
	m_edtInfor.CreateEx(EXSTYLE_EDIT, _T("EDIT"), _T(""), STYLE_EDIT|ES_READONLY, CRect(10,70,400,90), this, XFIDC_EDIT_INFOR); 
	m_btnOK.CreateEx(EXSTYLE_BUTTON, _T("BUTTON"), g_sLangTxt_OK /*_T("确定")*/, STYLE_BUTTON, CRect(60,100,110,125), this, IDOK); 
	m_btnCancel.CreateEx(EXSTYLE_BUTTON, _T("BUTTON"), g_sLangTxt_Cancel/*_T("取消")*/, STYLE_BUTTON, CRect(120,100,180,125), this, IDCANCEL); 

	CFont *pFont = g_pGlobalFont;
	m_stcSrcFileName.SetFont(pFont);
	m_edtSrcFileName.SetFont(pFont);
	m_stcDstFileName.SetFont(pFont);
	m_edtDestFileName.SetFont(pFont);
	m_edtInfor.SetFont(pFont);
	m_btnOK.SetFont(pFont);
	m_btnCancel.SetFont(pFont);

	m_bHasInitDialog = TRUE;
	MoveWindow(CRect( 0, 0, 410, 155), TRUE);
	CenterWindow();
	SetWindowText(g_sLangTxt_FolderNmMdf/*_T("文件夹名称修改")*/);

	if (m_pSrcFolder != NULL)
	{
		m_strSrcFolderName = m_pSrcFolder->m_strID;
		m_strDestFolderName = m_pSrcFolder->m_strID;
		UpdateData(FALSE);
		EnableOkButton();
	}

    xlang_InitAndAdjust();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CXFolderEditDlg::EnableOkButton()
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

	CXFolder *pFolder = (CXFolder*)m_pSrcFolder->GetParent();
	CXFolder *pFind = (CXFolder*)pFolder->FindByID(m_strDestFolderName) ;

	if ((pFind != NULL) && (pFind != m_pSrcFolder))
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

void CXFolderEditDlg::OnOK()
{
	UpdateData(TRUE);

	if (!xfile_CheckFileName(m_strDestFolderName, this))
	{
		return;
	}

	m_pSrcFolder->RenameFolder(m_strDestFolderName);

	CDynDialogEx::OnOK();
}
