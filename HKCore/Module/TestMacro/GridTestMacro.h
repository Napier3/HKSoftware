//GridTestMacro.h

#pragma once

#include "..\..\Module\GridBase\ExBaseListGrid.h"

#define TESTMCACRO_COLS                3
#define WM_MACRO_MAP  (WM_USER + 1053)

class CGridTestMacro : public CExBaseListGrid
{
public:
	CGridTestMacro();
	virtual ~CGridTestMacro();

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void OnEditCellLBDblClk(int nRow, int nCol, UINT nChar);

	void AttachMsgRcvWnd(CWnd *pWnd)			{	m_pMsgRcvWnd = pWnd;	}

protected:
	CWnd *m_pMsgRcvWnd;

//重载函数
public: 
	
//私有成员变量
private:

//私有成员变量访问方法
public:

};

