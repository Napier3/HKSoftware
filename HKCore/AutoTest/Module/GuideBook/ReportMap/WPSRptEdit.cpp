#include "StdAfx.h"
#include "WPSRptEdit.h"
#include "ReportMap.h"
#include "RptBkmk.h"
#include "RptData.h"
#include "../../../../Module/Office/KSO.h"
#include "..\GuideBook.h"
#include "WordRptEditTools\RptBkmkBatchCell.h"
#include "WordRptEditTools\RptBkmkBatchAddTool.h"

CWPSRptEdit::CWPSRptEdit(void):m_doc(NULL),m_WPSApp(NULL)
{
}

CWPSRptEdit::~CWPSRptEdit(void)
{
}

BOOL CWPSRptEdit::CreateWordApplication(BOOL bVisible)
{
	//创建对象
	COleVariant covTrue((long)TRUE),covFalse((long)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	try
	{
		if (m_WPSApp == NULL)
		{
			if (!m_WPSApp.CreateDispatch(_T("kwps.Application")))
			{
				AfxMessageBox(g_sLangTxt_NoWord);
				return FALSE;
			}

			m_WPSApp.put_Visible(bVisible);  //This shows the application.
		}
	}
	catch (...)
	{
	}

	if(!OpenWordReportFile(m_strReportTemplateFile))
	{
		AfxMessageBox(g_sLangTxt_OpenDocFail);
		try
		{
		}
		catch (...)
		{
		}
	}
	else
	{
		WPS::Window wnd = m_WPSApp.get_ActiveWindow();
		WPS::View v = wnd.get_View();
		v.put_ShowBookmarks(TRUE);
	}

	return TRUE;
}

BOOL CWPSRptEdit::OpenWordReportFile(const CString &strRptFile)
{
	if (m_WPSApp == NULL)
	{
		return FALSE;
	}

	WPS::Documents docs(m_WPSApp.get_Documents());

	if (docs == NULL)
	{
		return FALSE;
	}

	COleVariant vRptFile(strRptFile);			
	COleVariant covTrue((long)TRUE),covFalse((long)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	BOOL bRet = TRUE;
	if (FindFile(m_strReportTemplateFile))
	{
		try
		{
			//打开试验报告文件
			m_doc = docs.Open(&vRptFile,covOptional,covFalse,covTrue,covOptional,covOptional,covOptional,covOptional,
				covOptional,covOptional,covOptional,covTrue,covOptional,covOptional,covOptional,covOptional);
		}
		catch (...)
		{
			bRet = FALSE;
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
			bRet = FALSE;
		}
	}

	return bRet;
}

BOOL CWPSRptEdit::NewWordReportFile()
{
	if (m_WPSApp == NULL)
	{
		return FALSE;
	}

	WPS::Documents docs(m_WPSApp.get_Documents());

	if (docs == NULL)
	{
		return FALSE;
	}

	COleVariant covTrue((long)TRUE),covFalse((long)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	m_WPSApp.put_Visible(TRUE);
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

	return bTrue;
}

void CWPSRptEdit::InitAllBookmarks()
{
	if (m_doc == NULL)
	{
		return;
	}

	WPS::Bookmarks oBkmks = m_doc.get_Bookmarks();
	WPS::Bookmark  oBkmk = NULL;
	long nCount = oBkmks.get_Count();
	long nIndex = 1;
	m_listWordBkmks.DeleteAll();

	for (nIndex=1; nIndex<=nCount; nIndex++)
	{
		COleVariant index(nIndex);
		oBkmk = oBkmks.Item(&index);
		CWordBkmk *pNew = new CWordBkmk();
		pNew->m_strID = oBkmk.get_Name();
		m_listWordBkmks.AddTail(pNew);
	}
}

void  CWPSRptEdit::HideCommandBar(KSO::_CommandBars cmdBars )
{
	try
	{
		long nCount = cmdBars.get_Count();
		long nIndex = 1;
		for(nIndex=1;nIndex<=nCount;nIndex++)
		{
			KSO::CommandBar cmdbar = cmdBars.get_Item(COleVariant(nIndex));

			if (cmdbar.get_Enabled() && cmdbar.get_Visible())
			{
				cmdbar.put_Enabled(FALSE);
			}
		}
	}
	catch (...)
	{

	}
}

CExBaseObject * CWPSRptEdit::ReLocateBkmk()
{
	CRptBkmk* pBkmk = NULL;

	try
	{
		// 插入书签
		if(m_doc == NULL)
			return FALSE;
		COleVariant vOpt(DISP_E_PARAMNOTFOUND, VT_ERROR);
		WPS::Bookmarks wpsBookmarks = m_doc.get_Bookmarks();
		WPS::Bookmark wpsBookmark;
		WPS::Selection wpsSelection = m_WPSApp.get_Selection();
		WPS::Range wpsSelectionRange = wpsSelection.get_Range();

		long nStart = wpsSelectionRange.get_Start();
		long nID = wpsSelectionRange.get_BookmarkID();
		if(nID != 0)
		{
			//查找是否有对应书签
			long nCount = wpsBookmarks.get_Count();
			for (long nIndex=1; nIndex<nCount+1; nIndex++)
			{
				COleVariant index(nIndex);
				wpsBookmark = wpsBookmarks.Item(&index);
				long nTemp = wpsBookmark.get_Start();

				if (nStart == nTemp)//找到此位置的书签
				{
					CString Name = wpsBookmark.get_Name();

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

void CWPSRptEdit::ExitWord(BOOL bExitApp)
{	
	COleVariant vTrue((short)TRUE), vFalse((short)FALSE),
		vOpt((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	try
	{
		if (m_WPSApp != NULL)
		{
			WPS::Window wnd = m_WPSApp.get_ActiveWindow();
			WPS::View v = wnd.get_View();
			v.put_ShowBookmarks(TRUE);
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

		if (m_WPSApp != NULL && bExitApp)
		{
			m_WPSApp.Quit(vFalse,vOpt,vOpt);
			m_WPSApp = NULL;
		}
	}
	catch (...) 
	{
	}
}

long CWPSRptEdit::OpenWord(const CString &strGuideBookFile)
{
	if (m_WPSApp == NULL)
	{
		return 0;
	}

	m_strReportTemplateFile = ChangeFilePostfix(strGuideBookFile, _T("doc"));

	WPS::Documents docs(m_WPSApp.get_Documents());

	if (docs == NULL)
	{
		return FALSE;
	}

	COleVariant vTrue((long)TRUE), vFalse((long)FALSE), vOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	//关闭文档
	try
	{
		if (m_doc != NULL)
		{
			m_doc.Close(vFalse,vOptional,vOptional);
		}

		m_doc = NULL;
	}
	catch (...)
	{
		m_doc = NULL;

		TRACE(L"Close word doc error...");
	}

	COleVariant vRptFile(m_strReportTemplateFile);			

	BOOL bTrue = TRUE;
	if (FindFile(m_strReportTemplateFile))
	{
		try
		{
			//打开试验报告文件
//			m_doc = docs.Open(&vRptFile,covOptional,vFalse,vTrue,covOptional,covOptional,
//				covOptional,covOptional,covOptional,covOptional,covOptional,vTrue);
			m_doc = docs.Open(&vRptFile,vOptional,vFalse,vTrue,vOptional,vOptional,vOptional,vOptional,
				vOptional,vOptional,vOptional,vTrue,vOptional,vOptional,vOptional,vOptional);
		}
		catch (...)
		{
			bTrue = FALSE;
		}
	}

	return TRUE;
}

long CWPSRptEdit::LocateBkmk(const CString &  strBkmk)
{
	BOOL bFind = FALSE;
	WPS::Bookmarks wpsBookmarks;
	WPS::Bookmark wpsBookmark;

	try
	{
		if(m_doc == NULL)
			return FALSE;
		wpsBookmarks = m_doc.get_Bookmarks();		
		bFind = wpsBookmarks.Exists(strBkmk);
		if (bFind)
		{
			COleVariant index(strBkmk);
			wpsBookmark = wpsBookmarks.Item(&index);
			wpsBookmark.Select();
		}
	}
	catch (...)
	{
	}

	return 0;
}

long CWPSRptEdit::DeleteBkmk(const CString & strBkmk, BOOL bSelect)
{	
	CString str = strBkmk;
	COleVariant index(str);
	WPS::Bookmarks wpsBookmarks = m_doc.get_Bookmarks();
	WPS::Bookmark wpsBookmark;
	long nRet = 0;

	try
	{
		if (wpsBookmarks.Exists(str))
		{
			wpsBookmark = wpsBookmarks.Item(&index);

			if (bSelect)
			{
				wpsBookmark.Select();
			}

			wpsBookmark.Delete();
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

CExBaseObject* CWPSRptEdit::AddBkmk(CRptData *pData, const CString &strAttrID, const CString &strDataProcess, const CString &strFillMode)
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
		WPS::Bookmarks wpsBookmarks = m_doc.get_Bookmarks();
		WPS::Bookmark wpsBookmark;
		WPS::Selection wpsSelection = m_WPSApp.get_Selection();
		WPS::Range wpsSelectionRange = wpsSelection.get_Range();

		long nStart = wpsSelectionRange.get_Start();
		long nID = wpsSelectionRange.get_BookmarkID();

		if(nID != 0)
		{
			//查找是否有对应书签
			long nCount = wpsBookmarks.get_Count();
			for (long nIndex=1; nIndex<nCount+1; nIndex++)
			{
				COleVariant index(nIndex);
				wpsBookmark = wpsBookmarks.Item(&index);
				long nTemp = wpsBookmark.get_Start();

				if (nStart == nTemp)//找到此位置的书签
				{
					CString Name = wpsBookmark.get_Name();

					if (FindRptBkmk(Name)!=NULL)//是有效书签
					{
						int nResult = MessageBox(NULL,/*L"当前位置有标签，确定替换"*/g_sLangTxt_HaveMarkSureReplace,g_sLangTxt_Message/*L"提示"*/,MB_YESNO);

						if(nResult == IDNO)
						{
							return NULL;
						}
						else//替换书签
						{
							long nCount = wpsBookmarks.get_Count();
							for (long nIndex=1; nIndex<nCount+1; nIndex++)
							{
								COleVariant index(nIndex);
								wpsBookmark = wpsBookmarks.Item(&index);
								long nTemp = wpsBookmark.get_Start();
								if (nStart == nTemp)
								{
									CString Name = wpsBookmark.get_Name();
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
						wpsBookmark.Delete();
					}

					break;
				}
			}
		}

		CString strBkmk = CreateNewBkmk(pData);
		//strBkmk.Format(_T("Bmk%s_%x"),GetUIDString(), m_dwMaxBkmkIndex++);
		wpsBookmarks.Add(strBkmk, vOpt);
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

void CWPSRptEdit::InsertBkmk(const CString &strBkmk)
{
	try
	{
		// 插入书签
		COleVariant vOpt(DISP_E_PARAMNOTFOUND, VT_ERROR);
		WPS::Bookmarks wpsBookmarks = m_doc.get_Bookmarks();
		WPS::Bookmark wpsBookmark;
		WPS::Selection wpsSelection = m_WPSApp.get_Selection();
		WPS::Range wpsSelectionRange = wpsSelection.get_Range();
		wpsBookmarks.Add(strBkmk, vOpt);
	}
	catch (...)
	{
	}
}

CExBaseObject* CWPSRptEdit::AddArea(CExBaseList *pRptArea)
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
		WPS::Bookmarks wpsBookmarks = m_doc.get_Bookmarks();
		WPS::Bookmark wpsBookmark;
		WPS::Selection wpsSelection = m_WPSApp.get_Selection();
		WPS::Range wpsSelectionRange = wpsSelection.get_Range();

		long nStart = wpsSelectionRange.get_Start();
		long nEnd = wpsSelectionRange.get_End();
		long nID = wpsSelectionRange.get_BookmarkID();

		CRptArea *pArea = (CRptArea*)pRptArea;
		pArea->m_pBkmkBegin = InsertNewAreaBkmk(m_dwMaxBkmkIndex, pRptArea, wpsBookmarks, wpsSelection, nStart);
		pArea->m_pBkmkEnd = InsertNewAreaBkmk(m_dwMaxBkmkIndex, pRptArea, wpsBookmarks, wpsSelection, nEnd);

		SetRptItemBkmkState(pArea);
	}
	catch (...)
	{
	}
	
	SetMidified(TRUE);

	return pBkmk;
}

CExBaseObject* CWPSRptEdit::AddArea(CGbItemBase *pItem, long nStart, long nEnd)
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
		WPS::Bookmarks wpsBookmarks = m_doc.get_Bookmarks();
		WPS::Bookmark wpsBookmark;
		WPS::Selection wpsSelection = m_WPSApp.get_Selection();

		pArea->m_pBkmkBegin = InsertNewAreaBkmk(m_dwMaxBkmkIndex, pArea, wpsBookmarks, wpsSelection, nStart);
		pArea->m_pBkmkEnd = InsertNewAreaBkmk(m_dwMaxBkmkIndex, pArea, wpsBookmarks, wpsSelection, nEnd);

		SetRptItemBkmkState(pArea);
	}
	catch (...)
	{
	}

	return pArea;
}

long CWPSRptEdit::GetCurrPos()
{
	if(m_doc == NULL)
	{
		return 0;
	}

	long nPos = 0;

	try
	{
		WPS::Bookmarks wpsBookmarks = m_doc.get_Bookmarks();
		WPS::Bookmark wpsBookmark;
		WPS::Selection wpsSelection = m_WPSApp.get_Selection();
		WPS::Range wpsSelectionRange = wpsSelection.get_Range();

		long nStart = wpsSelectionRange.get_Start();
		long nEnd = wpsSelectionRange.get_End();

		ASSERT (nStart == nEnd);
		nPos = nEnd;
	}
	catch(...)
	{

	}

	return nPos;
}

long CWPSRptEdit::InitPage(BOOL bHort)
{
	try
	{
		long nValue = bHort;
		WPS::PageSetup oPageSetup = m_doc.get_PageSetup();
		oPageSetup.put_Orientation(nValue);
	}
	catch (...)
	{

	}

	return 0;
}

long CWPSRptEdit::Save()
{
	//Map文件保存
	m_pGuideBook->SaveXMLFile(m_strGuideBookFile);

	try
	{
		COleVariant vOpt(DISP_E_PARAMNOTFOUND, VT_ERROR);  	
		m_doc.SaveAs(COleVariant(m_strReportTemplateFile), vOpt, vOpt, vOpt, vOpt, vOpt, vOpt, vOpt, vOpt, vOpt, vOpt, vOpt, vOpt, vOpt, vOpt, vOpt);
	}
	catch(...)
	{
	}

	SetMidified(FALSE);

	return 0;
}

long CWPSRptEdit::SaveAs(const CString &strFile)
{
	CString strDocFile = ChangeFilePostfix(strFile, _T("doc"));

	//Doc文件保存
	COleVariant vOpt(DISP_E_PARAMNOTFOUND, VT_ERROR);  	
	m_doc.SaveAs(COleVariant(strDocFile), vOpt, vOpt, vOpt, vOpt, vOpt, vOpt, vOpt, vOpt, vOpt, vOpt, vOpt, vOpt, vOpt, vOpt, vOpt);
	
	SetMidified(FALSE);
	m_strReportTemplateFile = strFile;

	return 0;
}

long CWPSRptEdit::CloseWord()
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

		TRACE(L"Close wps doc error...");
	}

	return 0;
}

BOOL CWPSRptEdit::IsValidDoc()
{
	return (m_doc != NULL);
}

CString CWPSRptEdit::InitCurrBkmk()
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
		WPS::Bookmarks wpsBookmarks = m_doc.get_Bookmarks();
		WPS::Bookmark wpsBookmark;
		WPS::Selection wpsSelection = m_WPSApp.get_Selection();
		WPS::Range wpsSelectionRange = wpsSelection.get_Range();

		long nStart = wpsSelectionRange.get_Start();
		long nEnd = wpsSelectionRange.get_End();

		if (nEnd > nStart)
		{
			m_pCurrBkmk = NULL;
		}
		else
		{
			wpsBookmarks = wpsSelection.get_Bookmarks();

			long nCount = wpsBookmarks.get_Count();
			long nIndex = 0;
			m_pCurrBkmk = NULL;

			for (nIndex=1; nIndex<=nCount; nIndex++)
			{
				COleVariant vIndex(nIndex);
				wpsBookmark = wpsBookmarks.Item(&vIndex);
				long nStart2 = wpsBookmark.get_Start();
				long nEnd2 = wpsBookmark.get_End();

				if (nStart2 == nEnd2 && nStart2 == nStart)
				{
					strBkmk = wpsBookmark.get_Name();
					m_pCurrBkmk = (CWordBkmk*)m_listWordBkmks.FindByID((strBkmk));
					break;
				}
			}
		}
	}
	catch(...)
	{
		m_pCurrBkmk = NULL;
	}

	if (m_pCurrBkmk != NULL)
	{
		WPS::Table oTable = NULL;
		WPS::Cells oCells = NULL;

		GetBkmkRowCol(m_pCurrBkmk->m_pBkmk, oTable, oCells);
	}

	return strBkmk;
}

long CWPSRptEdit::GetAllSelBkmk(CExBaseList &oListOfficeBkmk)
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
		WPS::Bookmarks wpsBookmarks;
		WPS::Bookmark wpsBookmark;
		WPS::Selection wpsSelection = m_WPSApp.get_Selection();
		WPS::Range wpsSelectionRange = wpsSelection.get_Range();

		wpsBookmarks = wpsSelection.get_Bookmarks();
		long nCount = wpsBookmarks.get_Count();
		WPS::Cells oCells = wpsSelection.get_Cells();
		WPS::Cell oCell;
		long nCells = oCells.get_Count();
		long nCell = 0;
		long nIndex = 0;

		for (nCell=1; nCell<=nCells; nCell++)
		{
			oCell = oCells.Item(nCell);
			wpsSelectionRange = oCell.get_Range();
			wpsSelectionRange.Select();
			long nStart, nEnd;
			nStart = wpsSelectionRange.get_Start();
			nEnd = wpsSelectionRange.get_End()-1;
			wpsSelection.put_Start(nStart);
			wpsSelection.put_End(nEnd);
			wpsSelection.Select();
			wpsBookmarks = wpsSelection.get_Bookmarks();
			nCount = wpsBookmarks.get_Count();

			m_pCurrBkmk = NULL;

			for (nIndex=1; nIndex<=nCount; nIndex++)
			{
				COleVariant vIndex(nIndex);
				wpsBookmark = wpsBookmarks.Item(&vIndex);
				long nStart2 = wpsBookmark.get_Start();
				long nEnd2 = wpsBookmark.get_End();

				if (nStart2 == nEnd2)
				{
					strBkmk = wpsBookmark.get_Name();
					CWordBkmk *pFind = (CWordBkmk*)m_listWordBkmks.FindByID((strBkmk));

					if (pFind != NULL)
					{
						oListOfficeBkmk.AddTail(pFind);
					}
				}
			}
		}
	}
	catch(...)
	{
	}

	return oListOfficeBkmk.GetCount();
}

BOOL CWPSRptEdit::CanAddArea()
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
		WPS::Bookmarks wpsBookmarks = m_doc.get_Bookmarks();
		WPS::Bookmark wpsBookmark;
		WPS::Selection wpsSelection = m_WPSApp.get_Selection();
		WPS::Range wpsSelectionRange = wpsSelection.get_Range();

		long nStart = wpsSelectionRange.get_Start();
		long nEnd = wpsSelectionRange.get_End();

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

BOOL CWPSRptEdit::ReplaceBkmk(const CString& strBkmkSrc, const CString& strBkmkDest)
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
		WPS::Bookmarks wpsBookmarks = m_doc.get_Bookmarks();
		WPS::Bookmark wpsBookmark;
		WPS::Selection wpsSelection = m_WPSApp.get_Selection();
		WPS::Range wpsSelectionRange = wpsSelection.get_Range();
		wpsBookmarks.Add(strBkmkDest, vOpt);
	}
	catch (...)
	{
	}

	SetMidified(TRUE);
	return TRUE;
}

BOOL CWPSRptEdit::UpdateBkmk(CRptBkmk *pRptBkmk)
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
			WPS::Bookmarks wpsBookmarks = m_doc.get_Bookmarks();
			WPS::Bookmark wpsBookmark;
			WPS::Selection wpsSelection = m_WPSApp.get_Selection();
			WPS::Range wpsSelectionRange = wpsSelection.get_Range();
			wpsBookmarks.Add(strBkmk, vOpt);
		}
	}
	catch (...)
	{
	}

	SetMidified(TRUE);
	return TRUE;
}

void CWPSRptEdit::InsertTitle(const CString &strTitle, long nTitleLevel)
{
	wpsrpt_InsertTitle(m_WPSApp, m_doc,m_strReportTemplateFile, strTitle, nTitleLevel);
}


void CWPSRptEdit::InsertWPSEdit(CWPSRptEdit *pWPSEdit, long nAddRptGroupTitle)
{
	wpsrpt_InsertWPSEdit(m_WPSApp, m_doc, pWPSEdit->m_doc,m_strReportTemplateFile, pWPSEdit->m_strReportTemplateFile, nAddRptGroupTitle);
}

CRptBkmk* CWPSRptEdit::InsertNewAreaBkmk(DWORD &dwBkmkIndex, CExBaseList *pRptArea, WPS::Bookmarks wpsBookmarks, WPS::Selection wpsSelection, long nPos)
{
	CRptBkmk *pBkmk = new CRptBkmk();
	((CRptArea*)pRptArea)->InitAreaBkmkID(pBkmk, dwBkmkIndex);
	dwBkmkIndex++;
	pRptArea->AddTail(pBkmk);
	pBkmk->SetParent(pRptArea);

	COleVariant vOpt(DISP_E_PARAMNOTFOUND, VT_ERROR);
	wpsSelection.put_Start(nPos);
	wpsSelection.put_End(nPos);
	wpsSelection.Select();
	wpsBookmarks.Add(pBkmk->m_strID, vOpt);

	CWordBkmk *pNew = AddNewWordBookmarkToList(pBkmk->m_strID);
	pBkmk->m_pBkmk = pNew;
	pNew->m_pBkmk = pBkmk;

	return pBkmk;
}

BOOL CWPSRptEdit::ActiveWindow(const CString &strTitle)
{
	return wpsrpt_ActiveWindow(m_WPSApp, strTitle);
}

long CWPSRptEdit::GetBkmkPos(CRptBkmk *pBkmk, long &nBeginPos, long &nEndPos)
{
	nBeginPos = -1;
	nEndPos = -1;

	try
	{
		WPS::Selection oSelection;
		WPS::Bookmarks bookmarks;
		WPS::Bookmark bookmark;

		oSelection =  m_WPSApp.get_Selection();
		bookmarks = m_doc.get_Bookmarks();

		if(!pBkmk->m_strID.IsEmpty() && bookmarks.Exists(pBkmk->m_strID))
		{
			COleVariant vIndex(pBkmk->m_strID);
			bookmark = bookmarks.Item(&vIndex);
			nBeginPos = bookmark.get_Start();
			nEndPos = bookmark.get_End();
		}
	}
	catch(...)
	{
	}

	return 0;
}


void CWPSRptEdit::ClearBkmkText(CRptBkmk *pBkmk)
{
	try
	{
		WPS::Selection sel;
		WPS::Bookmarks bookmarks;
		WPS::Bookmark bookmark;

		WPS::Range  range = NULL;
		WPS::Paragraphs  paragraphs = NULL;
		WPS::Paragraph paragraph = NULL;
		WPS::Range rangeParagraph = NULL;
		long lRangeStart = 0;
		long lRangeEnd = 0;
		long lRangeStart2 = 0;
		long lRangeEnd2 = 0;
		long lEndTemp = 0;

		sel =  m_WPSApp.get_Selection();
		bookmarks = m_doc.get_Bookmarks();

		if(!pBkmk->m_strID.IsEmpty() && bookmarks.Exists(pBkmk->m_strID))
		{
			COleVariant vIndex(pBkmk->m_strID);
			bookmark = bookmarks.Item(&vIndex);
			bookmark.Select();

			range = bookmark.get_Range();
			paragraphs = range.get_Paragraphs();
			paragraph = paragraphs.get_First();
			rangeParagraph = paragraph.get_Range();
			lRangeStart2 = rangeParagraph.get_Start();
			lRangeEnd2 = rangeParagraph.get_End();
			lEndTemp = lRangeEnd2 - 1;
			if (lRangeStart2 <= lEndTemp)
				lRangeEnd2 = lEndTemp;

			sel.put_Start(lRangeStart2);
			sel.put_End(lRangeEnd2);

			sel.put_Text(_bstr_t(_T("")));
		}
	}
	catch(...)
	{
	}
}

long CWPSRptEdit::AdjustReport_DelArea(CRptArea *pArea)
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
		WPS::Selection oSelection;
		WPS::Bookmarks bookmarks;
		WPS::Bookmark bookmark;

		oSelection =  m_WPSApp.get_Selection();
		bookmarks = m_doc.get_Bookmarks();
		oSelection.put_Start(nPosBegin1);
		oSelection.put_End(nPosEnd2);
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

////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL CWPSRptEdit::GetBkmkRowCol(CRptBkmk *pBkmk, WPS::Table &oTable, WPS::Cells &oCells)
{
	if (pBkmk == NULL)
	{
		return FALSE;
	}

	if (pBkmk->m_strID.IsEmpty())
	{
		return FALSE;
	}

	WPS::Bookmarks oBkmks = NULL;
	WPS::Bookmark oBkmk = NULL;
	long nRow = 0, nCol = 0, nIndex=0;

	try
	{
		oBkmks = m_doc.get_Bookmarks();

		if (!oBkmks.Exists(pBkmk->m_strID))
		{
			return FALSE;
		}

		COleVariant vIndex(pBkmk->m_strID);
		oBkmk = oBkmks.Item(&vIndex);
		WPS::Range oRange = oBkmk.get_Range();
		oCells = oRange.get_Cells();

		if (oCells == NULL)
		{
			return FALSE;
		}

		long nCount = oCells.get_Count();
		if (nCount>0)
		{
			WPS::Cell oCel = oCells.Item(1);

			long nRowIndex = oCel.get_RowIndex();
			long nColIndex = oCel.get_ColumnIndex();
		}
		WPS::Tables oTables = oRange.get_Tables();
		UINT nID_Bkmk = oRange.get_BookmarkID();

		if (oTables.get_Count() > 0)
		{
			oTable = oTables.Item(1); 
		}
	}
	catch(...)
	{

	}

	return TRUE;
}

CWnd* CWPSRptEdit::AdjustSizeView()
{
	CWnd *pWnd = NULL;
	WPS::_Document doc = m_doc;
	WPS::_Application App = m_WPSApp;

	//获取WPS文档的窗口
	try
	{
		if (doc != NULL)
		{
			CString strWPSCaption1 = _T("WPS 文字");
			CString strWPSCaption2 = _T("WPS 文字 - 兼容模式");//App.get_Caption();
			WPS::Window docWnd = doc.get_ActiveWindow();
			if (docWnd != NULL)
			{
				CString strWndCaption = docWnd.get_Caption();
				CString strWndTitle1,strWndTitle2;
				strWndTitle1.Format(_T("%s - %s"),strWndCaption,strWPSCaption1);
				strWndTitle2.Format(_T("%s - %s"),strWndCaption,strWPSCaption2);
				pWnd = CWnd::FindWindow(NULL,strWndTitle1);
				if (pWnd == NULL)
				{
					pWnd = CWnd::FindWindow(NULL,strWndTitle2);
				}
			}
		}
	}
	catch(...)
	{
	}

	return pWnd;
}

void CWPSRptEdit::SetAppVisible(BOOL bVisible)
{
	if (m_WPSApp != NULL)
	{
		m_WPSApp.put_Visible(bVisible);
	}
}

void CWPSRptEdit::SetDisplayStatusBar(BOOL bVisible)
{
	if (m_WPSApp != NULL)
	{
		m_WPSApp.put_DisplayStatusBar(bVisible);
	}
}

void CWPSRptEdit::CopyApp(CRptEditInterface *pRptEditDest)
{
	CWPSRptEdit *pWPSRptEditDest = (CWPSRptEdit*)pRptEditDest;

	pWPSRptEditDest->m_WPSApp = m_WPSApp;
}

void CWPSRptEdit::rpt_RenameRptBkmks(CExBaseList *pList)
{
	WPS::_Application App = m_WPSApp;
	WPS::_Document doc = m_doc;

	wpsrpt_RenameRptBkmks(pList, App, doc);
}

void CWPSRptEdit::InsertWordEdit(CRptEditInterface *pRptEdit,long nAddRptGroupTitle)
{
	CWPSRptEdit *pWPSEdit = (CWPSRptEdit*)pRptEdit;
	wpsrpt_InsertWPSEdit(m_WPSApp, m_doc, pWPSEdit->m_doc,m_strReportTemplateFile, pWPSEdit->m_strReportTemplateFile, nAddRptGroupTitle);
}

BOOL CWPSRptEdit::rpt_CanEnterRptBkmkBatchAdd(CExBaseObject *pItem)
{
	WPS::Selection wpsSelection = m_WPSApp.get_Selection();

	WPS::Columns oCols = NULL;
	WPS::Column oCol = NULL;
	WPS::Paragraphs oParagraphs = NULL;
	WPS::Paragraph oParagraph = NULL;

	try
	{
		oCols = wpsSelection.get_Columns();
	}
	catch (...)
	{
		AfxMessageBox(g_sLangTxt_SelNoArea/*_T("没有选择表格区域！")*/, MB_OK | MB_ICONEXCLAMATION);
	}

	if (oCols == NULL)
	{
		return FALSE;
	}

	long nCols = oCols.get_Count();
	long nRows = 0;

	if (nCols == 0)
	{
		AfxMessageBox(g_sLangTxt_SelNoArea/*_T("没有选择表格区域！")*/, MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	WPS::Cells oCells = wpsSelection.get_Cells();
	oParagraphs = wpsSelection.get_Paragraphs();
	long nCells = oCells.get_Count();
	long nParagraphs = oCells.get_Count();

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

BOOL CWPSRptEdit::rpt_CanEnterRptBkmkBatchAddYc(CExBaseObject *pItem)
{
	WPS::Selection wpsSelection = m_WPSApp.get_Selection();

	WPS::Columns oCols = NULL;
	WPS::Column oCol = NULL;
	WPS::Paragraphs oParagraphs = NULL;
	WPS::Paragraph oParagraph = NULL;

	try
	{
		oCols = wpsSelection.get_Columns();
	}
	catch (...)
	{
		AfxMessageBox(g_sLangTxt_SelNoArea/*_T("没有选择表格区域！")*/, MB_OK | MB_ICONEXCLAMATION);
	}

	if (oCols == NULL)
	{
		return FALSE;
	}

	long nCols = oCols.get_Count();
	long nRows = 0;

	if (nCols == 0)
	{
		AfxMessageBox(g_sLangTxt_SelNoArea/*_T("没有选择表格区域！")*/, MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	WPS::Cells oCells = wpsSelection.get_Cells();
	oParagraphs = wpsSelection.get_Paragraphs();
	long nCells = oCells.get_Count();
	long nParagraphs = oCells.get_Count();

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

BOOL CWPSRptEdit::rpt_GetRptBkmkBatchRowsCols(long &nRows, long &nCols)
{
	WPS::Selection wpsSelection = m_WPSApp.get_Selection();

	WPS::Cells oCells = NULL;
	WPS::Columns oCols = NULL;

	try
	{
		oCells = wpsSelection.get_Cells();
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
		oCols = wpsSelection.get_Columns();
	}
	catch (...)
	{
	}

	if (oCols == NULL)
	{
		return FALSE;
	}

	nCols = oCols.get_Count();
	long nCells = oCells.get_Count();
	nRows = nCells / nCols;

	return TRUE;
}

void CWPSRptEdit::InsertBkmks(CExBaseList& oListCells, CExBaseList& oListBkmks)
{
	POS pos = oListCells.GetHeadPosition();
	CRptBkmkBatchCell_WPS *pCell = NULL;
	CRptBkmk* pObjBkmk = NULL;
	WPS::Range oRng = NULL;
	WPS::Selection oSelection = m_WPSApp.get_Selection();
	while (pos != NULL)
	{
		pCell = (CRptBkmkBatchCell_WPS *)oListCells.GetNext(pos);
		oRng = pCell->m_oCell.get_Range();
		long nStart = oRng.get_Start();
		long nEnd = oRng.get_End();
		oSelection.put_Start(nStart);
		oSelection.put_End(nStart);
		oSelection.Select();
		pObjBkmk = InsertCellBkmk((CGbItemBase*)pCell->m_pGbItem, pCell->m_pData, pCell->m_strDataAttr, pCell->m_strPrecision, pCell->m_nRepeatIndex, 
			pCell->m_strDataProcess, _T(""));
		oListBkmks.AddTail(pObjBkmk);
	}
}

void CWPSRptEdit::GetBatchCellList_ROWITEM_COLDATA(CExBaseList &oListBatchCell,CRptBatchItemMaps *pItemMaps, CRptBatchDataMaps *pDataMaps, long nCols)
{
	long nRow = 0;
	long nCol = 0;
	POS posItem = pItemMaps->GetHeadPosition();
	POS posData = pDataMaps->GetHeadPosition();
	CRptBatchItemMap *pItemMap = NULL;
	CRptBatchDataMap *pDataMap = NULL;
	CRptBkmkBatchCell_WPS *pCell = NULL;
	WPS::Selection wpsSelection = m_WPSApp.get_Selection();
	WPS::Cells oCells = wpsSelection.get_Cells();
	WPS::Cell  oCell = NULL;
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

				pCell = new CRptBkmkBatchCell_WPS();
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

void CWPSRptEdit::GetBatchCellList_ROWDATA_COLITEM(CExBaseList &oListBatchCell,CRptBatchItemMaps *pItemMaps, CRptBatchDataMaps *pDataMaps, long nRows)
{
	long nRow = 0;
	long nCol = 0;
	POS posItem = pItemMaps->GetHeadPosition();
	POS posData = pDataMaps->GetHeadPosition();
	CRptBatchItemMap *pItemMap = NULL;
	CRptBatchDataMap *pDataMap = NULL;
	CRptBkmkBatchCell_WPS *pCell = NULL;
	WPS::Selection wpsSelection = m_WPSApp.get_Selection();
	WPS::Cells oCells = wpsSelection.get_Cells();
	WPS::Cell  oCell = NULL;
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

				pCell = new CRptBkmkBatchCell_WPS();
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

void CWPSRptEdit::GetBatchCellList_ROWREPEAT_COLDATA_ITEMROW(CExBaseList &oListBatchCell,CRptBatchItemMaps *pItemMaps, CRptBatchDataMaps *pDataMaps, long nRepeatCount, long nCols)
{
	long nRow = 0;
	long nCol = 0;
	POS posItem = pItemMaps->GetHeadPosition();
	POS posData = pDataMaps->GetHeadPosition();
	CRptBatchItemMap *pItemMap = NULL;
	CRptBatchDataMap *pDataMap = NULL;
	CRptBkmkBatchCell_WPS *pCell = NULL;
	WPS::Selection wpsSelection = m_WPSApp.get_Selection();
	WPS::Cells oCells = wpsSelection.get_Cells();
	WPS::Cell  oCell = NULL;
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

					pCell = new CRptBkmkBatchCell_WPS();
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


