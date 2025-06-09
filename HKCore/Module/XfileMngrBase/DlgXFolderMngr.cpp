// D:\WorkPM\Source\Protocol\PpDev\PpTemplateFileMngr\DlgXFolderMngr.cpp : 实现文件
//

#include "stdafx.h"
#include "DlgXFolderMngr.h"
#include "..\XLanguage\XLanguageMngr.h"

#ifdef _Use_YUN_Client_
	#include "YunFileApi\XYunFileApi.h"
#else
	#include "YunFileApi\XYunFileApi_Server.h"
#endif

char CDlgXFolderMngr::g_pszFileName[MAX_PATH];

// CDlgXFolderMngr 对话框

IMPLEMENT_DYNAMIC(CDlgXFolderMngr, CDialog)

CDlgXFolderMngr::CDlgXFolderMngr(UINT nTemplateID,const CString& strFilePostFix,const CString& strPostFixDes,CXFileMngr* pFileMngrBase,UINT nMode,CWnd* pParent /*=NULL*/)
: CDynDialogEx(pParent)
{
	m_pFileMngrBase = pFileMngrBase;
}

CDlgXFolderMngr::~CDlgXFolderMngr()
{
}

void CDlgXFolderMngr::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgXFolderMngr, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgXFolderMngr::OnBnClickedOk)
END_MESSAGE_MAP()


int CDlgXFolderMngr::DoModal()   
{   
	int iRet = CDynDialogEx::DoModal();   

	return iRet;   
}   

// CDlgXFolderMngr 消息处理程序
void CDlgXFolderMngr::OnCancel()
{
	CDialog::OnCancel();
}

void CDlgXFolderMngr::OnBnClickedOk()
{
	CXFolder *pXFolder = NULL;
	HTREEITEM hItem = m_folderTree.GetSelectedItem();
	pXFolder = (CXFolder *)m_folderTree.GetItemData(hItem);
	m_strSelPath = pXFolder->GetFolderPath(TRUE);

	OnOK();
}

void CDlgXFolderMngr::CreateControls()
{
	CFont *pFont = GetFont();
	CreateTreeCtrl(m_folderTree, CRect(14, 35, 626, 352), XIDC_TREE_FOLDER, this);

	CreateButton(m_btnOK, CXLanguageResourceBase::g_sLangTxt_Open/*_T("打开")*/, CRect(463, 360, 533, 381), IDOK, this);
	CreateButton(m_btnCancel, CXLanguageResourceBase::g_sLangTxt_Cancel/*_T("取消")*/, CRect(552, 360, 622, 381), IDCANCEL, this);

	m_folderTree.SetFont(pFont);
	m_btnOK.SetFont(pFont);
	m_btnCancel.SetFont(pFont);

	m_folderTree.ModifyStyle(0, TVS_EDITLABELS);

}


BOOL CDlgXFolderMngr::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	xfile_LoadFileMngrBmp(&m_oImageList);

	LockWindowUpdate();
	CreateControls();

	EnableToolTips(TRUE);
	if( !m_ToolTip.Create(this,TTS_ALWAYSTIP) )
	{
		TRACE0("Unable to create the ToolTip");
	}
	else
	{
		m_ToolTip.Activate(TRUE);
		m_ToolTip.SetMaxTipWidth(200);
	}

	m_folderTree.SetFrameWnd(this);

	if (m_oImageList.ValidImageList())
	{
		m_folderTree.SetImageList(&m_oImageList,TVSIL_NORMAL);
	}

	m_folderTree.SetExBaseItemData(FALSE);
	m_folderTree.ShowXFileMngr(m_pFileMngrBase);
	m_folderTree.SelectItem(m_folderTree.GetRootItem());

	m_btnOK.EnableWindow(TRUE);

	CString strWindowText;
	m_btnOK.SetWindowText(CXLanguageResourceBase::g_sLangTxt_Open/*_T("打开")*/);
	strWindowText.Format(CXLanguageResourceBase::g_sLangTxt_ManagOpen/*_T("%s 管理---打开")*/,_T(""));
	SetWindowText(strWindowText);
	
	MoveWindow(CRect( 0, 0, 650, 420), TRUE);
	CenterWindow();
	UnlockWindowUpdate();

	return TRUE;
}

BOOL CDlgXFolderMngr::PreTranslateMessage(MSG* pMsg)
{
	m_ToolTip.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}

CString CDlgXFolderMngr::GetFileName()
{
	return m_strSelPath;
}
