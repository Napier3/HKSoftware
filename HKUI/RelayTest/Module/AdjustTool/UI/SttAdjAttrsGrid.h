//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

#pragma once

#include "..\..\..\..\Module\DataMngr\UI\XDataGroupGridBase.h"


class CSttAdjAttrsGrid : public CXDvmGrid_DataRow
{
public:
	CSttAdjAttrsGrid();
	virtual ~CSttAdjAttrsGrid();

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	CDvmData *m_pModuleType;   //20210717  shaolei  记录模块类型，用于区别显示模块属性
	//重载函数
public: 
	//virtual void ShowAttrCol(CDvmData *pData, const CString &strAttrID, long nRow, long nCol);  	//显示CDvmData的属性

//私有成员变量
private:

//私有成员变量访问方法
public:
	virtual CDataType* FindDataType(const CString &strDataType);
};

