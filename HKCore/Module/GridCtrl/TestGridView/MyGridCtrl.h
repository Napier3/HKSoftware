#pragma once
#include "..\gridctrl.h"

class CMyGridCtrl :	public CXGridCtrlBase
{
public:
	CMyGridCtrl(void);
	~CMyGridCtrl(void);

public:
	void InitGrid(int iRows);
	void InitGridTitle();

	void InitData();

	CGridDataTypes m_oDataTypes;

	virtual void FillComboBoxItems(int nRow, int nCol, LPARAM cltWnd);

};
