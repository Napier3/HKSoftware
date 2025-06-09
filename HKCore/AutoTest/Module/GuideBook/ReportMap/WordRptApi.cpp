#include "StdAfx.h"
#include "WordRptApi.h"
#include "ReportMap.h"
#include "RptBkmk.h"
#include "RptData.h"
#include "..\GuideBook.h"
#include "RptItem.h"

//////////////////////////////////////////////////////////////////////////
DWORD *g_pdwMaxBkmkIndex = NULL;

long wordrpt_DeleteBkmk(const CString &strBkmk, BOOL bSelect, MSWord::_Document &oDoc)
{	
	CString str = strBkmk;
	COleVariant index(str);
	MSWord::Bookmarks wordBookmarks = oDoc.GetBookmarks();
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

	return nRet;
}


BOOL wordrpt_RenameRptBkmk(CExBaseObject *pRptBkmk, MSWord::_Application	&oWordApp, MSWord::_Document		&oDoc)
{
	CRptBkmk *p = (CRptBkmk *)pRptBkmk;

	if(oDoc == NULL)
	{
		return FALSE;
	}

	CString strBkmk = pRptBkmk->m_strID;

	try
	{
		if (wordrpt_DeleteBkmk(strBkmk, TRUE, oDoc) > 0)
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
			MSWord::Bookmarks wordBookmarks = oDoc.GetBookmarks();
			MSWord::Bookmark wordBookmark;
			MSWord::Selection wordSelection = oWordApp.GetSelection();
			MSWord::Range wordSelectionRange = wordSelection.GetRange();
			wordBookmarks.Add(strBkmk, vOpt);
		}
	}
	catch (...)
	{
		return FALSE;
	}

	return TRUE;
}


void wordrpt_RenameRptBkmks(CExBaseList *pList, MSWord::_Application	&oWordApp, MSWord::_Document &oDoc)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pList->GetNext(pos);

		if (p->GetClassID() == RPTCLASSID_RPTBKMK)
		{
			wordrpt_RenameRptBkmk(p, oWordApp, oDoc);
		}
		else if (p->IsBaseList())
		{
			wordrpt_RenameRptBkmks((CExBaseList*)p, oWordApp, oDoc);
		}
	}
}


CString wordrpt_GetWordFileTitle(const CString &strRptFile)
{
	long nPos1 = strRptFile.ReverseFind('\\')+1;
	long nPos2 = strRptFile.ReverseFind('.');

	CString strTitle = strRptFile.Mid(nPos1, nPos2 - nPos1);
	return strTitle;
}


BOOL  wordrpt_ActiveWindow(MSWord::_Application	&oWordApp, const CString &strTitle)
{
	BOOL bTrue = FALSE;

	try
	{
		MSWord::Windows oWindows = oWordApp.GetWindows();
		COleVariant oIndex;

		long nIndex = 1;
		long nCount = oWindows.GetCount();

		for (nIndex=1; nIndex<=nCount; nIndex++)
		{
			oIndex = nIndex;
			MSWord::Window oWindow = oWindows.Item(&oIndex);
			CString strCaption = oWindow.GetCaption();

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

void wordrpt_InsertWordEdit(MSWord::_Application	&oWordApp, MSWord::_Document &oDocDest, MSWord::_Document &oDocSrc
							, const CString &strDestRptFile, const CString &strSrcRptFile, long nAddRptGroupTitle)
{
	if (oDocDest == NULL || oDocSrc == NULL)
	{
		return;
	}

	try
	{
		CString strTitle;
		strTitle = wordrpt_GetWordFileTitle(strSrcRptFile);

		if (!wordrpt_ActiveWindow(oWordApp, strTitle))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, /*_T("插入%s失败")*/g_sLangTxt_InsertFail, strSrcRptFile);
			return ;
		}

		MSWord::Selection wordSelection = oWordApp.GetSelection();
		wordSelection.WholeStory();
		wordSelection.Copy();
		strTitle = wordrpt_GetWordFileTitle(strDestRptFile);

		if (!wordrpt_ActiveWindow(oWordApp, strTitle))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, /*_T("插入%s失败")*/g_sLangTxt_InsertFail, strSrcRptFile);
			return ;
		}

		COleVariant vTrue((short)TRUE), vFalse((short)FALSE),
			vOpt((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
		COleVariant vUnit((long)MSWord::wdStory);
		COleVariant vUnit2((long)MSWord::wdCharacter);
		COleVariant vCount((long)1);

		wordSelection =oWordApp.GetSelection();
		wordSelection.EndKey(&vUnit, &vOpt);
		wordSelection.Paste();	

		if (nAddRptGroupTitle == 0)
		{
			wordSelection.Delete(&vUnit2, &vCount);
		}
	}
	catch (...)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, /*_T("插入%s失败")*/g_sLangTxt_InsertFail, strSrcRptFile);
	}
}

void wordrpt_InsertTitle(MSWord::_Application &oWordApp, MSWord::_Document &oDoc, const CString &strDocFile, const CString &strTitle, long nTitleLevel, BOOL bPasteFormat)
{
	COleVariant vTrue((short)TRUE), vFalse((short)FALSE),
		vOpt((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	COleVariant vUnit((long)MSWord::wdStory);
	MSWord::Selection wordSelection;/* = oWordApp.GetSelection();*/

	CString strFileTitle = wordrpt_GetWordFileTitle(strDocFile);

	if (!wordrpt_ActiveWindow(oWordApp, strFileTitle))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, /*_T("插入标题【%s】失败")*/g_sLangTxt_InsertTitleFail, strTitle);
		return ;
	}

	wordSelection = oWordApp.GetSelection();
	wordSelection.EndKey(&vUnit, &vOpt);
	wordSelection.TypeParagraph();

	if (nTitleLevel > 0)
	{
		wordSelection.TypeText(strTitle);
		MSWord::Styles oStyles = oDoc.GetStyles();
		CString strStyle;
		strStyle.Format(/*_T("标题 %d")*/g_sLangTxt_Title, nTitleLevel);
		COleVariant vStyleID = strStyle;
		//COleVariant vStyle = oStyles.Item(vStyleID);
		wordSelection.SetStyle(vStyleID);
		
		if (bPasteFormat)
		{
			wordSelection.PasteFormat();
		}
	}
	else
	{
		MSWord::_Font font = wordSelection.GetFont();
		float fSize = font.GetSize();
		font.SetBold(TRUE);
		font.SetSize(16);
		wordSelection.TypeText(strTitle);
		font.SetSize(fSize);
		font.SetBold(FALSE);
	}

	wordSelection.TypeParagraph();
}


// void wordrpt_InsertWordEdit(MSWord::_Application &oWordApp, MSWord::_Document &oDocDest 
// 							, const CString &strDestRptFile, const CString &strSrcRptFile
// 							, BOOL bRenameBkmk, long nAddRptGroupTitle)
// {
// 	if (oDocDest == NULL)
// 	{
// 		return;
// 	}
// 
// 	MSWord::_Document oDocSrc = NULL;
// 
// 	try
// 	{
// 		if (wordrpt_Open(oWordApp, oDocSrc, strSrcRptFile))
// 		{
// 			return;
// 		}
// 	}
// 	catch (...)
// 	{
// 		return;
// 	}
// 
// 	if (bRenameBkmk)
// 	{
// 
// 	}
// 
// 	wordrpt_InsertWordEdit(oWordApp, oDocDest, oDocSrc, strDestRptFile, strSrcRptFile, nAddRptGroupTitle);
// }



BOOL wordrpt_Open(MSWord::_Application &oWordApp, MSWord::_Document &oDoc, const CString  &strReportFile)
{
	//CFileFind find;
	//
	//if (!find.FindFile(strReportFile))
	if(!IsFileExist(strReportFile))
	{
		return FALSE;
	}

	if ( oWordApp == NULL)
	{
		return FALSE;
	}

	MSWord::Documents docs = NULL;
	docs =  oWordApp.GetDocuments();

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
		oDoc = docs.Open(&vRptFile,covOptional,covFalse,covTrue,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covTrue);

	}
	catch (...)
	{
		bTrue = FALSE;
	}

	return bTrue;
}