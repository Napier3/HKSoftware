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

	//��λ��������Ŀ���鱨���λ��
	//2006.04.07  ���
	//void LocateReport(MSWord::_Document doc, const CString &strVariable);//lijq 2008.8.14
	//lijq 2008.11.16  ���ͨ�������������ʧ�ܣ���ʹ������������λ���鱨��λ��
	BOOL LocateReport(MSWord::_Document doc, const CString &strVariable);

	CBookmarkObject* FindBookmark(const CString &strBkmk);
};

#endif // !defined(AFX_BOOKMARKOBJLIST_H__54A86711_93F8_48F2_9F9C_831B0232AC0B__INCLUDED_)
