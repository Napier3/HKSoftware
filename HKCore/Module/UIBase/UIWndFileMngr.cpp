//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UIWndFileMngr.cpp  CUIWndFileMngr


#include "stdafx.h"
#include "UIWndFileMngr.h"

CString CUIWndFileMngr::g_strWndAttrID_FolderSel = _T("folder-sel");
CString CUIWndFileMngr::g_strWndAttrID_FileSel   = _T("file-sel");


CUIWndFileMngr::CUIWndFileMngr()
{
	//初始化属性

	//初始化成员变量
//	m_pFileSelect = NULL;
}

CUIWndFileMngr::~CUIWndFileMngr()
{
	
}

long CUIWndFileMngr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CUIWindowBase::XmlReadOwn(oNode, pXmlRWKeys);
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strTreeViewWidthRateKey, oNode, m_nTreeViewWidthRate);
	xml_GetAttibuteValue(pXmlKeys->m_strTreeViewWidthMaxKey, oNode, m_nTreeViewWidthMax);

	return 0;
}

long CUIWndFileMngr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CUIWindowBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strTreeViewWidthRateKey, oElement, m_nTreeViewWidthRate);
	xml_SetAttributeValue(pXmlKeys->m_strTreeViewWidthMaxKey, oElement, m_nTreeViewWidthMax);

	return 0;
}


void CUIWndFileMngr::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == UICLASSID_CUIBASEFILETYPES)
		{
			m_pFileTypes = (CUIBaseFileTypes*)p;
		}
	}

	if (m_pFileTypes == NULL)
	{
		m_pFileTypes = (CUIBaseFileTypes*)AddNewChild(new CUIBaseFileTypes());
	}

	CUIWindowBase::InitAfterRead();
}

BOOL CUIWndFileMngr::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CUIWindowBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CUIWndFileMngr *p = (CUIWndFileMngr*)pObj;

	if(m_nTreeViewWidthRate != p->m_nTreeViewWidthRate)
	{
		return FALSE;
	}

	if(m_nTreeViewWidthMax != p->m_nTreeViewWidthMax)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CUIWndFileMngr::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CUIWindowBase::CopyOwn(pDest);

	CUIWndFileMngr *p = (CUIWndFileMngr*)pDest;

	p->m_nTreeViewWidthRate = m_nTreeViewWidthRate;
	p->m_nTreeViewWidthMax = m_nTreeViewWidthMax;

	return TRUE;
}

CBaseObject* CUIWndFileMngr::Clone()
{
	CUIWndFileMngr *p = new CUIWndFileMngr();
	Copy(p);
	return p;
}

CExBaseObject* CUIWndFileMngr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCUIBaseFileTypesKey)
	{
		pNew = new CUIBaseFileTypes();
	}
	else
	{
		pNew = CUIWindowBase::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);
	}


	return pNew;
}

CExBaseObject* CUIWndFileMngr::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == UICLASSID_CUIBASEFILETYPES)
	{
		pNew = new CUIBaseFileTypes();
	}
	else
	{
		pNew = CUIWindowBase::CreateNewChild(nClassID);
	}

	return pNew;
}
BOOL CUIWndFileMngr::CanPaste(UINT nClassID)
{
	if (nClassID == UICLASSID_CUIBASEFILETYPES)
	{
		return TRUE;
	}

	return FALSE;
}

long CUIWndFileMngr::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nTreeViewWidthRate);
		BinarySerializeCalLen(oBinaryBuffer, m_nTreeViewWidthMax);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nTreeViewWidthRate);
		BinarySerializeRead(oBinaryBuffer, m_nTreeViewWidthMax);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nTreeViewWidthRate);
		BinarySerializeWrite(oBinaryBuffer, m_nTreeViewWidthMax);
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CUIWndFileMngr, CStatic)
	//{{AFX_MSG_MAP(CUIWndFileMngr)
	//ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_MESSAGE(WM_MOUSEHOVER, OnMouseHover)
	//}}AFX_MSG_MAP
	ON_WM_SIZE()
	ON_NOTIFY(NM_DBLCLK, UI_IDC_LIST_FILE, &CUIWndFileMngr::OnNMDblclkListFile)
// 	ON_NOTIFY(NM_CLICK, UI_IDC_LIST_FILE, &CUIWndFileMngr::OnNMClickListFile)
// 	ON_NOTIFY(LVN_ITEMCHANGED, UI_IDC_LIST_FILE, &CUIWndFileMngr::OnLvnItemchangedListFile)
	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGR_FOLDER_ADD, &CUIWndFileMngr::OnUpdateFolderAdd)
	ON_COMMAND(XFID_XFILEMNGR_FOLDER_ADD, &CUIWndFileMngr::OnFolderAdd)
	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGR_FOLDER_DELETE, &CUIWndFileMngr::OnUpdateFolderDelete)
	ON_COMMAND(XFID_XFILEMNGR_FOLDER_DELETE, &CUIWndFileMngr::OnFolderDelete)
	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGR_FOLDER_EDIT, &CUIWndFileMngr::OnUpdateFolderEdit)
	ON_COMMAND(XFID_XFILEMNGR_FOLDER_EDIT, &CUIWndFileMngr::OnFolderEdit)
	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGR_FOLDER_EXPORT, &CUIWndFileMngr::OnUpdateFolderExport)
	ON_COMMAND(XFID_XFILEMNGR_FOLDER_EXPORT,&CUIWndFileMngr:: OnFolderExport)
	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGR_FOLDER_IMPORT, &CUIWndFileMngr::OnUpdateFolderImport)
	ON_COMMAND(XFID_XFILEMNGR_FOLDER_IMPORT, &CUIWndFileMngr::OnFolderImport)
	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGRFILE_COPY, &CUIWndFileMngr::OnUpdateFileCopy)
	ON_COMMAND(XFID_XFILEMNGRFILE_COPY, &CUIWndFileMngr::OnFileCopy)
	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGRFILE_PASTE, &CUIWndFileMngr::OnUpdateFilePaste)
	ON_COMMAND(XFID_XFILEMNGRFILE_PASTE, &CUIWndFileMngr::OnFilePaste)
	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGRFILE_DELETE, &CUIWndFileMngr::OnUpdateFileDelete)
	ON_COMMAND(XFID_XFILEMNGRFILE_DELETE, &CUIWndFileMngr::OnFileDelete)
	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGRFILE_EDIT, &CUIWndFileMngr::OnUpdateFileEdit)
	ON_COMMAND(XFID_XFILEMNGRFILE_EDIT, &CUIWndFileMngr::OnFileEdit)
	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGRFILE_EXPORT, &CUIWndFileMngr::OnUpdateFileExport)
	ON_COMMAND(XFID_XFILEMNGRFILE_EXPORT, &CUIWndFileMngr::OnFileExport)
	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGRFILE_IMPORT, &CUIWndFileMngr::OnUpdateFileImport)
	ON_COMMAND(XFID_XFILEMNGRFILE_IMPORT, &CUIWndFileMngr::OnFileImport)
	ON_MESSAGE(WM_THREAD_XFILE_MNGR, &CUIWndFileMngr::OnXFileSelChanged)
END_MESSAGE_MAP()



void CUIWndFileMngr::OnUpdateFolderAdd(CCmdUI* pCmdUI)
{
	m_folderTree.OnUpdateFolderAdd(pCmdUI);
}

void CUIWndFileMngr::OnFolderAdd()
{
	m_folderTree.OnFolderAdd();
}

void CUIWndFileMngr::OnUpdateFolderDelete(CCmdUI* pCmdUI)
{
	m_folderTree.OnUpdateFolderDelete(pCmdUI);
}

void CUIWndFileMngr::OnFolderDelete()
{
	m_folderTree.OnFolderDelete();
}

void CUIWndFileMngr::OnUpdateFolderEdit(CCmdUI* pCmdUI)
{
	m_folderTree.OnUpdateFolderEdit(pCmdUI);
}

void CUIWndFileMngr::OnFolderEdit()
{
	m_folderTree.OnFolderEdit();
}

void CUIWndFileMngr::OnUpdateFolderExport(CCmdUI* pCmdUI)
{
	m_folderTree.OnUpdateFolderExport(pCmdUI);
}

void CUIWndFileMngr::OnFolderExport()
{
	m_folderTree.OnFolderExport();
}

void CUIWndFileMngr::OnUpdateFolderImport(CCmdUI* pCmdUI)
{
	m_folderTree.OnUpdateFolderImport(pCmdUI);
}

void CUIWndFileMngr::OnFolderImport()
{
	m_folderTree.OnFolderImport();
}

void CUIWndFileMngr::OnUpdateFileCopy(CCmdUI* pCmdUI)
{

}

void CUIWndFileMngr::OnFileCopy()
{

}

void CUIWndFileMngr::OnUpdateFilePaste(CCmdUI* pCmdUI)
{

}

void CUIWndFileMngr::OnFilePaste()
{

}

void CUIWndFileMngr::OnUpdateFileDelete(CCmdUI* pCmdUI)
{

}

void CUIWndFileMngr::OnFileDelete()
{

}

void CUIWndFileMngr::OnUpdateFileEdit(CCmdUI* pCmdUI)
{

}

void CUIWndFileMngr::OnFileEdit()
{

}

void CUIWndFileMngr::OnUpdateFileExport(CCmdUI* pCmdUI)
{

}

void CUIWndFileMngr::OnFileExport()
{

}

void CUIWndFileMngr::OnUpdateFileImport(CCmdUI* pCmdUI)
{

}


void CUIWndFileMngr::OnFileImport()
{

}

BOOL CUIWndFileMngr::UICreate(CWnd *pParent)
{
	if (m_pWindow != NULL)
	{
		LOG_WriteLawString("recreate BitMap");
	}

	CRect rect = GetWndPosition();
	BOOL bState = FALSE;	

	bState = Create(NULL,WS_CHILD | WS_VISIBLE,// | SS_NOTIFY,
		rect,
		pParent,
		GenerateWindowID());

	if (!bState)
	{
		return FALSE;
	}

	LoadUIBitmap();
	ShowWindow(SW_SHOW);
	m_pWindow = this;

	DWORD dwStyle = (WS_BORDER | WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS);
	m_folderTree.Create(dwStyle, CRect(14, 35, 189, 260), this, UI_IDC_TREE_FOLDER);

	dwStyle = (WS_VISIBLE | WS_CHILD | WS_TABSTOP | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS);

	if (m_fileListCtrl.Create(dwStyle, CRect(198, 35, 626, 260), this, UI_IDC_LIST_FILE))
	{
		m_fileListCtrl.ModifyStyle(0L,LVS_NOSORTHEADER|LVS_SINGLESEL);
		m_fileListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	}

	AdjustWndSize(rect.Width(), rect.Height());
	
	CXFileTypes *pXFileTypes = m_oXFileMngr.GetXFileTypes();
	m_oXFileMngr.SetOnllySearchMainTypeFile(m_pFileTypes->m_bOnllySearchMainTypeFile);
	m_pFileTypes->InitXFileTypes(pXFileTypes);
	m_oXFileMngr.InitByXFileTypes();

	m_oXFileMngr.SetLibraryPath(m_pFileTypes->GetRootPath());
	m_oXFileMngr.m_strName = m_pFileTypes->GetRootName();
	m_folderTree.ShowXFileMngr(&m_oXFileMngr);
	m_fileListCtrl.SetXFileMngr(&m_oXFileMngr);
	m_folderTree.SetFrameWnd(this);
	m_fileListCtrl.SetFrameWnd(this);
	m_folderTree.AttacthXFileListView( &m_fileListCtrl );
	m_fileListCtrl.SetRelatedFolderTreeCtrl(&m_folderTree);
	m_folderTree.SelectItem((HTREEITEM)m_oXFileMngr.m_dwItemData);
	m_folderTree.OnTvnSelchanged((HTREEITEM)m_oXFileMngr.m_dwItemData);

	return TRUE;
}

BOOL CUIWndFileMngr::Destroy()
{
	if (m_pWindow != NULL)
	{
		DestroyWindow();
		m_pWindow = NULL;
	}

	return TRUE;
}

long CUIWndFileMngr::ExecWndCmd(const CString &strCmd, const CString &strPara)
{
	if (strCmd == _T("delete-file"))
	{
		m_fileListCtrl.OnFileDelete();
		return 1;
	}

	if (strCmd == _T("delete-folder"))
	{
		m_fileListCtrl.OnFolderDelete();
		return 1;
	}

	if (strCmd == _T("import-file"))
	{
		m_fileListCtrl.OnFileImport();
		return 1;
	}

	if (strCmd == _T("import-folder"))
	{
		m_fileListCtrl.OnFolderImport();
		return 1;
	}

	if (strCmd == _T("export-file"))
	{
		m_fileListCtrl.OnFileExport();
		return 1;
	}

	if (strCmd == _T("export-folder"))
	{
		m_fileListCtrl.OnFolderExport();
		return 1;
	}

	if (strCmd == _T("add-folder"))
	{
		m_fileListCtrl.OnFolderAdd();
		return 1;
	}

	return 0;
}

long CUIWndFileMngr::GetWndAttr(const CString &strAttrID, CString &strAttrValue)
{
	long nRet = 0;

	if (strAttrID == g_strWndAttrID_FolderSel)
	{
		strAttrValue.Format(_T("%d"), m_oXFileMngr.GetCurrSelFolder() != NULL);
		nRet = 1;
	}
	else if (strAttrID == g_strWndAttrID_FileSel)
	{
		strAttrValue.Format(_T("%d"), m_oXFileMngr.GetCurrSelFile() != NULL);
		nRet = 1;
	}

	return nRet;
}

long CUIWndFileMngr::SetWndAttr(const CString &strAttrID, const CString &strAttrValue)
{
	return -1;
}

void CUIWndFileMngr::LoadUIBitmap()
{
// 	CString str;
// 	str = _P_GetSource_Bitmap_Path();
// 	str += m_strNormalBmpFile;
// 	//str.Format("%sBitmaps\\%s", _P_GetConfigPath(), m_strBmp);
// 	m_oDib.Load(str);
}

void CUIWndFileMngr::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	//m_oDib.Draw(&dc, m_nLeft, m_nTop, m_nWidth, m_nHeight);
}

void CUIWndFileMngr::OnMouseMove(UINT nFlags, CPoint point) 
{
	UI_OnMouseMove(nFlags, point);

	CStatic::OnMouseMove(nFlags, point);
}

LRESULT CUIWndFileMngr::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	return UI_OnMouseLeave(wParam, lParam);
}


LRESULT CUIWndFileMngr::OnMouseHover(WPARAM wParam, LPARAM lParam)
{
	return UI_OnMouseHover(wParam, lParam);
}


void CUIWndFileMngr::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);

	AdjustWndSize(cx, cy);
}

void CUIWndFileMngr::AdjustWndSize(int cx, int cy)
{
	if (!::IsWindow(m_folderTree.m_hWnd))
	{
		return;
	}

	long nTreeViewWidth = cx * m_nTreeViewWidthRate / 100;

	if (nTreeViewWidth >= m_nTreeViewWidthMax)
	{
		nTreeViewWidth = m_nTreeViewWidthMax;
	}

	CRect rcTreeView, rcListView;
	rcTreeView.left = 0;
	rcTreeView.top = 0;
	rcTreeView.right = nTreeViewWidth;
	rcTreeView.bottom = cy;

	rcListView = rcTreeView;
	rcListView.left = rcTreeView.right + 2;
	rcListView.right = cx;

	m_folderTree.MoveWindow(rcTreeView, TRUE);
	m_fileListCtrl.MoveWindow(rcListView, TRUE);
}




void CUIWndFileMngr::OnNMDblclkListFile(NMHDR *pNMHDR, LRESULT *pResult)
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
			//SendMessage(WM_CHANGE_STATIC_PATH,0,0);
		}
	
		if( xfile_IsFile(pObj->GetClassID()) )
		{
			CXFile *pFile = (CXFile *)pObj;
			ExecXFile(pFile);
			//OnNMClickListFile(pNMHDR,pResult);
		}
	}

	*pResult = 0;
}

void CUIWndFileMngr::ExecXFile(CXFile *pFile)
{
	CXFileType *pXFileType = m_oXFileMngr.FindFileType(pFile);

	if (pXFileType == NULL)
	{
		return;
	}

	if (pXFileType->m_strExe.GetLength() == 0)
	{
		return;
	}

	CString strExe = _P_GetFullPath(pXFileType->m_strExe);
	CString strFile;
	strFile.Format(_T("\"%s\""), pFile->GetTotalFileName());

	ExecuteFile(strExe, strFile, pXFileType->m_strRunMode);
}
// 
// void CUIWndFileMngr::OnNMClickListFile(NMHDR *pNMHDR, LRESULT *pResult)
// {
// 	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
// 	long nCount = m_fileListCtrl.GetSelectedCount();
// 
// 	if(nCount == 1)
// 	{
// 		int nItem = -1;
// 		nItem = m_fileListCtrl.GetNextItem(nItem,LVNI_SELECTED);
// 		ASSERT(nItem != -1);
// 		CExBaseObject* pObj = (CExBaseObject*)m_fileListCtrl.GetItemData(nItem);
// 
// 		if( xfile_IsFile(pObj->GetClassID()) )
// 		{
// 			CXFile* pFile = (CXFile*)pObj;
// 			CXFolder* pFolderSelect = (CXFolder*)m_folderTree.GetItemData(m_folderTree.GetSelectedItem());
// 			m_pFileSelect = pFile;
// 			return ;
// 		}
// 
// 		m_pFileSelect = NULL;
// 		m_strFileName = _T("");
// 	}
// 
// 	UI_OnClicked();
// 
// 	*pResult = 0;
// }

// 
// void CUIWndFileMngr::OnLvnItemchangedListFile(NMHDR *pNMHDR, LRESULT *pResult)
// {
// 	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
// 	// TODO: 在此添加控件通知处理程序代码
// 
// // 	if ( ((pNMLV->uNewState & LVIS_FOCUSED) == LVIS_FOCUSED) 
// // 		&& ((pNMLV->uNewState & LVIS_SELECTED) == LVIS_SELECTED) )
// // 	{
// // 		OnNMClickListFile(pNMHDR, pResult);
// // 	}
// // 	else
// // 	{
// // 
// // 	}
// 
// 	UI_OnClicked();
// 
// 	*pResult = 0;
// }

// 
// void CUIWndFileMngr::OnEnChangeEditFileName()
// {
// 	m_btnOK.EnableWindow(FALSE);
// 	UpdateData(TRUE);
// 
// 	CString strRight = m_strFileName.Right(1);
// 	if(strRight == _T("\\") || strRight == _T("/") ||strRight==_T(":") ||strRight == _T("*") || strRight == _T("?")
// 		|| strRight == _T("<") || strRight == _T(">") || strRight == _T("|") )
// 	{
// 		long nStrLength = m_strFileName.GetLength();
// 		m_strFileName.Delete(nStrLength-1);
// 		UpdateData(FALSE);
// 		m_editFileName.SetSel(nStrLength,nStrLength,TRUE);
// 		m_editFileName.SetFocus();
// 	}
// 
// 	if(m_strFileName == _T(""))
// 	{
// 		m_btnOK.EnableWindow(FALSE);
// 	}
// 	else
// 	{
// 		m_btnOK.EnableWindow(TRUE);
// 	}
// }

LRESULT CUIWndFileMngr::OnXFileSelChanged(WPARAM wParam, LPARAM lParam)
{
	UI_OnClicked();

	return 0;
}

