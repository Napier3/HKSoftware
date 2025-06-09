// BookmarkObjList.h: interface for the CBookmarkObjList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BOOKMARKOBJLIST_H__54A86711_93F8_48F2_9F9C_831B0232AC0B__INCLUDED_)
#define AFX_BOOKMARKOBJLIST_H__54A86711_93F8_48F2_9F9C_831B0232AC0B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BookmarkObject.h"
#include "..\MemManager\EquationBuffer.h"

void _TrimStringData(CString &strData);

class CBookmarkObjList : public CBaseObject
{
public:
	CBaseObjectList m_listBookmark;
	
public:
	CBookmarkObjList();
	virtual ~CBookmarkObjList();

	void InitBookmarkObjList(MSWord::_Document doc);
	void EndIt();

	void SetReportData(MSWord::Selection wordSelection,BSTR bstrReport,COLORREF crTextColor=RGB(0,0,0));
	void SetReportData(MSWord::Selection wordSelection,const CString &strReport,COLORREF crTextColor=RGB(0,0,0));
	void SetReportData(MSWord::Selection wordSelection,const CString &strVariable,const CString &strData);

	//定位到测试项目试验报告的位置
	//2006.04.07  李俊庆
	//void LocateReport(MSWord::_Document doc, const CString &strVariable);//lijq 2008.8.14
	//lijq 2008.11.16  如果通过结果变量定义失败，则使用区域定义来定位试验报告位置
	BOOL LocateReport(MSWord::_Document doc, const CString &strVariable);

	CBookmarkObject* FindBookmark(const CString &strBkmk);
};

#endif // !defined(AFX_BOOKMARKOBJLIST_H__54A86711_93F8_48F2_9F9C_831B0232AC0B__INCLUDED_)
