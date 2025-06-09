//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//StationTest.h  CStationTestListCtrl

#pragma once

#include "..\..\GridBase\ExBaseListGrid.h"
#include "..\DvmDataset.h"

enum GridType
{
	UNKNOWN_TABLE = 0,                  //未知类型
	CLIENT_TABLE,                        //客户表
	SOFTDOG_TABLE,                       //软件狗表
	CLIENT_NEW_TEMPLATE_TABLE,           //客户模板表
	CLIENT_OLD_TEMPLATE_TABLE,           //客户历史模板表
	DEVELOP_TASK_TABLE,                  //开发任务表
	OLD_DEVELOP_TASK_TABLE,              //历史开发任务表
	DEVELOPER_TEMPLATE_STATISTICS_TABLE, //开发人员模板开发统计表
	DEVELOPER_CLIENT_STATISTICS_TABLE,   //客户单位模板开发统计表
	MAX_TABLE_TYPE,
};

class CDvmDatasetGrid : public CExBaseListGrid
{
public:
	CDvmDatasetGrid();
	virtual ~CDvmDatasetGrid();

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual CDataType* FindDataType(const CString &strDataType)	;

	void UpdateIedTestState();
	void SetTableType(GridType nTableType);


//重载函数
public: 
	virtual void  OnEditCellLBDblClk(int nRow, int nCol, UINT nChar);
	virtual void OnDataSelChanged(int nRow=-1, int nCol=-1);

//私有成员变量
private:
	CDataType m_oDataType;

	GridType m_nTableType;
	int m_nTableColNum;
//私有成员变量访问方法
public:
};

