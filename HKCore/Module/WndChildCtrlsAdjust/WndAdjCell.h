//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//WndAdjCell.h  CWndAdjCell

#pragma once

#include "WndChildCtrlsAdjustGlobal.h"



class CWndAdjCell : public CBaseObject
{
public:
	CWndAdjCell();
	virtual ~CWndAdjCell();


	long  m_nFixedWidth;
	long  m_nFixedHeight;
	long  m_nOriginLeft;
	long  m_nOriginTop;
	long  m_nOriginWidth;
	long  m_nOriginHeight;
//重载函数
public:
	virtual UINT GetClassID() {    return WCCACLASSID_CWNDADJCELL;   }

//私有成员变量
private:

//私有成员变量访问方法
public:
};

