// XFilePasteDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "XFilePasteDlg.h"
#include "..\..\Module\API\GloblaDrawFunctions.h"
#include "..\XLanguage\XLanguageMngr.h"
#include "..\XLanguage\XLangWndAdjust.h"


// CXFilePasteDlg 对话框

//IMPLEMENT_DYNAMIC(CXFilePasteDlg, CDynDialogEx)

CXFilePasteDlg::CXFilePasteDlg(CWnd* pParent /*=NULL*/)
	: CDynDialogEx(pParent)
	, m_strSrcFileName(_T(""))
	, m_strDestFileName(_T(""))
	, m_strInfor(_T(""))
{
	m_pSrcFile = NULL;
	m_pDestFile = NULL;
	m_pDestFolder = NULL;
}

CXFilePasteDlg::~CXFilePasteDlg()
{
}

void CXFilePasteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDynDialogEx::DoDataExchange(pDX);

	if (!m_bHasInitDialog)
	{
		return;
	}

	DDX_Text(pDX, XFIDC_EDIT_SRC_NAME, m_strSrcFileName);
	DDX_Text(pDX, XFIDC_EDIT_DEST_NAME, m_strDestFileName);
	DDX_Text(pDX, XFIDC_EDIT_INFOR, m_strInfor);
	//DDX_Control(pDX, IDOK, m_btnOK);
	//DDX_Control(pDX, XFID_OVERWRITE, m_btnOverWrite);
}


BEGIN_MESSAGE_MAP(CXFilePasteDlg, CDynDialogEx)
	ON_EN_CHANGE(XFIDC_EDIT_DEST_NAME, &CXFilePasteDlg::OnEnChangeEditDestName)
	ON_BN_CLICKED(XFID_OVERWRITE, &CXFilePasteDlg::OnBnClickedOverwrite)
END_MESSAGE_MAP()


// CXFilePasteDlg 消息处理程序

void CXFilePasteDlg::OnEnChangeEditDestName()
{
	EnableOkButton();
}

void CXFilePasteDlg::OnBnClickedOverwrite()
{
	m_pDestFile = m_pDestFolder->AddFile(m_pSrcFile);
	CDynDialogEx::OnOK();
}

void CXFilePasteDlg::xlang_InitAndAdjust()
{
	if (xlang_IsCurrXLanguageChinese())
	{
		return;
	}
	m_stcSrcFileName.SetLanguageID(g_sLangTxt_OrgnFileNm);
	m_stcDstFileName.SetLanguageID(g_sLangTxt_TgetFileNm);
	m_btnOK.SetLanguageID(g_sLangTxt_OK );
	m_btnCancel.SetLanguageID(g_sLangTxt_Cancel );
	m_btnOverWrite.SetLanguageID(g_sLangTxt_OverWrite );

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
    oWndAdjMngr.RegisterXCol(&m_btnOverWrite);

	oWndAdjMngr.Adjust(this, TRUE);
}

BOOL CXFilePasteDlg::OnInitDialog()
{
	CDynDialogEx::OnInitDialog();

	m_stcSrcFileName.CreateEx(EXSTYLE_STATIC, _T("STATIC"), g_sLangTxt_OrgnFileNm/*_T("原文件名称")*/, STYLE_STATIC, CRect(10,10,100,30), this, XFIDC_TITLE_SRC_NAME); 
	m_edtSrcFileName.CreateEx(EXSTYLE_EDIT, _T("EDIT"), _T(""), STYLE_EDIT| ES_READONLY, CRect(110,10,400,30), this, XFIDC_EDIT_SRC_NAME); 

	m_stcDstFileName.CreateEx(EXSTYLE_STATIC, _T("STATIC"), g_sLangTxt_TgetFileNm/*_T("目标文件名称")*/, STYLE_STATIC, CRect(10,40,100,60), this, XFIDC_TITLE_DEST_NAME); 
	m_edtDestFileName.CreateEx(EXSTYLE_EDIT, _T("EDIT"), _T(""), STYLE_EDIT, CRect(110,40,400,60), this, XFIDC_EDIT_DEST_NAME); 
	m_edtInfor.CreateEx(EXSTYLE_EDIT, _T("EDIT"), _T(""), STYLE_EDIT|ES_READONLY, CRect(10,70,400,90), this, XFIDC_EDIT_INFOR); 
	m_btnOK.CreateEx(EXSTYLE_BUTTON, _T("BUTTON"), g_sLangTxt_OK/*_T("确定")*/, STYLE_BUTTON, CRect(60,100,110,125), this, IDOK); 
	m_btnCancel.CreateEx(EXSTYLE_BUTTON, _T("BUTTON"), g_sLangTxt_Cancel/*_T("取消")*/, STYLE_BUTTON, CRect(120,100,180,125), this, IDCANCEL); 
	m_btnOverWrite.CreateEx(EXSTYLE_BUTTON, _T("BUTTON"), g_sLangTxt_OverWrite/*_T("覆盖")*/, STYLE_BUTTON, CRect(190,100,230,125), this, XFID_OVERWRITE); 

	CFont *pFont = g_pGlobalFont;
	m_stcSrcFileName.SetFont(pFont);
	m_edtSrcFileName.SetFont(pFont);
	m_stcDstFileName.SetFont(pFont);
	m_edtDestFileName.SetFont(pFont);
	m_edtInfor.SetFont(pFont);
	m_btnOK.SetFont(pFont);
	m_btnCancel.SetFont(pFont);
	m_btnOverWrite.SetFont(pFont);

	m_bHasInitDialog = TRUE;
	MoveWindow(CRect( 0, 0, 410, 155), TRUE);
	CenterWindow();
	SetWindowText(g_sLangTxt_FilePasteOprt/*_T("文件粘贴：操作处理")*/);

	if (m_pSrcFile != NULL)
	{
		m_strSrcFileName = m_pSrcFile->m_strID;
		m_strDestFileName = m_pSrcFile->m_strID;
		UpdateData(FALSE);
		EnableOkButton();

		CExBaseObject *pParent = (CExBaseObject*)m_pSrcFile->GetParent();
		m_btnOverWrite.EnableWindow(m_pDestFolder != NULL && pParent != m_pDestFolder);
	}
	else
	{
		m_btnOverWrite.EnableWindow(FALSE);
	}
    xlang_InitAndAdjust();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CXFilePasteDlg::EnableOkButton()
{
	if (m_pSrcFile == NULL || m_pDestFolder == NULL)
	{
		m_btnOK.EnableWindow(FALSE);
		return;
	}

	UpdateData(TRUE);

	if (m_strDestFileName.GetLength() == 0)
	{
		m_btnOK.EnableWindow(FALSE);
		return;
	}

	if (m_pDestFolder->FindByID(m_strDestFileName) != NULL)
	{
		m_strInfor.Format(g_sLangTxt_ExiSmNmFile3/*_T("存在同名称的文件【%s】")*/, m_strDestFileName);
		m_btnOK.EnableWindow(FALSE);
	}
	else
	{
		m_strInfor.Empty();
		m_btnOK.EnableWindow(TRUE);
	}

	UpdateData(FALSE);
}

void CXFilePasteDlg::OnOK()
{
	UpdateData(TRUE);

	m_pDestFile = m_pDestFolder->AddFile(m_pSrcFile, m_strDestFileName);

	CDynDialogEx::OnOK();
}
