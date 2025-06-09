#pragma once

#include "XLanguageMngr.h"


class CXLanguageWndInterface
{
public:
	CXLanguageWndInterface();
	virtual ~CXLanguageWndInterface();

public:
	virtual BOOL SetLanguageID(const CString &strLanguageID) = 0;
	virtual void CalXLangWndAdj(CRect &rcOrigin, long &nCalWidth);

public:
	virtual BOOL InitByLanguageID(const CString &strLanguageID, CWnd *pWnd);
	virtual void MoveWindow(const CRect &rcWnd);
	
protected:
	CString m_strLanguageID;
	CWnd *m_pWndRef;

};


void xlang_CalXLangWndAdj(CWnd *pWnd, CRect &rcOrigin, long &nCalWidth);
void xlang_MoveWindowTo(CWnd *pParent, CWnd *pWndFrom, CWnd *pWndTo);

class CXLanguageWndAlign
{
public:
	CXLanguageWndAlign();
	CXLanguageWndAlign(CWnd *pParent);
	virtual ~CXLanguageWndAlign();

	void SetParentWnd(CWnd *pParent);
	void AddWnd(CWnd *pWnd);
	void AlignLeft();
	void AlignRight();
	void AlignTop();
	void AlignBottom();
	void Reset();

	void MoveToLeft(long nGap=5);
	void MoveToRight(long nGap=5);
	void MoveToTop(long nGap=5);
	void MoveToBottom(long nGap=5);

protected:
	long m_nWndCount;
	long m_nWndArrayLen;
	ULONG *m_pdwWndArray;
	CWnd *m_pParentWnd;

	void ResizeWndArray(long nAdd=10);
};