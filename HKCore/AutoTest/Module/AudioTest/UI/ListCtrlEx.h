#pragma once


// CListCtrlEx
#include <afxtempl.h>
typedef struct
{
	COLORREF colText;
	COLORREF colTextBk;
}TEXT_Bk;

class CListCtrlEx : public CListCtrl
{
	//DECLARE_DYNAMIC(CListCtrlEx)

public:
	CListCtrlEx();
	virtual ~CListCtrlEx();
protected:
	afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()

	
};


