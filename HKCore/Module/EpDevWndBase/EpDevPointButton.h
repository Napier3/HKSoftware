#pragma once


// CEpDevPointButton
#include "EpDevPoint.h"

class CEpDevPointButton : public CButton, public CEpDevPoint
{
	DECLARE_DYNAMIC(CEpDevPointButton)

public:
	CEpDevPointButton();
	virtual ~CEpDevPointButton();

public:
	virtual CPoint GetConnectPoint();
	virtual void Show(UINT nShow);


	virtual long Expand(long nExpand);

	void SetExpand(long nExpand=EPDES_EXPAND);


protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClicked();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


