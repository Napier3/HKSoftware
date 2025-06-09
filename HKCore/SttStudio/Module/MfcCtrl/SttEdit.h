#pragma once

#include "SttWndCtrlInterface.h"

// CSttEdit

class CSttEdit : public CEdit, public CSttWndCtrlInterface
{
	DECLARE_DYNAMIC(CSttEdit)

public:
	CSttEdit();
	virtual ~CSttEdit();

public:
	virtual void ShowData();
	virtual void SaveData();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKillFocus(CWnd* pNewWnd);
};


