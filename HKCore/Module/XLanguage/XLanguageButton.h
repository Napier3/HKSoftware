#pragma once

#include "XLanguageWndInterface.h"

// CXLanguageButton

class CXLanguageButton : public CButton, public CXLanguageWndInterface
{
	DECLARE_DYNAMIC(CXLanguageButton)

public:
	CXLanguageButton();
	virtual ~CXLanguageButton();

public:
	virtual BOOL SetLanguageID(const CString &strLanguageID);
	virtual void CalXLangWndAdj(CRect &rcOrigin, long &nCalWidth);

protected:
	DECLARE_MESSAGE_MAP()
};


