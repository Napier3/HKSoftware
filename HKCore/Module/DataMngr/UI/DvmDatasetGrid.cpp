//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利


#include "stdafx.h"
#include "DvmDatasetGrid.h"

#define DVMDATASET_COL_INDEX      0
#define DVMDATASET_COL_NAME       1
#define DVMDATASET_COL_ID            2
#define DVMDATASET_COL_DATATYPE      3
#define DVMDATASET_COL_UNIT            4
#define DVMDATASET_COL_VALUE      5

#define DVMDATASET_COLS           6

//int nMaxCols[MAX_TABLE_TYPE] = {6, 5， 6， 6， 7， 6， 9， 9 };//每种表格类型对应的列数量

CDvmDatasetGrid::CDvmDatasetGrid()
{
	//初始化属性

	//初始化成员变量
	m_oDataType.AddNewValue(_T("long"), _T("long"), _T("0"));
	m_oDataType.AddNewValue(_T("string"), _T("string"), _T("1"));
	m_oDataType.AddNewValue(_T("float"), _T("float"), _T("2"));
	m_oDataType.AddNewValue(_T("time"), _T("time"), _T("3"));

	m_nAdjustBeginCol = 1;

	m_nTableType = UNKNOWN_TABLE;

	m_nTableColNum = 0;
}

CDvmDatasetGrid::~CDvmDatasetGrid()
{

}


void CDvmDatasetGrid::InitGrid()
{
	//m_nAdjustBeginCol = 1;
	ASSERT(m_nTableColNum>0);
	ASSERT(m_nTableType != UNKNOWN_TABLE);
	

	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(m_nTableColNum);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}


void CDvmDatasetGrid::InitGridTitle()
{
	switch(m_nTableType)
	{
	case CLIENT_TABLE://客户表
		{
			CString astrGridTitle[MAX_TABLE_TYPE] = {_T("编号"),_T("客户名称"),_T("客户编号"),_T("待开发模板数"),_T("授权模板数"), _T("受权软件狗数量")};
			int iGridWidth[MAX_TABLE_TYPE]={100,150,100, 100, 100,100};
			CExBaseListGrid::InitGridTitle(astrGridTitle, iGridWidth, m_nTableColNum);
		}
		break;
	case SOFTDOG_TABLE:                       //软件狗表
		{
			CString astrGridTitle[MAX_TABLE_TYPE] = {_T("编号"),_T("软件狗编号"),_T("测试人员名称"),_T("授权的权限信息"),_T("测试人员部门")};
			int iGridWidth[MAX_TABLE_TYPE]={100,150,100, 100, 100};
			CExBaseListGrid::InitGridTitle(astrGridTitle, iGridWidth, m_nTableColNum);
		}
		break;
	case CLIENT_NEW_TEMPLATE_TABLE:           //客户模板表
		{
			CString astrGridTitle[MAX_TABLE_TYPE] = {_T("编号"),_T("模板名称"),_T("开发人员"),_T("上传日期"),_T("审核人员"), _T("审核日期")};
			int iGridWidth[MAX_TABLE_TYPE]={100,150,100, 100, 100,100};
			CExBaseListGrid::InitGridTitle(astrGridTitle, iGridWidth, m_nTableColNum);
		}
		break;
	case OLD_DEVELOP_TASK_TABLE:              //历史开发任务表
	case CLIENT_OLD_TEMPLATE_TABLE:           //客户历史模板表
		{
			CString astrGridTitle[MAX_TABLE_TYPE] = {_T("编号"),_T("版本"),_T("开发人员"),_T("上传日期"),_T("审核人员"), _T("审核日期")};
			int iGridWidth[MAX_TABLE_TYPE]={100,150,100, 100, 100,100};
			CExBaseListGrid::InitGridTitle(astrGridTitle, iGridWidth, m_nTableColNum);
		}
		break;
	case DEVELOP_TASK_TABLE:                  //开发任务表
		{
			CString astrGridTitle[MAX_TABLE_TYPE] = {_T("编号"),_T("模板名称"), _T("状态"),_T("开发人员"),_T("上传日期"),_T("审核人员"), _T("审核日期")};
			int iGridWidth[MAX_TABLE_TYPE]={100,150,100, 100, 100, 100, 100};
			CExBaseListGrid::InitGridTitle(astrGridTitle, iGridWidth, m_nTableColNum);
		}
		break;
	case DEVELOPER_TEMPLATE_STATISTICS_TABLE: //开发人员模板开发统计表
		{
			CString astrGridTitle[MAX_TABLE_TYPE] = {_T("编号"),_T("开发人员"), _T("35KV及以下"),_T("110KV"),_T("220kV线路"),_T("220KV变压器"), _T("220KV母线"), _T("220KV以上"), _T("总数")};
			int iGridWidth[MAX_TABLE_TYPE]={100,100,100, 100, 100,100, 100, 100, 100};
			CExBaseListGrid::InitGridTitle(astrGridTitle, iGridWidth, m_nTableColNum);
		}
		break;
	case DEVELOPER_CLIENT_STATISTICS_TABLE:   //客户单位模板开发统计表
		{
			CString astrGridTitle[MAX_TABLE_TYPE] = {_T("编号"),_T("客户单位"), _T("35KV及以下"),_T("110KV"),_T("220kV线路"),_T("220KV变压器"), _T("220KV母线"), _T("220KV以上"), _T("总数")};
			int iGridWidth[MAX_TABLE_TYPE]={100,100,100, 100, 100,100, 100, 100, 100};
			CExBaseListGrid::InitGridTitle(astrGridTitle, iGridWidth, m_nTableColNum);
		}
		break;
	default:
		break;
	}
}

void CDvmDatasetGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (pData->GetClassID() != DVMCLASSID_CDVMDATA)
	{
		return;
	}

	CDvmData *pDvmData = (CDvmData*)pData;

	Show_Index(pDvmData, nRow, DVMDATASET_COL_INDEX);
	Show_String(pDvmData, nRow, DVMDATASET_COL_NAME, &pDvmData->m_strName);
	Show_String(pDvmData, nRow, DVMDATASET_COL_ID, &pDvmData->m_strID);
	Show_ComboBox(pDvmData, &m_oDataType, nRow, DVMDATASET_COL_DATATYPE, &pDvmData->m_strDataType);
	Show_String(pDvmData, nRow, DVMDATASET_COL_UNIT, &pDvmData->m_strUnit);
	Show_String(pDvmData, nRow, DVMDATASET_COL_VALUE, &pDvmData->m_strValue);

	//Show_Check(pShortData, nRow, DVMDATASET_COL_ID, (long*)&pShortData->m_strID);
// 
// #ifdef _UNICODE
// 	if (wcsicmp(pShortData->m_strDataTypeID, _T("bool")) == 0)
// #else
// 	if (stricmp(pShortData->m_strDataTypeID, _T("bool") == 0)
// #endif
// 	{
// 		Show_Check(pShortData, nRow, DVMDATASET_COL_VALUE, (long*)&pShortData->m_dwItemData);
// 	}
// 	else
// 	{
// 		Show_DataType_Val(pShortData, nRow, DVMDATASET_COL_VALUE, pShortData->m_strDataTypeID, (long*)&pShortData->m_dwItemData);
// 	}

	nRow++;
}

CDataType* CDvmDatasetGrid::FindDataType(const CString &strDataType)
{
	return &m_oDataType;
}


void  CDvmDatasetGrid::OnEditCellLBDblClk(int nRow, int nCol, UINT nChar)
{
	
}


void CDvmDatasetGrid::OnDataSelChanged(int nRow, int nCol)
{
	//CShortData *pData = (CShortData*)GetCurrSelData(1);
	CShortData *pData = (CShortData*)GetDataRow(nRow, 1);

	if (pData == NULL)
	{
		return;
	}

}

void CDvmDatasetGrid::SetTableType(GridType nTableType)
{
	m_nTableType = nTableType;
	switch(m_nTableType)
	{
	case CLIENT_TABLE://客户表
	case CLIENT_NEW_TEMPLATE_TABLE:           //客户模板表
	case OLD_DEVELOP_TASK_TABLE:              //历史开发任务表
	case CLIENT_OLD_TEMPLATE_TABLE:           //客户历史模板表
		{
			m_nTableColNum = 6;
		}
		break;
	case SOFTDOG_TABLE:                       //软件狗表
		{
			m_nTableColNum = 5;
		}
		break;
	case DEVELOP_TASK_TABLE:                  //开发任务表
		{
			m_nTableColNum = 7;
		}
		break;
	case DEVELOPER_TEMPLATE_STATISTICS_TABLE: //开发人员模板开发统计表
	case DEVELOPER_CLIENT_STATISTICS_TABLE:   //客户单位模板开发统计表
		{
			m_nTableColNum = 9;
		}
		break;
	default:
		break;
	}
}

