#pragma once


// CListCtrlEx
#include <afxtempl.h>
#include "../../../Module/GuideBook/Items.h"
typedef struct
{
	COLORREF colText;
	COLORREF colTextBk;
}TEXT_Bk;

class CListCtrlEx : public CListCtrl
{
	DECLARE_DYNAMIC(CListCtrlEx)

public:
	CListCtrlEx();
	virtual ~CListCtrlEx();
	int  GetListSelectRow();
	void SetListSelectRow(int nRow,int nLastRow = -1);
	void SetListRowState(int nRow);
	void SetIsShowLine(bool bFlag = false);

protected:
	afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	DECLARE_MESSAGE_MAP()

private:
	bool		m_bIsShowLine;

	
};


