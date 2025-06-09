#include "StdAfx.h"
#include "JsonRptEdit.h"
CJsonRptEdit::CJsonRptEdit(void)
{
}

CJsonRptEdit::~CJsonRptEdit(void)
{
}
BOOL CJsonRptEdit::CreateWordApplication(BOOL bVisible)
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
BOOL CJsonRptEdit::OpenWordReportFile(const CString &strRptFile)
{
	BOOL bTrue = TRUE;
	if (FindFile(m_strReportTemplateFile))
	{
		try
		{
			//打开试验报告文件
			bTrue = m_JsonProssData.OpenXmlFile(strRptFile);
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
BOOL CJsonRptEdit::NewWordReportFile()
{
	return FALSE;
}

void CJsonRptEdit::InitAllBookmarks()
{
	m_listWordBkmks.DeleteAll();
	map<CJSON*, CString>::iterator it;  
	for(it=m_JsonProssData.m_MapBkmks.begin(); it!=m_JsonProssData.m_MapBkmks.end(); it++)
	{
		CWordBkmk *pNew = new CWordBkmk();
		pNew->m_strID = it->second;
		m_listWordBkmks.AddTail(pNew);
	}
}

void CJsonRptEdit::ExitWord(BOOL bExitApp)
{	
	Close(m_bSave);
	m_xmlDlg.ExitWord();
}

//未见使用
long CJsonRptEdit::OpenWord(const CString &strGuideBookFile)
{	
	CString strType = GetReportSuffix();
	m_strReportTemplateFile = ChangeFilePostfix(strGuideBookFile, strType);	

	BOOL bTrue = TRUE;
	if (FindFile(m_strReportTemplateFile))
	{
		try
		{
			//打开试验报告文件
			bTrue = m_JsonProssData.OpenXmlFile(m_strReportTemplateFile);
		}
		catch (...)
		{
			bTrue = FALSE;
		}
	}

	return TRUE;
}
BOOL CJsonRptEdit::CheckChoosePoint()
{
	CJSON *cAttri = m_xmlDlg.GetSelJsonDPos();
	if(cAttri == NULL)	//未选中位置
		return FALSE;
	return TRUE;
}
CExBaseObject* CJsonRptEdit::AddBkmk(CRptData *pData, const CString &strAttrID, const CString &strDataProcess, const CString &strFillMode)
{
	CAutoSimpleLock oLock(m_oWordCriticSection);

	CRptBkmk* pBkmk = NULL;

	try
	{
		// 插入书签
		//判断选中位置是否存在标签
		CJSON *cAttri = (CJSON *)m_xmlDlg.GetSelJsonDPos();
		if(cAttri == NULL)
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
		m_JsonProssData.AddBkmk(cAttri, strBkmk);
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
void CJsonRptEdit::InsertBkmk(const CString &strBkmk)
{
	try
	{
		CJSON *cAttri = (CJSON *)m_xmlDlg.GetSelJsonDPos();
		if(cAttri == NULL)
			return ;

		m_JsonProssData.AddBkmk(cAttri, strBkmk);
	}
	catch (...)
	{
	}
}
CExBaseObject* CJsonRptEdit::BindBkmk(CRptData *pData, const CString &strAttrID, const CString &strDataProcess, const CString &strFillMode, const CString &strBkmk)
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
	CJSON *cAttri = m_xmlDlg.GetSelJsonDPos();
	if(cAttri == NULL)
		return NULL;

	{//删除旧标签
		CWordBkmk * pWordBkmk =(CWordBkmk *)m_listWordBkmks.FindByID(strOldBkmk);
		pBkmk = pWordBkmk->m_pBkmk;
		CExBaseList* pParent = (CExBaseList*)pBkmk->GetParent();
		pParent->DeleteByID(strOldBkmk);			//删除gbxml

		m_JsonProssData.Deletekmk(cAttri);		//删除报告
		m_listWordBkmks.DeleteByID(strOldBkmk);	//不用管删除的那个，只需保证同一个路径的个数一致
	}
	{//添加新标签
		strNewBkmk = CreateNewBkmk(pData);

		m_JsonProssData.AddBkmk(cAttri, strNewBkmk);
		m_xmlDlg.SetSelectBkmk(strNewBkmk);			//20230922 luozibing 设置最新的标签信息

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
CExBaseObject* CJsonRptEdit::AddArea(CGbItemBase *pItem, long nStart, long nEnd)
{
	//不支持区域标签
	return NULL;
}

CExBaseObject* CJsonRptEdit::AddArea(CExBaseList *pRptArea)
{
	//不支持区域标签
	return NULL;
}

//未见使用
long CJsonRptEdit::GetCurrPos()
{
	long nPos = 0;
	return nPos;
}

//未见使用
long CJsonRptEdit::InitPage(BOOL bHort)
{
	return 0;
}

long CJsonRptEdit::Save()
{
	m_pGuideBook->SaveXMLFile(m_strGuideBookFile);

	try
	{
		m_JsonProssData.SaveXmlFile(m_strReportTemplateFile);
	}
	catch(...)
	{
	}

	SetMidified(FALSE);

	return 0;
}

long CJsonRptEdit::SaveAs(const CString &strFile)
{
	CString strType = GetReportSuffix();
	CString strDocFile = ChangeFilePostfix(strFile, strType);

	//文件保存
	m_JsonProssData.SaveXmlFile(m_strReportTemplateFile);

	SetMidified(FALSE);
	m_strReportTemplateFile = strFile;

	return 0;
}

//未见使用
long CJsonRptEdit::CloseWord()
{
	return 0;
}

BOOL CJsonRptEdit::IsValidDoc()
{
	//return (m_doc != NULL);
	return TRUE;
}

void CJsonRptEdit::ClearBkmkText(CRptBkmk *pBkmk)
{
	try
	{
		DeleteBkmk(pBkmk->m_strID);		
	}
	catch(...)
	{
	}
}

CString CJsonRptEdit::InitCurrBkmk()
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

long CJsonRptEdit::GetAllSelBkmk(CExBaseList &oListWordBkmk)
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

BOOL CJsonRptEdit::CanAddArea()
{
	BOOL bCanAdd = FALSE;	//不支持区域标签
	return bCanAdd;
}

BOOL CJsonRptEdit::ReplaceBkmk(const CString &  strBkmkSrc, const CString &  strBkmkDest)
{
	try
	{
		CJSON *cAttri = m_xmlDlg.GetSelJsonDPos();
		if(cAttri == NULL)
			return FALSE;
		m_JsonProssData.Replacekmk(cAttri, strBkmkDest);
	}
	catch (...)
	{
	}

	SetMidified(TRUE);
	return TRUE;
}

BOOL CJsonRptEdit::UpdateBkmk(CRptBkmk *pRptBkmk)
{
	try
	{
	}
	catch (...)
	{
	}

	SetMidified(TRUE);
	return TRUE;
}

//未见使用
void CJsonRptEdit::InsertTitle(const CString &strTitle, long nTitleLevel)
{
}

//未见使用
BOOL CJsonRptEdit::ActiveWindow(const CString &strTitle)
{
	return true;
}

//未见使用
long CJsonRptEdit::GetBkmkPos(CRptBkmk *pBkmk, long &nBeginPos, long &nEndPos)
{
	nBeginPos = -1;
	nEndPos = -1;
	return 0;
}

//未见使用
long CJsonRptEdit::AdjustReport_DelArea(CRptArea *pArea)
{
	return 0;
}

CExBaseObject * CJsonRptEdit::ReLocateBkmk()
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

CWnd* CJsonRptEdit::AdjustSizeView()
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

void CJsonRptEdit::SetAppVisible(BOOL bVisible)
{
	if(m_xmlDlg.m_hWnd == NULL)
	{
		m_xmlDlg.ShowWindow(SW_SHOW);
	}
}

void CJsonRptEdit::SetDisplayStatusBar(BOOL bVisible)
{
}

//未见使用
void CJsonRptEdit::CopyApp(CRptEditInterface *pRptEditDest)
{
}
//未见使用
void CJsonRptEdit::rpt_RenameRptBkmks(CExBaseList *pList)
{
}
//未见使用
void CJsonRptEdit::InsertWordEdit(CRptEditInterface *pRptEdit, long nAddRptGroupTitle)
{
}

BOOL CJsonRptEdit::rpt_CanEnterRptBkmkBatchAdd(CExBaseObject *pItem)
{
	AfxMessageBox(_T("批量操作暂时取消！"), MB_OK | MB_ICONEXCLAMATION);
	return FALSE;//xml中没有表格，不具备批量插入条件
}

BOOL CJsonRptEdit::rpt_CanEnterRptBkmkBatchAddYc(CExBaseObject *pItem)
{
	AfxMessageBox(_T("批量操作暂时取消！"), MB_OK | MB_ICONEXCLAMATION);
	return FALSE;//xml中没有表格，不具备批量插入条件
}

BOOL CJsonRptEdit::rpt_GetRptBkmkBatchRowsCols(long &nRows, long &nCols)
{
	return FALSE;//xml中没有表格，不具备批量插入条件
}

void CJsonRptEdit::InsertBkmks(CExBaseList& oListCells, CExBaseList& oListBkmks)
{
	return ;//xml中没有表格，不具备批量插入条件
}

void CJsonRptEdit::GetBatchCellList_ROWITEM_COLDATA(CExBaseList &oListBatchCell,CRptBatchItemMaps *pItemMaps, CRptBatchDataMaps *pDataMaps, long nCols)
{
	return ;//xml中没有表格，不具备批量插入条件
}

void CJsonRptEdit::GetBatchCellList_ROWDATA_COLITEM(CExBaseList &oListBatchCell,CRptBatchItemMaps *pItemMaps, CRptBatchDataMaps *pDataMaps, long nRows)
{
	return ;//xml中没有表格，不具备批量插入条件
}

void CJsonRptEdit::GetBatchCellList_ROWREPEAT_COLDATA_ITEMROW(CExBaseList &oListBatchCell,CRptBatchItemMaps *pItemMaps, CRptBatchDataMaps *pDataMaps, long nRepeatCount, long nCols)
{
	return ;//xml中没有表格，不具备批量插入条件
}

long CJsonRptEdit::LocateBkmk(const CString &  strBkmk)
{
	DWORD hItem = m_JsonProssData.GetSelectBkmk(strBkmk, m_iFindIndex);
	m_xmlDlg.SetSelectBkmk(hItem,strBkmk);
	return 0;
}

long CJsonRptEdit::DeleteBkmk(const CString& strBkmk, BOOL bSelect)
{	
	long nRet = 0;

	CJSON *cAttri = m_xmlDlg.GetSelJsonDPos();
	if(cAttri == NULL)
		return nRet;

	if(m_JsonProssData.Deletekmk(cAttri))
	{
		nRet = 1;
	}
	SetMidified(TRUE);
	UpdateToFaceGrid();
	return nRet;
}
//20230616 luozibing 更新树形控件与表格
void CJsonRptEdit::UpdateToFaceTree()
{
	CJsonData * p = (CJsonData *)m_JsonProssData.GetHead();
	m_xmlDlg.SetShowDataJson(p);
}
void CJsonRptEdit::UpdateToFaceGrid()
{
	m_xmlDlg.UpdateGrid();
}

void CJsonRptEdit::AttachBookmarksAndRptBkmks()
{
	POS pos = m_listRptBkmks.GetHeadPosition();
	CRptBkmk *pRptBkmk = NULL;
	CWordBkmk *pBkmk = NULL;

	map<CString, int> mapBkmksCount;
	map<CString, int>::iterator it;  

	while (pos != NULL)
	{
		pRptBkmk = (CRptBkmk *)m_listRptBkmks.GetNext(pos);	

		//20231010 huangliang 非路径的标签不管
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
CWordBkmk *CJsonRptEdit::FindWorkList(const CString &strId, int iIndex)
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
CString CJsonRptEdit::CreateNewBkmk(CRptData *pData)
{
	return m_strSelectPath;
}