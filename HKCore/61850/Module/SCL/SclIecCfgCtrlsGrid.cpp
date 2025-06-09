#include "StdAfx.h"
#include "SclIecCfgCtrlsGrid.h"
#include "../SCL/SclIecCfgDatas.h"

#define SCL_IECCFG_CTRLS_GRID_COLS          5

#define SCL_IECCFG_CTRLS_COL_INDEX          0
#define SCL_IECCFG_CTRLS_COL_TYPE           1
#define SCL_IECCFG_CTRLS_COL_APPID          2
#define SCL_IECCFG_CTRLS_COL_DATASET        3
#define SCL_IECCFG_CTRLS_COL_IED_DESC       4



CSclIecCfgCtrlsGrid::CSclIecCfgCtrlsGrid(void)
{
	m_nAdjustBeginCol = 1;
}

CSclIecCfgCtrlsGrid::~CSclIecCfgCtrlsGrid(void)
{
}

void CSclIecCfgCtrlsGrid::InitGrid()
{
	SetListMode(TRUE);
	SetColumnCount(SCL_IECCFG_CTRLS_GRID_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CSclIecCfgCtrlsGrid::InitGridTitle()
{
	CString astrGridTitle[SCL_IECCFG_CTRLS_GRID_COLS] = {_T("编号"),_T("类型"),_T("AppID"),_T("数据集"),_T("IED描述")};
	int  iColType[SCL_IECCFG_CTRLS_GRID_COLS]={GVET_NOEDIT, GVET_NOEDIT,GVET_NOEDIT, GVET_NOEDIT, GVET_NOEDIT};
	int iGridWidth[SCL_IECCFG_CTRLS_GRID_COLS]={50, 50, 50, 50, 50};
	CExBaseListGrid::InitGridTitle(astrGridTitle, iGridWidth, SCL_IECCFG_CTRLS_GRID_COLS);
	SetFont(g_pGlobalFont11);
}

CDataType* CSclIecCfgCtrlsGrid::FindDataType(const CString &strDataType)
 {
	CDataType *pDataType = CCfgDataMngrConstGlobal::FindIecRtdDataType(strDataType);

	return pDataType;
}

void CSclIecCfgCtrlsGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	ASSERT (pData != NULL);
	CSclCtrlBase *pSclCtrlBase = (CSclCtrlBase *)pData;
	DWORD dwAppID = pSclCtrlBase->GetAppID();
	CString strAppID,strIedName,strTesterSmvPub = _T("测试仪SMV发布");
	strAppID.Format(_T("0x%04X"),dwAppID);
	CSclIed *pSclIed = (CSclIed*)pData->GetAncestor(SCLIECCLASSID_IED);

	if (pSclIed != NULL)
	{
		strIedName = pSclIed->m_strName;
	}

 	Show_Index(pData, nRow, SCL_IECCFG_CTRLS_COL_INDEX);					//编号

	if ((pSclCtrlBase->GetClassID() == SCLIECCLASSID_CTRL_SMV_OUT)||(pSclCtrlBase->GetClassID() == SCLIECCLASSID_CTRL_SMV_IN))
	{
		Show_StaticString(pData, nRow, SCL_IECCFG_CTRLS_COL_TYPE, &strTesterSmvPub);	
	} 
	else
	{
		Show_DataType_Val(pData, nRow, SCL_IECCFG_CTRLS_COL_TYPE, iecfg_SclCtrlAppDataType_Goose, (long*)&pData->m_dwItemData, EndEditCell_DataType_Val);//类型					
	}

 	Show_StaticString(pData, nRow, SCL_IECCFG_CTRLS_COL_APPID, &strAppID);						//AppID
 	Show_StaticString(pData, nRow, SCL_IECCFG_CTRLS_COL_DATASET, &pSclCtrlBase->m_strDataSetDesc);						//
 	Show_StaticString(pData, nRow, SCL_IECCFG_CTRLS_COL_IED_DESC, &strIedName);						//

	nRow++;
}


