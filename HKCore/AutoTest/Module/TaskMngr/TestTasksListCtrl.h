//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TestTasksListCtrl.h  CTestTasksListCtrl

#pragma once

#include "..\..\..\Module\BaseClass\ExBaseListListCtrl.h"
#include "TestTask.h"



class CTestTasksListCtrl : public CExBaseListListCtrl
{
public:
	CTestTasksListCtrl();
	virtual ~CTestTasksListCtrl();

	virtual void InitCollumns();
	virtual void UpdateListCtrl(CExBaseObject *pObj, long nIndex);

	//重载函数
public: 


	//私有成员变量
private:

	//私有成员变量访问方法
public:
};

