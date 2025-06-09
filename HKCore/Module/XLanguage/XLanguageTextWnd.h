#pragma once

#include "XLanguageWndInterface.h"
// CXLanguageTextWnd

class CXLanguageTextWnd : public CStatic, public CXLanguageWndInterface
{
	DECLARE_DYNAMIC(CXLanguageTextWnd)

public:
	CXLanguageTextWnd();
	virtual ~CXLanguageTextWnd();

public:
	virtual BOOL SetLanguageID(const CString &strLanguageID);
	virtual void CalXLangWndAdj(CRect &rcOrigin, long &nCalWidth);

protected:
	DECLARE_MESSAGE_MAP()
};


