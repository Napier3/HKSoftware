// D:\WorkPM\Source\Protocol\PpDev\PpTemplateFileMngr\XDlgFileMngr.cpp : 实现文件
//

#include "stdafx.h"
#include "XDlgFileMngr.h"

char CXDlgFileMngr::g_pszFileName[MAX_PATH];


CFrameWndEx* UI_GetFrameWndEx(CWnd* pWnd)
{
	CWnd* pFrameWndEx = pWnd->GetParent();
	ASSERT(pFrameWndEx != NULL);

	while( !pFrameWndEx->IsKindOf(RUNTIME_CLASS(CFrameWndEx)))
	{
		pFrameWndEx = pFrameWndEx->GetParent();
	}

	return (CFrameWndEx*)pFrameWndEx;
}

UINT UI_GetImgeListID()
{
	return 349;
}

// CXDlgFileMngr 对话框

IMPLEMENT_DYNAMIC(CXDlgFileMngr, CDialog)

CXDlgFileMngr::CXDlgFileMngr(UINT nTemplateID,const CString& strFilePostFix,const CString& strPostFixDes,CXFileMngr* pFileMngrBase,UINT nMode,CWnd* pParent /*=NULL*/)
: CDynDialogEx(pParent)
{
	m_nMode = nMode;
	m_strFilePostfix = strFilePostFix;
	m_strPostFixDes = strPostFixDes;
	m_pFileSelect = NULL;
	m_strFileName = _T("");
	m_strStaticPath = _T("");
	m_pFileMngrBase = pFileMngrBase;
	m_bIsSaveAs = FALSE;
}

CXDlgFileMngr::~CXDlgFileMngr()
{
}

void CXDlgFileMngr::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	if (!::IsWindow(m_folderTree.m_hWnd))
	{
		return;
	}
	//DDX_Control(pDX, XIDC_TREE_FOLDER, m_folderTree);
	//DDX_Control(pDX, XIDC_LIST_FILE, m_fileListCtrl);
	//DDX_Control(pDX, XIDC_COMBO_FILE_TYPE, m_comboBoxType);
	DDX_Text(pDX, XIDC_EDIT_FILE_NAME, m_strFileName);
	DDX_Text(pDX, XIDC_STATIC_PATH, m_strStaticPath);
}


BEGIN_MESSAGE_MAP(CXDlgFileMngr, CDialog)
	ON_BN_CLICKED(IDOK, &CXDlgFileMngr::OnBnClickedOk)
	//ON_BN_CLICKED(IDC_BUTTON_OPEN_OTHER_FILE,&CXDlgFileMngr::OnBnClickedOpenOtherFile)
	ON_NOTIFY(NM_DBLCLK, XIDC_LIST_FILE, &CXDlgFileMngr::OnNMDblclkListFile)
	ON_NOTIFY(NM_CLICK, XIDC_LIST_FILE, &CXDlgFileMngr::OnNMClickListFile)
	ON_EN_CHANGE(XIDC_EDIT_FILE_NAME, &CXDlgFileMngr::OnEnChangeEditFileName)
	ON_MESSAGE(WM_CHANGE_STATIC_PATH,&CXDlgFileMngr::OnChangeStaticPath)
	ON_NOTIFY(LVN_ITEMCHANGED, XIDC_LIST_FILE, &CXDlgFileMngr::OnLvnItemchangedListFile)

END_MESSAGE_MAP()


int CXDlgFileMngr::DoModal()   
{   
	CRect rect(0,0,422,238);   
	SetDlgRect(rect);
	//	AddDlgControl(_T("LISTBOX"), _T("ListboxText"), STYLE_LISTBOX, EXSTYLE_LISTBOX, &rect, &m_lstBox, IDC_LIST1);   
	int iRet = CDynDialogEx::DoModal();   

	return iRet;   
}   

// CXDlgFileMngr 消息处理程序
void CXDlgFileMngr::OnCancel()
{
	CWnd* pParentWnd = GetParent();
	g_pszFileName[0] = 0;
	LRESULT nRet = pParentWnd->SendMessage(WM_PARENT_OPEN_XML_FILE, (WPARAM)m_pFileSelect, (LPARAM)g_pszFileName);
	CDialog::OnCancel();
}

void CXDlgFileMngr::OnBnClickedOk()
{
	UpdateData(TRUE);

	if(m_nMode == SAVE_FILE_MODE)
	{
		if( ! SaveXmlFile() )
		{
			return;
		}
	}
	else if(m_nMode == OPEN_FILE_MODE)
	{
		if( ! OpenXmlFile())
		{
			return ;
		}
	}

	OnOK();
}

void CXDlgFileMngr::OnBnClickedOpenOtherFile()
{
	CString szFilter;
	szFilter.Format(_T("%s(*%s)|*%s||"),m_strPostFixDes,m_strFilePostfix,m_strFilePostfix);
	CFileDialog fileDlg(TRUE,m_strFilePostfix,0,4|2,szFilter);
	CString strMngrPath = m_pFileMngrBase->GetPath();
	fileDlg.m_ofn.lpstrInitialDir = strMngrPath;  

	if(fileDlg.DoModal() == IDOK)
	{
		m_strFileName = fileDlg.GetFileName();
		CString strFilePath = fileDlg.GetPathName();
		CString strTemp = strFilePath;
		strFilePath = strTemp.Left(strFilePath.Find(m_strFileName)-1);

		CString strTemp1 = strFilePath;
		CString strTemp2 = strMngrPath;

		if(strTemp1.MakeLower() != strTemp2.MakeLower())
		{
			CString strInfo;
			strInfo.Format(_T("请在 %s 下选择%s"),strMngrPath,m_strPostFixDes);
			MessageBox(strInfo,_T("提示信息"));
			return ;
		}
		else
		{
			if( m_pFileMngrBase->FindByLowerName(m_strFileName) == NULL)
			{
				m_pFileMngrBase->AddFile(NULL,m_strFileName/*,m_strPostFixDes*/,FALSE);
				m_pFileMngrBase->SaveXMLFile();
				m_fileListCtrl.RefreshFileViewList();
			}
			else
			{
				CString strInfo;
				strInfo.Format(_T("文件 %s 已经存在"),m_strFileName);
				MessageBox(strInfo,_T("提示信息"));
				return ;
			}
		}
	}
}

void CXDlgFileMngr::CreateControls()
{
	CreateTreeCtrl(m_folderTree, CRect(14, 35, 189, 260), XIDC_TREE_FOLDER, this);
	CreateListCtrl(m_fileListCtrl, CRect(198, 35, 626, 260), XIDC_LIST_FILE, this);

	CreateStatic(m_stcStaticPathTitle, _T("选择路径"), CRect(14, 13, 55, 27), XIDC_STATIC_PATH_TITLE, this);
	CreateStatic(m_stcStaticPath, _T(""), CRect(74, 13, 600, 27), XIDC_STATIC_PATH, this);

	CreateComboBox_DropList(m_comboBoxType, CRect(87, 304, 610, 326), XIDC_COMBO_FILE_TYPE, this);

	CreateStatic(m_stcFileNameTitle, _T("名称"), CRect(33,276, 70, 290), XIDC_FILE_TYPE_TITLE, this);
	CreateStatic(m_stcFileTypeTitle, _T("类型"), CRect(33,307, 70, 321), XIDC_EDIT_FILE_NAME_TITLE, this);

	CreateEdit(m_editFileName, CRect(87, 274, 610, 294), XIDC_EDIT_FILE_NAME, this);	

	CreateButton(m_btnOK, _T("打开"), CRect(463, 354, 533, 375), IDOK, this);
	CreateButton(m_btnCancel, _T("取消"), CRect(552, 354, 622, 375), IDCANCEL, this);

	CFont *pFont = GetFont();
	m_folderTree.SetFont(pFont);
	m_fileListCtrl.SetFont(pFont);
	m_stcStaticPathTitle.SetFont(pFont);
	m_stcStaticPath.SetFont(pFont);
	m_comboBoxType.SetFont(pFont);
	m_stcFileNameTitle.SetFont(pFont);
	m_stcFileTypeTitle.SetFont(pFont);
	m_editFileName.SetFont(pFont);
	m_btnOK.SetFont(pFont);
	m_btnCancel.SetFont(pFont);
}


BOOL CXDlgFileMngr::OnInitDialog()
{
	CDialog::OnInitDialog();

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

	m_ImgetList.Create(UI_GetImgeListID(), 16, 0, RGB(255, 0, 255));
	m_folderTree.SetFileMngr(m_pFileMngrBase);
	m_folderTree.SetImageList(&m_ImgetList,TVSIL_NORMAL);
	m_fileListCtrl.SetImageList(&m_ImgetList,LVSIL_SMALL);
	m_fileListCtrl.SetFileMngrBase(m_pFileMngrBase);
	m_folderTree.InitShowFolderViewTree();

	m_folderTree.SetRelatedListCtrl(&m_fileListCtrl);	
	m_fileListCtrl.SetRelatedFolderTreeCtrl(&m_folderTree);
	m_folderTree.SelectItem(m_folderTree.GetRootItem());
	InitTypeComboBox();
	m_fileListCtrl.RefreshFileViewList();

	m_btnOK.EnableWindow(FALSE);

	CString strWindowText;
	if(m_nMode == SAVE_FILE_MODE)
	{
		m_btnOK.SetWindowText(_T("保存"));
		strWindowText.Format(_T("%s 管理---保存"),m_strPostFixDes);
		SetWindowText(strWindowText);
	}
	else if(m_nMode == OPEN_FILE_MODE)
	{
		m_btnOK.SetWindowText(_T("打开"));
		strWindowText.Format(_T("%s 管理---打开"),m_strPostFixDes);
		SetWindowText(strWindowText);
		m_editFileName.EnableWindow(FALSE);
	}

// 	CWnd* pWnd = GetDlgItem(IDC_BUTTON_OPEN_OTHER_FILE);
// 	if(pWnd != NULL)
// 	{
// 		pWnd->ShowWindow(SW_HIDE);
// 	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CXDlgFileMngr::InitTypeComboBox()
{
	m_comboBoxType.ResetContent();
	CString strFileType;
	strFileType.Format(_T("%s(*%s)"),m_strPostFixDes,m_strFilePostfix);
	m_comboBoxType.AddString(strFileType);
	m_comboBoxType.SetCurSel(0);
	m_fileListCtrl.SetFilter(m_strFilePostfix);
}	

void CXDlgFileMngr::OnNMDblclkListFile(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	long nCount = m_fileListCtrl.GetSelectedCount();
	if(nCount == 1)
	{
		int nItem = -1;
		nItem = m_fileListCtrl.GetNextItem(nItem,LVNI_SELECTED);
		ASSERT(nItem != -1);
		CExBaseObject* pObj = (CExBaseObject*)m_fileListCtrl.GetItemData(nItem);
		if( IsFolder(pObj->GetClassID()) )
		{
			m_folderTree.SelectItem((HTREEITEM)pObj->m_dwItemData);
			SendMessage(WM_CHANGE_STATIC_PATH,0,0);
		}
		if( IsFile(pObj->GetClassID()) )
		{
			OnNMClickListFile(pNMHDR,pResult);
			OnBnClickedOk();
		}
	}

	*pResult = 0;
}

void CXDlgFileMngr::OnNMClickListFile(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	long nCount = m_fileListCtrl.GetSelectedCount();

	if(nCount == 1)
	{
		int nItem = -1;
		nItem = m_fileListCtrl.GetNextItem(nItem,LVNI_SELECTED);
		ASSERT(nItem != -1);
		CExBaseObject* pObj = (CExBaseObject*)m_fileListCtrl.GetItemData(nItem);
		if( IsFile(pObj->GetClassID()) )
		{
			CXFile* pFile = (CXFile*)pObj;
			CXFolder* pFolderSelect = (CXFolder*)m_folderTree.GetItemData(m_folderTree.GetSelectedItem());
			m_strFileName = pObj->m_strName;

			if(m_nMode == SAVE_FILE_MODE)
			{
				//去除文件后缀
				nCount = m_strFileName.GetLength();
				int nFind = m_strFileName.Find(m_strFilePostfix);
				if(nFind != -1)
				{
					m_strFileName = m_strFileName.Left(nFind-1);
				}
			}

			m_btnOK.EnableWindow(TRUE);
			m_pFileSelect = pFile;
			UpdateData(FALSE);
			return ;
		}

		m_pFileSelect = NULL;
		m_strFileName = _T("");
		m_btnOK.EnableWindow(FALSE);
		UpdateData(FALSE);
	}

	*pResult = 0;
}


void CXDlgFileMngr::OnLvnItemchangedListFile(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	if ( ((pNMLV->uNewState & LVIS_FOCUSED) == LVIS_FOCUSED) 
		&& ((pNMLV->uNewState & LVIS_SELECTED) == LVIS_SELECTED) )
	{
		OnNMClickListFile(pNMHDR, pResult);
	}
	else
	{
		
	}

	*pResult = 0;
}


BOOL CXDlgFileMngr::PreTranslateMessage(MSG* pMsg)
{
	m_ToolTip.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CXDlgFileMngr::SaveXmlFile()
{
	CString strInfo;
	CString strFileName= m_strFileName + m_strFilePostfix;
	CXFolder* pFolderSelect = (CXFolder*)m_folderTree.GetItemData(m_folderTree.GetSelectedItem());

	CXFile* pFileSelect = (CXFile*)pFolderSelect->FindByLowerName(strFileName);
	BOOL bFlag = (pFileSelect != NULL) ? (TRUE) : (FALSE);		//标识文件是否已经存在
	CXFile* pFile = NULL;

	CWnd* pParentWnd = GetParent();
	ASSERT(pParentWnd != NULL);

	if(bFlag)
	{
		strInfo.Format(_T("%s 文件已经存在，是否覆盖?"),strFileName);
		if( MessageBox(strInfo,_T("文件重名"),MB_ICONQUESTION |MB_OKCANCEL ) == IDOK )
		{	
			if(!pFileSelect->m_bIsOpen)
			{
				pFile = pFolderSelect->AddFile(NULL,strFileName/*,m_strPostFixDes*/,TRUE);
				pFile->m_bIsOpen = TRUE;

				AfxGetApp()->PostThreadMessage(WM_THREAD_DLG_FILE_MNGR,0,(LPARAM)this);
				if( !m_bIsSaveAs)
				{
					pParentWnd->SendMessage(WM_PARENT_SAVE_XML_FILE,0,(LPARAM)(char*)(_bstr_t)this->GetFileName());
				}

				return TRUE;
			}
			else
			{
				strInfo.Format(_T("%s 已经被打开，文件覆盖失败"),pFileSelect->m_strName);
				MessageBox(strInfo,_T("文件覆盖失败"),MB_OK);
			}
		}

		return FALSE;
	}
	else
	{
		pFile = pFolderSelect->AddFile(NULL,strFileName/*,m_strPostFixDes*/,FALSE);
		pFile->m_bIsOpen = TRUE;
		m_pFileMngrBase->SaveXMLFile();

		AfxGetApp()->PostThreadMessage(WM_THREAD_DLG_FILE_MNGR,0,(LPARAM)this);
		pParentWnd->SendMessage(WM_PARENT_SAVE_XML_FILE,0,(LPARAM)(char*)(_bstr_t)this->GetFileName());

		return TRUE;
	}
}

BOOL CXDlgFileMngr::OpenXmlFile()
{
	CString strFileName = GetFileName();
	CWnd* pParentWnd = GetParent();
	m_pFileSelect->m_bIsOpen = TRUE;
	CString_to_char(strFileName, g_pszFileName);
	LRESULT nRet = pParentWnd->SendMessage(WM_PARENT_OPEN_XML_FILE, (WPARAM)m_pFileSelect, (LPARAM)g_pszFileName);

	return (nRet == 0);
}

void CXDlgFileMngr::OnEnChangeEditFileName()
{
	m_btnOK.EnableWindow(FALSE);
	UpdateData(TRUE);

	CString strRight = m_strFileName.Right(1);
	if(strRight == _T("\\") || strRight == _T("/") ||strRight==_T(":") ||strRight == _T("*") || strRight == _T("?")
		|| strRight == _T("<") || strRight == _T(">") || strRight == _T("|") )
	{
		long nStrLength = m_strFileName.GetLength();
		m_strFileName.Delete(nStrLength-1);
		UpdateData(FALSE);
		m_editFileName.SetSel(nStrLength,nStrLength,TRUE);
		m_editFileName.SetFocus();
	}

	if(m_strFileName == _T(""))
	{
		m_btnOK.EnableWindow(FALSE);
	}
	else
	{
		m_btnOK.EnableWindow(TRUE);
	}
}

CString CXDlgFileMngr::GetFileName()
{
	if(m_nMode == OPEN_FILE_MODE)
	{
		return m_strStaticPath + g_strSlash + m_strFileName;	
	}
	else
	{
		CString strPath = m_strStaticPath;

		if (strPath.Right(1) != _T("\\"))
		{
			strPath += _T("\\");
		}

		strPath.AppendFormat(_T("%s.%s"), m_strFileName, m_strFilePostfix);
		return strPath;
	}
}

LRESULT CXDlgFileMngr::OnChangeStaticPath(WPARAM wParam,LPARAM lParam)
{
	CXFolder* pFolder = (CXFolder*)m_folderTree.GetItemData(m_folderTree.GetSelectedItem());
	m_strStaticPath = pFolder->GetPath();
	UpdateData(FALSE);

	return 0;
}



CString DlgFile_GetOpenFile(const CString &strFileType, const CString &strFileDes, CWnd *pParent, CXFileMngr *pFileMngr)
{
	CString strFileName;

	CXDlgFileMngr dlg(0,strFileType,strFileDes,pFileMngr,OPEN_FILE_MODE,pParent);

	if(dlg.DoModal() == IDOK)
	{
		strFileName = dlg.GetFileName();
	}

	return strFileName;
}
