// D:\WorkPM\Source\Protocol\PpDev\PpTemplateFileMngr\DlgXFileMngr.cpp : 实现文件
//

#include "stdafx.h"
#include "DlgXFileMngr.h"
#include "..\XLanguage\XLanguageMngr.h"

#ifdef _Use_YUN_Client_
	#include "YunFileApi\XYunFileApi.h"
#endif

char CDlgXFileMngr::g_pszFileName[MAX_PATH];


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

// CDlgXFileMngr 对话框

IMPLEMENT_DYNAMIC(CDlgXFileMngr, CDialog)

CDlgXFileMngr::CDlgXFileMngr(UINT nTemplateID,const CString& strFilePostFix,const CString& strPostFixDes,CXFileMngr* pFileMngrBase,UINT nMode,CWnd* pParent /*=NULL*/)
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

CDlgXFileMngr::~CDlgXFileMngr()
{
}

void CDlgXFileMngr::DoDataExchange(CDataExchange* pDX)
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


BEGIN_MESSAGE_MAP(CDlgXFileMngr, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgXFileMngr::OnBnClickedOk)
	ON_BN_CLICKED(XIDC_EDIT_FILE_NAME_GEN, &CDlgXFileMngr::OnBnClickedFileNameGen)
	ON_BN_CLICKED(XIDC_BTN_GO, &CDlgXFileMngr::OnBnClickedGO)
	ON_BN_CLICKED(XIDC_BTN_YUN_DOWNLOAD, &CDlgXFileMngr::OnBnClickedDownLoad)
	//ON_BN_CLICKED(IDC_BUTTON_OPEN_OTHER_FILE,&CDlgXFileMngr::OnBnClickedOpenOtherFile)
	ON_NOTIFY(NM_DBLCLK, XIDC_LIST_FILE, &CDlgXFileMngr::OnNMDblclkListFile)
	ON_NOTIFY(NM_CLICK, XIDC_LIST_FILE, &CDlgXFileMngr::OnNMClickListFile)
	ON_EN_CHANGE(XIDC_EDIT_FILE_NAME, &CDlgXFileMngr::OnEnChangeEditFileName)
	ON_MESSAGE(WM_CHANGE_STATIC_XPATH,&CDlgXFileMngr::OnChangeStaticPath)
	ON_NOTIFY(LVN_ITEMCHANGED, XIDC_LIST_FILE, &CDlgXFileMngr::OnLvnItemchangedListFile)
	ON_CBN_SELCHANGE(XIDC_COMBO_HISTORY, &CDlgXFileMngr::OnCbnSelchangeHistory)
	ON_MESSAGE(WM_XFILEMNGR_OPEN_XFILE,&CDlgXFileMngr::OnCFileMngrOpenFile)
	ON_MESSAGE(WM_THREAD_XFILE_MNGR,&CDlgXFileMngr::OnCFileMngrSelFile)
#ifdef _Use_YUN_Client_
	ON_MESSAGE(YUN_OPER_RSLT_MSG,&CDlgXFileMngr::OnYunOperFinished)
#endif
END_MESSAGE_MAP()


int CDlgXFileMngr::DoModal()   
{   
// 	CRect rect(0,0,422,238);   
// 	SetDlgRect(rect);
	//	AddDlgControl(_T("LISTBOX"), _T("ListboxText"), STYLE_LISTBOX, EXSTYLE_LISTBOX, &rect, &m_lstBox, IDC_LIST1);   
	int iRet = CDynDialogEx::DoModal();   

	return iRet;   
}   

// CDlgXFileMngr 消息处理程序
void CDlgXFileMngr::OnCancel()
{
	CWnd* pParentWnd = GetParent();
	g_pszFileName[0] = 0;
	LRESULT nRet = pParentWnd->SendMessage(WM_PARENT_OPEN_XML_FILE, (WPARAM)m_pFileSelect, (LPARAM)g_pszFileName);
	CDialog::OnCancel();
}
void CDlgXFileMngr::OnBnClickedFileNameGen()
{
	CDlgXFileNameGen dlg(m_strFileNameGenConfigPath, this);

	if (dlg.DoModal() == IDOK)
	{
		m_strFileName = dlg.m_strFileName;
		m_editFileName.SetWindowText(m_strFileName);
	}
}

void CDlgXFileMngr::OnBnClickedOk()
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

	SaveHistrory();

	OnOK();
}

void CDlgXFileMngr::SaveHistrory()
{
	if (m_pFileSelect != NULL && m_strHistoryMngrFile.GetLength() > 3)
	{
		CString strFile = m_pFileSelect->GetTotalFileName();
		strFile.MakeLower();
		CString strTmplPath;
		strTmplPath = _P_GetTemplatePath();
		strTmplPath.MakeLower();
		strFile.Replace(strTmplPath, _T(""));
		CFilterText *pNew = m_oFilterTextMngr.AddText(strFile);
		m_oFilterTextMngr.BringToHead(pNew);

		while (m_oFilterTextMngr.GetCount() > 10)
		{
			m_oFilterTextMngr.DeleteTail();
		}

		m_oFilterTextMngr.SaveXmlFile();
	}
}

void CDlgXFileMngr::OnBnClickedGO()
{
	UpdateData(TRUE);

	CString strFolder = m_strStaticPath;
	strFolder.MakeLower();

	if (strFolder.Right(1) != _P_FOLDER_PATH_SEPARATOR_)
	{
		strFolder += _P_FOLDER_PATH_SEPARATOR_;
	}

	CXFolder *pFolder = m_pFileMngrBase->SelectFolder(strFolder, TRUE);

	if (pFolder != NULL)
	{
		m_folderTree.SelectItem((HTREEITEM)pFolder->m_dwItemData);
		m_pFileSelect = NULL;
		m_strFileName = _T("");
		UpdateData(FALSE);
		m_btnOK.EnableWindow(FALSE);
	}
}

void CDlgXFileMngr::OnBnClickedDownLoad()
{
	if (m_pFileSelect == NULL)
	{
		return;
	}

#ifdef _Use_YUN_Client_
	Yun_DownLoad(m_pFileSelect, TRUE);
#endif
}

void CDlgXFileMngr::OnBnClickedOpenOtherFile()
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
			strInfo.Format(g_sLangTxt_PleaseChoose/*_T("请在 %s 下选择%s")*/,strMngrPath,m_strPostFixDes);
			MessageBox(strInfo,g_sLangTxt_PromptMessage/*_T("提示信息")*/);
			return ;
		}
		else
		{
			if( m_pFileMngrBase->FindByLowerName(m_strFileName) == NULL)
			{
				m_pFileMngrBase->AddFile(m_strFileName/*,m_strPostFixDes*/,FALSE);
// 				m_pFileMngrBase->SaveXMLFile();
				m_fileListCtrl.RefreshFileViewList();
			}
			else
			{
				CString strInfo;
				strInfo.Format(g_sLangTxt_FileAlrExi/*_T("文件 %s 已经存在")*/,m_strFileName);
				MessageBox(strInfo,g_sLangTxt_PromptMessage/*_T("提示信息")*/);
				return ;
			}
		}
	}
}

void CDlgXFileMngr::CreateControls()
{
	CFont *pFont = GetFont();
	CreateTreeCtrl(m_folderTree, CRect(14, 35, 189, 260), XIDC_TREE_FOLDER, this);
	CreateListCtrl(m_fileListCtrl, CRect(198, 35, 626, 260), XIDC_LIST_FILE, this);

	CreateStatic(m_stcStaticPathTitle, g_sLangTxt_Path/*_T("路径")*/, CRect(14, 13, 40, 27), XIDC_STATIC_PATH_TITLE, this);
	CreateEdit(m_editPath,                  CRect(50, 10, 560, 30),   XIDC_STATIC_PATH, this);

	if (m_nMode == SAVE_FILE_MODE)
	{
		if (m_strFileNameGenConfigPath.GetLength() > 5)
		{
			CreateEdit(m_editFileName,              CRect(50, 274, 556, 294), XIDC_EDIT_FILE_NAME, this);	
			CreateButton(m_btnFileNameGen, g_sLangTxt_StandardFileName/*_T("标准文件名")*/, CRect(560, 274, 626, 294), XIDC_EDIT_FILE_NAME_GEN, this);
			m_btnFileNameGen.SetFont(pFont);
		}
		else
		{
			CreateEdit(m_editFileName,              CRect(50, 274, 626, 294), XIDC_EDIT_FILE_NAME, this);	
		}
	}
	else
	{
		CreateEdit(m_editFileName,              CRect(50, 274, 565, 294), XIDC_EDIT_FILE_NAME, this);
		CreateButton(m_btnYunDownLoad, g_sLangTxt_DownLoad/*_T("下载")*/, CRect(570, 274, 626, 294), XIDC_BTN_YUN_DOWNLOAD, this);
		m_btnYunDownLoad.SetFont(pFont);
	}
	
	CreateComboBox_DropList(m_comboBoxType, CRect(50, 304, 626, 326), XIDC_COMBO_FILE_TYPE, this);
	CreateComboBox_DropList(m_cmbHistory,   CRect(50, 334, 626, 358), XIDC_COMBO_HISTORY, this);

	CreateStatic(m_stcFileNameTitle, g_sLangTxt_Name/*_T("名称")*/, CRect(14,276, 50, 290), XIDC_FILE_TYPE_TITLE, this);
	CreateStatic(m_stcFileTypeTitle, g_sLangTxt_Type/*_T("类型")*/, CRect(14,307, 50, 321), XIDC_EDIT_FILE_NAME_TITLE, this);
	CreateStatic(m_stcHistoryTitle, g_sLangTxt_History/*_T("历史")*/,  CRect(14,338, 50, 352), XIDC_EDIT_HISTORY_TITLE, this);

	CreateButton(m_btnOK, g_sLangTxt_Open/*_T("打开")*/, CRect(463, 360, 533, 381), IDOK, this);
	CreateButton(m_btnCancel, g_sLangTxt_Cancel/*_T("取消")*/, CRect(552, 360, 622, 381), IDCANCEL, this);
	CreateButton(m_btnGO, g_sLangTxt_Location/*_T("定位")*/, CRect(570, 10, 626, 30), XIDC_BTN_GO, this);

	m_folderTree.SetFont(pFont);
	m_fileListCtrl.SetFont(pFont);
	m_stcStaticPathTitle.SetFont(pFont);
	m_editPath.SetFont(pFont);
	m_comboBoxType.SetFont(pFont);
	m_stcFileNameTitle.SetFont(pFont);
	m_stcFileTypeTitle.SetFont(pFont);
	m_editFileName.SetFont(pFont);
	m_btnOK.SetFont(pFont);
	m_btnCancel.SetFont(pFont);
	m_stcHistoryTitle.SetFont(pFont);
	m_cmbHistory.SetFont(pFont);
	m_btnGO.SetFont(pFont);

	m_folderTree.ModifyStyle(0, TVS_EDITLABELS);

}


BOOL CDlgXFileMngr::OnInitDialog()
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

	m_fileListCtrl.SetFrameWnd(this);
	m_folderTree.SetFrameWnd(this);

//	m_ImgetList.Create(UI_GetImgeListID(), 16, 0, RGB(255, 0, 255));

	if (m_oImageList.ValidImageList())
	{
		m_folderTree.SetImageList(&m_oImageList,TVSIL_NORMAL);
		m_fileListCtrl.SetImageList(&m_oImageList,LVSIL_SMALL);
	}

	m_fileListCtrl.SetXFileMngr(m_pFileMngrBase);

	m_fileListCtrl.SetRelatedFolderTreeCtrl(&m_folderTree);
	m_folderTree.AttacthXFileListView(&m_fileListCtrl);	

	m_folderTree.ShowXFileMngr(m_pFileMngrBase);
	m_folderTree.SelectItem(m_folderTree.GetRootItem());
	m_fileListCtrl.RefreshFileViewList();

	InitTypeComboBox();

	m_btnOK.EnableWindow(FALSE);

	CString strWindowText;
	if(m_nMode == SAVE_FILE_MODE)
	{
		m_btnOK.SetWindowText(g_sLangTxt_Save/*_T("保存")*/);
		strWindowText.Format(g_sLangTxt_ManagSave/*_T("%s 管理---保存")*/,m_strPostFixDes);
		SetWindowText(strWindowText);
	}
	else if(m_nMode == OPEN_FILE_MODE)
	{
		m_btnOK.SetWindowText(g_sLangTxt_Open/*_T("打开")*/);
		strWindowText.Format(g_sLangTxt_ManagOpen/*_T("%s 管理---打开")*/,m_strPostFixDes);
		SetWindowText(strWindowText);
		m_editFileName.EnableWindow(FALSE);
	}

	InitHistoryCmboBox();
	CFilterText *pFilter = (CFilterText*)m_oFilterTextMngr.GetHead();

	if (pFilter != NULL)
	{
		SelectFile(pFilter);
	}

// 	CWnd* pWnd = GetDlgItem(IDC_BUTTON_OPEN_OTHER_FILE);
// 	if(pWnd != NULL)
// 	{
// 		pWnd->ShowWindow(SW_HIDE);
// 	}

	MoveWindow(CRect( 0, 0, 650, 420), TRUE);
	CenterWindow();
	UnlockWindowUpdate();

	if (m_nMode == OPEN_FILE_MODE)
	{
		m_btnYunDownLoad.EnableWindow(FALSE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgXFileMngr::InitHistoryCmboBox()
{
	POS pos = m_oFilterTextMngr.GetHeadPosition();
	CFilterText *pFilter = NULL;
	CString strText;

	while (pos != NULL)
	{
		pFilter = (CFilterText *)m_oFilterTextMngr.GetNext(pos);
		strText = pFilter->m_strName;
		strText.MakeLower();
		strText.Replace(m_strTrim, _T(""));
		long nIndex = m_cmbHistory.AddString(strText);
		m_cmbHistory.SetItemDataPtr(nIndex, pFilter);
	}
	//m_oFilterTextMngr.InsertChildreComboBox(&m_cmbHistory);
	
}

void CDlgXFileMngr::SelectFile(CFilterText *pFilter)
{
	CString strFile = pFilter->m_strName;
	strFile.MakeLower();
	CXFile *pFileBase = m_pFileMngrBase->SelectFile(strFile, TRUE);

	if (pFileBase == NULL)
	{
		strFile = _P_GetTemplatePath();
		strFile += pFilter->m_strName;
		strFile.MakeLower();
		pFileBase = m_pFileMngrBase->SelectFile(strFile, TRUE);
	}

	if (pFileBase == NULL)
	{
		return;
	}

	CXFolder *pFolder = (CXFolder*)pFileBase->GetParent();
	m_folderTree.SelectItem((HTREEITEM)pFolder->m_dwItemData);
	ShowSelectFile(pFileBase);
	xfile_PostXFileObjSelChangeMsg(this, WM_THREAD_XFILE_MNGR, pFileBase);

}

void CDlgXFileMngr::InitTypeComboBox()
{
	m_comboBoxType.ResetContent();
	CString strFileType;
	strFileType.Format(_T("%s(*%s)"),m_strPostFixDes,m_strFilePostfix);
	m_comboBoxType.AddString(strFileType);
	m_comboBoxType.SetCurSel(0);
	m_fileListCtrl.SetFilter(m_strFilePostfix);
}	

void CDlgXFileMngr::OnNMDblclkListFile(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	long nCount = m_fileListCtrl.GetSelectedCount();
	if(nCount == 1)
	{
		int nItem = -1;
		nItem = m_fileListCtrl.GetNextItem(nItem,LVNI_SELECTED);
		ASSERT(nItem != -1);
		CExBaseObject* pObj = (CExBaseObject*)m_fileListCtrl.GetItemData(nItem);
		if( xfile_IsFolder(pObj->GetClassID()) )
		{
			m_folderTree.SelectItem((HTREEITEM)pObj->m_dwItemData);
			SendMessage(WM_CHANGE_STATIC_XPATH,0,0);
		}
		if( xfile_IsFile(pObj->GetClassID()) )
		{
			OnNMClickListFile(pNMHDR,pResult);
			OnBnClickedOk();
		}
	}

	*pResult = 0;
}



LRESULT CDlgXFileMngr::OnCFileMngrOpenFile(WPARAM wParam,LPARAM lParam)
{
	CXFile *pXFile = (CXFile*)lParam;

	if (pXFile->GetClassID() != CLASSID_XFILE)
	{
		return 0;
	}

	OnBnClickedOk();

	return 0;
}

LRESULT CDlgXFileMngr::OnYunOperFinished(WPARAM wParam,LPARAM lParam)
{
	if (wParam == 0 || lParam == 0)
	{
		MessageBox(g_sLangTxt_YunDownFileFaild);//_T("从云端下载文件失败!"));
		return 0;
	}

	OpenXmlFile_msg();  //打开文件
	SaveHistrory();   //保存历史记录
	OnOK();   //关闭对话框

	return 0;
}

LRESULT CDlgXFileMngr::OnCFileMngrSelFile(WPARAM wParam,LPARAM lParam)
{
	CExBaseObject *pSel = (CExBaseObject*)lParam;
	ASSERT(pSel != NULL);

	if (pSel == NULL)
	{
		return 0;
	}

	CXFolder *pFolder = NULL;

	if (pSel->GetClassID() == CLASSID_XFILE)
	{
		CXFile *pXFile = (CXFile*)lParam;
		pFolder = (CXFolder *)pXFile->GetParent();
		ShowSelectFile(pXFile);
	}
	else
	{
		pFolder = (CXFolder *)lParam;
		m_pFileSelect = NULL;
		m_strFileName = _T("");
		m_btnOK.EnableWindow(FALSE);
	}

	m_strStaticPath = pFolder->GetFolderPath();
	UpdateData(FALSE);

	return 0;
}

void CDlgXFileMngr::OnNMClickListFile(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	long nCount = m_fileListCtrl.GetSelectedCount();

	if(nCount == 1)
	{
		int nItem = -1;
		nItem = m_fileListCtrl.GetNextItem(nItem,LVNI_SELECTED);
		ASSERT(nItem != -1);
		CExBaseObject* pObj = (CExBaseObject*)m_fileListCtrl.GetItemData(nItem);
		if( xfile_IsFile(pObj->GetClassID()) )
		{
			CXFile* pFile = (CXFile*)pObj;
			CXFolder* pFolderSelect = (CXFolder*)m_folderTree.GetItemData(m_folderTree.GetSelectedItem());
// 			m_strFileName = pObj->m_strName;
// 
// 			if(m_nMode == SAVE_FILE_MODE)
// 			{
// 				//去除文件后缀
// 				nCount = m_strFileName.GetLength();
// 				int nFind = m_strFileName.Find(m_strFilePostfix);
// 				if(nFind != -1)
// 				{
// 					m_strFileName = m_strFileName.Left(nFind-1);
// 				}
// 			}
// 
// 			m_btnOK.EnableWindow(TRUE);
// 			m_pFileSelect = pFile;
// 			UpdateData(FALSE);
			ShowSelectFile(pFile);
			return ;
		}

		m_pFileSelect = NULL;
		m_strFileName = _T("");
		m_btnOK.EnableWindow(FALSE);
		UpdateData(FALSE);
	}

	*pResult = 0;
}

void CDlgXFileMngr::ShowSelectFile(CXFile *pFile)
{
// 	CXFolder* pFolderSelect = (CXFolder*)m_folderTree.GetItemData(m_folderTree.GetSelectedItem());
	m_strFileName = pFile->m_strName;
	long nCount = 0;

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

	m_editFileName.SetWindowText(m_strFileName);
	m_btnOK.EnableWindow(TRUE);
	m_pFileSelect = pFile;

	if (m_pFileSelect->IsYunFile())
	{
		if (m_nMode == OPEN_FILE_MODE)
		{
			m_btnYunDownLoad.EnableWindow(TRUE);
		}

		CString strFile;
		strFile = m_pFileSelect->GetPath();

		if (!IsFileExist(strFile))
		{
			m_btnOK.EnableWindow(FALSE);
		}
	}
	else
	{
		if (m_nMode == OPEN_FILE_MODE)
		{
			m_btnYunDownLoad.EnableWindow(FALSE);
		}
	}


	UpdateData(FALSE);
}

void CDlgXFileMngr::OnLvnItemchangedListFile(NMHDR *pNMHDR, LRESULT *pResult)
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


BOOL CDlgXFileMngr::PreTranslateMessage(MSG* pMsg)
{
	m_ToolTip.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CDlgXFileMngr::SaveXmlFile()
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
		strInfo.Format(g_sLangTxt_FileExYN/*_T("%s 文件已经存在，是否覆盖?")*/,strFileName);
		if( MessageBox(strInfo,g_sLangTxt_FileDupliName/*_T("文件重名")*/,MB_ICONQUESTION |MB_OKCANCEL ) == IDOK )
		{	
			if(!pFileSelect->m_bIsOpen)
			{
				pFile = pFolderSelect->AddFile(strFileName/*,m_strPostFixDes*/,TRUE);
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
				strInfo.Format(g_sLangTxt_AlrOpenFail/*_T("%s 已经被打开，文件覆盖失败")*/,pFileSelect->m_strName);
				MessageBox(strInfo,g_sLangTxt_FileCoverFail/*_T("文件覆盖失败")*/,MB_OK);
			}
		}

		return FALSE;
	}
	else
	{
		pFile = pFolderSelect->AddFile(strFileName/*,m_strPostFixDes*/,FALSE);
		pFile->m_bIsOpen = TRUE;
// 		m_pFileMngrBase->SaveXMLFile();

		AfxGetApp()->PostThreadMessage(WM_THREAD_DLG_FILE_MNGR,0,(LPARAM)this);
		pParentWnd->SendMessage(WM_PARENT_SAVE_XML_FILE,0,(LPARAM)(char*)(_bstr_t)this->GetFileName());

		return TRUE;
	}
}

BOOL CDlgXFileMngr::OpenXmlFile()
{
#ifdef _Use_YUN_Client_
	//2016-12-5
	//如果是云文件，则执行相关的云操作
	if (m_pFileSelect->IsYunFile())
	{
		DWORD nSize = m_pFileSelect->GetFileSize();

		if (m_pFileSelect->m_nYunSize != nSize)
		{
			Yun_SetBatchOperMode(TRUE, m_hWnd);
			Yun_DownLoad(m_pFileSelect, TRUE);
			Yun_BatchOper();
			return FALSE;
		}
	}
#endif

	return OpenXmlFile_msg();
}


BOOL CDlgXFileMngr::OpenXmlFile_msg()
{
	CString strFileName = GetFileName();
	CWnd* pParentWnd = GetParent();
	m_pFileSelect->m_bIsOpen = TRUE;
	CString_to_char(strFileName, g_pszFileName);

	LRESULT nRet = pParentWnd->SendMessage(WM_PARENT_OPEN_XML_FILE, (WPARAM)m_pFileSelect, (LPARAM)g_pszFileName);

	return (nRet == 0);
}


void CDlgXFileMngr::OnEnChangeEditFileName()
{
	m_btnOK.EnableWindow(FALSE);
	UpdateData(TRUE);

	CString strRight = m_strFileName.Right(1);
	if(strRight == _P_FOLDER_PATH_SEPARATOR_ || strRight == _T("/") ||strRight==_T(":") ||strRight == _T("*") || strRight == _T("?")
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

CString CDlgXFileMngr::GetFileName()
{
	if(m_nMode == OPEN_FILE_MODE)
	{
		if (m_strStaticPath.Right(1) == _P_FOLDER_PATH_SEPARATOR_)
		{
			return m_strStaticPath + m_strFileName;
		}
		else
		{
			return m_strStaticPath + _P_FOLDER_PATH_SEPARATOR_ + m_strFileName;	
		}
	}
	else
	{
		CString strPath = m_strStaticPath;

		if (strPath.Right(1) != _P_FOLDER_PATH_SEPARATOR_)
		{
			strPath += _P_FOLDER_PATH_SEPARATOR_;
		}

		strPath.AppendFormat(_T("%s.%s"), m_strFileName, m_strFilePostfix);
		return strPath;
	}
}

void CDlgXFileMngr::InitHistory(const CString &strFileName, const CString &strTrim)
{
	m_strTrim = strTrim;
	m_strTrim.MakeLower();
	m_strHistoryMngrFile = _P_GetConfigPath();
	m_strHistoryMngrFile += strFileName;
	m_oFilterTextMngr.OpenXmlFile(m_strHistoryMngrFile);
}

LRESULT CDlgXFileMngr::OnChangeStaticPath(WPARAM wParam,LPARAM lParam)
{
	CXFolder* pFolder = (CXFolder*)m_folderTree.GetItemData(m_folderTree.GetSelectedItem());
	m_strStaticPath = pFolder->GetFolderPath();
	UpdateData(FALSE);

	return 0;
}

void CDlgXFileMngr::OnCbnSelchangeHistory()
{
	long nIndex = m_cmbHistory.GetCurSel();

	if (nIndex == CB_ERR)
	{
		return;
	}

	CFilterText *pText = (CFilterText*)m_cmbHistory.GetItemDataPtr(nIndex);
	SelectFile(pText);
}

CString DlgXFile_GetOpenFile(const CString &strFileType, const CString &strFileDes, CWnd *pParent, CXFileMngr *pFileMngr)
{
	CString strFileName;

	CDlgXFileMngr dlg(0,strFileType,strFileDes,pFileMngr,OPEN_FILE_MODE,pParent);

	if(dlg.DoModal() == IDOK)
	{
		strFileName = dlg.GetFileName();
	}

	return strFileName;
}
