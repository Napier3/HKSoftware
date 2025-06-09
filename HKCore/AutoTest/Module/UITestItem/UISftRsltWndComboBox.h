#pragma once

/*
	π¶ƒ‹√Ë ˆ£∫
*/
#include "UISftRsltWndInterface.h"

class CUISftRsltWndComboBox : public CComboBox
{
public:
	CUISftRsltWndComboBox(CShortData *pData);
	virtual ~CUISftRsltWndComboBox();

public:
	CUISftRsltWndInterface* m_pResultWndInterface;
	CShortData *m_pData;

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnCbnSelchange();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};