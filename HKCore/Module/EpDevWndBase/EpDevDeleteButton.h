#pragma once


// CEpDevDeleteButton
#include "EpDevBase.h"

class CEpDevDeleteButton : public CButton, public CEpDevBase
{
	DECLARE_DYNAMIC(CEpDevDeleteButton)

public:
	CEpDevDeleteButton();
	virtual ~CEpDevDeleteButton();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClicked();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


