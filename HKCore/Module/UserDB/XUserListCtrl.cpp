//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//StationTest.cpp  CXUserListCtrl


#include "stdafx.h"
#include "XUserListCtrl.h"

CXUserListCtrl::CXUserListCtrl()
{
	//初始化属性

	//初始化成员变量
}

CXUserListCtrl::~CXUserListCtrl()
{

}

void CXUserListCtrl::InitCollumns()
{
	InsertColumn(XUSER_COL_INDEX,     _T("编号"),          LVCFMT_CENTER,40);
	InsertColumn(XUSER_COL_NAME,      _T("名称"),          LVCFMT_CENTER,180);
	InsertColumn(XUSER_COL_ID,        _T("ID"),            LVCFMT_CENTER,200);
	InsertColumn(XUSER_COL_CURRTOOL,  _T("当前使用的工具"),LVCFMT_CENTER,80);

}

void CXUserListCtrl::UpdateListCtrl(CExBaseObject *pObj, long nIndex)
{
	CXUser *pUser = (CXUser*)pObj;

	SetItemData(nIndex, (DWORD)pObj);
}
