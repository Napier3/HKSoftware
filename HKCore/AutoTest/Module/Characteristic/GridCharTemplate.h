//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//GridCharTemplate.h  CGridCharTemplate

#pragma once

#include "..\..\..\Module\GridBase\ExBaseListGrid.h"
#include "CharacteristicTmplate.h"


#define CHARTEMPLATE_COL_INDEX        0
#define CHARTEMPLATE_COL_NAME         1
#define CHARTEMPLATE_COL_ID           2
#define CHARTEMPLATE_COL_AXIS         3


#define CHARTEMPLATE_COLS             4


class CGridCharTemplate : public CExBaseListGrid
{
public:
	CGridCharTemplate();
	virtual ~CGridCharTemplate();

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

//重载函数
public: 
	
//私有成员变量
private:

//私有成员变量访问方法
public:

};

