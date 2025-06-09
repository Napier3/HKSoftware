// XFolderSelDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "XFolderSelDlg.h"
#include "..\..\Module\API\GloblaDrawFunctions.h"


// CXFolderSelDlg 对话框

//IMPLEMENT_DYNAMIC(CXFolderSelDlg, CDynDialogEx)

CXFolderSelDlg::CXFolderSelDlg(CWnd* pParent /*=NULL*/)
	: CDynDialogEx(pParent)
{
	m_pSrcFolder = NULL;
	m_pXFileMngr = NULL;
	m_pImgFolder = NULL;
}

CXFolderSelDlg::~CXFolderSelDlg()
{
}

void CXFolderSelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDynDialogEx::DoDataExchange(pDX);

	if (!m_bHasInitDialog)
	{
		return;
	}
}


BEGIN_MESSAGE_MAP(CXFolderSelDlg, CDynDialogEx)
	ON_MESSAGE(WM_THREAD_XFILE_MNGR, OnXFileMngrSelChanged)
END_MESSAGE_MAP()


// CXFolderSelDlg 消息处理程序

BOOL CXFolderSelDlg::OnInitDialog()
{
	CDynDialogEx::OnInitDialog();
	CreateTreeCtrl(m_treeFolder, CRect(10, 10, 390, 290), XFIDC_TREE_FOLDER, this);

	m_btnOK.CreateEx(EXSTYLE_BUTTON, _T("BUTTON"), _T("确定"), STYLE_BUTTON, CRect(240,300,310,325), this, IDOK); 
	m_btnCancel.CreateEx(EXSTYLE_BUTTON, _T("BUTTON"), _T("取消"), STYLE_BUTTON, CRect(320,300,390,325), this, IDCANCEL); 

	CFont *pFont = g_pGlobalFont;
	m_treeFolder.SetFont(pFont);
	m_btnOK.SetFont(pFont);
	m_btnCancel.SetFont(pFont);

	MoveWindow(CRect( 0, 0, 405, 365), TRUE);
	CenterWindow();
	SetWindowText(_T("选择文件夹"));

	m_treeFolder.SetFrameWnd(this);

	if (m_pImgFolder != NULL)//周宏军 20200228 用于增加树形控件的文件夹图标
	{
		m_treeFolder.SetImageList(m_pImgFolder, TVSIL_NORMAL);
	}

	ASSERT (m_pXFileMngr != NULL);
	m_treeFolder.SetExBaseItemData(FALSE);
	m_treeFolder.ShowXFileMngr(m_pXFileMngr);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CXFolderSelDlg::EnableOkButton()
{
	if (m_pSrcFolder == NULL)
	{
		m_btnOK.EnableWindow(FALSE);
		return;
	}

	UpdateData(FALSE);
}

void CXFolderSelDlg::OnOK()
{

	CDynDialogEx::OnOK();
}

LRESULT CXFolderSelDlg::OnXFileMngrSelChanged(WPARAM wParam, LPARAM lParam)
{
	CExBaseObject *pSel = (CExBaseObject*)wParam;

	m_pXFileMngr->SetCurrSel(pSel);
	m_pSrcFolder = m_pXFileMngr->GetCurrSelFolder();

	return 0;
}

