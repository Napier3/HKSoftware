#include "StdAfx.h"
#include "WPSRptApi.h"
#include "ReportMap.h"
#include "RptBkmk.h"
#include "RptData.h"
#include "..\GuideBook.h"
#include "RptItem.h"

//////////////////////////////////////////////////////////////////////////
//DWORD *g_pdwMaxBkmkIndex = NULL;

long wpsrpt_DeleteBkmk(const CString &strBkmk, BOOL bSelect, WPS::_Document &oDoc)
{	
	CString str = strBkmk;
	COleVariant index(str);
	WPS::Bookmarks wpsBookmarks = oDoc.get_Bookmarks();
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

	return nRet;
}


BOOL wpsrpt_RenameRptBkmk(CExBaseObject *pRptBkmk, WPS::_Application &oWPSApp, WPS::_Document &oDoc)
{
	CRptBkmk *p = (CRptBkmk *)pRptBkmk;

	if(oDoc == NULL)
	{
		return FALSE;
	}

	CString strBkmk = pRptBkmk->m_strID;

	try
	{
		if (wpsrpt_DeleteBkmk(strBkmk, TRUE, oDoc) > 0)
		{
			long nPos = strBkmk.ReverseFind('_');

			if (nPos  > 0)
			{
				strBkmk = strBkmk.Left(nPos+1);
			}

			strBkmk.AppendFormat(_T("%d"), (*g_pdwMaxBkmkIndex)++);
			pRptBkmk->m_strID = strBkmk;

			// 插入书签
			COleVariant vOpt(DISP_E_PARAMNOTFOUND, VT_ERROR);
			WPS::Bookmarks wpsBookmarks = oDoc.get_Bookmarks();
			WPS::Bookmark wpsBookmark;
			WPS::Selection wpsSelection = oWPSApp.get_Selection();
			WPS::Range wpsSelectionRange = wpsSelection.get_Range();
			wpsBookmarks.Add(strBkmk, vOpt);
		}
	}
	catch (...)
	{
		return FALSE;
	}

	return TRUE;
}


void wpsrpt_RenameRptBkmks(CExBaseList *pList, WPS::_Application	&oWPSApp, WPS::_Document &oDoc)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pList->GetNext(pos);

		if (p->GetClassID() == RPTCLASSID_RPTBKMK)
		{
			wpsrpt_RenameRptBkmk(p, oWPSApp, oDoc);
		}
		else if (p->IsBaseList())
		{
			wpsrpt_RenameRptBkmks((CExBaseList*)p, oWPSApp, oDoc);
		}
	}
}


CString wpsrpt_GetWPSFileTitle(const CString &strRptFile)
{
	long nPos1 = strRptFile.ReverseFind('\\')+1;
	long nPos2 = strRptFile.ReverseFind('.');

	CString strTitle = strRptFile.Mid(nPos1, nPos2 - nPos1);
	return strTitle;
}


BOOL  wpsrpt_ActiveWindow(WPS::_Application	&oWPSApp, const CString &strTitle)
{
	BOOL bTrue = FALSE;

	try
	{
		WPS::Windows oWindows = oWPSApp.get_Windows();
		COleVariant oIndex;

		long nIndex = 1;
		long nCount = oWindows.get_Count();

		for (nIndex=1; nIndex<=nCount; nIndex++)
		{
			oIndex = nIndex;
			WPS::Window oWindow = oWindows.Item(oIndex);
			CString strCaption = oWindow.get_Caption();

			if (strCaption.Find(strTitle) >= 0)
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

void wpsrpt_InsertWPSEdit(WPS::_Application	&oWPSApp, WPS::_Document &oDocDest, WPS::_Document &oDocSrc
							, const CString &strDestRptFile, const CString &strSrcRptFile, long nAddRptGroupTitle)
{
	if (oDocDest == NULL || oDocSrc == NULL)
	{
		return;
	}

	try
	{
		CString strTitle;
		strTitle = wpsrpt_GetWPSFileTitle(strSrcRptFile);

		if (!wpsrpt_ActiveWindow(oWPSApp, strTitle))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, /*_T("插入%s失败")*/g_sLangTxt_InsertFail, strSrcRptFile);
			return ;
		}

		WPS::Selection wpsSelection = oWPSApp.get_Selection();
		wpsSelection.WholeStory();
		wpsSelection.Copy();
		strTitle = wpsrpt_GetWPSFileTitle(strDestRptFile);

		if (!wpsrpt_ActiveWindow(oWPSApp, strTitle))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, /*_T("插入%s失败")*/g_sLangTxt_InsertFail, strSrcRptFile);
			return ;
		}

		COleVariant vTrue((short)TRUE), vFalse((short)FALSE),
			vOpt((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
		COleVariant vUnit((long)WPS::wpsStory);
		COleVariant vUnit2((long)WPS::wpsCharacter);
		COleVariant vCount((long)1);

		wpsSelection =oWPSApp.get_Selection();
		wpsSelection.EndKey(&vUnit, &vOpt);
		wpsSelection.Paste();	

		if (nAddRptGroupTitle == 0)
		{
			wpsSelection.Delete(&vUnit2, &vCount);
		}
	}
	catch (...)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, /*_T("插入%s失败")*/g_sLangTxt_InsertFail, strSrcRptFile);
	}
}

void wpsrpt_InsertTitle(WPS::_Application &oWPSApp, WPS::_Document &oDoc, const CString &strDocFile, const CString &strTitle, long nTitleLevel)
{
	COleVariant vTrue((short)TRUE), vFalse((short)FALSE),
		vOpt((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	COleVariant vUnit((long)WPS::wpsStory);
	WPS::Selection wpsSelection = oWPSApp.get_Selection();

	CString strFileTitle = wpsrpt_GetWPSFileTitle(strDocFile);

	if (!wpsrpt_ActiveWindow(oWPSApp, strFileTitle))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, /*_T("插入标题【%s】失败")*/g_sLangTxt_InsertTitleFail, strTitle);
		return ;
	}

	wpsSelection = oWPSApp.get_Selection();
	wpsSelection.EndKey(&vUnit, &vOpt);
	wpsSelection.TypeParagraph();

	if (nTitleLevel > 0)
	{
		wpsSelection.TypeText(strTitle);
		WPS::Styles oStyles = oDoc.get_Styles();
		CString strStyle;
		strStyle.Format(/*_T("标题 %d")*/g_sLangTxt_Title, nTitleLevel);
		COleVariant vStyleID = strStyle;
		wpsSelection.put_Style(vStyleID);
	}
	else
	{
		WPS::_Font font = wpsSelection.get_Font();
		float fSize = font.get_Size();
		font.put_Bold(TRUE);
		font.put_Size(16);
		wpsSelection.TypeText(strTitle);
		font.put_Size(fSize);
		font.put_Bold(FALSE);
	}

	wpsSelection.TypeParagraph();
}

BOOL wpsrpt_Open(WPS::_Application &oWPSApp, WPS::_Document &oDoc, const CString  &strReportFile)
{
	if(!IsFileExist(strReportFile))
	{
		return FALSE;
	}

	if ( oWPSApp == NULL)
	{
		return FALSE;
	}

	WPS::Documents docs = NULL;
	docs =  oWPSApp.get_Documents();

	if (docs == NULL)
	{
		return FALSE;
	}
	
	COleVariant vRptFile(strReportFile);			
	COleVariant covTrue((long)TRUE),covFalse((long)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	BOOL bRet = TRUE;

	try
	{
		//打开试验报告文件
		oDoc = docs.Open(&vRptFile,covOptional,covFalse,covTrue,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covTrue,covOptional,covOptional,covOptional,covOptional);
	}
	catch (...)
	{
		bRet = FALSE;
	}

	return bRet;
}