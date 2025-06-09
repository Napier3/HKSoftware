#pragma once

/*
	π¶ƒ‹√Ë ˆ£∫
*/

#include "..\..\..\Module\MfcCtrlEx\MacEdit.h"
#include "UISftRsltWndInterface.h"

class CUISftRsltWndMacEdit : public CMacEdit
{
public:
	CUISftRsltWndMacEdit();
	virtual ~CUISftRsltWndMacEdit();

public:
	CUISftRsltWndInterface* m_pResultWndInterface;

public:


	DECLARE_MESSAGE_MAP()
	afx_msg void OnEnChange();
	afx_msg void OnEnKillfocus();

};