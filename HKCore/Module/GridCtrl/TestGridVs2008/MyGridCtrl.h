#pragma once
#include "..\gridctrl.h"

#include "..\..\API\GloblaDrawFunctions.h"

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

	virtual void FillComboBoxItems(int nRow, int nCol, LPARAM cltWnd);

};
