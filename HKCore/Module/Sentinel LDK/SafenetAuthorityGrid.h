//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

#pragma once

#include "../GridBase/ExBaseListGrid.h"
#include "XSafenetBase.h"

#define SAFENET_AUTHORITY_COL_INDEX      0
#define SAFENET_AUTHORITY_COL_SEL          1
#define SAFENET_AUTHORITY_COL_NAME       2
#define SAFENET_AUTHORITY_COL_ID            3

#define SAFENET_AUTHORITY_COLS               4


class CSafenetAuthorityGrid : public CExBaseListGrid
{
public:
	CSafenetAuthorityGrid();
	virtual ~CSafenetAuthorityGrid();

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

//重载函数
public: 
	BOOL m_bUseEnable;

//私有成员变量
private:

//私有成员变量访问方法
public:
};

