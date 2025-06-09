#pragma once
#include "..\gridctrl.h"

class CMyGridCtrl :	public CGridCtrl
{
public:
	CMyGridCtrl(void);
	~CMyGridCtrl(void);

public:
	void InitGrid(int iRows);
	void InitGridTitle();

	void InitData();

	CGridDataTypes m_oDataTypes;

	virtual void FillComboBoxItems(int nCol, LPARAM cltWnd);

};
