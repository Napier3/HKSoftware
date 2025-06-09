#pragma once


// CMFCTabCtrlEx

class CMFCTabCtrlEx : public CMFCTabCtrl
{
	DECLARE_DYNAMIC(CMFCTabCtrlEx)

public:
	CMFCTabCtrlEx();
	virtual ~CMFCTabCtrlEx();

protected:
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

};


