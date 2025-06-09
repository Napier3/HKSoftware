#include "StdAfx.h"
#include "XmlRptEdit.h"

CXmlRptEdit::CXmlRptEdit(void)
{
}

CXmlRptEdit::~CXmlRptEdit(void)
{
}

BOOL CXmlRptEdit::CreateWordApplication(BOOL bVisible)
{
	if(m_xmlDlg.m_hWnd == NULL)
	{
		m_xmlDlg.Create(IDD_DIALOG_EDIT, NULL);			
	}

	//创建对象
	if(!OpenWordReportFile(m_strReportTemplateFile))
	{
		AfxMessageBox(/*L"打开文档失败！"*/g_sLangTxt_OpenDocFail);
		m_strReportTemplateFile= "";
		return FALSE;
	}

	return TRUE;
}
BOOL CXmlRptEdit::OpenWordReportFile(const CString &strRptFile)
{
	BOOL bTrue = TRUE;
	if (FindFile(m_strReportTemplateFile))
	{
		try
		{
			//打开试验报告文件
			bTrue = m_XmlProssData.OpenXmlFile(strRptFile);
			UpdateToFaceTree();					//20230616 luozibing 更新树形控件与表格
			UpdateToFaceGrid();
		}
		catch (...)
		{
			bTrue = FALSE;
		}
	}
	else
	{
		bTrue = FALSE;
	}

	return bTrue;
}

//未见使用
BOOL CXmlRptEdit::NewWordReportFile()
{
	return FALSE;
}

void CXmlRptEdit::InitAllBookmarks()
{
	m_listWordBkmks.DeleteAll();
	map<BDAttr*,CString>::iterator it;
	for(it=m_XmlProssData.m_MapBkmks.begin(); it!=m_XmlProssData.m_MapBkmks.end(); it++)
    {
        CWordBkmk *pNew = new CWordBkmk();
		pNew->m_strID = it->second;
		m_listWordBkmks.AddTail(pNew);
    }
}

void CXmlRptEdit::ExitWord(BOOL bExitApp)
{	
	Close(m_bSave);
	m_xmlDlg.ExitWord();
}

//未见使用
long CXmlRptEdit::OpenWord(const CString &strGuideBookFile)
{	
	CString strType = GetReportSuffix();
	m_strReportTemplateFile = ChangeFilePostfix(strGuideBookFile, strType);	

	BOOL bTrue = TRUE;
	if (FindFile(m_strReportTemplateFile))
	{
		try
		{
			//打开试验报告文件
			bTrue = m_XmlProssData.OpenXmlFile(m_strReportTemplateFile);
		}
		catch (...)
		{
			bTrue = FALSE;
		}
	}

	return TRUE;
}

CExBaseObject* CXmlRptEdit::AddBkmk(CRptData *pData, const CString &strAttrID, const CString &strDataProcess, const CString &strFillMode)
{
	CAutoSimpleLock oLock(m_oWordCriticSection);

	CRptBkmk* pBkmk = NULL;

	try
	{
		// 插入书签
		//判断选中位置是否存在标签
		BDAttr *cAttri = m_xmlDlg.GetSelectDataPos();
		if(cAttri == NULL)	//未选中位置
			return NULL;

		CString strSelBkmk = m_xmlDlg.GetSelectBkmk();
		if(strSelBkmk != _T(""))
		{
			if (FindRptBkmk(strSelBkmk)!=NULL)//是有效书签
			{
				int nResult = MessageBox(NULL,/*L"当前位置有标签，确定替换"*/g_sLangTxt_HaveMarkSureReplace,g_sLangTxt_Message/*L"提示"*/,MB_YESNO);
				if(nResult == IDNO)
				{
					return NULL;
				}
				else//替换书签
				{
					//如果要插入的书签数据与Data相同则返回
					if (pData->FindByID(strSelBkmk) != NULL)
					{
						return NULL;
					}
					DeleteBkmk(strSelBkmk);
				}
			}
			else
			{
				DeleteBkmk(strSelBkmk);
			}
		}

		CString strBkmk = CreateNewBkmk(pData);
		m_XmlProssData.AddBkmk(cAttri, strBkmk);
		m_xmlDlg.SetSelectBkmk(strBkmk);

		pBkmk = (CRptBkmk*)pData->AddNew2(strBkmk);
		pBkmk->m_strDataAttrID = strAttrID;
		pBkmk->m_strProcess = strDataProcess;
		pBkmk->m_strFillMode = strFillMode;
		
		CWordBkmk *pNew = new CWordBkmk();
		pNew->m_strID = strBkmk;
		pNew->m_pBkmk = pBkmk;
		pBkmk->m_pBkmk = pNew;
		m_listWordBkmks.AddTail(pNew);

		SetRptItemBkmkState(pBkmk);
	}
	catch (...)
	{
	}
	
	SetMidified(TRUE);

	return pBkmk;
}

void CXmlRptEdit::InsertBkmk(const CString &strBkmk)
{
	try
	{
		BDAttr *cAttri = m_xmlDlg.GetSelectDataPos();
		if(cAttri == NULL)
			return ;

		m_XmlProssData.AddBkmk(cAttri, strBkmk);
	}
	catch (...)
	{
	}
}
CExBaseObject* CXmlRptEdit::BindBkmk(CRptData *pData, const CString &strAttrID, const CString &strDataProcess, const CString &strFillMode, const CString &strBkmk)
{
	if(!IsValidDoc())
	{
		return FALSE;
	}

	if (pData->FindByID(strBkmk) != NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, /*_T("书签【%s】在数据报告中【%s】已经存在")*/g_sLangTxt_BookMarkExist, strBkmk, pData->m_strID);
		return NULL;
	}
	CString strNewBkmk;
	CRptBkmk* pBkmk = NULL;
	CString strOldBkmk= m_xmlDlg.GetSelectBkmk();
	BDAttr *cAttri = m_xmlDlg.GetSelectDataPos();

	{//删除旧标签
		CWordBkmk * pWordBkmk =(CWordBkmk *)m_listWordBkmks.FindByID(strOldBkmk);
		pBkmk = pWordBkmk->m_pBkmk;
		CExBaseList* pParent = (CExBaseList*)pBkmk->GetParent();
		pParent->DeleteByID(strOldBkmk);			//删除gbxml

		m_XmlProssData.Deletekmk(cAttri);		//删除报告
		m_listWordBkmks.DeleteByID(strOldBkmk);
	}
	{//添加新标签
		strNewBkmk = CreateNewBkmk(pData);

		m_XmlProssData.AddBkmk(cAttri, strNewBkmk);
		m_xmlDlg.SetSelectBkmk(strNewBkmk);//20230922 luozibing 设置最新的标签信息
		

		pBkmk = (CRptBkmk*)pData->AddNew2(strNewBkmk);
		pBkmk->m_strDataAttrID = strAttrID;
		pBkmk->m_strProcess = strDataProcess;
		pBkmk->m_strFillMode = strFillMode;

		CWordBkmk *pNew = new CWordBkmk();
		pNew->m_strID = strNewBkmk;
		pNew->m_pBkmk = pBkmk;
		pBkmk->m_pBkmk = pNew;
		m_listWordBkmks.AddTail(pNew);

		SetRptItemBkmkState(pBkmk);
		SetMidified(TRUE);
	}
	UpdateToFaceGrid();
	return pBkmk;
}

CExBaseObject* CXmlRptEdit::AddArea(CGbItemBase *pItem, long nStart, long nEnd)
{
	//不支持区域标签
	return NULL;
}

CExBaseObject* CXmlRptEdit::AddArea(CExBaseList *pRptArea)
{
	//不支持区域标签
	return NULL;
}

//未见使用
long CXmlRptEdit::GetCurrPos()
{
	long nPos = 0;
	return nPos;
}

//未见使用
long CXmlRptEdit::InitPage(BOOL bHort)
{
	return 0;
}

long CXmlRptEdit::Save()
{
	m_pGuideBook->SaveXMLFile(m_strGuideBookFile);

	try
	{
		m_XmlProssData.SaveXmlFile(m_strReportTemplateFile);
	}
	catch(...)
	{
	}

	SetMidified(FALSE);

	return 0;
}

long CXmlRptEdit::SaveAs(const CString &strFile)
{
	CString strType = GetReportSuffix();
	CString strDocFile = ChangeFilePostfix(strFile, strType);

	//文件保存
	m_XmlProssData.SaveXmlFile(m_strReportTemplateFile);

	SetMidified(FALSE);
	m_strReportTemplateFile = strFile;

	return 0;
}

//未见使用
long CXmlRptEdit::CloseWord()
{
	return 0;
}

BOOL CXmlRptEdit::IsValidDoc()
{
	//return (m_doc != NULL);
	return TRUE;
}

void CXmlRptEdit::ClearBkmkText(CRptBkmk *pBkmk)
{
	try
	{
		DeleteBkmk(pBkmk->m_strID);		
	}
	catch(...)
	{
	}
}

CString CXmlRptEdit::InitCurrBkmk()
{
	CAutoSimpleLock oLock(m_oWordCriticSection);
	CString strBkmk;
	BOOL bCanAdd = TRUE;

	try
	{
		strBkmk = m_xmlDlg.GetSelectBkmk();
		m_pCurrBkmk = (CWordBkmk*)m_listWordBkmks.FindByID((strBkmk));
	}
	catch(...)
	{
		m_pCurrBkmk = NULL;
	}
	return strBkmk;
}

long CXmlRptEdit::GetAllSelBkmk(CExBaseList &oListWordBkmk)
{
	CAutoSimpleLock oLock(m_oWordCriticSection);
	CString strBkmk;
	BOOL bCanAdd = TRUE;

	try
	{
		strBkmk = m_xmlDlg.GetSelectBkmk();
		CWordBkmk *pFind = (CWordBkmk*)m_listWordBkmks.FindByID((strBkmk));
		if (pFind != NULL)
		{
			oListWordBkmk.AddTail(pFind);
		}
	}
	catch(...)
	{
	}

	return oListWordBkmk.GetCount();
}

BOOL CXmlRptEdit::CanAddArea()
{
	BOOL bCanAdd = FALSE;	//不支持区域标签
	return bCanAdd;
}

BOOL CXmlRptEdit::ReplaceBkmk(const CString &  strBkmkSrc, const CString &  strBkmkDest)
{
	try
	{
		BDAttr *cAttri = m_xmlDlg.GetSelectDataPos();
		if(cAttri == NULL)
			return FALSE;
		m_XmlProssData.Replacekmk(cAttri, strBkmkDest);
	}
	catch (...)
	{
	}

	SetMidified(TRUE);
	return TRUE;
}

BOOL CXmlRptEdit::UpdateBkmk(CRptBkmk *pRptBkmk)
{
	//CString strBkmk = pRptBkmk->m_strID;

	try
	{
// 		long nPos = strBkmk.ReverseFind('_');
// 		if (nPos  > 0)
// 		{
// 			strBkmk = strBkmk.Left(nPos+1);
// 		}
// 
// 		strBkmk.AppendFormat(_T("%d"), m_dwMaxBkmkIndex++);
// 
// 		m_XmlProssData.Replacekmk(pRptBkmk->m_strID, strBkmk);
// 		pRptBkmk->m_strID = strBkmk;
	}
	catch (...)
	{
	}

	SetMidified(TRUE);
	return TRUE;
}

//未见使用
void CXmlRptEdit::InsertTitle(const CString &strTitle, long nTitleLevel)
{
}

//未见使用
BOOL CXmlRptEdit::ActiveWindow(const CString &strTitle)
{
	return true;
}

//未见使用
long CXmlRptEdit::GetBkmkPos(CRptBkmk *pBkmk, long &nBeginPos, long &nEndPos)
{
	nBeginPos = -1;
	nEndPos = -1;
	return 0;
}

//未见使用
long CXmlRptEdit::AdjustReport_DelArea(CRptArea *pArea)
{
	return 0;
}

CExBaseObject * CXmlRptEdit::ReLocateBkmk()
{
	CRptBkmk* pBkmk = NULL;

	try
	{
		CString strBkmk = m_xmlDlg.GetSelectBkmk();
		pBkmk = (CRptBkmk*)FindRptBkmk(strBkmk);
	}
	catch (...)
	{
	}

	return pBkmk;
}

CWnd* CXmlRptEdit::AdjustSizeView()
{
	CWnd *pWnd = NULL;

	//获取Word文档的窗口
	try
	{
		if(m_xmlDlg.m_hWnd == NULL)
		{
			m_xmlDlg.Create(IDD_DIALOG_EDIT, NULL);			
		}

		m_xmlDlg.ShowWindow(SW_SHOW);
		pWnd = &m_xmlDlg;
	}
	catch(...)
	{
	}

	return pWnd;
}

void CXmlRptEdit::SetAppVisible(BOOL bVisible)
{
	if(m_xmlDlg.m_hWnd == NULL)
	{
		m_xmlDlg.ShowWindow(SW_SHOW);
	}
}

void CXmlRptEdit::SetDisplayStatusBar(BOOL bVisible)
{
}

//未见使用
void CXmlRptEdit::CopyApp(CRptEditInterface *pRptEditDest)
{
}
//未见使用
void CXmlRptEdit::rpt_RenameRptBkmks(CExBaseList *pList)
{
}
//未见使用
void CXmlRptEdit::InsertWordEdit(CRptEditInterface *pRptEdit, long nAddRptGroupTitle)
{
}

BOOL CXmlRptEdit::rpt_CanEnterRptBkmkBatchAdd(CExBaseObject *pItem)
{
	AfxMessageBox(_T("批量操作暂时取消！"), MB_OK | MB_ICONEXCLAMATION);
	return FALSE;//xml中没有表格，不具备批量插入条件
}

BOOL CXmlRptEdit::rpt_CanEnterRptBkmkBatchAddYc(CExBaseObject *pItem)
{
	AfxMessageBox(_T("批量操作暂时取消！"), MB_OK | MB_ICONEXCLAMATION);
	return FALSE;//xml中没有表格，不具备批量插入条件
}

BOOL CXmlRptEdit::rpt_GetRptBkmkBatchRowsCols(long &nRows, long &nCols)
{
	return FALSE;//xml中没有表格，不具备批量插入条件
}

void CXmlRptEdit::InsertBkmks(CExBaseList& oListCells, CExBaseList& oListBkmks)
{
	return ;//xml中没有表格，不具备批量插入条件
}

void CXmlRptEdit::GetBatchCellList_ROWITEM_COLDATA(CExBaseList &oListBatchCell,CRptBatchItemMaps *pItemMaps, CRptBatchDataMaps *pDataMaps, long nCols)
{
	return ;//xml中没有表格，不具备批量插入条件
}

void CXmlRptEdit::GetBatchCellList_ROWDATA_COLITEM(CExBaseList &oListBatchCell,CRptBatchItemMaps *pItemMaps, CRptBatchDataMaps *pDataMaps, long nRows)
{
	return ;//xml中没有表格，不具备批量插入条件
}

void CXmlRptEdit::GetBatchCellList_ROWREPEAT_COLDATA_ITEMROW(CExBaseList &oListBatchCell,CRptBatchItemMaps *pItemMaps, CRptBatchDataMaps *pDataMaps, long nRepeatCount, long nCols)
{
	return ;//xml中没有表格，不具备批量插入条件
}

long CXmlRptEdit::LocateBkmk(const CString &  strBkmk)
{
	DWORD hItem = m_XmlProssData.GetSelectBkmk(strBkmk, m_iFindIndex);
	m_xmlDlg.SetSelectBkmk(hItem,strBkmk);
	return 0;
}

long CXmlRptEdit::DeleteBkmk(const CString& strBkmk, BOOL bSelect)
{	
	long nRet = 0;

	BDAttr *cAttri = m_xmlDlg.GetSelectDataPos();
	if(cAttri == NULL)
		return nRet;
	if(m_XmlProssData.Deletekmk(cAttri))
	{
		nRet = 1;
	}

	SetMidified(TRUE);
	UpdateToFaceGrid();

	return nRet;
}
//20230616 luozibing 更新树形控件与表格
void CXmlRptEdit::UpdateToFaceTree()
{
	CXmlData* pObj = (CXmlData*)m_XmlProssData.GetHead();
	m_xmlDlg.SetShowData(pObj);
}
void CXmlRptEdit::UpdateToFaceGrid()
{
	m_xmlDlg.UpdateGrid();
}

BOOL CXmlRptEdit::CheckChoosePoint()
{
	BDAttr *cAttri = m_xmlDlg.GetSelectDataPos();
	if(cAttri == NULL)	//未选中位置
		return FALSE;
	return TRUE;
}

//20231010 huangliang 关联标签
void CXmlRptEdit::AttachBookmarksAndRptBkmks()
{
	POS pos = m_listRptBkmks.GetHeadPosition();
	CRptBkmk *pRptBkmk = NULL;
	CWordBkmk *pBkmk = NULL;

	map<CString, int> mapBkmksCount;
	map<CString, int>::iterator it;  

	while (pos != NULL)
	{
		pRptBkmk = (CRptBkmk *)m_listRptBkmks.GetNext(pos);	

		if(xml_CheckBkmk(pRptBkmk->m_strID) != BMK_PATH)
		{
			continue;
		}
		
		int iCount = 0;
		it = mapBkmksCount.find(pRptBkmk->m_strID); 
		if(it == mapBkmksCount.end())
		{
			mapBkmksCount.insert(pair<CString, int>(pRptBkmk->m_strID, iCount+1));
		}
		else
		{
			iCount = it->second;
			it->second++;
		}

		pBkmk = FindWorkList(pRptBkmk->m_strID, iCount);

		if (pBkmk != NULL)
		{
			pBkmk->m_pBkmk = pRptBkmk;
			pRptBkmk->m_pBkmk = pBkmk;
		}
	}
}
CWordBkmk *CXmlRptEdit::FindWorkList(const CString &strId, int iIndex)
{
	POS pos = m_listWordBkmks.GetHeadPosition();
	CWordBkmk *pBkmk = NULL;

	int iCount = 0;
	while (pos != NULL)
	{
		pBkmk = (CWordBkmk *)m_listWordBkmks.GetNext(pos);	
		if (pBkmk->m_strID == strId)
		{
			if(iCount == iIndex)
				return pBkmk;
			iCount++;
		}
	}
	return NULL;
}

//2023-09-26 huangliang 
CString CXmlRptEdit::CreateNewBkmk(CRptData *pData)
{
	return m_strSelectPath;
}