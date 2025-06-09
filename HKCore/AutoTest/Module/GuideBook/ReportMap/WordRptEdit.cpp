#include "StdAfx.h"
#include "WordRptEdit.h"
//#include "RptMapFile.h"
#include "ReportMap.h"
#include "RptBkmk.h"
#include "RptData.h"
#include "../../../../Module/Office/mso9.h"
#include "..\GuideBook.h"
#include "WordRptEditTools\RptBkmkBatchAddTool.h"

CWordRptEdit::CWordRptEdit(void):m_doc(NULL),m_WordApp(NULL)
{

}

CWordRptEdit::~CWordRptEdit(void)
{

}

long CWordRptEdit::OpenWord(const CString &strGuideBookFile)
{
	if (m_WordApp == NULL)
	{
		return 0;
	}

	m_strReportTemplateFile = ChangeFilePostfix(strGuideBookFile, _T("doc"));

	MSWord::Documents docs(m_WordApp.GetDocuments());

	if (docs == NULL)
	{
		return FALSE;
	}

	COleVariant vTrue((long)TRUE), vFalse((long)FALSE),
		covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	//关闭文档
	try
	{
		if (m_doc != NULL)
		{
			m_doc.Close(vFalse,covOptional,covOptional);
		}

		m_doc = NULL;
	}
	catch (...)
	{
		m_doc = NULL;

		TRACE(L"Close word doc error...");
	}

	COleVariant vRptFile(m_strReportTemplateFile);			
	//COleVariant covTrue((long)TRUE),covFalse((long)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	BOOL bTrue = TRUE;

	if (FindFile(m_strReportTemplateFile))
	{
		try
		{
			//打开试验报告文件
			m_doc = docs.Open(&vRptFile,covOptional,vFalse,vTrue,covOptional,covOptional,
				covOptional,covOptional,covOptional,covOptional,covOptional,vTrue);
		}
		catch (...)
		{
			bTrue = FALSE;
		}
	}

	return TRUE;
}

void CWordRptEdit::InitAllBookmarks()
{
	if (m_doc == NULL)
	{
		return;
	}

	MSWord::Bookmarks oBkmks = m_doc.GetBookmarks();
	MSWord::Bookmark  oBkmk = NULL;
	long nCount = oBkmks.GetCount();
	long nIndex = 1;
	m_listWordBkmks.DeleteAll();

	for (nIndex=1; nIndex<=nCount; nIndex++)
	{
		COleVariant index(nIndex);
		oBkmk = oBkmks.Item(&index);
		CWordBkmk *pNew = new CWordBkmk();
		pNew->m_strID = oBkmk.GetName();
		m_listWordBkmks.AddTail(pNew);
	}
}

long CWordRptEdit::LocateBkmk(const CString &  strBkmk)
{
	BOOL bFind = FALSE;
	MSWord::Bookmarks wordBookmarks;
	MSWord::Bookmark wordBookmark;

	try
	{
		if(m_doc == NULL)
			return FALSE;
		wordBookmarks = m_doc.GetBookmarks();		
		bFind = wordBookmarks.Exists(strBkmk);
		if (bFind)
		{
			COleVariant index(strBkmk);
			wordBookmark = wordBookmarks.Item(&index);
			wordBookmark.Select();
		}
	}
	catch (...)
	{
	}

	return 0;
}

CExBaseObject * CWordRptEdit::ReLocateBkmk()
{
	CRptBkmk* pBkmk = NULL;

	try
	{
		// 插入书签
		if(m_doc == NULL)
			return FALSE;
		COleVariant vOpt(DISP_E_PARAMNOTFOUND, VT_ERROR);
		MSWord::Bookmarks wordBookmarks = m_doc.GetBookmarks();
		MSWord::Bookmark wordBookmark;
		MSWord::Selection wordSelection = m_WordApp.GetSelection();
		MSWord::Range wordSelectionRange = wordSelection.GetRange();

		long nStart = wordSelectionRange.GetStart();
		long nID = wordSelectionRange.GetBookmarkID();
		if(nID != 0)
		{
			//查找是否有对应书签
			long nCount = wordBookmarks.GetCount();
			for (long nIndex=1; nIndex<nCount+1; nIndex++)
			{
				COleVariant index(nIndex);
				wordBookmark = wordBookmarks.Item(&index);
				long nTemp = wordBookmark.GetStart();

				if (nStart == nTemp)//找到此位置的书签
				{
					CString Name = wordBookmark.GetName();

					pBkmk = (CRptBkmk*)FindRptBkmk(Name);
					break;
				}
			}
		}
	}
	catch (...)
	{
	}

	return pBkmk;
}

long CWordRptEdit::DeleteBkmk(const CString& strBkmk, BOOL bSelect)
{	
	CString str = strBkmk;
	COleVariant index(str);
	MSWord::Bookmarks wordBookmarks = m_doc.GetBookmarks();
	MSWord::Bookmark wordBookmark;
	long nRet = 0;

	try
	{
		if (wordBookmarks.Exists(str))
		{
			wordBookmark = wordBookmarks.Item(&index);

			if (bSelect)
			{
				wordBookmark.Select();
			}

			wordBookmark.Delete();
			nRet = 1;
		}
	}
	catch(...)
	{
		TRACE0("Fail to Delete BookMark");
	}	

	SetMidified(TRUE);

	return nRet;
}

BOOL CWordRptEdit::GetBkmkRowCol(CRptBkmk *pBkmk, MSWord::Table &oTable, MSWord::Cells &oCells)
{
	if (pBkmk == NULL)
	{
		return FALSE;
	}

	if (oTable == NULL)
	{
		return FALSE;
	}

	if (pBkmk->m_strID.IsEmpty())
	{
		return FALSE;
	}

	MSWord::Bookmarks oBkmks = NULL;
	MSWord::Bookmark oBkmk = NULL;
	long nRow = 0, nCol = 0, nIndex=0;

	try
	{
		oBkmks = m_doc.GetBookmarks();

		if (!oBkmks.Exists(pBkmk->m_strID))
		{
			return FALSE;
		}

		COleVariant vIndex(pBkmk->m_strID);
		oBkmk = oBkmks.Item(&vIndex);
		//oBkmk.Select();
		MSWord::Range oRange = oBkmk.GetRange();
		oCells = oRange.GetCells();
		long nCount = oCells.GetCount();
		if (nCount>0)
		{
			MSWord::Cell oCel = oCells.Item(1);

			long nRowIndex = oCel.GetRowIndex();
			long nColIndex = oCel.GetColumnIndex();
		}
		MSWord::Tables oTables = oRange.GetTables();
		UINT nID_Bkmk = oRange.GetBookmarkID();

		if (oTables.GetCount() > 0)
		{
			oTable = oTables.Item(1); 
		}
	}
	catch(...)
	{

	}

	return TRUE;
}

CExBaseObject* CWordRptEdit::AddBkmk(CRptData *pData, const CString &strAttrID, const CString &strDataProcess, const CString &strFillMode)
{
	if(m_doc == NULL)
	{
		return FALSE;
	}

	CAutoSimpleLock oLock(m_oWordCriticSection);

	CRptBkmk* pBkmk = NULL;

	try
	{
		// 插入书签
		COleVariant vOpt(DISP_E_PARAMNOTFOUND, VT_ERROR);
		MSWord::Bookmarks wordBookmarks = m_doc.GetBookmarks();
		MSWord::Bookmark wordBookmark;
		MSWord::Selection wordSelection = m_WordApp.GetSelection();
		MSWord::Range wordSelectionRange = wordSelection.GetRange();

		long nStart = wordSelectionRange.GetStart();
		long nID = wordSelectionRange.GetBookmarkID();

		if(nID != 0)
		{
			//查找是否有对应书签
			long nCount = wordBookmarks.GetCount();
			for (long nIndex=1; nIndex<nCount+1; nIndex++)
			{
				COleVariant index(nIndex);
				wordBookmark = wordBookmarks.Item(&index);
				long nTemp = wordBookmark.GetStart();

				if (nStart == nTemp)//找到此位置的书签
				{
					CString Name = wordBookmark.GetName();

					if (FindRptBkmk(Name)!=NULL)//是有效书签
					{
						int nResult = MessageBox(NULL,/*L"当前位置有标签，确定替换"*/g_sLangTxt_HaveMarkSureReplace,g_sLangTxt_Message/*L"提示"*/,MB_YESNO);

						if(nResult == IDNO)
						{
							return NULL;
						}
						else//替换书签
						{
							long nCount = wordBookmarks.GetCount();
							for (long nIndex=1; nIndex<nCount+1; nIndex++)
							{
								COleVariant index(nIndex);
								wordBookmark = wordBookmarks.Item(&index);
								long nTemp = wordBookmark.GetStart();
								if (nStart == nTemp)
								{
									CString Name = wordBookmark.GetName();
									//如果要插入的书签数据与Data相同则返回
									if (pData->FindByID(Name) != NULL)
									{
										return NULL;
									}
									DeleteBkmk(Name);
									break;
								}
							}			
						}
					}
					else
					{
						wordBookmark.Delete();
					}
					
					break;
				}
			}
		}

		CString strBkmk = CreateNewBkmk(pData);
		//strBkmk.Format(_T("Bmk%s_%x"),GetUIDString(), m_dwMaxBkmkIndex++);
		wordBookmarks.Add(strBkmk, vOpt);
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

void CWordRptEdit::InsertBkmk(const CString &strBkmk)
{
	try
	{
		// 插入书签
		COleVariant vOpt(DISP_E_PARAMNOTFOUND, VT_ERROR);
		MSWord::Bookmarks wordBookmarks = m_doc.GetBookmarks();
		MSWord::Bookmark wordBookmark;
		MSWord::Selection wordSelection = m_WordApp.GetSelection();
		MSWord::Range wordSelectionRange = wordSelection.GetRange();
		wordBookmarks.Add(strBkmk, vOpt);

	}
	catch (...)
	{
	}
}

BOOL CWordRptEdit::ReplaceBkmk(const CString &  strBkmkSrc, const CString &  strBkmkDest)
{
	if(m_doc == NULL)
	{
		return FALSE;
	}

	CRptBkmk* pBkmk = NULL;

	try
	{
		DeleteBkmk(strBkmkSrc);
	
		// 插入书签
		COleVariant vOpt(DISP_E_PARAMNOTFOUND, VT_ERROR);
		MSWord::Bookmarks wordBookmarks = m_doc.GetBookmarks();
		MSWord::Bookmark wordBookmark;
		MSWord::Selection wordSelection = m_WordApp.GetSelection();
		MSWord::Range wordSelectionRange = wordSelection.GetRange();
		wordBookmarks.Add(strBkmkDest, vOpt);
	}
	catch (...)
	{
	}

	SetMidified(TRUE);
	return TRUE;
}

BOOL CWordRptEdit::UpdateBkmk(CRptBkmk *pRptBkmk)
{
	if(m_doc == NULL)
	{
		return FALSE;
	}

	CString strBkmk = pRptBkmk->m_strID;

	try
	{
		if (DeleteBkmk(strBkmk, TRUE) > 0)
		{
			long nPos = strBkmk.ReverseFind('_');

			if (nPos  > 0)
			{
				strBkmk = strBkmk.Left(nPos+1);
			}

			strBkmk.AppendFormat(_T("%d"), m_dwMaxBkmkIndex++);
			pRptBkmk->m_strID = strBkmk;

			// 插入书签
			COleVariant vOpt(DISP_E_PARAMNOTFOUND, VT_ERROR);
			MSWord::Bookmarks wordBookmarks = m_doc.GetBookmarks();
			MSWord::Bookmark wordBookmark;
			MSWord::Selection wordSelection = m_WordApp.GetSelection();
			MSWord::Range wordSelectionRange = wordSelection.GetRange();
			wordBookmarks.Add(strBkmk, vOpt);
		}
	}
	catch (...)
	{
	}

	SetMidified(TRUE);
	return TRUE;
}

CString CWordRptEdit::InitCurrBkmk()
{
	if(m_doc == NULL)
	{
		m_pCurrBkmk = NULL;
		return _T("");
	}

	CAutoSimpleLock oLock(m_oWordCriticSection);
	CString strBkmk;
	BOOL bCanAdd = TRUE;

	try
	{
		// 插入书签
		COleVariant vOpt(DISP_E_PARAMNOTFOUND, VT_ERROR);
		MSWord::Bookmarks wordBookmarks = m_doc.GetBookmarks();
		MSWord::Bookmark wordBookmark;
		MSWord::Selection wordSelection = m_WordApp.GetSelection();
		MSWord::Range wordSelectionRange = wordSelection.GetRange();

		long nStart = wordSelectionRange.GetStart();
		long nEnd = wordSelectionRange.GetEnd();

		if (nEnd > nStart)
		{
			m_pCurrBkmk = NULL;
		}
		else
		{
			wordBookmarks = wordSelection.GetBookmarks();

			long nCount = wordBookmarks.GetCount();
			long nIndex = 0;
			m_pCurrBkmk = NULL;

			for (nIndex=1; nIndex<=nCount; nIndex++)
			{
				COleVariant vIndex(nIndex);
				wordBookmark = wordBookmarks.Item(&vIndex);
				long nStart2 = wordBookmark.GetStart();
				long nEnd2 = wordBookmark.GetEnd();

				if (nStart2 == nEnd2 && nStart2 == nStart)
				{
					strBkmk = wordBookmark.GetName();
					m_pCurrBkmk = (CWordBkmk*)m_listWordBkmks.FindByID((strBkmk));
					break;
				}
			}
//2011.8.22修改，一个大范围书签中，包含一个小范围书签，导致不正确
// 			if (nCount == 1)
// 			{
// 				COleVariant vIndex((long)1);
// 				wordBookmark = wordBookmarks.Item(&vIndex);
// 				CString bstrID = wordBookmark.GetName();
// 				m_pCurrBkmk = (CBkmk*)m_listBkmks.FindByID((bstrID));
// 			}
// 			else
// 			{
// 				m_pCurrBkmk = NULL;
// 			}
		}
	}
	catch(...)
	{
		m_pCurrBkmk = NULL;
	}

	if (m_pCurrBkmk != NULL)
	{
		MSWord::Table oTable = NULL;
		MSWord::Cells oCells = NULL;

		GetBkmkRowCol(m_pCurrBkmk->m_pBkmk, oTable, oCells);
	}

	return strBkmk;
}

long CWordRptEdit::GetAllSelBkmk(CExBaseList &oListWordBkmk)
{
	if(m_doc == NULL)
	{
		return 0;
	}

	CAutoSimpleLock oLock(m_oWordCriticSection);
	CString strBkmk;
	BOOL bCanAdd = TRUE;

	try
	{
		// 插入书签
		COleVariant vOpt(DISP_E_PARAMNOTFOUND, VT_ERROR);
		MSWord::Bookmarks wordBookmarks;;
		MSWord::Bookmark wordBookmark;
		MSWord::Selection wordSelection = m_WordApp.GetSelection();
		MSWord::Range wordSelectionRange = wordSelection.GetRange();

// 		MSWord::Cells oCells = wordSelection.GetCells();
// 		long nCells = oCells.GetCount();

		wordBookmarks = wordSelection.GetBookmarks();
		long nCount = wordBookmarks.GetCount();
		MSWord::Cells oCells = wordSelection.GetCells();
		MSWord::Cell oCell;
		long nCells = oCells.GetCount();
		long nCell = 0;
		long nIndex = 0;

		for (nCell=1; nCell<=nCells; nCell++)
		{
			oCell = oCells.Item(nCell);
			wordSelectionRange = oCell.GetRange();
			wordSelectionRange.Select();
			long nStart, nEnd;
			nStart = wordSelectionRange.GetStart();
			nEnd = wordSelectionRange.GetEnd()-1;
			wordSelection.SetStart(nStart);
			wordSelection.SetEnd(nEnd);
			wordSelection.Select();
			wordBookmarks = wordSelection.GetBookmarks();
			nCount = wordBookmarks.GetCount();

			m_pCurrBkmk = NULL;

			for (nIndex=1; nIndex<=nCount; nIndex++)
			{
				COleVariant vIndex(nIndex);
				wordBookmark = wordBookmarks.Item(&vIndex);
				long nStart2 = wordBookmark.GetStart();
				long nEnd2 = wordBookmark.GetEnd();

				if (nStart2 == nEnd2)
				{
					strBkmk = wordBookmark.GetName();
					CWordBkmk *pFind = (CWordBkmk*)m_listWordBkmks.FindByID((strBkmk));

					if (pFind != NULL)
					{
						oListWordBkmk.AddTail(pFind);
					}
				}
			}
		}
	}
	catch(...)
	{
	}

	return oListWordBkmk.GetCount();
}
// 
// long CWordRptEdit::GetAllSelBkmk(CExBaseList &oListWordBkmk)
// {
// 	if(m_doc == NULL)
// 	{
// 		return 0;
// 	}
// 
// 	CAutoSimpleLock oLock(m_oWordCriticSection);
// 	CString strBkmk;
// 	BOOL bCanAdd = TRUE;
// 
// 	try
// 	{
// 		// 插入书签
// 		COleVariant vOpt(DISP_E_PARAMNOTFOUND, VT_ERROR);
// 		MSWord::Bookmarks wordBookmarks;;
// 		MSWord::Bookmark wordBookmark;
// 		MSWord::Selection wordSelection = m_WordApp.GetSelection();
// 		MSWord::Range wordSelectionRange = wordSelection.GetRange();
// 
// 		wordBookmarks = wordSelectionRange.GetBookmarks();
// 
// 		long nCount = wordBookmarks.GetCount();
// 		long nIndex = 0;
// 		m_pCurrBkmk = NULL;
// 
// 		for (nIndex=1; nIndex<=nCount; nIndex++)
// 		{
// 			COleVariant vIndex(nIndex);
// 			wordBookmark = wordBookmarks.Item(&vIndex);
// 			long nStart2 = wordBookmark.GetStart();
// 			long nEnd2 = wordBookmark.GetEnd();
// 
// 			if (nStart2 == nEnd2)
// 			{
// 				strBkmk = wordBookmark.GetName();
// 				CWordBkmk *pFind = (CWordBkmk*)m_listWordBkmks.FindByID((strBkmk));
// 
// 				if (pFind != NULL)
// 				{
// 					oListWordBkmk.AddTail(pFind);
// 				}
// 			}
// 		}
// 	}
// 	catch(...)
// 	{
// 		
// 	}
// 
// 	return oListWordBkmk.GetCount();
// }
BOOL CWordRptEdit::CanAddArea()
{
	if(m_doc == NULL)
	{
		return FALSE;
	}

	BOOL bCanAdd = TRUE;

	try
	{
		// 插入书签
		COleVariant vOpt(DISP_E_PARAMNOTFOUND, VT_ERROR);
		MSWord::Bookmarks wordBookmarks = m_doc.GetBookmarks();
		MSWord::Bookmark wordBookmark;
		MSWord::Selection wordSelection = m_WordApp.GetSelection();
		MSWord::Range wordSelectionRange = wordSelection.GetRange();

		long nStart = wordSelectionRange.GetStart();
		long nEnd = wordSelectionRange.GetEnd();

		if (nEnd <= nStart+1)
		{
			bCanAdd = FALSE;
		}
	}
	catch(...)
	{
		bCanAdd = FALSE;
	}

	return bCanAdd;
}

long CWordRptEdit::GetCurrPos()
{
	if(m_doc == NULL)
	{
		return 0;
	}

	long nPos = 0;

	try
	{
		MSWord::Bookmarks wordBookmarks = m_doc.GetBookmarks();
		MSWord::Bookmark wordBookmark;
		MSWord::Selection wordSelection = m_WordApp.GetSelection();
		MSWord::Range wordSelectionRange = wordSelection.GetRange();

		long nStart = wordSelectionRange.GetStart();
		long nEnd = wordSelectionRange.GetEnd();

		ASSERT (nStart == nEnd);
		nPos = nEnd;
	}
	catch(...)
	{

	}

	return nPos;
}

CExBaseObject* CWordRptEdit::AddArea(CGbItemBase *pItem, long nStart, long nEnd)
{
	if(m_doc == NULL)
	{
		return NULL;
	}

	CReportMap *pRptMap = pItem->GetReportMap();
	ASSERT (pRptMap != NULL);
	
	if (pRptMap->m_pArea != NULL)
	{
		return pRptMap->m_pArea;
	}

	CRptArea *pArea = pRptMap->AddArea();

	CRptBkmk* pBkmk = NULL;

	try
	{
		COleVariant vOpt(DISP_E_PARAMNOTFOUND, VT_ERROR);
		MSWord::Bookmarks wordBookmarks = m_doc.GetBookmarks();
		MSWord::Bookmark wordBookmark;
		MSWord::Selection wordSelection = m_WordApp.GetSelection();

		pArea->m_pBkmkBegin = InsertNewAreaBkmk(m_dwMaxBkmkIndex, pArea, wordBookmarks, wordSelection, nStart);
		pArea->m_pBkmkEnd = InsertNewAreaBkmk(m_dwMaxBkmkIndex, pArea, wordBookmarks, wordSelection, nEnd);

		SetRptItemBkmkState(pArea);
	}
	catch (...)
	{
	}

	return pArea;
}

CExBaseObject* CWordRptEdit::AddArea(CExBaseList *pRptArea)
{
	if(m_doc == NULL)
	{
		return FALSE;
	}

	CRptBkmk* pBkmk = NULL;

	try
	{
		// 插入书签
		COleVariant vOpt(DISP_E_PARAMNOTFOUND, VT_ERROR);
		MSWord::Bookmarks wordBookmarks = m_doc.GetBookmarks();
		MSWord::Bookmark wordBookmark;
		MSWord::Selection wordSelection = m_WordApp.GetSelection();
		MSWord::Range wordSelectionRange = wordSelection.GetRange();

		long nStart = wordSelectionRange.GetStart();
		long nEnd = wordSelectionRange.GetEnd();
		long nID = wordSelectionRange.GetBookmarkID();

		CRptArea *pArea = (CRptArea*)pRptArea;
		pArea->m_pBkmkBegin = InsertNewAreaBkmk(m_dwMaxBkmkIndex, pRptArea, wordBookmarks, wordSelection, nStart);
		pArea->m_pBkmkEnd = InsertNewAreaBkmk(m_dwMaxBkmkIndex, pRptArea, wordBookmarks, wordSelection, nEnd);

		SetRptItemBkmkState(pArea);
	}
	catch (...)
	{
	}
	
	SetMidified(TRUE);

	return pBkmk;
}

CRptBkmk* CWordRptEdit::InsertNewAreaBkmk(DWORD &dwBkmkIndex, CExBaseList *pRptArea, MSWord::Bookmarks wordBookmarks, MSWord::Selection wordSelection, long nPos)
{
	CRptBkmk *pBkmk = new CRptBkmk();
	((CRptArea*)pRptArea)->InitAreaBkmkID(pBkmk, dwBkmkIndex);
	dwBkmkIndex++;
	pRptArea->AddTail(pBkmk);
	pBkmk->SetParent(pRptArea);

	COleVariant vOpt(DISP_E_PARAMNOTFOUND, VT_ERROR);
	wordSelection.SetStart(nPos);
	wordSelection.SetEnd(nPos);
	wordSelection.Select();
	wordBookmarks.Add(pBkmk->m_strID, vOpt);

	CWordBkmk *pNew = AddNewWordBookmarkToList(pBkmk->m_strID);
	pBkmk->m_pBkmk = pNew;
	pNew->m_pBkmk = pBkmk;

	return pBkmk;
}

//目前不使用这种方式创建、打开word，因为这种方式下当word已打开时会弹出**已打开对话框。
BOOL CWordRptEdit::CreateWordApplication(BOOL bVisible)
{
	//创建对象
	COleVariant covTrue((long)TRUE),covFalse((long)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	try
	{
		if (m_WordApp == NULL)
		{
			if (!m_WordApp.CreateDispatch(_T("Word.Application")))
			{
				AfxMessageBox(/*L"没有安装Word"*/g_sLangTxt_NoWord);
				return FALSE;
			}

			m_WordApp.SetVisible(bVisible);  //This shows the application.
		}
	}
	catch (...)
	{
	}

	if(!OpenWordReportFile(m_strReportTemplateFile))
	{
		AfxMessageBox(/*L"打开文档失败！"*/g_sLangTxt_OpenDocFail);
		try
		{
		}
		catch (...)
		{
		}
	}
	else
	{
		MSWord::Window wnd = m_WordApp.GetActiveWindow();
		MSWord::View v = wnd.GetView();
		v.SetShowBookmarks(TRUE);
	}

	return TRUE;
}

BOOL CWordRptEdit::OpenWordReportFile(const CString &strRptFile)
{
	if (m_WordApp == NULL)
	{
		return FALSE;
	}

	MSWord::Documents docs(m_WordApp.GetDocuments());

	if (docs == NULL)
	{
		return FALSE;
	}

	COleVariant vRptFile(strRptFile);			
	COleVariant covTrue((long)TRUE),covFalse((long)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	BOOL bTrue = TRUE;
	if (FindFile(m_strReportTemplateFile))
	{

		try
		{
			//打开试验报告文件
			m_doc = docs.Open(&vRptFile,covOptional,covFalse,covTrue,covOptional,covOptional,
				covOptional,covOptional,covOptional,covOptional,covOptional,covTrue);
		}
		catch (...)
		{
			bTrue = FALSE;
		}
	}
	else
	{
		try
		{
			CComVariant Template(_T("")); 
			CComVariant NewTemplate(false),DocumentType(0),Visible;
			m_doc = docs.Add(&Template,&NewTemplate,&DocumentType,&Visible);
		}
		catch(...)
		{
			bTrue = FALSE;
		}
	}

	MSO9::_CommandBars cmdbars;
	cmdbars = m_WordApp.GetCommandBars();
	//HideCommandBar(cmdbars);
	return bTrue;
}


BOOL CWordRptEdit::NewWordReportFile()
{
	if (m_WordApp == NULL)
	{
		return FALSE;
	}

	MSWord::Documents docs(m_WordApp.GetDocuments());

	if (docs == NULL)
	{
		return FALSE;
	}

	COleVariant covTrue((long)TRUE),covFalse((long)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	m_WordApp.SetVisible(TRUE);
	BOOL bTrue = TRUE;
	try
	{
		CComVariant Template(_T("")); 
		CComVariant NewTemplate(false),DocumentType(0),Visible;
		m_doc = docs.Add(&Template,&NewTemplate,&DocumentType,&Visible);
	}
	catch(...)
	{
		bTrue = FALSE;
	}

	MSO9::_CommandBars cmdbars;
	cmdbars = m_WordApp.GetCommandBars();
	//HideCommandBar(cmdbars);
	return bTrue;
}

void  CWordRptEdit::HideCommandBar(MSO9::_CommandBars cmdBars )
{
	try
	{
		long nCount = cmdBars.GetCount();
		long nIndex = 1;
		for(nIndex=1;nIndex<=nCount;nIndex++)
		{
			MSO9::CommandBar cmdbar = cmdBars.GetItem(COleVariant(nIndex));

			if (cmdbar.GetEnabled() && cmdbar.GetVisible())
			{
				cmdbar.SetEnabled(FALSE);
			}
		}
	}
	catch (...)
	{

	}
}

long CWordRptEdit::InitPage(BOOL bHort)
{
	try
	{
		long nValue = bHort;
		MSWord::PageSetup oPageSetup = m_doc.GetPageSetup();
		oPageSetup.SetOrientation(nValue);
	}
	catch (...)
	{
		
	}

	return 0;
}

long CWordRptEdit::Save()
{
	//Map文件保存
//	if (!HasModified())
	{
		m_pGuideBook->SaveXMLFile(m_strGuideBookFile);
	}

	try
	{
		//Doc文件保存
		COleVariant vOpt(DISP_E_PARAMNOTFOUND, VT_ERROR);  	

		m_doc.SaveAs(COleVariant(m_strReportTemplateFile), vOpt, vOpt, vOpt,
			vOpt, vOpt, vOpt, vOpt, vOpt, vOpt, vOpt);
	}
	catch(...)
	{
	}

	SetMidified(FALSE);

	return 0;
}

long CWordRptEdit::SaveAs(const CString &strFile)
{
	CString strDocFile = ChangeFilePostfix(strFile, _T("doc"));

	//Doc文件保存
	COleVariant vOpt(DISP_E_PARAMNOTFOUND, VT_ERROR);  	

	m_doc.SaveAs(COleVariant(strDocFile), vOpt, vOpt, vOpt,
		vOpt, vOpt, vOpt, vOpt, vOpt, vOpt, vOpt);

	SetMidified(FALSE);
	m_strReportTemplateFile = strFile;

	return 0;
}

long CWordRptEdit::CloseWord()
{
	COleVariant vTrue((long)TRUE), vFalse((long)FALSE),
		covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	try
	{
		if (m_doc != NULL)
		{
			m_doc.Close(vFalse,covOptional,covOptional);
		}

		m_doc = NULL;
	}
	catch (...)
	{
		m_doc = NULL;

		TRACE(L"Close word doc error...");
	}

	return 0;
}

BOOL CWordRptEdit::IsValidDoc()
{
	return (m_doc != NULL);
}

void CWordRptEdit::ClearBkmkText(CRptBkmk *pBkmk)
{
	try
	{
		MSWord::Selection sel;
		MSWord::Bookmarks bookmarks;
		MSWord::Bookmark bookmark;

		MSWord::Range  range = NULL;
		MSWord::Paragraphs  paragraphs = NULL;
		MSWord::Paragraph paragraph = NULL;
		MSWord::Range rangeParagraph = NULL;
		long lRangeStart = 0;
		long lRangeEnd = 0;
		long lRangeStart2 = 0;
		long lRangeEnd2 = 0;
		long lEndTemp = 0;

		sel =  m_WordApp.GetSelection();
		bookmarks = m_doc.GetBookmarks();

		if(!pBkmk->m_strID.IsEmpty() && bookmarks.Exists(pBkmk->m_strID))
		{
			COleVariant vIndex(pBkmk->m_strID);
			bookmark = bookmarks.Item(&vIndex);
			bookmark.Select();

			range = bookmark.GetRange();
			paragraphs = range.GetParagraphs();
			paragraph = paragraphs.GetFirst();
			rangeParagraph = paragraph.GetRange();
			lRangeStart2 = rangeParagraph.GetStart();
			lRangeEnd2 = rangeParagraph.GetEnd();
			lEndTemp = lRangeEnd2 - 1;
			if (lRangeStart2 <= lEndTemp)
				lRangeEnd2 = lEndTemp;

			sel.SetStart(lRangeStart2);
			sel.SetEnd(lRangeEnd2);

			sel.SetText(_bstr_t(_T("")));
		}
	}
	catch(...)
	{
	}
}

void CWordRptEdit::ExitWord(BOOL bExitApp)
{	
	COleVariant vTrue((short)TRUE), vFalse((short)FALSE),
		vOpt((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	try
	{
		if (m_WordApp != NULL)
		{
			MSWord::Window wnd = m_WordApp.GetActiveWindow();
			MSWord::View v = wnd.GetView();
			v.SetShowBookmarks(TRUE);
		}
	}
	catch (...)
	{
		
	}

	if (m_doc!=NULL)
	{
		Close(m_bSave);

		try
		{
			if (m_doc != NULL)
			{
				m_doc.Close(vFalse,vOpt,vOpt);
			}

			m_doc = NULL;
		}
		catch (...)
		{
			m_doc = NULL;

			TRACE(L"Close word doc error...");
		}
	}

	try
	{
		m_doc = NULL;

		if (m_WordApp != NULL && bExitApp)
		{
			m_WordApp.Quit(vFalse,vOpt,vOpt);
			m_WordApp = NULL;
		}
	}
	catch (...) 
	{
	}

}

BOOL CWordRptEdit::ActiveWindow(const CString &strTitle)
{
	return wordrpt_ActiveWindow(m_WordApp, strTitle);
// 	BOOL bTrue = FALSE;
// 
// 	try
// 	{
// 		MSWord::Windows oWindows = m_WordApp.GetWindows();
// 		COleVariant oIndex;
// 
// 		long nIndex = 1;
// 		long nCount = oWindows.GetCount();
// 
// 		for (nIndex=1; nIndex<=nCount; nIndex++)
// 		{
// 			oIndex = nIndex;
// 			MSWord::Window oWindow = oWindows.Item(&oIndex);
// 			CString strCaption = oWindow.GetCaption();
// 
// 			if (strCaption.Find(strTitle) >= 0)
// 			{
// 				oWindow.Activate();
// 				bTrue = TRUE;
// 				break;
// 			}
// 		}
// 	}
// 	catch (...)
// 	{
// 		
// 	}
// 
// 	return bTrue;
}

void CWordRptEdit::InsertTitle(const CString &strTitle, long nTitleLevel)
{
	MSWord::Paragraphs wordParagraphs = m_doc.GetParagraphs();
	long nCount = wordParagraphs.GetCount();
	CString strStyle;
	strStyle.Format(_T("标题 %d"), nTitleLevel);
	VARIANT varStyle;
	MSWord::Selection wordSelection;
	MSWord::Range wordRange;
	MSWord::Paragraph wordParagraph;
	BOOL bPasteFormat = FALSE;

	for (long i = 1; i <= nCount; i++)
	{
		wordParagraph = wordParagraphs.Item(i);   
		varStyle = wordParagraph.GetStyle();
		CString strStyle2 = VariantToString(varStyle);

		if (strStyle2.Find(_T("标题")) >= 0)
		{
			int j = 0;
		}

		if (strStyle2 == strStyle)
		{
			wordRange = wordParagraph.GetRange();
			wordRange.Select();
			wordSelection = m_WordApp.GetSelection();
			wordSelection.CopyFormat();
			bPasteFormat = TRUE;
			break;
		}
	}

	wordrpt_InsertTitle(m_WordApp, m_doc,m_strReportTemplateFile, strTitle, nTitleLevel, bPasteFormat);
// 	COleVariant vTrue((short)TRUE), vFalse((short)FALSE),
// 		vOpt((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
// 	COleVariant vUnit((long)MSWord::wdStory);
// 	MSWord::Selection wordSelection = m_WordApp.GetSelection();
// 
// 	CString strFileTitle = GetWordFileTitle();
// 
// 	if (!ActiveWindow(strFileTitle))
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, /*_T("插入标题【%s】失败")*/g_sLangTxt_InsertTitleFail, strTitle);
// 		return ;
// 	}
// 
// 	wordSelection = m_WordApp.GetSelection();
// 	wordSelection.EndKey(&vUnit, &vOpt);
// 	wordSelection.TypeParagraph();
// 
// 	if (nTitleLevel > 0)
// 	{
// 		wordSelection.TypeText(strTitle);
// 		MSWord::Styles oStyles = m_doc.GetStyles();
// 		CString strStyle;
// 		strStyle.Format(/*_T("标题 %d")*/g_sLangTxt_Title, nTitleLevel);
// 		COleVariant vStyleID = strStyle;
// 		//COleVariant vStyle = oStyles.Item(vStyleID);
// 		wordSelection.SetStyle(vStyleID);
// 	}
// 	else
// 	{
// 		MSWord::_Font font = wordSelection.GetFont();
// 		float fSize = font.GetSize();
// 		font.SetBold(TRUE);
// 		font.SetSize(16);
// 		wordSelection.TypeText(strTitle);
// 		font.SetSize(fSize);
// 		font.SetBold(FALSE);
// 	}
// 
// 	wordSelection.TypeParagraph();
}

void CWordRptEdit::InsertWordEdit(CRptEditInterface *pRptEdit, long nAddRptGroupTitle)
{
	CWordRptEdit *pWordEdit = (CWordRptEdit*)pRptEdit;
	wordrpt_InsertWordEdit(m_WordApp, m_doc, pWordEdit->m_doc,m_strReportTemplateFile, pWordEdit->m_strReportTemplateFile, nAddRptGroupTitle);
}

BOOL CWordRptEdit::rpt_CanEnterRptBkmkBatchAdd(CExBaseObject *pItem)
{
	MSWord::Selection wordSelection = m_WordApp.GetSelection();

	MSWord::Columns oCols = NULL;
	MSWord::Column oCol = NULL;
	MSWord::Paragraphs oParagraphs = NULL;
	MSWord::Paragraph oParagraph = NULL;

	try
	{
		oCols = wordSelection.GetColumns();
	}
	catch (...)
	{
		AfxMessageBox(g_sLangTxt_SelNoArea/*_T("没有选择表格区域！")*/, MB_OK | MB_ICONEXCLAMATION);
	}

	if (oCols == NULL)
	{
		return FALSE;
	}

	long nCols = oCols.GetCount();
	long nRows = 0;

	if (nCols == 0)
	{
		AfxMessageBox(g_sLangTxt_SelNoArea/*_T("没有选择表格区域！")*/, MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	MSWord::Cells oCells = wordSelection.GetCells();
	oParagraphs = wordSelection.GetParagraphs();
	long nCells = oCells.GetCount();
	long nParagraphs = oCells.GetCount();

	if (nCells < 2)
	{
		AfxMessageBox(g_sLangTxt_SelOnlyOneRowCol/*_T("选择表格区域只有一行一列，不具备批量插入条件！")*/, MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	nRows = nCells / nCols;
	long nCol = 1;
	BOOL bCan = TRUE;

	if (nRows * nCols != nCells)
	{
		AfxMessageBox(g_sLangTxt_ColRowsNotSame
			/*_T("选择表格区域每列的行列数不相同，不具备批量插入条件！")*/, MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	if (pItem == NULL)
	{
		AfxMessageBox(g_sLangTxt_SelNoItem
			/*_T("没有选择测试项目！")*/, MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	CExBaseList *pItems = rpt_GetItems(pItem);
	POS pos = NULL;
	CMacroTest *pMacroTest = NULL;
	CMacroTest *pCurr = NULL;
	CString strMsg;
	pos = pItems->GetHeadPosition();

	while (pos != NULL)
	{
		pItem = (CExBaseObject *)pItems->GetNext(pos);

		if (pItem->GetClassID() == GBCLASSID_MACROTEST)
		{
			if (pMacroTest == NULL)
			{
				pMacroTest = (CMacroTest*)pItem;
			}
			else
			{
				pCurr = (CMacroTest *)pItem;

				if (pCurr->m_nRepeatTimes != pMacroTest->m_nRepeatTimes)
				{
					bCan = FALSE;
					strMsg.Format(g_sLangTxt_RepeatTimeNotSame
						/*_T("【%s】的重复次数%d与【%s】的重复次数%d不一致!")*/
						, pMacroTest->m_strName, pMacroTest->m_nRepeatTimes, pCurr->m_strName, pCurr->m_nRepeatTimes);
					break;
				}

				if (pMacroTest->GetMacroTestPara()->GetMacroID() != pCurr->GetMacroTestPara()->GetMacroID())
				{
					bCan = FALSE;
					strMsg.Format(g_sLangTxt_MacroTestNotSame
						/*_T("【%s】与【%s】的测试功能不一致!")*/
						, pMacroTest->m_strName, pCurr->m_strName);
					break;
				}
			}
		}
	}

	if (pMacroTest == NULL)
	{
		strMsg.Format(g_sLangTxt_HasNoMacroTest
			/*_T("【%s】下没有电气量测试功能")*/, pItems->m_strName);
		bCan = FALSE;
	}

	if (!bCan)
	{
		AfxMessageBox(strMsg, MB_OK | MB_ICONEXCLAMATION);
		return bCan;
	}

	return bCan;
}

BOOL CWordRptEdit::rpt_CanEnterRptBkmkBatchAddYc(CExBaseObject *pItem)
{
	MSWord::Selection wordSelection = m_WordApp.GetSelection();

	MSWord::Columns oCols = NULL;
	MSWord::Column oCol = NULL;
	MSWord::Paragraphs oParagraphs = NULL;
	MSWord::Paragraph oParagraph = NULL;

	try
	{
		oCols = wordSelection.GetColumns();
	}
	catch (...)
	{
		AfxMessageBox(g_sLangTxt_SelNoArea/*_T("没有选择表格区域！")*/, MB_OK | MB_ICONEXCLAMATION);
	}

	if (oCols == NULL)
	{
		return FALSE;
	}

	long nCols = oCols.GetCount();
	long nRows = 0;

	if (nCols == 0)
	{
		AfxMessageBox(g_sLangTxt_SelNoArea/*_T("没有选择表格区域！")*/, MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	MSWord::Cells oCells = wordSelection.GetCells();
	oParagraphs = wordSelection.GetParagraphs();
	long nCells = oCells.GetCount();
	long nParagraphs = oCells.GetCount();

	if (nCells < 2)
	{
		AfxMessageBox(g_sLangTxt_SelOnlyOneRowCol/*_T("选择表格区域只有一行一列，不具备批量插入条件！")*/, MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	nRows = nCells / nCols;
	long nCol = 1;
	BOOL bCan = TRUE;

	if (nRows * nCols != nCells)
	{
		AfxMessageBox(g_sLangTxt_ColRowsNotSame
			/*_T("选择表格区域每列的行列数不相同，不具备批量插入条件！")*/, MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	if (pItem == NULL)
	{
		AfxMessageBox(g_sLangTxt_SelNoItem
			/*_T("没有选择测试项目！")*/, MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	POS pos = NULL;
	CMacroTest *pMacroTest = NULL;
	CMacroTest *pCurr = NULL;
	CString strMsg;

	CExBaseList *pItemsSel = NULL;

	if (pItem->GetClassID() == GBCLASSID_ITEMS)
	{
		pItemsSel = (CExBaseList *)pItem;
	}

	if (pItemsSel == NULL)
	{
		AfxMessageBox(g_sLangTxt_MustSelYcItem
			/*_T("请选择包含遥测项目的项目分类！")*/, MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	CExBaseList listMacroTest;
	rpt_GetAllMacroTestItemsEx(pItemsSel, &listMacroTest);
	pos = listMacroTest.GetHeadPosition();

	while (pos != NULL)
	{
		pItem = (CExBaseObject *)listMacroTest.GetNext(pos);

		if (pItem->GetClassID() == GBCLASSID_MACROTEST)
		{
			if (pMacroTest == NULL)
			{
				pMacroTest = (CMacroTest*)pItem;
			}
			else
			{
				pCurr = (CMacroTest *)pItem;

				if (pCurr->m_nRepeatTimes != pMacroTest->m_nRepeatTimes)
				{
					bCan = FALSE;
					strMsg.Format(g_sLangTxt_RepeatTimeNotSame
						/*_T("【%s】的重复次数%d与【%s】的重复次数%d不一致!")*/
						, pMacroTest->m_strName, pMacroTest->m_nRepeatTimes, pCurr->m_strName, pCurr->m_nRepeatTimes);
					break;
				}

				if (pMacroTest->GetMacroTestPara()->GetMacroID() != pCurr->GetMacroTestPara()->GetMacroID())
				{
					bCan = FALSE;
					strMsg.Format(g_sLangTxt_MacroTestNotSame
						/*_T("【%s】与【%s】的测试功能不一致!")*/
						, pMacroTest->m_strName, pCurr->m_strName);
					break;
				}
			}
		}
	}

	listMacroTest.RemoveAll();

	if (pMacroTest == NULL)
	{
		strMsg.Format(g_sLangTxt_HasNoYcItem
			/*_T("【%s】下没有遥测测试电气量测试功能")*/, pItemsSel->m_strName);
		bCan = FALSE;
	}

	if (!bCan)
	{
		AfxMessageBox(strMsg, MB_OK | MB_ICONEXCLAMATION);
		return bCan;
	}

	return bCan;
}

BOOL CWordRptEdit::rpt_GetRptBkmkBatchRowsCols(long &nRows, long &nCols)
{
	MSWord::Selection wordSelection = m_WordApp.GetSelection();

	MSWord::Cells oCells = NULL;
	MSWord::Columns oCols = NULL;

	try
	{
		oCells = wordSelection.GetCells();
	}
	catch (...)
	{
	}

	if (oCells == NULL)
	{
		return FALSE;
	}

	try
	{
		oCols = wordSelection.GetColumns();
	}
	catch (...)
	{
	}

	if (oCols == NULL)
	{
		return FALSE;
	}

	nCols = oCols.GetCount();
	long nCells = oCells.GetCount();
	nRows = nCells / nCols;

	return TRUE;
}

void CWordRptEdit::InsertBkmks(CExBaseList& oListCells, CExBaseList& oListBkmks)
{
	POS pos = oListCells.GetHeadPosition();
	CRptBkmkBatchCell_Word *pCell = NULL;
	CRptBkmk* pObjBkmk = NULL;
	MSWord::Range oRng = NULL;
	MSWord::Selection oSelection = m_WordApp.GetSelection();
	while (pos != NULL)
	{
		pCell = (CRptBkmkBatchCell_Word *)oListCells.GetNext(pos);
		oRng = pCell->m_oCell.GetRange();
		long nStart = oRng.GetStart();
		long nEnd = oRng.GetEnd();
		oSelection.SetStart(nStart);
		oSelection.SetEnd(nStart);
		oSelection.Select();
		pObjBkmk = InsertCellBkmk((CGbItemBase*)pCell->m_pGbItem, pCell->m_pData, pCell->m_strDataAttr, pCell->m_strPrecision, pCell->m_nRepeatIndex, 
			pCell->m_strDataProcess, _T(""));
		oListBkmks.AddTail(pObjBkmk);
	}

}

void CWordRptEdit::GetBatchCellList_ROWITEM_COLDATA(CExBaseList &oListBatchCell,CRptBatchItemMaps *pItemMaps, CRptBatchDataMaps *pDataMaps, long nCols)
{
	long nRow = 0;
	long nCol = 0;
	POS posItem = pItemMaps->GetHeadPosition();
	POS posData = pDataMaps->GetHeadPosition();
	CRptBatchItemMap *pItemMap = NULL;
	CRptBatchDataMap *pDataMap = NULL;
	CRptBkmkBatchCell_Word *pCell = NULL;
	MSWord::Selection wordSelection = m_WordApp.GetSelection();
	MSWord::Cells oCells = wordSelection.GetCells();
	MSWord::Cell  oCell = NULL;
	long nCellIndex = 0;

	while (posItem != NULL)
	{
		pItemMap = (CRptBatchItemMap *)pItemMaps->GetNext(posItem);
		posData = pDataMaps->GetHeadPosition();

		if (!pItemMap->IsMaped())
		{
			nRow++;
			continue;
		}

		nCol = 0;

		while (posData != NULL)
		{
			pDataMap = (CRptBatchDataMap *)pDataMaps->GetNext(posData);

			if (pDataMap->IsMaped())
			{
				try
				{
					nCellIndex = nRow * nCols + nCol+1;
					oCell = oCells.Item(nCellIndex);
				}
				catch (...)
				{
					break;
				}

				pCell = new CRptBkmkBatchCell_Word();
				pCell->m_oCell = oCell;
				pCell->m_pGbItem = pItemMap->m_pItemRef;
				pCell->m_pData = pDataMap->m_pDataRef;
				pCell->m_strDataAttr = pDataMap->m_strDataAttr;
				pCell->m_nRepeatIndex = pDataMap->m_nRepeatIndex;
				pCell->m_strPrecision = pDataMap->m_strPrecision;
				pCell->m_strDataProcess = pDataMap->m_strDataProcess;
				oListBatchCell.AddTail(pCell);
			}

			nCol++;
		}

		nRow++;
	}
}

void CWordRptEdit::GetBatchCellList_ROWDATA_COLITEM(CExBaseList &oListBatchCell,CRptBatchItemMaps *pItemMaps, CRptBatchDataMaps *pDataMaps, long nRows)
{
	long nRow = 0;
	long nCol = 0;
	POS posItem = pItemMaps->GetHeadPosition();
	POS posData = pDataMaps->GetHeadPosition();
	CRptBatchItemMap *pItemMap = NULL;
	CRptBatchDataMap *pDataMap = NULL;
	CRptBkmkBatchCell_Word *pCell = NULL;
	MSWord::Selection wordSelection = m_WordApp.GetSelection();
	MSWord::Cells oCells = wordSelection.GetCells();
	MSWord::Cell  oCell = NULL;
	long nCellIndex = 0;

	while (posItem != NULL)
	{
		pItemMap = (CRptBatchItemMap *)pItemMaps->GetNext(posItem);
		posData = pDataMaps->GetHeadPosition();

		if (!pItemMap->IsMaped())
		{
			nCol++;
			continue;
		}

		nRow = 0;

		while (posData != NULL)
		{
			pDataMap = (CRptBatchDataMap *)pDataMaps->GetNext(posData);

			if (pDataMap->IsMaped())
			{
				try
				{
					nCellIndex = nCol * nRows + nRow+1;
					oCell = oCells.Item(nCellIndex);
				}
				catch (...)
				{
					break;
				}

				pCell = new CRptBkmkBatchCell_Word();
				pCell->m_oCell = oCell;
				pCell->m_pGbItem = pItemMap->m_pItemRef;
				pCell->m_pData = pDataMap->m_pDataRef;
				pCell->m_strDataAttr = pDataMap->m_strDataAttr;
				pCell->m_nRepeatIndex = pDataMap->m_nRepeatIndex;
				pCell->m_strPrecision = pDataMap->m_strPrecision;
				pCell->m_strDataProcess = pDataMap->m_strDataProcess;
				oListBatchCell.AddTail(pCell);
			}

			nRow++;
		}

		nCol++;
	}
}

void CWordRptEdit::GetBatchCellList_ROWREPEAT_COLDATA_ITEMROW(CExBaseList &oListBatchCell,CRptBatchItemMaps *pItemMaps, CRptBatchDataMaps *pDataMaps, long nRepeatCount, long nCols)
{
	long nRow = 0;
	long nCol = 0;
	POS posItem = pItemMaps->GetHeadPosition();
	POS posData = pDataMaps->GetHeadPosition();
	CRptBatchItemMap *pItemMap = NULL;
	CRptBatchDataMap *pDataMap = NULL;
	CRptBkmkBatchCell_Word *pCell = NULL;
	MSWord::Selection wordSelection = m_WordApp.GetSelection();
	MSWord::Cells oCells = wordSelection.GetCells();
	MSWord::Cell  oCell = NULL;
	long nCellIndex = 0;
	long nItemCells = 0;

	while (posItem != NULL)
	{
		pItemMap = (CRptBatchItemMap *)pItemMaps->GetNext(posItem);
		posData = pDataMaps->GetHeadPosition();

		if (!pItemMap->IsMaped())
		{
			continue;
		}

		nCol = 0;
		nRow = 0;

		for (nRow=0; nRow<nRepeatCount; nRow++)
		{
			posData = pDataMaps->GetHeadPosition();
			nCol = 0;

			while (posData != NULL)
			{
				pDataMap = (CRptBatchDataMap *)pDataMaps->GetNext(posData);

				if (pDataMap->IsMaped())
				{
					try
					{
						nCellIndex = nRow * nCols + nCol+1 + nItemCells;
						oCell = oCells.Item(nCellIndex);
					}
					catch (...)
					{
						break;
					}

					pCell = new CRptBkmkBatchCell_Word();
					pCell->m_oCell = oCell;
					pCell->m_pGbItem = pItemMap->m_pItemRef;
					pCell->m_pData = pDataMap->m_pDataRef;
					pCell->m_strDataAttr = pDataMap->m_strDataAttr;
					pCell->m_nRepeatIndex = nRow;
					pCell->m_strPrecision = pDataMap->m_strPrecision;
					pCell->m_strDataProcess = pDataMap->m_strDataProcess;
					oListBatchCell.AddTail(pCell);
				}

				nCol++;
			}
		}

		nItemCells += nRepeatCount * nCols;
	}
}

long CWordRptEdit::GetBkmkPos(CRptBkmk *pBkmk, long &nBeginPos, long &nEndPos)
{
	nBeginPos = -1;
	nEndPos = -1;

	try
	{
		MSWord::Selection oSelection;
		MSWord::Bookmarks bookmarks;
		MSWord::Bookmark bookmark;

		oSelection =  m_WordApp.GetSelection();
		bookmarks = m_doc.GetBookmarks();

		if(!pBkmk->m_strID.IsEmpty() && bookmarks.Exists(pBkmk->m_strID))
		{
			COleVariant vIndex(pBkmk->m_strID);
			bookmark = bookmarks.Item(&vIndex);
			nBeginPos = bookmark.GetStart();
			nEndPos = bookmark.GetEnd();
		}
	}
	catch(...)
	{
	}

	return 0;
}

long CWordRptEdit::AdjustReport_DelArea(CRptArea *pArea)
{
	if (pArea == NULL)
	{
		return 0;
	}

	if (pArea->GetCount() != 2)
	{
		return 0;
	}

	ASSERT (pArea->m_pBkmkBegin != NULL && pArea->m_pBkmkEnd != NULL);
	long nPosBegin1 = 0, nPosEnd1 = 0;
	long nPosBegin2 = 0, nPosEnd2 = 0;

	GetBkmkPos(pArea->m_pBkmkBegin, nPosBegin1, nPosEnd1);
	GetBkmkPos(pArea->m_pBkmkEnd, nPosBegin2, nPosEnd2);

	if (nPosBegin1 == -1 || nPosEnd2 == -1)
	{
		return 0;
	}

	try
	{
		MSWord::Selection oSelection;
		MSWord::Bookmarks bookmarks;
		MSWord::Bookmark bookmark;

		oSelection =  m_WordApp.GetSelection();
		bookmarks = m_doc.GetBookmarks();
		oSelection.SetStart(nPosBegin1);
		oSelection.SetEnd(nPosEnd2);
		oSelection.Select();
		oSelection.Cut();

		DeleteBkmk(pArea->m_pBkmkBegin->m_strID);
		DeleteBkmk(pArea->m_pBkmkEnd->m_strID);
	}
	catch(...)
	{
	}

	return 0;
}

CWnd* CWordRptEdit::AdjustSizeView()
{
	CWnd *pWnd = NULL;
	MSWord::_Document doc = m_doc;
	MSWord::_Application App = m_WordApp;

	//获取Word文档的窗口
	try
	{
		if (doc != NULL)
		{
			CString strWordCaption = App.GetCaption();
			MSWord::Window docWnd = doc.GetActiveWindow();
			if (docWnd != NULL)
			{
				CString strWndCaption = docWnd.GetCaption();
				CString strWndTitle;
				strWndTitle.Format(_T("%s - %s"),strWndCaption,strWordCaption);
				pWnd=CWnd::FindWindow(NULL,strWndTitle);
			}
		}
	}
	catch(...)
	{
	}

	return pWnd;
}

void CWordRptEdit::SetAppVisible(BOOL bVisible)
{
	if (m_WordApp != NULL)
	{
		m_WordApp.SetVisible(bVisible);
	}
}

void CWordRptEdit::SetDisplayStatusBar(BOOL bVisible)
{
	if (m_WordApp != NULL)
	{
		m_WordApp.SetDisplayStatusBar(bVisible);
	}
}

void CWordRptEdit::CopyApp(CRptEditInterface *pRptEditDest)
{
	CWordRptEdit *pWordRptEditDest = (CWordRptEdit*)pRptEditDest;

	pWordRptEditDest->m_WordApp = m_WordApp;
}

void CWordRptEdit::rpt_RenameRptBkmks(CExBaseList *pList)
{
	MSWord::_Application App = m_WordApp;
	MSWord::_Document doc = m_doc;

	wordrpt_RenameRptBkmks(pList, App, doc);
}
