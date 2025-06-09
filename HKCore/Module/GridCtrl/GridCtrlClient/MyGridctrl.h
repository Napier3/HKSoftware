// MyGridctrl.h: interface for the CMyGridctrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYGRIDCTRL_H__8559AA25_6950_4F4B_8CB0_B753C0328F75__INCLUDED_)
#define AFX_MYGRIDCTRL_H__8559AA25_6950_4F4B_8CB0_B753C0328F75__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\Gridctrl.h"

class CMyGridctrl : public CGridCtrl  
{
public:
	CMyGridctrl();
	virtual ~CMyGridctrl();
	void InitGrid(int iRows);
	void InitGridTitle();

	void InitData();

	CGridDataTypes m_oDataTypes;

	virtual void FillComboBoxItems(int nCol, LPARAM cltWnd);
	
};

#endif // !defined(AFX_MYGRIDCTRL_H__8559AA25_6950_4F4B_8CB0_B753C0328F75__INCLUDED_)
