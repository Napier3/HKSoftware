// BookmarkObjList.cpp: implementation of the CBookmarkObjList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BookmarkObjList.h"
#include "..\api\globlaapi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBookmarkObjList::CBookmarkObjList()
{
	m_listBookmark.EndIt();	
}

CBookmarkObjList::~CBookmarkObjList()
{
	EndIt();
}

void CBookmarkObjList::InitBookmarkObjList(MSWord::_Document doc)
{
	EndIt();
//	ASSERT(doc != NULL);
	if (doc == NULL)
	{
		return;
	}
	MSWord::Bookmarks bkmrks;
	try
	{
		bkmrks = doc.GetBookmarks();
	}
	catch (...)
	{
		return;
	}

	//TRACE("\n********************************************\n");
	MSWord::Bookmark  bkmrk;
	try
	{
		long lCount = bkmrks.GetCount();
		long lIndex = 0;
		CBookmarkObject *pBkmkObj = NULL;
		for (lIndex=1;lIndex<=lCount;lIndex++)
		{
			COleVariant index(lIndex);
			bkmrk = bkmrks.Item(index);
			pBkmkObj = new CBookmarkObject();
			pBkmkObj->m_strBookmark = bkmrk.GetName();
			//TRACE("%s\n",pBkmkObj->m_strBookmark);
			pBkmkObj->m_Bookmark = bkmrk;
			m_listBookmark.AddTail(pBkmkObj);
		}
	}
	catch (...) 
	{
	}
	//TRACE("\n********************************************\n");
}

void CBookmarkObjList::EndIt()
{
	m_listBookmark.EndIt();
}

void CBookmarkObjList::SetReportData(MSWord::Selection wordSelection,BSTR bstrReport,COLORREF crTextColor)
{
	CString strReport = bstrReport;
	SetReportData(wordSelection,strReport,crTextColor);
}

void CBookmarkObjList::SetReportData(MSWord::Selection wordSelection,const CString &strReport,COLORREF crTextColor)
{
	CEquationBuffer buff;
	buff.InitBuffer(strReport);

	MSWord::Range  range = NULL;
	MSWord::Paragraphs  paragraphs = NULL;
	MSWord::Paragraph paragraph = NULL;
	MSWord::Range rangeParagraph = NULL;
	long lRangeStart = 0;
	long lRangeEnd = 0;
	long lRangeStart2 = 0;
	long lRangeEnd2 = 0;
	long lEndTemp = 0;
	CString strData;

	try
	{
		MSWord::_Document doc = wordSelection.GetDocument();
		MSWord::Bookmarks oBkmks = doc.GetBookmarks();

		POSITION pos = m_listBookmark.GetHeadPosition();
		CBookmarkObject *pBkmkObj = NULL;
		while (pos != NULL)
		{
			pBkmkObj = (CBookmarkObject*)m_listBookmark.GetNext(pos);
			if (buff.ParseString(pBkmkObj->m_strBookmark,strData) != 1)
			{
				continue;
			}
			if (pBkmkObj->m_Bookmark != NULL && oBkmks.Exists(pBkmkObj->m_strBookmark))
			{
				pBkmkObj->m_Bookmark.Select();
				range = pBkmkObj->m_Bookmark.GetRange();
				paragraphs = range.GetParagraphs();
				paragraph = paragraphs.GetFirst();
				rangeParagraph = paragraph.GetRange();
				lRangeStart2 = rangeParagraph.GetStart();
				lRangeEnd2 = rangeParagraph.GetEnd();
				lEndTemp = lRangeEnd2 - 1;
				if (lRangeStart2 <= lEndTemp)
					lRangeEnd2 = lEndTemp;
				
				wordSelection.SetStart(lRangeStart2);
				wordSelection.SetEnd(lRangeEnd2);
				_ChopResultFloatString(strData);
				_TrimStringData(strData);	//2007/04/25	过滤字符串数据
				wordSelection.SetText(_bstr_t(strData));
				MSWord::_Font font = wordSelection.GetFont();
				font.SetColor(crTextColor);
				//wordSelection.SetFont(font);
			}
		}	
	}
	catch (...)
	{
	}
}

void CBookmarkObjList::SetReportData(MSWord::Selection wordSelection,const CString &strVariable,const CString &strData)
{
//	POSITION pos = m_listBookmark.GetHeadPosition();
//	CBookmarkObject *pBkmkObj = NULL;
	MSWord::Range  range = NULL;
	MSWord::Paragraphs  paragraphs = NULL;
	MSWord::Paragraph paragraph = NULL;
	MSWord::Range rangeParagraph = NULL;
	long lRangeStart = 0;
	long lRangeEnd = 0;
	long lRangeStart2 = 0;
	long lRangeEnd2 = 0;
	long lEndTemp = 0;

	try
	{
		MSWord::_Document doc = wordSelection.GetDocument();
		MSWord::Bookmarks oBkmks = doc.GetBookmarks();
		
		//while (pos != NULL)
		{
		//	pBkmkObj = (CBookmarkObject*)m_listBookmark.GetNext(pos);
			if (/*strVariable == pBkmkObj->m_strBookmark && */oBkmks.Exists(strVariable))
			{
				MSWord::Bookmark  oBkmk;
				COleVariant vIndex(strVariable);
				oBkmk = oBkmks.Item(&vIndex);
				if (oBkmk != NULL)
				{
					oBkmk.Select();
					range = oBkmk.GetRange();
					paragraphs = range.GetParagraphs();
					paragraph = paragraphs.GetFirst();
					rangeParagraph = paragraph.GetRange();
					lRangeStart2 = rangeParagraph.GetStart();
					lRangeEnd2 = rangeParagraph.GetEnd();
					lEndTemp = lRangeEnd2 - 1;
					if (lRangeStart2 <= lEndTemp)
						lRangeEnd2 = lEndTemp;
					
					wordSelection.SetStart(lRangeStart2);
					wordSelection.SetEnd(lRangeEnd2);
					
					wordSelection.SetText(_bstr_t(strData));
				}
				
			}
		}	
	}
	catch (...)
	{
	}
}

void _TrimStringData(CString &strData)
{
	long nLen = strData.GetLength();

	if (nLen >= 2)
	{
		if ((strData.Left(1) == "\"") && (strData.Right(1) == "\""))
		{
			strData = strData.Mid(1,nLen-2);
		}
	}
}

//定位到测试项目试验报告的位置
//2006.04.07  李俊庆
BOOL CBookmarkObjList::LocateReport(MSWord::_Document doc, const CString &strVariable)
{
	CString strData = strVariable;
	BOOL bFind = FALSE;
	
	POSITION pos = m_listBookmark.GetHeadPosition();
	CBookmarkObject *pBkmkObj = NULL;
	CBookmarkObject *pBkmkObjFind = NULL;

	const char *pszLeft = NULL;
	const char *pszRight = strData.GetBuffer(0);
	long nLen = strVariable.GetLength();
	
	while (pos != NULL)
	{
		pBkmkObj = (CBookmarkObject*)m_listBookmark.GetNext(pos);
		
		pszLeft = pBkmkObj->m_strBookmark.GetBuffer(0);
		if (strncmp(pszLeft,pszRight,nLen) == 0)
		{
			pBkmkObjFind = pBkmkObj;
			break;
		}
	}

	try
	{
		MSWord::Bookmarks oBkmks = doc.GetBookmarks();
		
		if (pBkmkObjFind != NULL && oBkmks.Exists(pBkmkObjFind->m_strBookmark))
		{
			if (pBkmkObjFind->m_Bookmark != NULL)
			{
				pBkmkObj->m_Bookmark.Select();
				bFind = TRUE;
			}
		}
	}
	catch (...)
	{
	}

	if (!bFind)
	{//如果没有定位到结果数据，则定位区域标签
		CString strTemp = strVariable;
		strTemp.Format("area_%s", strVariable);
		strTemp = strTemp.Left(strTemp.GetLength() - 1);
		pos = m_listBookmark.GetHeadPosition();
		nLen = strTemp.GetLength();
		
		while (pos != NULL)
		{
			pBkmkObj = (CBookmarkObject*)m_listBookmark.GetNext(pos);
			
			if (strncmp(strTemp,pBkmkObj->m_strBookmark,nLen) == 0)
			{
				pBkmkObjFind = pBkmkObj;
				break;
			}
		}
		
		try
		{
			MSWord::Bookmarks oBkmks = doc.GetBookmarks();
			
			if (pBkmkObjFind != NULL && oBkmks.Exists(pBkmkObjFind->m_strBookmark))
			{
				if (pBkmkObjFind->m_Bookmark != NULL)
				{
					pBkmkObj->m_Bookmark.Select();
					bFind = TRUE;
				}
			}
		}
		catch (...)
		{
		}
	}

	return bFind;
}

CBookmarkObject* CBookmarkObjList::FindBookmark(const CString &strBkmk)
{
	POSITION pos = m_listBookmark.GetHeadPosition();
	CBookmarkObject *pBkmkObj = NULL;
	CBookmarkObject *pBkmkObjFind = NULL;
	
	while (pos != NULL)
	{
		pBkmkObj = (CBookmarkObject*)m_listBookmark.GetNext(pos);
		
		if (stricmp(strBkmk, pBkmkObj->m_strBookmark) == 0)
		{
			pBkmkObjFind = pBkmkObj;
			break;
		}
	}

	return pBkmkObjFind;
}

