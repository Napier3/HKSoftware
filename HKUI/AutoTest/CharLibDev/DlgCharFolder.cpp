// DlgCharFolder.cpp : 实现文件
//

#include "stdafx.h"
#include "CharLibDev.h"
#include "DlgCharFolder.h"
#include "XLanguageResourceAts_CharLibDev.h"

// CDlgCharFolder 对话框

IMPLEMENT_DYNAMIC(CDlgCharFolder, CDialog)

CDlgCharFolder::CDlgCharFolder(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCharFolder::IDD, pParent)
	, m_strName(_T(""))
{

}

CDlgCharFolder::~CDlgCharFolder()
{
}

void CDlgCharFolder::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_STATIC_FOLDERNAME, m_wndFolderName);
	DDX_Control(pDX, IDC_EDIT_NAME, m_edtFolderName);
}


BEGIN_MESSAGE_MAP(CDlgCharFolder, CDialog)
	ON_EN_CHANGE(IDC_EDIT_NAME, &CDlgCharFolder::OnEnChangeEditName)
END_MESSAGE_MAP()


// CDlgCharFolder 消息处理程序

void CDlgCharFolder::OnEnChangeEditName()
{
	UpdateData(TRUE);

	if (m_strName.GetLength() == 0)
	{
		m_btnOK.EnableWindow(FALSE);
	}
	else
	{
		m_btnOK.EnableWindow(TRUE);
	}
}

void CDlgCharFolder::xlang_InitAndAdjust()
{
	if (xlang_IsCurrXLanguageChinese())
	{
		return;
	}

	m_wndFolderName.SetLanguageID(g_sLangID_FolderName);
	m_btnOK.SetLanguageID(g_sLangID_OK);
	m_btnCancel.SetLanguageID(g_sLangID_Cancel);

	CXLangWndAdjMngr oWndAdjMngr;         
	oWndAdjMngr.RegisterCols(); 
	oWndAdjMngr.RegisterXCol(&m_wndFolderName);
	oWndAdjMngr.RegisterCol();
	oWndAdjMngr.RegisterWnd(&m_edtFolderName);
	oWndAdjMngr.RegisterCols();
	oWndAdjMngr.RegisterXCol(&m_btnOK);
	oWndAdjMngr.RegisterXCol(&m_btnCancel);
	

	oWndAdjMngr.Adjust(this, TRUE);
	xlang_InitByLgugStr(g_sLangID_CurveMageFolder, this);
}

BOOL CDlgCharFolder::OnInitDialog()
{
	CDialog::OnInitDialog();

	OnEnChangeEditName();

	xlang_InitAndAdjust();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgCharFolder::OnOK()
{
	UpdateData(TRUE);

	CString strMsg;
	CExBaseObject *pFind = m_pParentFolder->FindByName(m_strName);

	if (pFind != NULL && pFind != m_pCurrEdit)
	{
		strMsg.Format(g_sLangTxt_FatherSame/*_T("父文件夹“%s”存在相同名称的“%s”子文件夹！")*/, m_pParentFolder->m_strName, m_strName);
		MessageBox(strMsg, g_sLangTxt_Message1/*_T("提示")*/, MB_OK | MB_ICONERROR);
		return;
	}

	CDialog::OnOK();
}
