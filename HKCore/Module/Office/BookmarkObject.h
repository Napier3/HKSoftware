// BookmarkObject.h: interface for the CBookmarkObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BOOKMARKOBJECT_H__A65CCB28_13E3_4E4F_B25C_9AD52A2D45DA__INCLUDED_)
#define AFX_BOOKMARKOBJECT_H__A65CCB28_13E3_4E4F_B25C_9AD52A2D45DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\BaseObject\BaseObject.h"
#include "msword9.h"

class CBookmarkObject : public CBaseObject
{
public:
	CString m_strBookmark;
	MSWord::Bookmark  m_Bookmark;
	
public:
	virtual ~CBookmarkObject();
	CBookmarkObject();

	void EndIt();
	BOOL IsReportDataBookmark();
};

#endif // !defined(AFX_BOOKMARKOBJECT_H__A65CCB28_13E3_4E4F_B25C_9AD52A2D45DA__INCLUDED_)
