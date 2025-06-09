#pragma once


// CEpDevMinimizeButton
#include "EpDevBase.h"

class CEpDevMinimizeButton : public CButton, public CEpDevBase
{
	DECLARE_DYNAMIC(CEpDevMinimizeButton)

public:
	CEpDevMinimizeButton();
	virtual ~CEpDevMinimizeButton();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClicked();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


