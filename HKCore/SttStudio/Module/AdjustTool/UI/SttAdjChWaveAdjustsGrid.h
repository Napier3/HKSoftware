//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

#pragma once

#include "..\..\..\..\Module\DataMngr\UI\XDataGroupGridBase.h"


class CSttAdjChWaveAdjustsGrid : public CXDvmGrid_GroupRowDataCol
{
public:
	CSttAdjChWaveAdjustsGrid();
	virtual ~CSttAdjChWaveAdjustsGrid();

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

//删去相位校准列
class CSttAdjChWaveAdjustsGrid2 : public CXDvmGrid_GroupRowDataCol
{
public:
	CSttAdjChWaveAdjustsGrid2();
	virtual ~CSttAdjChWaveAdjustsGrid2();

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
};

//相位校准列改为硬件零漂
class CSttAdjChWaveAdjustsGrid3 : public CXDvmGrid_GroupRowDataCol
{
public:
	CSttAdjChWaveAdjustsGrid3();
	virtual ~CSttAdjChWaveAdjustsGrid3();

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
};
