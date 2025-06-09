// BookmarkObject.cpp: implementation of the CBookmarkObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BookmarkObject.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBookmarkObject::CBookmarkObject()
{
	m_Bookmark = NULL;
}

CBookmarkObject::~CBookmarkObject()
{
	EndIt();
}

void CBookmarkObject::EndIt()
{
	try
	{
		m_Bookmark.ReleaseDispatch();
		m_Bookmark = NULL;
	}
	catch (...)
	{
	}
}

BOOL CBookmarkObject::IsReportDataBookmark()
{
	CString strTemp;
	BOOL bTrue = FALSE;
	long nPos = m_strBookmark.Find("_");

	if (nPos >= 0)
	{
		strTemp = m_strBookmark.Left(nPos+1);

		if ( stricmp(g_pszWRVPF_TestItemPoint, strTemp) == 0)
		{
			bTrue = TRUE;
		}
		else if ( stricmp(g_pszWRVPF_TestItemHDChk, strTemp) == 0)
		{
			bTrue = TRUE;
		}
		else if (stricmp(g_pszWRVPF_TestItemSafety, strTemp) == 0)
		{
			bTrue = TRUE;
		}
		else if (stricmp(g_pszWRVPF_TestItemProtCommand, strTemp) == 0)
		{
			bTrue = TRUE;
		}
		else
		{
		}
	}

	return bTrue;
}

