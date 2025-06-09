// XFileSaveAsDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "XFileSaveAsDlg.h"
#include "..\API\GloblaDrawFunctions.h"
#include "..\XLanguage\XLanguageMngr.h"
#include "..\XLanguage\XLangWndAdjust.h"

// CXFileSaveAsDlg 对话框

//IMPLEMENT_DYNAMIC(CXFileSaveAsDlg, CDynDialogEx)

CXFileSaveAsDlg::CXFileSaveAsDlg(CWnd* pParent /*=NULL*/)
	: CDynDialogEx(pParent)
	, m_strXFile(_T(""))
{
	m_pCurrSelFolder = NULL;
	m_pXFileMngr = NULL;
}

CXFileSaveAsDlg::~CXFileSaveAsDlg()
{
}

void CXFileSaveAsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDynDialogEx::DoDataExchange(pDX);

	if (!m_bHasInitDialog)
	{
		return;
	}

	DDX_Control(pDX, XFIDC_TREE_FOLDER, m_treeFolder);
	DDX_Text(pDX, XFIDC_EDIT_FILENAME, m_strXFile);
	DDX_Control(pDX, IDOK, m_btnOK);
}


BEGIN_MESSAGE_MAP(CXFileSaveAsDlg, CDynDialogEx)
	ON_EN_CHANGE(XFIDC_EDIT_FILENAME, &CXFileSaveAsDlg::OnEnChangeEditFilename)
	ON_NOTIFY(TVN_SELCHANGED, XFIDC_TREE_FOLDER, &CXFileSaveAsDlg::OnTvnSelchangedTreeFolder)
	ON_NOTIFY(NM_DBLCLK, XFIDC_TREE_FOLDER, &CXFileSaveAsDlg::OnNMDblclkTreeFolder)
END_MESSAGE_MAP()


// CXFileSaveAsDlg 消息处理程序

void CXFileSaveAsDlg::OnEnChangeEditFilename()
{
	EnableOkButton();
}

void CXFileSaveAsDlg::OnTvnSelchangedTreeFolder(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	*pResult = 0;
	EnableOkButton();
}

void CXFileSaveAsDlg::xlang_InitAndAdjust()
{
	if (xlang_IsCurrXLanguageChinese())
	{
		return;
	}
	m_stcTitleSelFolder.SetLanguageID(g_sLangTxt_SelFolder);
	m_stcTitleFileName.SetLanguageID(g_sLangTxt_FileName);
	m_btnOK.SetLanguageID(g_sLangTxt_OK );
	m_btnCancel.SetLanguageID(g_sLangTxt_Cancel );

	CXLangWndAdjMngr oWndAdjMngr;  
	oWndAdjMngr.RegisterCols();
	oWndAdjMngr.RegisterCol();
	oWndAdjMngr.RegisterCols();
	oWndAdjMngr.RegisterXCol(&m_stcTitleSelFolder);
	oWndAdjMngr.RegisterCols();
	oWndAdjMngr.RegisterXCol(&m_stcTitleFileName);
	oWndAdjMngr.RegisterCol();
	oWndAdjMngr.RegisterWnd(&m_treeFolder);
	oWndAdjMngr.RegisterWnd(&m_edtFileName);
	/*oWndAdjMngr.RegisterCols();*/
	oWndAdjMngr.RegisterXCol(&m_btnOK);
	oWndAdjMngr.RegisterXCol(&m_btnCancel);



	oWndAdjMngr.Adjust(this, TRUE);
}

BOOL CXFileSaveAsDlg::OnInitDialog()
{
	CDynDialogEx::OnInitDialog();

	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS | WS_BORDER;

	m_stcTitleSelFolder.CreateEx(EXSTYLE_STATIC, _T("STATIC"), g_sLangTxt_SelFolder/*_T("选择文件夹")*/, STYLE_STATIC, CRect(5,10,355,25), this, XFIDC_TITLE_SRC_NAME); 
	m_treeFolder.Create(dwViewStyle, CRect(5, 30, 355, 300), this, XFIDC_TREE_FOLDER);

	m_stcTitleFileName.CreateEx(EXSTYLE_STATIC, _T("STATIC"), g_sLangTxt_FileName/*_T("文件名")*/, STYLE_STATIC, CRect(5,312, 50, 328), this, XFIDC_TITLE_DEST_NAME); 
	m_edtFileName.CreateEx(EXSTYLE_EDIT, _T("EDIT"), _T(""), STYLE_EDIT, CRect(55,310,355,332), this, XFIDC_EDIT_FILENAME); 

	m_btnOK.CreateEx(EXSTYLE_BUTTON, _T("BUTTON"),g_sLangTxt_OK /*_T("确定")*/, STYLE_BUTTON, CRect(100,342, 180, 368), this, IDOK); 
	m_btnCancel.CreateEx(EXSTYLE_BUTTON, _T("BUTTON"), g_sLangTxt_Cancel/*_T("取消")*/, STYLE_BUTTON, CRect(200,342,280,368), this, IDCANCEL); 

	CFont *pFont = g_pGlobalFont;
	m_stcTitleSelFolder.SetFont(pFont);
	m_treeFolder.SetFont(pFont);
	m_stcTitleFileName.SetFont(pFont);
	m_edtFileName.SetFont(pFont);
	m_btnOK.SetFont(pFont);
	m_btnCancel.SetFont(pFont);

	MoveWindow(CRect( 0, 0, 368, 403), TRUE);
	CenterWindow();
	SetWindowText(g_sLangTxt_NewFolder/*_T("新建文件夹")*/);

	m_treeFolder.SetExBaseItemData(FALSE);
	m_treeFolder.ShowXFileMngr(m_pXFileMngr);
// 	m_strXFile = theApp.m_oXDatasMngr.GetXSystemConfig()->GetLastFile();
// 	m_strXFile = GetPathFileNameFromFilePathName(m_strXFile);
// 	long nPos = m_strXFile.Find('.');
// 
// 	if (nPos > 0)
// 	{
// 		m_strXFile = m_strXFile.Left(nPos);
// 	}

	UpdateData(FALSE);
    xlang_InitAndAdjust();
	return TRUE;
}

CString CXFileSaveAsDlg::GetXFilePath()
{
	CString strFile;
	CXFolder *pFolder = GetSelFolder();

	strFile = pFolder->GetFolderPath();
	strFile += m_strXFile;
	strFile = ChangeFilePostfix(strFile, m_strXFilePostFix);

	return strFile;
}

CString CXFileSaveAsDlg::GetXFile()
{
	CString strFile;
	strFile.Format(_T("%s.%s"), m_strXFile, m_strXFilePostFix);
	return strFile;
}

void CXFileSaveAsDlg::EnableOkButton()
{
	UpdateData(TRUE);

	BOOL bEnable = TRUE;
	m_pCurrSelFolder = GetSelFolder();

	if (m_pCurrSelFolder == NULL)
	{
		bEnable = FALSE;
	}

	if (m_strXFile.GetLength() == 0)
	{
		bEnable = FALSE;
	}

	m_btnOK.EnableWindow(bEnable);
}

void CXFileSaveAsDlg::OnOK()
{
	m_strXFilePath = GetXFilePath();
	CString strFile = GetXFile();

	if (!xfile_CheckFileName(strFile, this))
	{
		return;
	}

	strFile.MakeLower();
	m_pCurrSelFolder = GetSelFolder();
	CXFile *pFile = m_pCurrSelFolder->SelectFileInCurrFolder(strFile);

	if (pFile != NULL)
	{
		CString strMsg;
		strMsg.Format(g_sLangTxt_ExiFileOvwt/*_T("文件【%s】已经存在，覆盖吗？")*/, m_strXFilePath);

		if (MessageBox(strMsg,g_sLangTxt_Message/* _T("提示")*/, MB_YESNO) == IDNO)
		{
			return;
		}
	}

	CDynDialogEx::OnOK();
}

void CXFileSaveAsDlg::OnNMDblclkTreeFolder(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
