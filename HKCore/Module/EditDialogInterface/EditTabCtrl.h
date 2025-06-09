#pragma once

#include <afxtabctrl.h>
// CEditTabCtrl

class CEditTabCtrl : public CMFCTabCtrl
{
	DECLARE_DYNAMIC(CEditTabCtrl)

public:
	CEditTabCtrl();
	virtual ~CEditTabCtrl();
	CFont m_font;

protected:
	DECLARE_MESSAGE_MAP()
public:

};


