//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

#pragma once

#include "..\..\..\..\Module\DataMngr\UI\XDataGroupGridBase.h"


class CSttAdjModulesGrid : public CXDvmGrid_GroupRowDataCol
{
public:
	CSttAdjModulesGrid();
	virtual ~CSttAdjModulesGrid();

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	//virtual void ShowAttrCol(CDataGroup *pDataGroup, const CString &strDataID, long nRow, long nCol) ;
//重载函数
public: 

//私有成员变量
private:

//私有成员变量访问方法
public:
	virtual CDataType* FindDataType(const CString &strDataType);
};

