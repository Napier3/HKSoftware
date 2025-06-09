//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//WndAdjRow.h  CWndAdjRow

#pragma once

#include "WndChildCtrlsAdjustGlobal.h"

#include "WndAdjCellList.h"


class CWndAdjRow : public CWndAdjCellList
{
public:
	CWndAdjRow();
	virtual ~CWndAdjRow();


//重载函数
public:
	virtual UINT GetClassID() {    return WCCACLASSID_CWNDADJROW;   }

//私有成员变量
private:

//私有成员变量访问方法
public:
};

