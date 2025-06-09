#include "StdAfx.h"
#include "WordRptFill.h"
#include "..\..\..\..\..\Module\API\GlobalApi.h"

#include "..\..\..\TCtrlCntrDefine.h"

#include "..\..\..\XLanguageResourceAts.h"

#include "..\..\..\TestControl/TctrlCntrBaseApp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////
//CRptFillWordApp

CRptFillWordApp::CRptFillWordApp()
{
	m_WordCommandBarMngr.Init();
	m_WordApp = NULL;
}

CRptFillWordApp::~CRptFillWordApp()
{
	if (m_WordApp != NULL)
	{
		m_WordApp.ReleaseDispatch();
		m_WordApp = NULL;
	}
}

MSWord::_Application CRptFillWordApp::GetWordApp(BOOL bShow)
{
	if (m_WordApp == NULL)
	{
		//创建对象
		CreateApplication(bShow);
	}

	return m_WordApp;
}

void CRptFillWordApp::CreateApplication(BOOL bShow,long nHideAllCmdbars)
{
	COleVariant covTrue((long)TRUE),covFalse((long)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	try
	{
		if (!m_WordApp.CreateDispatch(_T("Word.Application")))
		{
			AfxMessageBox(_T("没有安装Word"));
			return ;
		}

		m_WordApp.SetVisible(bShow);  //This shows the application.
	}
	catch (...)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("******打开WINWORD.EXE异常******"));
	}

	//关闭全部的工具条
	MSO9::_CommandBars cmdbars;
	try
	{
		if (nHideAllCmdbars != 0)
		{
			cmdbars = m_WordApp.GetCommandBars();
			m_WordCommandBarMngr.InitWordCommandBarMngr(cmdbars);
		}
	}
	catch (...)
	{
		TRACE("catch error-----");
	}
}

void CRptFillWordApp::SetViewSettings()
{
	if (m_WordApp == NULL)
	{
		return;
	}

	try
	{
		MSWord::View vw;
		MSWord::Window wnd;
		wnd = m_WordApp.GetActiveWindow();

		if (wnd != NULL)
		{
			wnd.SetDocumentMap(FALSE);
			vw = wnd.GetView();

			if (vw != NULL)
			{
				m_bShowParagraphs = vw.GetShowParagraphs();
				m_bShowBookmarks = vw.GetShowBookmarks();
				vw.SetShowParagraphs(FALSE);
				vw.SetShowBookmarks(FALSE);
				m_WordApp.SetDisplayStatusBar(FALSE);
			}
		}
	}
	catch(...)
	{
	}
}

void CRptFillWordApp::RestoreViewSettings()
{
	if (m_WordApp == NULL)
	{
		return;
	}

	try
	{
		MSWord::Documents oDocs = m_WordApp.GetDocuments();

		if (oDocs.GetCount() > 1)
		{
			return;
		}
	}
	catch (...)
	{
		TRACE("catch error-----");
	}

	try
	{
		MSWord::View vw;
		MSWord::Window wnd;
		wnd = m_WordApp.GetActiveWindow();

		if (wnd != NULL)
		{
			vw = wnd.GetView();

			if (vw != NULL)
			{
				vw.SetShowParagraphs(m_bShowParagraphs);
				vw.SetShowParagraphs(m_bShowBookmarks);
				m_WordApp.SetDisplayStatusBar(TRUE);
			}
		}
	}
	catch(...)
	{
	}
}

void CRptFillWordApp::CloseApplication()
{
	if (m_WordApp == NULL)
	{
		return;
	}

	COleVariant covTrue((long)TRUE);
	COleVariant covFalse((long)FALSE);
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	try
	{
		MSWord::Documents oDocs = m_WordApp.GetDocuments();

		if (oDocs.GetCount() > 0)
		{
			return;
		}
	}
	catch (...)
	{
		TRACE("catch error-----");
	}

	RestoreCommandBars();

	try
	{
		if(m_WordApp)
		{
			m_WordApp.Quit(covFalse, covOptional, covOptional);
			m_WordApp = NULL;
		}
	}
	catch (...) 
	{
		TRACE("catch error-----");
	}

	m_WordApp = NULL;
}

void CRptFillWordApp::RestoreCommandBars()
{
	if (m_WordApp == NULL)
	{
		return;
	}

	MSO9::_CommandBars cmdbars;
	try
	{
		cmdbars = m_WordApp.GetCommandBars();
		m_WordCommandBarMngr.LoadWordCommandBarMngr(cmdbars);
	}
	catch (...)
	{
		TRACE("catch error-----");
	}	

}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//CWordRptFill

CWordRptFill::CWordRptFill(void)
{
	m_oDoc = NULL;
	m_pWordApp = (CRptFillWordApp*)g_theRptFillApp;
}

CWordRptFill::~CWordRptFill(void)
{
	
}

long CWordRptFill::OpenOnly(const CString  &strReportFile)
{
	m_strReportFile = strReportFile;

	if (!IsFileExist(strReportFile))
	{
		return FALSE;
	}

	if ( m_pWordApp->m_WordApp == NULL)
	{
		m_pWordApp->GetWordApp(FALSE);
//		return FALSE;
	}

	MSWord::Documents docs = m_pWordApp->m_WordApp.GetDocuments();

	if (docs == NULL)
	{
		return FALSE;
	}

	COleVariant vRptFile(strReportFile);			
	COleVariant covTrue((long)TRUE),covFalse((long)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	BOOL bTrue = TRUE;

	try
	{
		if (docs != NULL)
		{
			//打开试验报告文件
			m_oDoc = docs.Open(&vRptFile,covOptional,covFalse,covTrue,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covTrue);
		}
	}
	catch (...)
	{
		bTrue = FALSE;
	}

	return bTrue;
}

long CWordRptFill::New(CString strReportMapFile, CString strReportTemplFile, CString strReportFile, BOOL bFirst)
{
	CTCtrlCntrBaseApp* pApp = g_theTCtrlCntrApp;

	m_strReportMapFile = strReportMapFile;
	m_strReportTemplFile = strReportTemplFile;
	m_strReportFile = strReportFile;

	COleVariant covTrue((long)TRUE),covFalse((long)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	COleVariant vTemplate(m_strReportTemplFile);			
	COleVariant vRptFile(m_strReportFile);			
	BOOL bWordCreate = TRUE;

	if ( m_pWordApp->m_WordApp == NULL)
	{
		return 0;
	}

	MSWord::Documents docs;

	try
	{
		//如果打开了报告文档，则保存并关闭文档
		docs = m_pWordApp->m_WordApp.GetDocuments();

		//打开报告文档
		if (!Open(m_strReportFile, bFirst))
		{
			try
			{
				//如果打开失败，则打开测试模板，并且填写试验报告
				if (AddNewReport(m_strReportTemplFile))
				{
					g_theRptFillApp->SetViewSettings();
				}
			}
			catch (...)
			{
			}
		}

		AdjustWordWindow();
	}
	catch(...)
	{
	}

	return TRUE;
}

long CWordRptFill::Open(const CString &strReportFile, BOOL bFirst)
{
	CTCtrlCntrBaseApp* pApp = g_theTCtrlCntrApp;

	m_strReportFile = strReportFile;
	
	if (!IsFileExist(strReportFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("[%s] error!"), strReportFile);
		return FALSE;
	}

	if ( m_pWordApp->m_WordApp == NULL)
	{
		m_pWordApp->GetWordApp(FALSE);
//		return FALSE;
	}

	if ( m_pWordApp->m_WordApp == NULL)
	{//2020-03-03  lijq  创建之后再次判断是否为空
		return FALSE;
	}

	MSWord::Documents docs = NULL;
	docs =  m_pWordApp->m_WordApp.GetDocuments();

	if (docs == NULL)
	{
		return FALSE;
	}

	COleVariant vRptFile(strReportFile);			
	COleVariant covTrue((long)TRUE),covFalse((long)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	BOOL bTrue = TRUE;

	try
	{
		//打开试验报告文件
		if (bFirst)
		{
			m_oDoc = docs.Open(&vRptFile,covOptional,covFalse,covTrue,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covTrue);
		}
		else
		{
			m_oDoc = docs.Open(&vRptFile,covOptional,covFalse,covTrue,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covFalse);
		}

		g_theRptFillApp->SetViewSettings();
	}
	catch (...)
	{
		bTrue = FALSE;
	}

	AdjustWordWindow();

	return bTrue;
}

long CWordRptFill::Save()
{
	if( !IsValidApp() || !IsValidDoc())
		return FALSE;

	m_oDoc.Save();

	return TRUE;
}

long CWordRptFill::SaveAs(CString  strRptFile)
{
	if( !IsValidApp() || !IsValidDoc())
		return FALSE;

	COleVariant covTrue((long)TRUE),covFalse((long)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	COleVariant vRptFile(strRptFile);
	m_oDoc.SaveAs(vRptFile,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional);

	return TRUE;
}

long CWordRptFill::Close(long nSave)
{
	if( !IsValidApp() || !IsValidDoc())
	{
		return TRUE;
	}

	CloseWordDocWindow();
	g_theRptFillApp->CloseApplication();

	return TRUE;
}

void CWordRptFill::CloseDoc(DWORD dwFlag)
{
	COleVariant covTrue((long)TRUE);
	COleVariant covFalse((long)FALSE);
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	try
	{
		if (m_oDoc != NULL)
		{
			m_oDoc.Close(covFalse,covOptional,covOptional);
			m_oDoc = NULL;
		}
	}
	catch (...) 
	{
		TRACE("CloseWordDocWindow:Error");
	}
}

BOOL CWordRptFill::IsValidApp()
{
	return(m_pWordApp->m_WordApp != NULL);
}

BOOL CWordRptFill::IsValidDoc()
{
	return(m_oDoc != NULL);
}

void CWordRptFill::AdjustWordWindow()
{
	CTCtrlCntrBaseApp* pApp = g_theTCtrlCntrApp;

	CWnd *pWnd = NULL;
	//获取Word文档的窗口
	try
	{
		if (m_oDoc != NULL)
		{
			pWnd = FindRptDocWindowEx();
			MSWord::Window docWnd = m_oDoc.GetActiveWindow();

			if (docWnd != NULL)
			{
				CString strWordCaption =  m_pWordApp->m_WordApp.GetCaption();
				CString strWndCaption = docWnd.GetCaption();
				CString strWndTitle;
				strWndTitle.Format(_T("%s - %s"),strWndCaption,strWordCaption);
				ActiveWindow(strWndTitle);
			}
		}
	}
	catch(...)
	{
	}

	ASSERT(pApp->GetCntrConfig() != NULL);

	if (pWnd == NULL)
	{
		if (::IsWindow(m_hWordWnd))
		{
			pWnd = CWnd::FromHandle(m_hWordWnd);
		}
	}

	if (pWnd != NULL)
	{
		AdjustDocWindow(pWnd);

		if ( m_pWordApp->m_WordApp != NULL)
		{
			try
			{
				m_pWordApp->m_WordApp.SetVisible(TRUE);
				m_pWordApp->m_WordApp.SetDisplayStatusBar(TRUE);
			}
			catch (...)
			{
			}
		}
	}
	else
	{
		try
		{
			m_pWordApp->m_WordApp.SetVisible(FALSE);
			m_pWordApp->m_WordApp.SetDisplayStatusBar(TRUE);
		}
		catch (...)
		{
		}
	}

	try
	{
		if (m_oDoc != NULL)
		{
			MSWord::Window docWnd = m_oDoc.GetActiveWindow();
			docWnd.SetVisible(TRUE);
			CString strCaption = docWnd.GetCaption();
			MSWord::View docView = docWnd.GetView();
			docView.SetType(MSWord::wdPrintView);

			if (pApp->GetCntrConfig()->m_nHideAllCmdbars == 1)
			{
				MSO9::_CommandBars cmdbars;
				cmdbars = m_oDoc.GetCommandBars();
				long nCount = cmdbars.GetCount();
				long nIndex = 1;
				CWordCommandBar *pCmdBar = NULL;

				for(nIndex=1;nIndex<=nCount;nIndex++)
				{
					MSO9::CommandBar cmdbar = cmdbars.GetItem(COleVariant(nIndex));

					if (cmdbar.GetEnabled() && cmdbar.GetVisible())
					{
						cmdbar.SetEnabled(FALSE);
					}
				}
			}
		}
	}
	catch(...)
	{
	}
}

BOOL CWordRptFill::CloseWordDocWindow()
{
	try
	{
		g_theRptFillApp->RestoreViewSettings();
	}
	catch (...) 
	{
		TRACE("CloseWordDocWindow:Error");
	}

	CloseDoc(0xFFFFFFFF);

	return TRUE;
}

BOOL CWordRptFill::ActiveWindow(const CString &strTitle)
{
	BOOL bTrue = FALSE;
	CTCtrlCntrBaseApp* pApp = g_theTCtrlCntrApp;

	try
	{
		MSWord::Windows oWindows = m_pWordApp->m_WordApp.GetWindows();
		COleVariant oIndex;

		long nIndex = 1;
		long nCount = oWindows.GetCount();

		for (nIndex=1; nIndex<=nCount; nIndex++)
		{
			oIndex = nIndex;
			MSWord::Window oWindow = oWindows.Item(&oIndex);
			CString strCaption = oWindow.GetCaption();

			if (strTitle.Find(strCaption) >= 0)
			{
				oWindow.Activate();
				bTrue = TRUE;
				break;
			}
		}
	}
	catch (...)
	{

	}

	return bTrue;
}

BOOL CWordRptFill::AddNewReport(const CString &strRptTmplFile)
{
	CTCtrlCntrBaseApp* pApp = g_theTCtrlCntrApp;

	COleVariant covTrue((long)TRUE),covFalse((long)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	COleVariant FileFormat((long)0);
	COleVariant Password(_T(""));
	COleVariant WritePassword(_T(""));

	CString strWordRptFile;
	COleVariant TmplFile(strRptTmplFile);

	if (!IsFileExist(strRptTmplFile))
	{
		return FALSE;
	}

	BOOL bTrue = TRUE;
	MSWord::Documents docs = m_pWordApp->m_WordApp.GetDocuments();

	try
	{
		m_oDoc = docs.Add(&TmplFile,&covFalse,&FileFormat,&covTrue);
	}
	catch (...)
	{
		bTrue = FALSE;
	}

	return bTrue;
}

long CWordRptFill::FillReport(CReport* pReport, long nRepeatIndex, long nInsertDataLinkWhenEligible)
{
	CTCtrlCntrBaseApp* pApp = g_theTCtrlCntrApp;
	
	CExBaseList *pRptDataList = FillReportParentItem(pReport, nRepeatIndex, nInsertDataLinkWhenEligible);

	if (pRptDataList == NULL)
	{
		return 0;
	}

	try
	{
		COleVariant vTrue((short)TRUE), vFalse((short)FALSE),
			vOpt((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
		COleVariant vUnit((long)MSWord::wdStory);
		COleVariant vCount((long)0);

		CGbItemBase *pGbItem = GetParentGbItem(pReport);

		//定位到文档末尾
		MSWord::Selection wordSelection = m_pWordApp->m_WordApp.GetSelection();
		wordSelection = m_pWordApp->m_WordApp.GetSelection();
		MSWord::_ParagraphFormat oFormat = wordSelection.GetParagraphFormat();
		wordSelection.EndKey(&vUnit, &vCount);

		//字体和停靠
		oFormat.SetAlignment(MSWord::wdAlignParagraphLeft);
		MSWord::_Font oFont = wordSelection.GetFont();
		oFont.SetSize(10);
		CString strText = pGbItem->GetNamePathEx(GBCLASSID_DEVICE, TRUE, _T(" / "));
		wordSelection.TypeText(strText);
		wordSelection.TypeParagraph();

		//列举每个标签
		POS pos = pRptDataList->GetHeadPosition();
		CRptData *pRptData = NULL;
		UINT nClassID = 0;

		while (pos != NULL)
		{
			pRptData = (CRptData*)pRptDataList->GetNext(pos);
			nClassID = pRptData->GetClassID();

			if (nClassID == RPTCLASSID_RPTDATA)
			{
				//数据名称
				strText = _T("\t") + pRptData->m_strName;
				wordSelection.TypeText(strText);
				wordSelection.TypeParagraph();

				POS posBkmk = pRptData->GetHeadPosition();
				CRptBkmk *pBkmk = NULL;
				long nIndex = 1;

				while (posBkmk != NULL)
				{
					//插入标签超级链接
					pBkmk = (CRptBkmk*)pRptData->GetNext(posBkmk);
					strText.Format(g_sLangTxt_DataD2/*_T("数据%d【%s】")*/, nIndex, pBkmk->m_strName);
					wordSelection.TypeText(strText);
					COleVariant vHUnit((long)MSWord::wdLine);
					COleVariant vHCount((long)1);
					COleVariant vHCount2((long)0);
					wordSelection.HomeKey(&vHUnit, &vHCount);
					MSWord::Range oRange = wordSelection.GetRange();
					MSWord::Hyperlinks oHyperlinks = m_oDoc.GetHyperlinks();
					COleVariant vAddr, vAddrSub, vScreenTip, vTextToDisplay;
					vAddr = _bstr_t(_T(""));
					vAddrSub = pBkmk->m_strID;
					vScreenTip = pRptData->m_strName;
					vTextToDisplay = strText;
					oHyperlinks.Add(oRange, vAddr, vAddrSub, vScreenTip, vTextToDisplay, vOpt);
					wordSelection.HomeKey(&vHUnit, &vHCount2);
					strText = _T("\t\t");
					wordSelection.TypeText(strText);
					wordSelection = m_pWordApp->m_WordApp.GetSelection();
					wordSelection.EndKey(&vUnit, &vHCount2);
					wordSelection.TypeParagraph();
				}
			}
		}

		wordSelection.TypeParagraph();
	}
	catch (...)
	{
		
	}

	return 0;
}

void CWordRptFill::PrintReport()
{
	CTCtrlCntrBaseApp* pApp = g_theTCtrlCntrApp;

	if( !IsValidApp() || !IsValidDoc())
	{
		return;
	}

	try
	{
		COleVariant covTrue((short)TRUE),covFalse((short)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);	
		m_oDoc.PrintOut(covFalse,
			covOptional,//Append.
			covOptional,//Range.
			covOptional,//OutputFileName.
			covOptional,//From.
			covOptional,//To.
			covOptional,//Item.
			covOptional,//Copies.
			covOptional,//Pages.
			covOptional,//PageType.
			covOptional,//PrintToFile.
			covOptional,//Collate.
			covOptional,//ActivePrinterMacGX.
			covOptional,//ManualDuplexPrint.
			covOptional,//PrintZoomColumnNewwithWord2002
			covOptional,//PrintZoomRowditto
			covOptional,//PrintZoomPaperWidthditto
			covOptional);//PrintZoomPaperHeightditto	
	}
	catch (...)
	{
	}
}

void CWordRptFill::ExportPdf()
{

}

void CWordRptFill::ZoomReport(long nPercentage)
{
	CTCtrlCntrBaseApp* pApp = g_theTCtrlCntrApp;

	if( !IsValidApp() || !IsValidDoc())
	{
		return;
	}

	try
	{
		MSWord::Window wnd;
		MSWord::View vw;
		wnd = m_pWordApp->m_WordApp.GetActiveWindow();
		vw = wnd.GetView();
		MSWord::Zoom zm;
		zm = vw.GetZoom();
		zm.SetPercentage(nPercentage);
	}
	catch (...) 
	{
	}	
}

long CWordRptFill::GetZoomReport()
{
	CTCtrlCntrBaseApp* pApp = g_theTCtrlCntrApp;
	long nPercentage = 100;

	if( !IsValidApp() || !IsValidDoc())
	{
		return nPercentage;
	}

	try
	{
		MSWord::Window wnd;
		MSWord::View vw;
		wnd = m_pWordApp->m_WordApp.GetActiveWindow();
		vw = wnd.GetView();
		MSWord::Zoom zm;
		zm = vw.GetZoom();
		nPercentage = zm.GetPercentage();
	}
	catch (...) 
	{
	}

	return nPercentage;
}

long CWordRptFill::AdjustReport_DelArea(CRptArea *pArea)
{
	if (pArea == NULL || pArea->GetCount() != 2 || !pArea->IsRptAdjustArea())
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

	CTCtrlCntrBaseApp* pApp = g_theTCtrlCntrApp;

	try
	{
		MSWord::Selection oSelection;
		MSWord::Bookmarks bookmarks;
		MSWord::Bookmark bookmark;

		oSelection = m_pWordApp->m_WordApp.GetSelection();
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

long CWordRptFill::LocateReport(CRptBkmk *pBkmk)
{
	CTCtrlCntrBaseApp* pApp = g_theTCtrlCntrApp;

	if( !IsValidApp() || !IsValidDoc())
	{
		return -1;
	}

	try
	{
		MSWord::Selection sel;
		MSWord::Bookmarks bookmarks;
		MSWord::Bookmark bookmark;

		sel = m_pWordApp->m_WordApp.GetSelection();

		bookmarks = m_oDoc.GetBookmarks();
		if(!pBkmk->m_strID.IsEmpty() && bookmarks.Exists(pBkmk->m_strID))
		{
			COleVariant vIndex(pBkmk->m_strID);
			bookmark = bookmarks.Item(&vIndex);
			bookmark.Select();
			return 1;
		}
	}
	catch(...)
	{
	}

	return 0;
}

long CWordRptFill::GetBkmkPos(CRptBkmk *pBkmk, long &nBeginPos, long &nEndPos)
{
	GetBkmkPos(m_oDoc, pBkmk, nBeginPos, nEndPos);

	return 0;
}

void CWordRptFill::EmptyReportText()
{
	CTCtrlCntrBaseApp* pApp = g_theTCtrlCntrApp;

	MSWord::Selection sel;
	MSWord::Bookmarks bookmarks;
	sel = m_pWordApp->m_WordApp.GetSelection();
	bookmarks = m_oDoc.GetBookmarks();

	ClearBkmksText(m_pGuideBook, sel, bookmarks);
}

void CWordRptFill::DeleteBkmk(const CString &strBkmk)
{
	try
	{
		MSWord::Bookmarks bookmarks = m_oDoc.GetBookmarks();
		if (bookmarks.Exists(strBkmk))
		{
			COleVariant vIndex(strBkmk);
			MSWord::Bookmark  bookmark = bookmarks.Item(&vIndex);
			bookmark.Delete();
		}
	}
	catch (...)
	{
	}
}


void CWordRptFill::AdjustReport_DelRow(CRptBkmk *pBkmk)
{
	try
	{
		MSWord::Bookmarks bookmarks = NULL;
		MSWord::Bookmark bookmark = NULL;
		MSWord::Selection sel = NULL;
		MSWord::Rows  rows = NULL;

		bookmarks = m_oDoc.GetBookmarks();

		if(pBkmk->m_strID.IsEmpty() || (!bookmarks.Exists(pBkmk->m_strID)) )
		{
			return;
		}

		COleVariant vIndex(pBkmk->m_strID);
		bookmark = bookmarks.Item(&vIndex);
		bookmark.Select();
		sel = m_pWordApp->m_WordApp.GetSelection();
		rows = sel.GetRows();
		rows.Delete();
	}
	catch(...)
	{
	}
}

void CWordRptFill::AdjustReport_DelCol(CRptBkmk *pBkmk)
{
	try
	{
		MSWord::Bookmarks bookmarks = NULL;
		MSWord::Bookmark bookmark = NULL;
		MSWord::Selection sel = NULL;
		MSWord::Columns  cols = NULL;

		bookmarks = m_oDoc.GetBookmarks();

		if(pBkmk->m_strID.IsEmpty() || (!bookmarks.Exists(pBkmk->m_strID)) )
		{
			return;
		}

		COleVariant vIndex(pBkmk->m_strID);
		bookmark = bookmarks.Item(&vIndex);
		bookmark.Select();
		sel = m_pWordApp->m_WordApp.GetSelection();
		cols = sel.GetColumns();
		cols.Delete();
	}
	catch(...)
	{
	}
}

long CWordRptFill::GetBkmkPos(MSWord::_Document &oDoc, CRptBkmk *pBkmk, long &nBeginPos, long &nEndPos)
{
	nBeginPos = -1;
	nEndPos = -1;
	CTCtrlCntrBaseApp* pApp = g_theTCtrlCntrApp;

	try
	{
		MSWord::Bookmarks bookmarks;
		MSWord::Bookmark bookmark;

		bookmarks = oDoc.GetBookmarks();

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

//根据pReport获得Item对象，如果Item对象为通讯命令对象
//且通讯命令对象中能够找到pData数据
//如果pData数据对应的Tag对象的DataTyoe为“col-mode”
//则获取报告数据的m_oRprDataEx
//获取pItem的m_oRptTags中的“Count”Tag，
//获取表格，逐行填写

/*
Sub Test()
'
' Test Macro
' 宏在 2010-12-23 由 LJQ 创建
'
	Dim nIndex As Long
	Dim oTable As Table
	Dim oCell As Cell
	Dim oRow As Row
	Dim oRng As Range
	Dim oBkmk As Bookmark
	Dim oBkmks As Bookmarks
	Dim oCols As Columns
	Dim oCol As Column


	nIndex = 1

	Set oBkmks = ActiveDocument.Bookmarks
	Set oBkmk = oBkmks.Item(1)
	oBkmk.Select
	Set oCols = oBkmk.Range.Columns
	Set oCol = oCols.Item(1)

	Dim count As Long

	Dim oCells As Cells

	Set oCells = oCol.Cells
	count = oCells.count

	For nIndex = 1 To count
		Set oCell = oCells.Item(nIndex)
		oCell.Select
		Set oRng = oCell.Range
		oRng.Text = "123456789"
	Next nIndex

End Sub

*/

MSWord::Cells CWordRptFill::GetCells(CRptBkmk *pBkmk, BOOL bRowMode)
{
	if (pBkmk->m_strID.IsEmpty())
	{
		return NULL;
	}

	MSWord::Cells oCells = NULL;
	MSWord::Bookmarks oBkmks = NULL;
	MSWord::Bookmark oBkmk = NULL;

	try
	{
		oBkmks = m_oDoc.GetBookmarks();

		if (oBkmks.Exists(pBkmk->m_strID))
		{
			COleVariant vIndex(pBkmk->m_strID);
			oBkmk = oBkmks.Item(&vIndex);
			oBkmk.Select();
			MSWord::Range oRange = oBkmk.GetRange();

			if (bRowMode)
			{
				MSWord::Columns oCols = NULL;
				MSWord::Column oCol = NULL;
				oCols = oRange.GetColumns();
				oCol = oCols.Item(1);
				oCells = oCol.GetCells();
			}
			else
			{
				MSWord::Rows oRows = NULL;
				MSWord::Row oRow = NULL;
				oRows = oRange.GetColumns();
				oRow = oRows.Item(1);
				oCells = oRow.GetCells();
			}
		}
	}
	catch(...)
	{

	}

	return oCells;
}

/*
<data name="测试仪定义" id="TestAppDef" precision="">
	<bkmk attr-id="Factory" process="" fill-mode="row">Bmk211D016D00D11L951_54</bkmk>
	<bkmk attr-id="Model" process="" fill-mode="row">Bmk21D1B0C16C001H493K7_55</bkmk>
	<bkmk attr-id="Name" process="" fill-mode="row">Bmk21D1B01I600E17L995_56</bkmk>
	<bkmk attr-id="SN" process="" fill-mode="row">Bmk2C1C1B0C160D0D20D17I6_57</bkmk>
	<bkmk attr-id="DateManufac" process="" fill-mode="row">Bmk211D016D002F261M9_58</bkmk>
</data>
*/
void CWordRptFill::FillReportDatasetRowMode(CRptData *pData, CDvmDataset *pDataset)
{
	CTCtrlCntrBaseApp* pApp = g_theTCtrlCntrApp;

	if( !IsValidApp() || !IsValidDoc() || pData->GetCount() == 0)
	{
		return;
	}

	long nDataCount = pDataset->GetCount();
	long nIndex = 0;

	if (nDataCount <= 0)
	{
		return;
	}

	POS posbkmk = pData->GetHeadPosition();
	CRptBkmk *pBkmk = (CRptBkmk*)pData->GetHead();
	MSWord::Cells oCells = NULL;
	MSWord::Cell oCell = NULL;
	CDvmData * oData;
	CString strValue;
	CString bstrDataExTagID;

	while (posbkmk != NULL)
	{
		pBkmk = (CRptBkmk*)pData->GetNext(posbkmk);
		bstrDataExTagID = pBkmk->m_strDataAttrID;
		oCells = GetCells(pBkmk, TRUE);

		if (oCells == NULL)
		{
			return;
		}

		try
		{
			//从第一行开始
			for (nIndex=2; nIndex<=nDataCount; nIndex++)
			{
				oData = (CDvmData*)pDataset->GetAtIndex(nIndex-2);

				if (oData == NULL)
				{
					break;
				}

				oCell = oCells.Item(nIndex);
				if (!oData->GetValueByID(bstrDataExTagID, strValue))
				{
					strValue = L"****";
				}

				FillReportCell(_bstr_t(strValue), oCell);
			}
		}
		catch(...)
		{
		}
	}
}

void CWordRptFill::FillReportGroupColMode(CRptData *pData, CReport *pReport, CShortData * oTagDataDef)
{
	CTCtrlCntrBaseApp* pApp = g_theTCtrlCntrApp;

	if( !IsValidApp() || !IsValidDoc() || pData->GetCount() == 0)
	{
		return;
	}

	//获取pItem的m_oRptTags中的“Count”Tag，
	CCommCmd *pCommCmd = (CCommCmd*)pReport->GetParent()->GetParent();
	long nDataCount = Gb_RptFill_GetReportGroupDataCount(pCommCmd, pReport);
	long nIndex = 0;
	_bstr_t bstrRptExTagID = oTagDataDef->m_strValue;

	if (nDataCount <= 0)
	{
		return;
	}

	CRptBkmk *pBkmk = (CRptBkmk*)pData->GetHead();
	MSWord::Cells oCells = NULL;
	MSWord::Cell oCell = NULL;

	oCells = GetCells(pBkmk, FALSE);

	if (oCells == NULL)
	{
		return;
	}

	try
	{
		//扩展报告数据
		CDvmDataset * oDatas;
		CDvmData * oData;
		oDatas = pReport->m_pRptDvmDataset;
		CString bstrDataExTagID = oTagDataDef->m_strValue;
		CString strValue;
		long nCountTemp = oDatas->GetCount();

		//从第二行开始
		for (nIndex=2; nIndex<=nDataCount; nIndex++)
		{
			if (nCountTemp <= nIndex - 2)
			{
				break;
			}

			oData = (CDvmData*)oDatas->GetAtIndex(nIndex-2);

			if (oData == NULL)
			{
				break;
			}

			oCell = oCells.Item(nIndex);
			if (!oData->GetValueByID(bstrDataExTagID, strValue))
			{
				strValue = L"****";
			}

			FillReportCell(_bstr_t(strValue), oCell);
		}
	}
	catch(...)
	{
	}
}

void CWordRptFill::FillReportCell(const _bstr_t &strValue, MSWord::Cell oCell)
{
	oCell.Select();
	MSWord::Range oRange = oCell.GetRange();
	oRange.SetText(strValue);
}

void CWordRptFill::FillReport_Cell(const CString &strValue, CRptBkmk *pBkmk, long nRptIndex, BOOL bSetColor)
{
	CTCtrlCntrBaseApp* pApp = g_theTCtrlCntrApp;

	try
	{
		MSWord::Bookmarks bookmarks;
		MSWord::Bookmark bookmark;

		bookmarks = m_oDoc.GetBookmarks();

		if(pBkmk->m_strID.IsEmpty() || (!bookmarks.Exists(pBkmk->m_strID)) )
		{
			return;
		}

		COleVariant vIndex(pBkmk->m_strID);
		bookmark = bookmarks.Item(&vIndex);
		FillReport_Cell(strValue, bookmark, nRptIndex, bSetColor);
	}
	catch(...)
	{
	}
}

void CWordRptFill::FillReport_Cell(const CString &strValue, MSWord::Bookmark &bookmark, long nRptIndex, BOOL bSetColor)
{
	CTCtrlCntrBaseApp* pApp = g_theTCtrlCntrApp;

	try
	{
		MSWord::Selection sel;
		MSWord::Range  range = NULL;
		MSWord::Paragraphs  paragraphs = NULL;
		MSWord::Paragraph paragraph = NULL;
		MSWord::Range rangeParagraph = NULL;
		long lRangeStart = 0;
		long lRangeEnd = 0;
		long lRangeStart2 = 0;
		long lRangeEnd2 = 0;
		long lEndTemp = 0;

		bookmark.Select();
		sel = m_pWordApp->m_WordApp.GetSelection();

		if (g_bClearBeforeFillRpt)
		{
			MSWord::Cells oCells = sel.GetCells();

			if (oCells.GetCount() > 0)
			{
				MSWord::Cell oCell = oCells.Item(1);
				oCell.Select();
				sel = m_pWordApp->m_WordApp.GetSelection();
			}
			else
			{
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
			}
		}
		else
		{
			lRangeStart2 = sel.GetStart();
			lRangeEnd2 = sel.GetEnd();
		}

		if (bSetColor)
		{
			try
			{
				MSWord::_Font oFont = sel.GetFont();
				COLORREF cr = oFont.GetColor();
				oFont.SetColor(m_crReport);
				oFont.SetBold(m_nInlegibleFontBold);  //2021-2-26  lijunqing

				range = bookmark.GetRange();
				paragraphs = range.GetParagraphs();
				paragraph = paragraphs.GetFirst();
				rangeParagraph = paragraph.GetRange();
				rangeParagraph.SetHighlightColorIndex(m_crReportBackground);
			}
			catch (...)
			{
			}
		}

		sel.SetText(_bstr_t(strValue));

		After_Put_Text(sel, bookmark, lRangeEnd2);
	}
	catch(...)
	{
	}
}

//第二次调用【sel.put_Text(_bstr_t(strValue));】会导致bookmark消失，因此需要增加书签添加功能
void CWordRptFill::After_Put_Text(MSWord::Selection &sel, MSWord::Bookmark &bookmark, long lRangeEndPrev)
{
	WPS::Bookmarks wpsBookmarks = m_oDoc.GetBookmarks();

	if((!wpsBookmarks.Exists(m_pCurrBkmk->m_strID)))
	{
		COleVariant vOpt(DISP_E_PARAMNOTFOUND, VT_ERROR);
		wpsBookmarks.Add(m_pCurrBkmk->m_strID, vOpt);
	}

	//会影响标签的位置
	//shaolei 注释此处  2023-10-12 begin
// 	long lRangeEnd3 = sel.GetEnd();
// 
// 	if (lRangeEndPrev != lRangeEnd3)
// 	{
// 		bookmark.SetEnd(lRangeEnd3);
// 	}
	//end
}


void CWordRptFill::FillReport_Col(const CString &strValue, CRptBkmk *pBkmk, long nRptIndex, BOOL bSetColor)
{
	CTCtrlCntrBaseApp* pApp = g_theTCtrlCntrApp;
	m_pCurrBkmk = pBkmk;

	try
	{
		MSWord::Cell oCell   = NULL;
		MSWord::Cells oCells = NULL;
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

		bookmarks = m_oDoc.GetBookmarks();

		if(pBkmk->m_strID.IsEmpty() || (!bookmarks.Exists(pBkmk->m_strID)) )
		{
			return;
		}

		COleVariant vIndex(pBkmk->m_strID);
		bookmark = bookmarks.Item(&vIndex);
		bookmark.Select();
		MSWord::Range oRange = bookmark.GetRange();
		oCells = oRange.GetCells();
		long nCount = oCells.GetCount();
		MSWord::Cell oCel = oCells.Item(1);
		long nRowIndex = oCel.GetRowIndex();
		long nColIndex = oCel.GetColumnIndex();

		long nCurrRowIndex = nRowIndex + nRptIndex;

		MSWord::Column oCol = oCel.GetColumn();
		oCells = oCol.GetCells();
		sel = m_pWordApp->m_WordApp.GetSelection();
		long nCurrCells = oCells.GetCount();

		if (nCurrCells < nCurrRowIndex)
		{
			oCel = oCells.Item(nCurrCells);
			oCel.Select();
			CComVariant vCount(long(nCurrRowIndex - nCurrCells)); 
			sel.InsertRowsBelow(&vCount);
			oCells = oCol.GetCells();
		}

		oCel = oCells.Item(nCurrRowIndex);
		oCel.Select();

		if (bSetColor)
		{
			try
			{
				MSWord::_Font oFont = sel.GetFont();
				COLORREF cr = oFont.GetColor();
				oFont.SetColor(m_crReport);
				oFont.SetBold(m_nInlegibleFontBold);  //2021-2-26  lijunqing

				paragraphs = oRange.GetParagraphs();
				paragraph = paragraphs.GetFirst();
				rangeParagraph = paragraph.GetRange();
				rangeParagraph.SetHighlightColorIndex(m_crReportBackground);
			}
			catch (...)
			{
			}
		}

		sel.SetText(_bstr_t(strValue));
	}
	catch(...)
	{
	}

	m_pCurrBkmk = NULL;
}

void CWordRptFill::FillReport_Row(const CString &strValue, CRptBkmk *pBkmk, long nRptIndex, BOOL bSetColor)
{
	CTCtrlCntrBaseApp* pApp = g_theTCtrlCntrApp;
	m_pCurrBkmk = pBkmk;

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

		bookmarks = m_oDoc.GetBookmarks();
		if(!pBkmk->m_strID.IsEmpty() && bookmarks.Exists(pBkmk->m_strID))
		{
			COleVariant vIndex(pBkmk->m_strID);
			bookmark = bookmarks.Item(&vIndex);
			bookmark.Select();
			sel = m_pWordApp->m_WordApp.GetSelection();

			if (g_bClearBeforeFillRpt)
			{
				MSWord::Cells oCells = sel.GetCells();
				if (oCells.GetCount() > 0)
				{
					MSWord::Cell oCell = oCells.Item(1);
					oCell.Select();
					sel = m_pWordApp->m_WordApp.GetSelection();
				}
				else
				{
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
				}
			}
			else
			{
				MSWord::Cells oCells = GetCells(pBkmk, TRUE);

				if (oCells != NULL)
				{
					if (oCells.GetCount() > 0)
					{
						MSWord::Cell oCell = oCells.Item(nRptIndex + 1);
						oCell.Select();
						sel = m_pWordApp->m_WordApp.GetSelection();
					}
				}
				
				lRangeStart2 = sel.GetStart();
				lRangeEnd2 = sel.GetEnd();
			}
			
			if (bSetColor)
			{
				try
				{
					MSWord::_Font oFont = sel.GetFont();
					COLORREF cr = oFont.GetColor();
					oFont.SetColor(m_crReport);
					oFont.SetBold(m_nInlegibleFontBold);  //2021-2-26  lijunqing

					range = bookmark.GetRange();
					paragraphs = range.GetParagraphs();
					paragraph = paragraphs.GetFirst();
					rangeParagraph = paragraph.GetRange();
					rangeParagraph.SetHighlightColorIndex(m_crReportBackground);
				}
				catch (...)
				{
				}
			}

			sel.SetText(_bstr_t(strValue));
			After_Put_Text(sel, bookmark, lRangeEnd2);
		}
	}
	catch(...)
	{
	}
}


CString CWordRptFill::GetBkmkText(MSWord::Bookmark &bookmark)
{
	CTCtrlCntrBaseApp* pApp = g_theTCtrlCntrApp;
	CString strText;

	try
	{
		MSWord::Selection sel;
		MSWord::Range  range = NULL;
		MSWord::Paragraphs  paragraphs = NULL;
		MSWord::Paragraph paragraph = NULL;
		MSWord::Range rangeParagraph = NULL;
		long lRangeStart = 0;
		long lRangeEnd = 0;
		long lRangeStart2 = 0;
		long lRangeEnd2 = 0;
		long lEndTemp = 0;

		bookmark.Select();
		sel = m_pWordApp->m_WordApp.GetSelection();
		MSWord::Cells oCells = sel.GetCells();

		if (oCells.GetCount() > 0)
		{
			MSWord::Cell oCell = oCells.Item(1);
			oCell.Select();
			sel = m_pWordApp->m_WordApp.GetSelection();
		}
		else
		{
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
		}

		strText = sel.GetText();

		long nRight = strText.GetLength() - 1;
		while (nRight >= 0)
		{
			if (strText.GetAt(nRight) <= 0x0F)
			{
				strText.SetAt(nRight, 0);
			}
			else
			{
				break;
			}

			nRight--;
		}
	}
	catch(...)
	{
	}

	return strText;
}

CString CWordRptFill::GetBkmkText(MSWord::_Document &oDoc, CRptBkmk *pBkmk)
{
	CString strText;

	try
	{
		MSWord::Selection sel;
		MSWord::Bookmarks bookmarks;
		MSWord::Bookmark bookmark;

		bookmarks = m_oDoc.GetBookmarks();
	
		if(!pBkmk->m_strID.IsEmpty() && bookmarks.Exists(pBkmk->m_strID))
		{
			COleVariant vIndex(pBkmk->m_strID);
			bookmark = bookmarks.Item(&vIndex);
			strText = GetBkmkText(bookmark);
		}
	}
	catch (...)
	{
		
	}

	return strText;
}

/*
Selection.InlineShapes.AddPicture FileName:="D:\Test_2.png", LinkToFile:= _
False, SaveWithDocument:=True
*/

void CWordRptFill::FillReportFile(const CString &strValue, CRptBkmk *pBkmk)
{
	CTCtrlCntrBaseApp* pApp = g_theTCtrlCntrApp;

	if( !IsValidApp() || !IsValidDoc())
	{
		return;
	}
	
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

		sel = m_pWordApp->m_WordApp.GetSelection();

		bookmarks = m_oDoc.GetBookmarks();
		if(!pBkmk->m_strID.IsEmpty() && bookmarks.Exists(pBkmk->m_strID))
		{
			COleVariant vIndex(pBkmk->m_strID);
			COleVariant vUnit((long)MSWord::wdCharacter);
			COleVariant vCount((long)1);
			bookmark = bookmarks.Item(&vIndex);
			bookmark.Select();

			range = bookmark.GetRange();
			MSWord::Cells oCells = range.GetCells();
			MSWord::Cell  oCell = oCells.Item(1);
			oCell.Select();
			sel = m_pWordApp->m_WordApp.GetSelection();
			sel.Delete(vUnit, vCount);

			MSWord::InlineShapes oInlineShapes = sel.GetInlineShapes();

			COleVariant vLinkFile((long)0);
			COleVariant vSave((long)1);
			COleVariant vRange;
			vRange.vt=VT_DISPATCH;
			vRange.pdispVal = range.m_lpDispatch;
			range.m_lpDispatch->AddRef();

			oInlineShapes.AddPicture(strValue, &vLinkFile, &vSave, &vRange);
			vRange.Detach();

			vCount = ((long)1);
			COleVariant vExtend((long)MSWord::wdExtend);
			sel = m_pWordApp->m_WordApp.GetSelection();
			sel.MoveLeft(&vUnit, &vCount, &vExtend);
			oInlineShapes = sel.GetInlineShapes();
			MSWord::InlineShape oInlineShape = oInlineShapes.Item(1);

			if (oInlineShape != NULL)
			{
				MSWord::Shape oShape = oInlineShape.ConvertToShape();
				MSWord::PictureFormat oFormat = oShape.GetPictureFormat();
				MSWord::WrapFormat wrapp = oShape.GetWrapFormat();
				wrapp.SetType(MSWord::wdWrapSquare);
			}
		}
	}
	catch(...)
	{
	}
}

void CWordRptFill::FillReportClipboard(CRptBkmk *pBkmk)
{
	if( !IsValidApp() || !IsValidDoc())
	{
		return;
	}

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

		sel = m_pWordApp->m_WordApp.GetSelection();
		bookmarks = m_oDoc.GetBookmarks();

		if(!pBkmk->m_strID.IsEmpty() && bookmarks.Exists(pBkmk->m_strID))
		{
			COleVariant vIndex(pBkmk->m_strID);
			COleVariant vUnit((long)MSWord::wdCharacter);
			COleVariant vCount((long)1);
			bookmark = bookmarks.Item(&vIndex);
			bookmark.Select();

			range = bookmark.GetRange();
			MSWord::Cells oCells = range.GetCells();
			MSWord::Cell  oCell = oCells.Item(1);
			oCell.Select();
			sel = m_pWordApp->m_WordApp.GetSelection();
			lRangeStart2 = sel.GetStart();
			lRangeEnd2 = sel.GetEnd();
			sel.Delete(vUnit, vCount);
			sel.Delete(vUnit, vCount);
			sel.Paste();
			After_Put_Text(sel, bookmark, lRangeEnd2);
		}
	}
	catch(...)
	{
	}
}

void CWordRptFill::ClearBkmksText(CExBaseList *pList, MSWord::Selection &sel, MSWord::Bookmarks &bookmarks)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = pList->GetNext(pos);

		if (p->GetClassID() == RPTCLASSID_RPTAREA)
		{
			continue;
		}

		if (p->IsBaseList())
		{
			ClearBkmksText((CExBaseList*)p, sel, bookmarks);
		}
		else
		{
			if (p->GetClassID() == RPTCLASSID_RPTBKMK)
			{
				ClearBkmkText((CRptBkmk*)p, sel, bookmarks);
			}
		}
	}
}

void CWordRptFill::ClearBkmkText(CRptBkmk *pBkmk, MSWord::Selection &sel, MSWord::Bookmarks &bookmarks)
{
	m_pCurrBkmk = pBkmk;

	try
	{
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

			//shaolei 2021 06 24 调用SetText会删除书签，此处再补上书签
			After_Put_Text(sel, bookmark, lRangeEnd2);
		}
	}
	catch(...)
	{
	}

	m_pCurrBkmk = NULL;
}

//////////////////////////////////////////////////////////////////////////
//
void CWordRptFill::InitWordRptBkmkMgrpCmbn()
{
	try
	{
		MSWord::Bookmarks bookmarks;
		MSWord::Bookmark bookmark;
		bookmarks = m_oDoc.GetBookmarks();
		InitWordRptBkmkMgrpCmbn(m_pGuideBook, bookmarks);
	}
	catch (...)
	{
		
	}
}

void CWordRptFill::CmbmMgrpt(CRptFillInterface *pRptFill, long nMgbrpIndex)
{
	CWordRptFill* pWordRptFill = (CWordRptFill*)pRptFill;
	static CString g_strTitleIndex[14] = {_T("二"), _T("三"),_T("四"),_T("五"),_T("六"), _T("七"), _T("八"), _T("九"), _T("十")
		, _T("十一"), _T("十三"), _T("十四"), _T("十五")};
	m_strMgrpIndex.Format(_T("通道%s"), g_strTitleIndex[nMgbrpIndex]);

	//合并区域
	CmbmMgrpt((CExBaseList*)m_pGuideBook, pWordRptFill);

	//合并标签
	WordRptBkmkMgrpCmbn(pWordRptFill->m_oDoc);
}

void CWordRptFill::CmbmMgrpt(CExBaseList *pListItems, CWordRptFillBase *pRptFill)
{
	CWordRptFill* pWordRptFill = (CWordRptFill*)pRptFill;
	MSWord::_Document oDocMgrpt = pWordRptFill->m_oDoc;

	UINT nClassID = pListItems->GetClassID();
	BOOL bTrue = FALSE;

	POS pos = pListItems->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pListItems->GetNext(pos);
		nClassID = p->GetClassID();
		bTrue = FALSE;

		if (nClassID == GBCLASSID_ITEMS)
		{
//			CmbmMgrpt((CItems*)p, oDocMgrpt);
			CmbmMgrpt((CItems*)p, pRptFill);
			bTrue = TRUE;
		}
		else if (nClassID == GBCLASSID_GUIDEBOOK
			|| nClassID == GBCLASSID_DEVICE
			|| nClassID == GBCLASSID_JOBGUIDE)
		{
			bTrue = TRUE;
		}

		if (bTrue)
		{
//			CmbmMgrpt((CExBaseList*)p, oDocMgrpt);
			CmbmMgrpt((CExBaseList*)p, pRptFill);
		}
	}
}

void CWordRptFill::CmbmMgrpt(CItems *pItems, CWordRptFillBase *pRptFill)
{
	CWordRptFill* pWordRptFill = (CWordRptFill*)pRptFill;
	MSWord::_Document oDocMgrpt = pWordRptFill->m_oDoc;

	CReportMap *pRptMap = pItems->GetReportMap();

	if (pRptMap == NULL)
	{
		return;
	}

	if (pRptMap->m_pArea == NULL)
	{
		return;
	}

	if (pRptMap->m_pArea->GetCount() != 2)
	{
		return;
	}

	if (pRptMap->m_pArea->IsRptAdjustArea())
	{
		return;
	}

	CmbmMgrpt(pRptMap->m_pArea, pRptFill);
}

void CWordRptFill::CmbmMgrpt(CRptArea *pArea, CWordRptFillBase *pRptFill)
{
	CWordRptFill* pWordRptFill = (CWordRptFill*)pRptFill;
	MSWord::_Document oDocMgrpt = pWordRptFill->m_oDoc;

	if (!CmbnCopyMgrpt(pArea, oDocMgrpt))
	{
		return;
	}

	CmbnPasteMgrpt(pArea->m_pBkmkEnd);
}

BOOL CWordRptFill::CmbnSelectBkmk(CRptBkmk *pBkmk, MSWord::_Document& oDoc)
{
	try
	{
		MSWord::Selection oSelection;
		MSWord::Bookmarks bookmarks;
		MSWord::Bookmark bookmark;

		bookmarks = oDoc.GetBookmarks();

		if (bookmarks.Exists(pBkmk->m_strID))
		{
			COleVariant vIndex(pBkmk->m_strID);
			bookmark = bookmarks.Item(&vIndex);
			bookmark.Select();
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	catch(...)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CWordRptFill::CmbnCopyMgrpt(CRptArea *pArea, MSWord::_Document& oDoc)
{
	long nBeginPos1, nEndPos1, nBeginPos2, nEndPos2;
	GetBkmkPos(oDoc, pArea->m_pBkmkBegin, nBeginPos1, nEndPos1);
	GetBkmkPos(oDoc, pArea->m_pBkmkEnd, nBeginPos2, nEndPos2);

	if (nEndPos1 == -1 || nEndPos1 == -1 || nBeginPos2 == -1 || nEndPos2 == -1)
	{
		return FALSE;
	}

	if (!CmbnSelectBkmk(pArea->m_pBkmkBegin, oDoc))
	{
		return FALSE;
	}

	try
	{
		MSWord::Selection oSelection;
		MSWord::Bookmarks bookmarks;
		MSWord::Bookmark bookmark;

		bookmarks = oDoc.GetBookmarks();
		oSelection = m_pWordApp->m_WordApp.GetSelection();
		bookmarks = oDoc.GetBookmarks();
		oSelection.SetStart(nBeginPos1);
		oSelection.SetEnd(nEndPos2);
		oSelection.Select();
		oSelection.Copy();
	}
	catch(...)
	{
		return FALSE;
	}

	return TRUE;
}

void CWordRptFill::CmbnPasteMgrpt(CRptBkmk *pEndBkmk)
{
	if (!CmbnSelectBkmk(pEndBkmk, m_oDoc))
	{
		return;
	}

	try
	{
		MSWord::Selection oSelection;

		oSelection = m_pWordApp->m_WordApp.GetSelection();
		oSelection.TypeText(m_strMgrpIndex);
		oSelection.TypeParagraph();
		oSelection.Paste();
	}
	catch(...)
	{
	}
}


void CWordRptFill::InitWordRptBkmkMgrpCmbn(CExBaseList *pList, MSWord::Bookmarks &oBookmarks)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;
	CRptBkmk *pBkmk = NULL;
	CWordRptBkmkMgrpCmbn *pNew = NULL;

	while (pos != NULL)
	{
		p = pList->GetNext(pos);

		if (p->GetClassID() == RPTCLASSID_RPTBKMK)
		{
			pBkmk = (CRptBkmk*)p;

			if (pBkmk->m_strMgrpCmbnMode.GetLength() > 0)
			{
				pNew = new CWordRptBkmkMgrpCmbn();
				pNew->m_pBkmkRef = pBkmk;

				if(pBkmk->m_strID.IsEmpty() || (!oBookmarks.Exists(pBkmk->m_strID)) )
				{
					continue;;
				}

				COleVariant vIndex(pBkmk->m_strID);
				pNew->m_oBkmk = oBookmarks.Item(&vIndex);
				pNew->m_strValue = GetBkmkText(pNew->m_oBkmk);
				AddNewChild(pNew);
			}
		}
		else
		{
			if (p->IsBaseList())
			{
				InitWordRptBkmkMgrpCmbn((CExBaseList*)p, oBookmarks);
			}
		}
	}
}

void CWordRptFill::WordRptBkmkMgrpCmbn(MSWord::_Document &oDoc)
{
	POS pos = GetHeadPosition();
	CWordRptBkmkMgrpCmbn *pBkmkMgrpCmbn = NULL;

	while (pos != NULL)
	{
		pBkmkMgrpCmbn = (CWordRptBkmkMgrpCmbn *)GetNext(pos);
		WordRptBkmkMgrpCmbn(pBkmkMgrpCmbn, oDoc);
	}
}

void CWordRptFill::WordRptBkmkMgrpCmbn(CWordRptBkmkMgrpCmbn *pBkmkMgrpCmbn, MSWord::_Document &oDoc)
{
	CString strText;
	strText = GetBkmkText(oDoc, pBkmkMgrpCmbn->m_pBkmkRef);

	if (strText == pBkmkMgrpCmbn->m_strValue)
	{
		return;
	}

	if (pBkmkMgrpCmbn->m_pBkmkRef->m_strMgrpCmbnMode == _T("max_len"))
	{
		return WordRptBkmkMgrpCmbn_max_len(pBkmkMgrpCmbn, strText);
	}

	if (pBkmkMgrpCmbn->m_pBkmkRef->m_strMgrpCmbnMode == _T("min_len"))
	{
		return WordRptBkmkMgrpCmbn_min_len(pBkmkMgrpCmbn, strText);
	}

	if (pBkmkMgrpCmbn->m_pBkmkRef->m_strMgrpCmbnMode == _T("max_val"))
	{
		return WordRptBkmkMgrpCmbn_max_val(pBkmkMgrpCmbn, strText);
	}

	if (pBkmkMgrpCmbn->m_pBkmkRef->m_strMgrpCmbnMode == _T("min_val"))
	{
		return WordRptBkmkMgrpCmbn_min_val(pBkmkMgrpCmbn, strText);
	}

	if (pBkmkMgrpCmbn->m_pBkmkRef->m_strMgrpCmbnMode == _T("avg"))
	{
		return WordRptBkmkMgrpCmbn_avg(pBkmkMgrpCmbn, strText);
	}

	if (pBkmkMgrpCmbn->m_pBkmkRef->m_strMgrpCmbnMode == _T("sum"))
	{
		return WordRptBkmkMgrpCmbn_sum(pBkmkMgrpCmbn, strText);
	}
}

void CWordRptFill::WordRptBkmkMgrpCmbn_max_len(CWordRptBkmkMgrpCmbn *pBkmkMgrpCmbn, const CString &strText)
{
	if (strText.GetLength() <= pBkmkMgrpCmbn->m_strValue.GetLength())
	{
		return;
	}

	pBkmkMgrpCmbn->m_strValue = strText;
	FillReport_Cell(strText, pBkmkMgrpCmbn->m_oBkmk, 0, FALSE);
}

void CWordRptFill::WordRptBkmkMgrpCmbn_min_len(CWordRptBkmkMgrpCmbn *pBkmkMgrpCmbn, const CString &strText)
{
	if (strText.GetLength() > pBkmkMgrpCmbn->m_strValue.GetLength())
	{
		return;
	}

	pBkmkMgrpCmbn->m_strValue = strText;
	FillReport_Cell(strText, pBkmkMgrpCmbn->m_oBkmk, 0, FALSE);
}

void CWordRptFill::WordRptBkmkMgrpCmbn_max_val(CWordRptBkmkMgrpCmbn *pBkmkMgrpCmbn, const CString &strText)
{
	double dVal1 = CString_To_double(pBkmkMgrpCmbn->m_strValue);
	double dVal2 = CString_To_double(strText);

	if (dVal2 < dVal1)
	{
		return;
	}

	pBkmkMgrpCmbn->m_strValue = strText;
	FillReport_Cell(strText, pBkmkMgrpCmbn->m_oBkmk, 0, FALSE);
}

void CWordRptFill::WordRptBkmkMgrpCmbn_min_val(CWordRptBkmkMgrpCmbn *pBkmkMgrpCmbn, const CString &strText)
{
	double dVal1 = CString_To_double(pBkmkMgrpCmbn->m_strValue);
	double dVal2 = CString_To_double(strText);

	if (dVal2 > dVal1)
	{
		return;
	}

	pBkmkMgrpCmbn->m_strValue = strText;
	FillReport_Cell(strText, pBkmkMgrpCmbn->m_oBkmk, 0, FALSE);
}

void CWordRptFill::WordRptBkmkMgrpCmbn_avg(CWordRptBkmkMgrpCmbn *pBkmkMgrpCmbn, const CString &strText)
{

}

void CWordRptFill::WordRptBkmkMgrpCmbn_sum(CWordRptBkmkMgrpCmbn *pBkmkMgrpCmbn, const CString &strText)
{
	double dVal1 = CString_To_double(pBkmkMgrpCmbn->m_strValue);
	double dVal2 = CString_To_double(strText);
	dVal1 += dVal2;

	CRptData *pData = (CRptData *)pBkmkMgrpCmbn->m_pBkmkRef->GetParent();
	pBkmkMgrpCmbn->m_strValue.Format(_T("%f"), dVal1);
	ChopValueString(pData, pBkmkMgrpCmbn->m_strValue);

	FillReport_Cell(pBkmkMgrpCmbn->m_strValue, pBkmkMgrpCmbn->m_oBkmk, 0, FALSE);
}
