//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ServerUser.h  CServerUserListCtrl

#pragma once

#include "..\BaseClass\ExBaseListListCtrl.h"



class CServerUserListCtrl : public CExBaseListListCtrl
{
public:
	CServerUserListCtrl();
	virtual ~CServerUserListCtrl();

	virtual void InitCollumns();

//重载函数
public:
	virtual void UpdateListCtrl(CExBaseObject *pObj, long nIndex);
	virtual void UpdateListCtrl(CExBaseObject *pObj);


//私有成员变量
private:

//私有成员变量访问方法
public:
};

