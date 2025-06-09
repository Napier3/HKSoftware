//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

#pragma once

#include "..\..\..\..\Module\DataMngr\UI\XDataGroupGridBase.h"

#include "..\SttAdjBase.h"

class CSttAdjModeGrid : public CXDvmGrid_DataRow
//class CSttAdjModeGrid : public CXDvmGrid_GroupRowDataCol
{
public:
	CSttAdjModeGrid();
	virtual ~CSttAdjModeGrid();

	virtual void InitGrid();
	virtual void InitGridTitle();
	//virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

//重载函数
public: 
	//virtual void ShowAttrCol(CDvmData *pData, const CString &strAttrID, long nRow, long nCol);  	//显示CDvmData的属性
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow);

//私有成员变量
private:

//私有成员变量访问方法
public:
};

