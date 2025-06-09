#include "StdAfx.h"
#include "WPSRptFill.h"
#include "..\..\..\..\..\Module\API\GlobalApi.h"

#include "..\..\..\TCtrlCntrDefine.h"

#include "..\..\..\XLanguageResourceAts.h"

#include "..\..\..\TestControl/TctrlCntrBaseApp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//CRptFillWPSApp

CRptFillWPSApp::CRptFillWPSApp()
{
	m_WPSCommandBarMngr.Init();
	m_WPSApp = NULL;
}

CRptFillWPSApp::~CRptFillWPSApp()
{
	if (m_WPSApp != NULL)
	{
		m_WPSApp.ReleaseDispatch();
		m_WPSApp = NULL;
	}
}

WPS::_Application CRptFillWPSApp::GetWPSApp(BOOL bShow)
{
	if (m_WPSApp == NULL)
	{
		//创建对象
		CreateApplication(bShow);
	}

	return m_WPSApp;
}

void CRptFillWPSApp::CreateApplication(BOOL bShow,long nHideAllCmdbars)
{
	COleVariant covTrue((long)TRUE),covFalse((long)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	try
	{
		if (!m_WPSApp.CreateDispatch(_T("kwps.Application")))
		{
			AfxMessageBox(_T("没有安装WPS"));
			return ;
		}

		m_WPSApp.put_Visible(bShow);  //This shows the application.
	}
	catch (...)
	{
		TRACE("catch error-----");
	}

	//关闭全部的工具条
	KSO::_CommandBars cmdbars;
	try
	{
		if (nHideAllCmdbars != 0)
		{
			cmdbars = m_WPSApp.get_CommandBars();
			m_WPSCommandBarMngr.InitWordCommandBarMngr(cmdbars);
		}
	}
	catch (...)
	{
		TRACE("catch error-----");
	}
}

void CRptFillWPSApp::SetViewSettings()
{
	if (m_WPSApp == NULL)
	{
		return;
	}

	try
	{
		WPS::View vw;
		WPS::Window wnd;
		wnd = m_WPSApp.get_ActiveWindow();

		if (wnd != NULL)
		{
			wnd.put_DocumentMap(FALSE);
			vw = wnd.get_View();

			if (vw != NULL)
			{
				m_bShowParagraphs = vw.get_ShowParagraphs();
				m_bShowBookmarks = vw.get_ShowBookmarks();
				vw.put_ShowParagraphs(FALSE);
				vw.put_ShowBookmarks(TRUE);
				m_WPSApp.put_DisplayStatusBar(FALSE);
			}
		}
	}
	catch(...)
	{
	}
}

void CRptFillWPSApp::RestoreViewSettings()
{
	if (m_WPSApp == NULL)
	{
		return;
	}

	try
	{
		WPS::Documents oDocs = m_WPSApp.get_Documents();
		if (oDocs.get_Count() > 1)
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
		WPS::View vw;
		WPS::Window wnd;
		wnd = m_WPSApp.get_ActiveWindow();

		if (wnd != NULL)
		{
			vw = wnd.get_View();

			if (vw != NULL)
			{
				vw.put_ShowParagraphs(m_bShowParagraphs);
				vw.put_ShowParagraphs(m_bShowBookmarks);
				m_WPSApp.put_DisplayStatusBar(TRUE);
			}
		}
	}
	catch(...)
	{
	}
}

void CRptFillWPSApp::CloseApplication()
{
	if (m_WPSApp == NULL)
	{
		return;
	}

	COleVariant covTrue((long)TRUE);
	COleVariant covFalse((long)FALSE);
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	try
	{
		WPS::Documents oDocs = m_WPSApp.get_Documents();

		if (oDocs.get_Count() > 0)
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
		if(m_WPSApp)
		{
			m_WPSApp.Quit(covFalse, covOptional, covOptional);
			m_WPSApp = NULL;
		}
	}
	catch (...) 
	{
		TRACE("catch error-----");
	}

	m_WPSApp = NULL;
}

void CRptFillWPSApp::RestoreCommandBars()
{
//	if (m_pCtrlCntrConfig->m_nHideAllCmdbars == 0)
//	{
//		return;
//	}

	if (m_WPSApp == NULL)
	{
		return;
	}

	KSO::_CommandBars cmdbars;
	try
	{
		cmdbars = m_WPSApp.get_CommandBars();
		m_WPSCommandBarMngr.LoadWordCommandBarMngr(cmdbars);
	}
	catch (...)
	{
		TRACE("catch error-----");
	}	

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//CWPSRptFill

CWPSRptFill::CWPSRptFill(void)
{
	m_oDoc = NULL;
	m_pWPSApp = (CRptFillWPSApp*)g_theRptFillApp;
}

CWPSRptFill::~CWPSRptFill(void)
{
	
}

long CWPSRptFill::OpenOnly(const CString  &strReportFile)
{
	CTCtrlCntrBaseApp* pApp = g_theTCtrlCntrApp;

	m_strReportFile = strReportFile;

	if (!IsFileExist(strReportFile))
	{
		return FALSE;
	}

	if ( m_pWPSApp->m_WPSApp == NULL)
	{
		m_pWPSApp->GetWPSApp(FALSE);
//		return FALSE;
	}

	if ( m_pWPSApp->m_WPSApp == NULL)
	{//2020-03-03  lijq  创建之后再次判断是否为空
		return FALSE;
	}

	m_strReportFile = strReportFile;

	WPS::Documents docs = NULL;
	docs =  m_pWPSApp->m_WPSApp.get_Documents();

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
//		m_oDoc = docs.Open(&vRptFile,covOptional,covFalse,covTrue,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covTrue);
		m_oDoc = docs.Open(&vRptFile,covOptional,covFalse,covTrue,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covTrue,
			covOptional,covOptional,covOptional,covOptional);
	}
	catch (...)
	{
		bTrue = FALSE;
	}

	return bTrue;
}

long CWPSRptFill::New(CString strReportMapFile, CString strReportTemplFile, CString strReportFile, BOOL bFirst)
{
	CTCtrlCntrBaseApp* pApp = g_theTCtrlCntrApp;

	m_strReportMapFile = strReportMapFile;
	m_strReportTemplFile = strReportTemplFile;
	m_strReportFile = strReportFile;

	COleVariant covTrue((long)TRUE),covFalse((long)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	COleVariant vTemplate(m_strReportTemplFile);			
	COleVariant vRptFile(m_strReportFile);			
	BOOL bWPSCreate = TRUE;

	if (m_pWPSApp->m_WPSApp == NULL)
	{
		return 0;
	}

	WPS::Documents docs;

	try
	{
		//如果打开了报告文档，则保存并关闭文档
		docs = m_pWPSApp->m_WPSApp.get_Documents();

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

long CWPSRptFill::Open(const CString  &strReportFile, BOOL bFirst)
{
	CTCtrlCntrBaseApp* pApp = g_theTCtrlCntrApp;

	m_strReportFile = strReportFile;
	
	if (!IsFileExist(strReportFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("[%s] error!"), strReportFile);
		return FALSE;
	}

	if (m_pWPSApp->m_WPSApp == NULL)
	{
		m_pWPSApp->GetWPSApp(FALSE);
//		return FALSE;

		if (m_pWPSApp->m_WPSApp == NULL)
		{
			return FALSE;
		}
	}


	WPS::Documents docs = NULL;
	docs = m_pWPSApp->m_WPSApp.get_Documents();

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
//			m_oDoc = docs.Open(&vRptFile,covOptional,covFalse,covTrue,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covTrue);
			m_oDoc = docs.Open(&vRptFile,covOptional,covFalse,covTrue,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covTrue,
				covOptional,covOptional,covOptional,covOptional);
		}
		else
		{
//			m_oDoc = docs.Open(&vRptFile,covOptional,covFalse,covTrue,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covFalse);
			m_oDoc = docs.Open(&vRptFile,covOptional,covFalse,covTrue,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covFalse,
				covOptional,covOptional,covOptional,covOptional);
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

long CWPSRptFill::Save()
{
	if( m_pWPSApp->m_WPSApp == NULL)
		return FALSE;

	if(m_oDoc == NULL)
		return FALSE;

	m_oDoc.Save();

	return TRUE;
}

long CWPSRptFill::SaveAs(CString  strRptFile)
{
	if( !IsValidApp() || !IsValidDoc())
		return FALSE;

	COleVariant covTrue((long)TRUE),covFalse((long)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	COleVariant vRptFile(strRptFile);
//	m_oDoc.SaveAs(vRptFile,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional);
	m_oDoc.SaveAs(vRptFile,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional);

	return TRUE;
}

long CWPSRptFill::Close(long nSave)
{
	if( !IsValidApp() || !IsValidDoc())
	{
		return TRUE;
	}

	CloseWordDocWindow();
	g_theRptFillApp->CloseApplication();

	return TRUE;
}

void CWPSRptFill::CloseDoc(DWORD dwFlag)
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
		TRACE("CloseWPSDocWindow:Error");
	}
}

BOOL CWPSRptFill::IsValidApp()
{
	return(m_pWPSApp->m_WPSApp != NULL);
}

BOOL CWPSRptFill::IsValidDoc()
{
	return(m_oDoc != NULL);
}

void CWPSRptFill::AdjustWordWindow()
{
	CTCtrlCntrBaseApp* pApp = g_theTCtrlCntrApp;

	CWnd *pWnd = NULL;
	//获取Word文档的窗口
	try
	{
		if (m_oDoc != NULL)
		{
			pWnd = FindRptDocWindowEx();
			WPS::Window docWnd = m_oDoc.get_ActiveWindow();

			if (docWnd != NULL)
			{
				CString strWPSCaption = m_pWPSApp->m_WPSApp.get_Caption();
				CString strWndCaption = docWnd.get_Caption();
				CString strWndTitle;
				strWndTitle.Format(_T("%s - %s"),strWndCaption,strWPSCaption);
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

		if (m_pWPSApp->m_WPSApp != NULL)
		{
			try
			{
				m_pWPSApp->m_WPSApp.put_Visible(TRUE);
				m_pWPSApp->m_WPSApp.put_DisplayStatusBar(TRUE);
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
			m_pWPSApp->m_WPSApp.put_Visible(FALSE);
			m_pWPSApp->m_WPSApp.put_DisplayStatusBar(TRUE);
		}
		catch (...)
		{
		}
	}

	try
	{
		if (m_oDoc != NULL)
		{
			WPS::Window docWnd = m_oDoc.get_ActiveWindow();
			docWnd.put_Visible(TRUE);
			CString strCaption = docWnd.get_Caption();
			WPS::View docView = docWnd.get_View();
			docView.put_Type(WPS::wpsPrintView);

			if (pApp->GetCntrConfig()->m_nHideAllCmdbars == 1)
			{
				KSO::_CommandBars cmdbars;
				cmdbars = m_oDoc.get_CommandBars();
				long nCount = cmdbars.get_Count();
				long nIndex = 1;
				CWordCommandBar *pCmdBar = NULL;

				for(nIndex=1;nIndex<=nCount;nIndex++)
				{
					KSO::CommandBar cmdbar = cmdbars.get_Item(COleVariant(nIndex));
					if (cmdbar.get_Enabled() && cmdbar.get_Visible())
					{
						cmdbar.put_Enabled(FALSE);
					}
				}
			}
		}
	}
	catch(...)
	{
	}
}

BOOL CWPSRptFill::CloseWordDocWindow()
{
	COleVariant covTrue((long)TRUE);
	COleVariant covFalse((long)FALSE);
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	try
	{
		g_theRptFillApp->RestoreViewSettings();

		if (m_oDoc != NULL)
		{
			m_oDoc.Close(covFalse,covOptional,covOptional);
			m_oDoc = NULL;
		}
	}
	catch (...) 
	{
		TRACE("CloseWPSDocWindow:Error");
	}

	return TRUE;
}

BOOL CWPSRptFill::ActiveWindow(const CString &strTitle)
{
	BOOL bTrue = FALSE;
	CTCtrlCntrBaseApp* pApp = g_theTCtrlCntrApp;

	try
	{
		WPS::Windows oWindows = m_pWPSApp->m_WPSApp.get_Windows();
		COleVariant oIndex;

		long nIndex = 1;
		long nCount = oWindows.get_Count();

		for (nIndex=1; nIndex<=nCount; nIndex++)
		{
			oIndex = nIndex;
			WPS::Window oWindow = oWindows.Item(&oIndex);
			CString strCaption = oWindow.get_Caption();

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

BOOL CWPSRptFill::AddNewReport(const CString &strRptTmplFile)
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
	WPS::Documents docs = m_pWPSApp->m_WPSApp.get_Documents();

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

long CWPSRptFill::FillReport(CReport* pReport, long nRepeatIndex, long nInsertDataLinkWhenEligible)
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
		COleVariant vUnit((long)WPS::wpsStory);
		COleVariant vCount((long)0);

		CGbItemBase *pGbItem = GetParentGbItem(pReport);

		//定位到文档末尾
		WPS::Selection wpsSelection = m_pWPSApp->m_WPSApp.get_Selection();
		wpsSelection = m_pWPSApp->m_WPSApp.get_Selection();
		WPS::_ParagraphFormat oFormat = wpsSelection.get_ParagraphFormat();
		wpsSelection.EndKey(&vUnit, &vCount);

		//字体和停靠
		oFormat.put_Alignment(WPS::wpsAlignParagraphLeft);
		WPS::_Font oFont = wpsSelection.get_Font();
		oFont.put_Size(10);
		CString strText = pGbItem->GetNamePathEx(GBCLASSID_DEVICE, TRUE, _T(" / "));
		wpsSelection.TypeText(strText);
		wpsSelection.TypeParagraph();

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
				wpsSelection.TypeText(strText);
				wpsSelection.TypeParagraph();

				POS posBkmk = pRptData->GetHeadPosition();
				CRptBkmk *pBkmk = NULL;
				long nIndex = 1;

				while (posBkmk != NULL)
				{
					//插入标签超级链接
					pBkmk = (CRptBkmk*)pRptData->GetNext(posBkmk);
					strText.Format(g_sLangTxt_DataD2/*_T("数据%d【%s】")*/, nIndex, pBkmk->m_strName);
					wpsSelection.TypeText(strText);
					COleVariant vHUnit((long)MSWord::wdLine);
					COleVariant vHCount((long)1);
					COleVariant vHCount2((long)0);
					wpsSelection.HomeKey(&vHUnit, &vHCount);
					WPS::Range oRange = wpsSelection.get_Range();
					WPS::Hyperlinks oHyperlinks = m_oDoc.get_Hyperlinks();
					COleVariant vAddr, vAddrSub, vScreenTip, vTextToDisplay;
					vAddr = _bstr_t(_T(""));
					vAddrSub = pBkmk->m_strID;
					vScreenTip = pRptData->m_strName;
					vTextToDisplay = strText;
					oHyperlinks.Add(oRange, vAddr, vAddrSub, vScreenTip, vTextToDisplay, vOpt);
					wpsSelection.HomeKey(&vHUnit, &vHCount2);
					strText = _T("\t\t");
					wpsSelection.TypeText(strText);
					wpsSelection = m_pWPSApp->m_WPSApp.get_Selection();
					wpsSelection.EndKey(&vUnit, &vHCount2);
					wpsSelection.TypeParagraph();
				}
			}
		}

		wpsSelection.TypeParagraph();
	}
	catch (...)
	{

	}

	return 0;
}

void CWPSRptFill::PrintReport()
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

void CWPSRptFill::ExportPdf()
{
	
}

void CWPSRptFill::ZoomReport(long nPercentage)
{
	CTCtrlCntrBaseApp* pApp = g_theTCtrlCntrApp;

	if( !IsValidApp() || !IsValidDoc())
	{
		return;
	}

	try
	{
		WPS::Window wnd;
		WPS::View vw;
		wnd = m_pWPSApp->m_WPSApp.get_ActiveWindow();
		vw = wnd.get_View();
		WPS::Zoom zm;
		zm = vw.get_Zoom();
		zm.put_Percentage(nPercentage);
	}
	catch (...) 
	{
	}	
}

long CWPSRptFill::GetZoomReport()
{
	CTCtrlCntrBaseApp* pApp = g_theTCtrlCntrApp;
	long nPercentage = 100;

	if( !IsValidApp() || !IsValidDoc())
	{
		return nPercentage;
	}

	try
	{
		WPS::Window wnd;
		WPS::View vw;
		wnd = m_pWPSApp->m_WPSApp.get_ActiveWindow();
		vw = wnd.get_View();
		WPS::Zoom zm;
		zm = vw.get_Zoom();
		nPercentage = zm.get_Percentage();
	}
	catch (...) 
	{
	}

	return nPercentage;
}

//调整报告的区域位置
long CWPSRptFill::AdjustReport_DelArea(CRptArea *pArea)
{
	if (pArea == NULL || pArea->GetCount() != 2 || !pArea->IsRptAdjustArea())
	{
		return 0;
	}

	ASSERT (pArea->m_pBkmkBegin != NULL && pArea->m_pBkmkEnd != NULL);
	long nPosBegin1 = 0, nPosEnd1 = 0;
	long nPosBegin2 = 0, nPosEnd2 = 0;
	CTCtrlCntrBaseApp* pApp = g_theTCtrlCntrApp;

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

		oSelection = m_pWPSApp->m_WPSApp.get_Selection();
		bookmarks = m_oDoc.get_Bookmarks();
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

long CWPSRptFill::LocateReport(CRptBkmk *pBkmk)
{
	if( !IsValidApp() || !IsValidDoc())
	{
		return -1;
	}

	try
	{
		WPS::Selection sel;
		WPS::Bookmarks bookmarks;
		WPS::Bookmark bookmark;

		sel = m_pWPSApp->m_WPSApp.get_Selection();

		bookmarks = m_oDoc.get_Bookmarks();
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

long CWPSRptFill::GetBkmkPos(CRptBkmk *pBkmk, long &nBeginPos, long &nEndPos)
{
	GetBkmkPos(m_oDoc, pBkmk, nBeginPos, nEndPos);

	return 0;
}

void CWPSRptFill::EmptyReportText()
{
	WPS::Selection sel;
	WPS::Bookmarks bookmarks;
	sel = m_pWPSApp->m_WPSApp.get_Selection();
	bookmarks = m_oDoc.get_Bookmarks();

	ClearBkmksText(m_pGuideBook, sel, bookmarks);
}

void CWPSRptFill::DeleteBkmk(const CString &strBkmk)
{
	try
	{
		WPS::Bookmarks bookmarks = m_oDoc.get_Bookmarks();
		if (bookmarks.Exists(strBkmk))
		{
			COleVariant vIndex(strBkmk);
			WPS::Bookmark  bookmark = bookmarks.Item(&vIndex);
			bookmark.Delete();
		}
	}
	catch (...)
	{
	}
}

void CWPSRptFill::AdjustReport_DelRow(CRptBkmk *pBkmk)
{
	try
	{
		WPS::Bookmarks bookmarks = NULL;
		WPS::Bookmark bookmark = NULL;
		WPS::Selection sel = NULL;
		WPS::Rows  rows = NULL;

		bookmarks = m_oDoc.get_Bookmarks();

		if(pBkmk->m_strID.IsEmpty() || (!bookmarks.Exists(pBkmk->m_strID)) )
		{
			return;
		}

		COleVariant vIndex(pBkmk->m_strID);
		bookmark = bookmarks.Item(&vIndex);
		bookmark.Select();
		sel = m_pWPSApp->m_WPSApp.get_Selection();
		rows = sel.get_Rows();
		rows.Delete();
	}
	catch(...)
	{
	}
}

void CWPSRptFill::AdjustReport_DelCol(CRptBkmk *pBkmk)
{
	try
	{
		WPS::Bookmarks bookmarks = NULL;
		WPS::Bookmark bookmark = NULL;
		WPS::Selection sel = NULL;
		WPS::Columns  cols = NULL;

		bookmarks = m_oDoc.get_Bookmarks();

		if(pBkmk->m_strID.IsEmpty() || (!bookmarks.Exists(pBkmk->m_strID)) )
		{
			return;
		}

		COleVariant vIndex(pBkmk->m_strID);
		bookmark = bookmarks.Item(&vIndex);
		bookmark.Select();
		sel = m_pWPSApp->m_WPSApp.get_Selection();
		cols = sel.get_Columns();
		cols.Delete();
	}
	catch(...)
	{
	}
}

long CWPSRptFill::GetBkmkPos(WPS::_Document &oDoc, CRptBkmk *pBkmk, long &nBeginPos, long &nEndPos)
{
	nBeginPos = -1;
	nEndPos = -1;
	
	try
	{
		WPS::Bookmarks bookmarks;
		WPS::Bookmark bookmark;

		bookmarks = oDoc.get_Bookmarks();

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

WPS::Cells CWPSRptFill::GetCells(CRptBkmk *pBkmk, BOOL bRowMode)
{
	if (pBkmk->m_strID.IsEmpty())
	{
		return NULL;
	}

	WPS::Cells oCells = NULL;
	WPS::Bookmarks oBkmks = NULL;
	WPS::Bookmark oBkmk = NULL;

	try
	{
		oBkmks = m_oDoc.get_Bookmarks();

		if (oBkmks.Exists(pBkmk->m_strID))
		{
			COleVariant vIndex(pBkmk->m_strID);
			oBkmk = oBkmks.Item(&vIndex);
			oBkmk.Select();
			WPS::Range oRange = oBkmk.get_Range();

			if (bRowMode)
			{
				WPS::Columns oCols = NULL;
				WPS::Column oCol = NULL;
				oCols = oRange.get_Columns();
				oCol = oCols.Item(1);
				oCells = oCol.get_Cells();
			}
			else
			{
				WPS::Rows oRows = NULL;
				WPS::Row oRow = NULL;
				oRows = oRange.get_Columns();
				oRow = oRows.Item(1);
				oCells = oRow.get_Cells();
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
void CWPSRptFill::FillReportDatasetRowMode(CRptData *pData, CDvmDataset *pDataset)
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
	WPS::Cells oCells = NULL;
	WPS::Cell oCell = NULL;
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

void CWPSRptFill::FillReportGroupColMode(CRptData *pData, CReport *pReport, CShortData * oTagDataDef)
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
	WPS::Cells oCells = NULL;
	WPS::Cell oCell = NULL;

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

void CWPSRptFill::FillReportCell(const _bstr_t &strValue, WPS::Cell oCell)
{
	oCell.Select();
	WPS::Range oRange = oCell.get_Range();
	oRange.put_Text(strValue);
}

void CWPSRptFill::FillReport_Cell(const CString &strValue, CRptBkmk *pBkmk, long nRptIndex, BOOL bSetColor)
{
	m_pCurrBkmk = pBkmk;

	try
	{
		WPS::Bookmarks bookmarks;
		WPS::Bookmark bookmark;

		bookmarks = m_oDoc.get_Bookmarks();

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

	m_pCurrBkmk = NULL;
}

void CWPSRptFill::FillReport_Cell(const CString &strValue, WPS::Bookmark &bookmark, long nRptIndex, BOOL bSetColor)
{
	try
	{
		WPS::Selection sel;
		WPS::Range  range = NULL;
		WPS::Paragraphs  paragraphs = NULL;
		WPS::Paragraph paragraph = NULL;
		WPS::Range rangeParagraph = NULL;
		long lRangeStart = 0;
		long lRangeEnd = 0;
		long lRangeStart2 = 0;
		long lRangeEnd2 = 0;
		long lEndTemp = 0;

		bookmark.Select();
		sel = m_pWPSApp->m_WPSApp.get_Selection();
	
		if (g_bClearBeforeFillRpt)
		{
			WPS::Cells oCells = sel.get_Cells();

			if (oCells.get_Count() > 0)
			{
				WPS::Cell oCell = oCells.Item(1);
				oCell.Select();
				sel = m_pWPSApp->m_WPSApp.get_Selection();
			}
			else
			{
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
			}
		}
		else
		{
			lRangeStart2 = sel.get_Start();
			lRangeEnd2 = sel.get_End();
		}
		

		if (bSetColor)
		{
			try
			{
				WPS::_Font oFont = sel.get_Font();
				COLORREF cr = oFont.get_Color();
				oFont.put_Color(m_crReport);
				oFont.put_Bold(m_nInlegibleFontBold);  //2021-2-26  lijunqing
			}
			catch (...)
			{
			}
		}

		CString strBkmkID = bookmark.get_Name();
		
		//第二次调用会导致bookmark消失，因此需要增加书签添加功能
		sel.put_Text(_bstr_t(strValue));

		//第二次调用【sel.put_Text(_bstr_t(strValue));】会导致bookmark消失，因此需要增加书签添加功能
		After_Put_Text(sel, bookmark, lRangeEnd2);
	}
	catch(...)
	{
	}
}

//第二次调用【sel.put_Text(_bstr_t(strValue));】会导致bookmark消失，因此需要增加书签添加功能
void CWPSRptFill::After_Put_Text(WPS::Selection &sel, WPS::Bookmark &bookmark, long lRangeEndPrev)
{
	WPS::Bookmarks wpsBookmarks = m_oDoc.get_Bookmarks();

	if((!wpsBookmarks.Exists(m_pCurrBkmk->m_strID)))
	{
		COleVariant vOpt(DISP_E_PARAMNOTFOUND, VT_ERROR);
		wpsBookmarks.Add(m_pCurrBkmk->m_strID, vOpt);
	}

	long lRangeEnd3 = sel.get_End();

	if (lRangeEndPrev != lRangeEnd3)
	{
		bookmark.put_End(lRangeEnd3);
	}
}

void CWPSRptFill::FillReport_Col(const CString &strValue, CRptBkmk *pBkmk, long nRptIndex, BOOL bSetColor)
{
	CTCtrlCntrBaseApp* pApp = g_theTCtrlCntrApp;

	try
	{
		WPS::Cell oCell   = NULL;
		WPS::Cells oCells = NULL;
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

		bookmarks = m_oDoc.get_Bookmarks();
		if(pBkmk->m_strID.IsEmpty()||(!bookmarks.Exists(pBkmk->m_strID)))
		{
			return;
		}

		COleVariant vIndex(pBkmk->m_strID);
		bookmark = bookmarks.Item(&vIndex);
		bookmark.Select();
		WPS::Range oRange = bookmark.get_Range();
		oCells = oRange.get_Cells();
		long nCount = oCells.get_Count();
		WPS::Cell oCel = oCells.Item(1);
		long nRowIndex = oCel.get_RowIndex();
		long nColIndex = oCel.get_ColumnIndex();

		long nCurrRowIndex = nRowIndex + nRptIndex;

		WPS::Column oCol = oCel.get_Column();
		oCells = oCol.get_Cells();
		sel = m_pWPSApp->m_WPSApp.get_Selection();
		long nCurrCells = oCells.get_Count();

		if (nCurrCells < nCurrRowIndex)
		{
			oCel = oCells.Item(nCurrCells);
			oCel.Select();
			CComVariant vCount(long(nCurrRowIndex - nCurrCells)); 
			sel.InsertRowsBelow(&vCount);
			oCells = oCol.get_Cells();
		}

		oCel = oCells.Item(nCurrRowIndex);
		oCel.Select();

		if (bSetColor)
		{
			try
			{
				WPS::_Font oFont = sel.get_Font();
				COLORREF cr = oFont.get_Color();
				oFont.put_Color(m_crReport);
				oFont.put_Bold(m_nInlegibleFontBold);  //2021-2-26  lijunqing
			}
			catch (...)
			{
			}
		}

		sel.put_Text(_bstr_t(strValue));
	}
	catch(...)
	{
	}
}

void CWPSRptFill::FillReport_Row(const CString &strValue, CRptBkmk *pBkmk, long nRptIndex, BOOL bSetColor)
{
	CTCtrlCntrBaseApp* pApp = g_theTCtrlCntrApp;
	m_pCurrBkmk = pBkmk;

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

		bookmarks = m_oDoc.get_Bookmarks();
		if(!pBkmk->m_strID.IsEmpty() && bookmarks.Exists(pBkmk->m_strID))
		{
			COleVariant vIndex(pBkmk->m_strID);
			bookmark = bookmarks.Item(&vIndex);
			bookmark.Select();
			sel = m_pWPSApp->m_WPSApp.get_Selection();

			if (g_bClearBeforeFillRpt)
			{
				WPS::Cells oCells = sel.get_Cells();
				if (oCells.get_Count() > 0)
				{
					WPS::Cell oCell = oCells.Item(1);
					oCell.Select();
					sel = m_pWPSApp->m_WPSApp.get_Selection();
				}
				else
				{
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
				}
			}
			else
			{
				lRangeStart2 = sel.get_Start();
				lRangeEnd2 = sel.get_End();
			}

			if (bSetColor)
			{
				try
				{
					WPS::_Font oFont = sel.get_Font();
					COLORREF cr = oFont.get_Color();
					oFont.put_Color(m_crReport);
					oFont.put_Bold(m_nInlegibleFontBold);  //2021-2-26  lijunqing
				}
				catch (...)
				{
				}
			}

			//第二次调用会导致bookmark消失，因此需要增加书签添加功能
			sel.put_Text(_bstr_t(strValue));

			//第二次调用【sel.put_Text(_bstr_t(strValue));】会导致bookmark消失，因此需要增加书签添加功能
			After_Put_Text(sel, bookmark, lRangeEnd2);
		}
	}
	catch(...)
	{
	}

	m_pCurrBkmk = NULL;
}

CString CWPSRptFill::GetBkmkText(WPS::Bookmark &bookmark)
{
	CTCtrlCntrBaseApp* pApp = g_theTCtrlCntrApp;
	CString strText;

	try
	{
		WPS::Selection sel;
		WPS::Range  range = NULL;
		WPS::Paragraphs  paragraphs = NULL;
		WPS::Paragraph paragraph = NULL;
		WPS::Range rangeParagraph = NULL;
		long lRangeStart = 0;
		long lRangeEnd = 0;
		long lRangeStart2 = 0;
		long lRangeEnd2 = 0;
		long lEndTemp = 0;

		bookmark.Select();
		sel = m_pWPSApp->m_WPSApp.get_Selection();
		WPS::Cells oCells = sel.get_Cells();

		if (oCells.get_Count() > 0)
		{
			WPS::Cell oCell = oCells.Item(1);
			oCell.Select();
			sel = m_pWPSApp->m_WPSApp.get_Selection();
		}
		else
		{
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
		}

		strText = sel.get_Text();

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

CString CWPSRptFill::GetBkmkText(WPS::_Document &oDoc, CRptBkmk *pBkmk)
{
	CString strText;

	try
	{
		WPS::Selection sel;
		WPS::Bookmarks bookmarks;
		WPS::Bookmark bookmark;

		bookmarks = m_oDoc.get_Bookmarks();
	
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

void CWPSRptFill::FillReportFile(const CString &strValue, CRptBkmk *pBkmk)
{
	CTCtrlCntrBaseApp* pApp = g_theTCtrlCntrApp;

	if( !IsValidApp() || !IsValidDoc())
	{
		return;
	}
	
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

		sel = m_pWPSApp->m_WPSApp.get_Selection();

		bookmarks = m_oDoc.get_Bookmarks();
		if(!pBkmk->m_strID.IsEmpty() && bookmarks.Exists(pBkmk->m_strID))
		{
			COleVariant vIndex(pBkmk->m_strID);
			COleVariant vUnit((long)WPS::wpsCharacter);
			COleVariant vCount((long)1);
			bookmark = bookmarks.Item(&vIndex);
			bookmark.Select();

			range = bookmark.get_Range();
			WPS::Cells oCells = range.get_Cells();
			WPS::Cell  oCell = oCells.Item(1);
			oCell.Select();
			sel = m_pWPSApp->m_WPSApp.get_Selection();
			sel.Delete(vUnit, vCount);

			WPS::InlineShapes oInlineShapes = sel.get_InlineShapes();

			COleVariant vLinkFile((long)0);
			COleVariant vSave((long)1);
			COleVariant vRange;
			vRange.vt=VT_DISPATCH;
			vRange.pdispVal = range.m_lpDispatch;
			range.m_lpDispatch->AddRef();

			oInlineShapes.AddPicture(strValue, &vLinkFile, &vSave, &vRange);
			vRange.Detach();

			vCount = ((long)1);
			COleVariant vExtend((long)WPS::wpsExtend);
			sel = m_pWPSApp->m_WPSApp.get_Selection();
			sel.MoveLeft(&vUnit, &vCount, &vExtend);
			oInlineShapes = sel.get_InlineShapes();
			WPS::InlineShape oInlineShape = oInlineShapes.Item(1);

			if (oInlineShape != NULL)
			{
				WPS::Shape oShape = oInlineShape.ConvertToShape();
				WPS::PictureFormat oFormat = oShape.get_PictureFormat();
				WPS::WrapFormat wrapp = oShape.get_WrapFormat();
				wrapp.put_Type(WPS::wpsWrapSquare);
			}
		}
	}
	catch(...)
	{
	}
}


void CWPSRptFill::FillReportClipboard(CRptBkmk *pBkmk)
{
	if( !IsValidApp() || !IsValidDoc())
	{
		return;
	}

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

		sel = m_pWPSApp->m_WPSApp.get_Selection();

		bookmarks = m_oDoc.get_Bookmarks();
		if(!pBkmk->m_strID.IsEmpty() && bookmarks.Exists(pBkmk->m_strID))
		{
			COleVariant vIndex(pBkmk->m_strID);
			COleVariant vUnit((long)WPS::wpsCharacter);
			COleVariant vCount((long)1);
			bookmark = bookmarks.Item(&vIndex);
			bookmark.Select();

			range = bookmark.get_Range();
			WPS::Cells oCells = range.get_Cells();
			WPS::Cell  oCell = oCells.Item(1);
			oCell.Select();
			sel = m_pWPSApp->m_WPSApp.get_Selection();
			lRangeStart2 = sel.get_Start();
			lRangeEnd2 = sel.get_End();
			sel.Delete(vUnit, vCount);
			sel.Paste();
			After_Put_Text(sel, bookmark, lRangeEnd2);
		}
	}
	catch(...)
	{
	}
}

void CWPSRptFill::ClearBkmksText(CExBaseList *pList, WPS::Selection &sel, WPS::Bookmarks &bookmarks)
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

void CWPSRptFill::ClearBkmkText(CRptBkmk *pBkmk, WPS::Selection &sel, WPS::Bookmarks &bookmarks)
{
	try
	{
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

//////////////////////////////////////////////////////////////////////////

void CWPSRptFill::CmbmMgrpt(CRptFillInterface *pRptFill, long nMgbrpIndex)
{
	CWPSRptFill* pWPSRptFill = (CWPSRptFill*)pRptFill;
	static CString g_strTitleIndex[14] = {_T("二"), _T("三"),_T("四"),_T("五"),_T("六"), _T("七"), _T("八"), _T("九"), _T("十")
		, _T("十一"), _T("十三"), _T("十四"), _T("十五")};
	m_strMgrpIndex.Format(_T("通道%s"), g_strTitleIndex[nMgbrpIndex]);

	//合并区域
	CmbmMgrpt((CExBaseList*)m_pGuideBook, pWPSRptFill);

	//合并标签
	WPS::_Document oDocMgrpt = pWPSRptFill->m_oDoc;
	WPSRptBkmkMgrpCmbn(oDocMgrpt);
}

void CWPSRptFill::CmbmMgrpt(CExBaseList *pListItems, CWordRptFillBase *pRptFill)
{
	CWPSRptFill* pWPSRptFill = (CWPSRptFill*)pRptFill;
	WPS::_Document oDocMgrpt = pWPSRptFill->m_oDoc;

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

void CWPSRptFill::CmbmMgrpt(CItems *pItems, CWordRptFillBase *pRptFill)
{
	CWPSRptFill* pWPSRptFill = (CWPSRptFill*)pRptFill;
	WPS::_Document oDocMgrpt = pWPSRptFill->m_oDoc;

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

void CWPSRptFill::CmbmMgrpt(CRptArea *pArea, CWordRptFillBase *pRptFill)
{
	CWPSRptFill* pWPSRptFill = (CWPSRptFill*)pRptFill;
	WPS::_Document oDocMgrpt = pWPSRptFill->m_oDoc;

	if (!CmbnCopyMgrpt(pArea, oDocMgrpt))
	{
		return;
	}

	CmbnPasteMgrpt(pArea->m_pBkmkEnd);
}

BOOL CWPSRptFill::CmbnCopyMgrpt(CRptArea *pArea, WPS::_Document& oDoc)
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
		WPS::Selection oSelection;
		WPS::Bookmarks bookmarks;
		WPS::Bookmark bookmark;

		bookmarks = oDoc.get_Bookmarks();
		oSelection = m_pWPSApp->m_WPSApp.get_Selection();
		bookmarks = oDoc.get_Bookmarks();
		oSelection.put_Start(nBeginPos1);
		oSelection.put_End(nEndPos2);
		oSelection.Select();
		oSelection.Copy();
	}
	catch(...)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CWPSRptFill::CmbnSelectBkmk(CRptBkmk *pBkmk, WPS::_Document &oDoc)
{
	try
	{
		WPS::Selection oSelection;
		WPS::Bookmarks bookmarks;
		WPS::Bookmark bookmark;

		bookmarks = oDoc.get_Bookmarks();

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

void CWPSRptFill::CmbnPasteMgrpt(CRptBkmk *pEndBkmk)
{
	if (!CmbnSelectBkmk(pEndBkmk, m_oDoc))
	{
		return;
	}

	try
	{
		WPS::Selection oSelection;

		oSelection = m_pWPSApp->m_WPSApp.get_Selection();
		oSelection.TypeText(m_strMgrpIndex);
		oSelection.TypeParagraph();
		oSelection.Paste();
	}
	catch(...)
	{
	}
}

void CWPSRptFill::InitWordRptBkmkMgrpCmbn()
{
	try
	{
		WPS::Bookmarks bookmarks;
		WPS::Bookmark bookmark;
		bookmarks = m_oDoc.get_Bookmarks();
		InitWordRptBkmkMgrpCmbn(m_pGuideBook, bookmarks);
	}
	catch (...)
	{

	}
}

void CWPSRptFill::InitWordRptBkmkMgrpCmbn(CExBaseList *pList, WPS::Bookmarks &oBookmarks)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;
	CRptBkmk *pBkmk = NULL;
	CWPSRptBkmkMgrpCmbn *pNew = NULL;

	while (pos != NULL)
	{
		p = pList->GetNext(pos);

		if (p->GetClassID() == RPTCLASSID_RPTBKMK)
		{
			pBkmk = (CRptBkmk*)p;

			if (pBkmk->m_strMgrpCmbnMode.GetLength() > 0)
			{
				pNew = new CWPSRptBkmkMgrpCmbn();
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

void CWPSRptFill::WPSRptBkmkMgrpCmbn(WPS::_Document &oDoc)
{
	POS pos = GetHeadPosition();
	CWPSRptBkmkMgrpCmbn *pBkmkMgrpCmbn = NULL;

	while (pos != NULL)
	{
		pBkmkMgrpCmbn = (CWPSRptBkmkMgrpCmbn *)GetNext(pos);
		WPSRptBkmkMgrpCmbn(pBkmkMgrpCmbn, oDoc);
	}
}

void CWPSRptFill::WPSRptBkmkMgrpCmbn(CWPSRptBkmkMgrpCmbn *pBkmkMgrpCmbn, WPS::_Document &oDoc)
{
	CString strText;
	strText = GetBkmkText(oDoc, pBkmkMgrpCmbn->m_pBkmkRef);

	if (strText == pBkmkMgrpCmbn->m_strValue)
	{
		return;
	}

	if (pBkmkMgrpCmbn->m_pBkmkRef->m_strMgrpCmbnMode == _T("max_len"))
	{
		return WPSRptBkmkMgrpCmbn_max_len(pBkmkMgrpCmbn, strText);
	}

	if (pBkmkMgrpCmbn->m_pBkmkRef->m_strMgrpCmbnMode == _T("min_len"))
	{
		return WPSRptBkmkMgrpCmbn_min_len(pBkmkMgrpCmbn, strText);
	}

	if (pBkmkMgrpCmbn->m_pBkmkRef->m_strMgrpCmbnMode == _T("max_val"))
	{
		return WPSRptBkmkMgrpCmbn_max_val(pBkmkMgrpCmbn, strText);
	}

	if (pBkmkMgrpCmbn->m_pBkmkRef->m_strMgrpCmbnMode == _T("min_val"))
	{
		return WPSRptBkmkMgrpCmbn_min_val(pBkmkMgrpCmbn, strText);
	}

	if (pBkmkMgrpCmbn->m_pBkmkRef->m_strMgrpCmbnMode == _T("avg"))
	{
		return WPSRptBkmkMgrpCmbn_avg(pBkmkMgrpCmbn, strText);
	}

	if (pBkmkMgrpCmbn->m_pBkmkRef->m_strMgrpCmbnMode == _T("sum"))
	{
		return WPSRptBkmkMgrpCmbn_sum(pBkmkMgrpCmbn, strText);
	}
}

void CWPSRptFill::WPSRptBkmkMgrpCmbn_max_len(CWPSRptBkmkMgrpCmbn *pBkmkMgrpCmbn, const CString &strText)
{
	if (strText.GetLength() <= pBkmkMgrpCmbn->m_strValue.GetLength())
	{
		return;
	}

	pBkmkMgrpCmbn->m_strValue = strText;
	FillReport_Cell(strText, pBkmkMgrpCmbn->m_oBkmk, 0, FALSE);
}

void CWPSRptFill::WPSRptBkmkMgrpCmbn_min_len(CWPSRptBkmkMgrpCmbn *pBkmkMgrpCmbn, const CString &strText)
{
	if (strText.GetLength() > pBkmkMgrpCmbn->m_strValue.GetLength())
	{
		return;
	}

	pBkmkMgrpCmbn->m_strValue = strText;
	FillReport_Cell(strText, pBkmkMgrpCmbn->m_oBkmk, 0, FALSE);
}

void CWPSRptFill::WPSRptBkmkMgrpCmbn_max_val(CWPSRptBkmkMgrpCmbn *pBkmkMgrpCmbn, const CString &strText)
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

void CWPSRptFill::WPSRptBkmkMgrpCmbn_min_val(CWPSRptBkmkMgrpCmbn *pBkmkMgrpCmbn, const CString &strText)
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

void CWPSRptFill::WPSRptBkmkMgrpCmbn_avg(CWPSRptBkmkMgrpCmbn *pBkmkMgrpCmbn, const CString &strText)
{

}

void CWPSRptFill::WPSRptBkmkMgrpCmbn_sum(CWPSRptBkmkMgrpCmbn *pBkmkMgrpCmbn, const CString &strText)
{
	double dVal1 = CString_To_double(pBkmkMgrpCmbn->m_strValue);
	double dVal2 = CString_To_double(strText);
	dVal1 += dVal2;

	CRptData *pData = (CRptData *)pBkmkMgrpCmbn->m_pBkmkRef->GetParent();
	pBkmkMgrpCmbn->m_strValue.Format(_T("%f"), dVal1);
	ChopValueString(pData, pBkmkMgrpCmbn->m_strValue);

	FillReport_Cell(pBkmkMgrpCmbn->m_strValue, pBkmkMgrpCmbn->m_oBkmk, 0, FALSE);
}
