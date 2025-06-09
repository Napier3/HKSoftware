//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//WndAdjCellList.h  CWndAdjCellList

#pragma once

#include "WndChildCtrlsAdjustGlobal.h"

#include "WndAdjCell.h"


class CWndAdjCellList : public CWndAdjCell
{
public:
	CWndAdjCellList();
	virtual ~CWndAdjCellList();


//重载函数
public:
	virtual UINT GetClassID() {    return WCCACLASSID_CWNDADJCELLLIST;   }

//私有成员变量
private:

//私有成员变量访问方法
public:
	CWndAdjCell* CreateCell(CWnd *pWnd, BOOL bFixedWidth, BOOL bFixedHeight);
};

