// XFileEditDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "XFileEditDlg.h"
#include "..\..\Module\API\GloblaDrawFunctions.h"
#include "..\XLanguage\XLanguageMngr.h"
#include "..\XLanguage\XLangWndAdjust.h"


// CXFileEditDlg �Ի���

//IMPLEMENT_DYNAMIC(CXFileEditDlg, CDynDialogEx)

CXFileEditDlg::CXFileEditDlg(CWnd* pParent /*=NULL*/)
	: CDynDialogEx(pParent)
{
	m_pSrcFile = NULL;
	m_bHasInitDialog = FALSE;
	m_bAddSystemButtons = FALSE;
	m_pXFileMsgRcvWnd = NULL;
}

CXFileEditDlg::~CXFileEditDlg()
{
}

void CXFileEditDlg::DoDataExchange(CDataExchange* pDX)
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
}


BEGIN_MESSAGE_MAP(CXFileEditDlg, CDynDialogEx)
	ON_EN_CHANGE(XFIDC_EDIT_DEST_NAME, &CXFileEditDlg::OnEnChangeEditDestName)
END_MESSAGE_MAP()


// CXFileEditDlg ��Ϣ�������

void CXFileEditDlg::OnEnChangeEditDestName()
{
	EnableOkButton();
}

/*
int CXFileEditDlg::DoModal()   
{   
	CRect rectOK(96,70,96+50,70+14);   
	AddDlgControl(_T("BUTTON"), _T("ȷ��"), STYLE_BUTTON, EXSTYLE_BUTTON, &rectOK, &m_btnOK, IDOK);   

	CRect rectCancel(154,70,154+50,70+14);   
	AddDlgControl(_T("BUTTON"), _T("ȡ��"), STYLE_BUTTON, EXSTYLE_BUTTON, &rectCancel, NULL, IDCANCEL);   

	CRect rectTitleSrc(15,14,15+41,14+8);   
	AddDlgControl(_T("STATIC"), _T("ԭ�ļ�����"), STYLE_STATIC, EXSTYLE_STATIC, &rectTitleSrc);   

	CRect rectTitleDst(7,30,7+49,14+8);   
	AddDlgControl(_T("STATIC"), _T("Ŀ���ļ�����"), STYLE_STATIC, EXSTYLE_STATIC, &rectTitleDst);   

	CRect rectEditSrc(62,11,62+231,11+14);   
	AddDlgControl(_T("EDIT"), _T(""), STYLE_EDIT, EXSTYLE_EDIT, rectEditSrc, NULL, XFIDC_EDIT_SRC_NAME);   

	CRect rectEditDst(62,27,62+231,27+14);   
	AddDlgControl(_T("EDIT"), _T(""), STYLE_EDIT, EXSTYLE_EDIT, rectEditDst, NULL, XFIDC_EDIT_DEST_NAME);   

	CRect rectEditInfor(7,49,7+286,49+14);   
	AddDlgControl(_T("EDIT"), _T(""), STYLE_EDIT|ES_READONLY, EXSTYLE_EDIT, rectEditInfor, NULL, XFIDC_EDIT_INFOR);   

	int iRet = CDynDialogEx::DoModal();   

	return iRet;   
}   
*/

/*
IDD_DIALOG_STCFGFILE_EDIT DIALOGEX 0, 0, 300, 91
STYLE DS_SETFONT | DS_MODALFRAME | DS_FIXEDSYS | WS_POPUP | WS_CAPTION | WS_SYSMENU
CAPTION "�޸��ļ�����"
FONT 8, "MS Shell Dlg", 400, 0, 0x1
	DEFPUSHBUTTON   "ȷ��",IDOK,96,70,50,14
	PUSHBUTTON      "ȡ��",IDCANCEL,154,70,50,14
	LTEXT           "ԭ�ļ�����",IDC_STATIC,15,14,41,8
	LTEXT           "Ŀ���ļ�����",IDC_STATIC,7,30,49,8
	EDITTEXT        XFIDC_EDIT_SRC_NAME,62,11,231,14,ES_AUTOHSCROLL | ES_READONLY
	EDITTEXT        XFIDC_EDIT_DEST_NAME,62,27,231,14,ES_AUTOHSCROLL
	EDITTEXT        XFIDC_EDIT_INFOR,7,49,286,14,ES_AUTOHSCROLL | ES_READONLY
*/

void CXFileEditDlg::xlang_InitAndAdjust()
{
	if (xlang_IsCurrXLanguageChinese())
	{
		return;
	}
	m_stcSrcFileName.SetLanguageID(g_sLangTxt_OrgnFileNm);
	m_stcDstFileName.SetLanguageID(g_sLangTxt_TgetFileNm);
	//m_btnOK.SetLanguageID(g_sLangTxt_OK );
	//m_btnCancel.SetLanguageID(g_sLangTxt_Cancel );

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
	///*oWndAdjMngr.RegisterCols();*/
	//oWndAdjMngr.RegisterXCol(&m_btnOK);
	//oWndAdjMngr.RegisterXCol(&m_btnCancel);



	oWndAdjMngr.Adjust(this, TRUE);
}

BOOL CXFileEditDlg::OnInitDialog()
{
	CDynDialogEx::OnInitDialog();

	CreateStatic(m_stcSrcFileName,  g_sLangTxt_OrgnFileNm/*_T("ԭ�ļ�����")*/, CRect(10,10,100,30), XFIDC_TITLE_SRC_NAME, this);
	CreateEdit(m_edtSrcFileName, CRect(110,10,400,30), XFIDC_EDIT_SRC_NAME, this, EXSTYLE_EDIT, STYLE_EDIT| ES_READONLY);

	CreateStatic(m_stcDstFileName,  g_sLangTxt_TgetFileNm/*_T("Ŀ���ļ�����")*/, CRect(10,40,100,60), XFIDC_TITLE_DEST_NAME, this);
	CreateEdit(m_edtDestFileName, CRect(110,40,400,60), XFIDC_EDIT_DEST_NAME, this);
	CreateEdit(m_edtInfor, CRect(10,70,400,90), XFIDC_EDIT_INFOR, this, EXSTYLE_EDIT, STYLE_EDIT| ES_READONLY);

	CreateButton(m_btnOK, g_sLangTxt_OK/*_T("ȷ��")*/, CRect(60,100,110,125), IDOK, this);
	CreateButton(m_btnCancel, g_sLangTxt_Cancel/*_T("ȡ��")*/, CRect(120,100,180,125), IDCANCEL, this);

	CFont *pFont = g_pGlobalFont;
	m_stcSrcFileName.SetFont(pFont);
	m_edtSrcFileName.SetFont(pFont);
	m_stcDstFileName.SetFont(pFont);
	m_edtDestFileName.SetFont(pFont);
	m_edtInfor.SetFont(pFont);
	m_btnOK.SetFont(pFont);
	m_btnCancel.SetFont(pFont);

	m_bHasInitDialog = TRUE;
	if (m_pSrcFile != NULL)
	{
		m_strSrcFileName = m_pSrcFile->m_strID;
		m_strDestFileName = m_pSrcFile->m_strID;
		UpdateData(FALSE);
		EnableOkButton();
	}

	m_strFilePostfix = ParseFilePostfix(m_strSrcFileName);

	MoveWindow(CRect( 0, 0, 410, 155), TRUE);
	CenterWindow();
	SetWindowText(g_sLangTxt_FileRename/*_T("�ļ������޸�")*/);

	xlang_InitAndAdjust();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CXFileEditDlg::EnableOkButton()
{
	if (m_pSrcFile == NULL)
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

	CString strDestName = m_strDestFileName;
	ChangeFilePostfix(strDestName, m_strFilePostfix);
	CXFolder *pFolder = (CXFolder*)m_pSrcFile->GetParent();
	CExBaseObject *pFind = pFolder->FindByID(strDestName);

	if ((pFind != NULL) && (pFind != m_pSrcFile))
	{
		m_strInfor.Format(g_sLangTxt_ExiSmNmFile2/*_T("�ļ��С�%s������ͬ���Ƶ��ļ���%s��")*/,pFolder->m_strName, m_strDestFileName);
		m_btnOK.EnableWindow(FALSE);
	}
	else
	{
		m_strInfor.Empty();
		m_btnOK.EnableWindow(TRUE);
	}

	UpdateData(FALSE);
}

void CXFileEditDlg::OnOK()
{
	UpdateData(TRUE);

	CString strDestName = m_strDestFileName;

	if (m_strFilePostfix.GetLength() != 0)
	{
		strDestName = ChangeFilePostfix(strDestName, m_strFilePostfix);
	}

	if (!xfile_CheckFileName(strDestName, this))
	{
		return;
	}

	if (m_pXFileMsgRcvWnd != NULL)
	{
		m_pXFileMsgRcvWnd->XEditXFile(m_pSrcFile, strDestName);
	}
	else
	{
		m_pSrcFile->RenameFile(strDestName);
	}

	CDynDialogEx::OnOK();
}
