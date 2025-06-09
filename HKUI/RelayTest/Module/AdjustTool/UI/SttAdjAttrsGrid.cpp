//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利


#include "stdafx.h"
#include "SttAdjAttrsGrid.h"
#include "../SttAdjBase.h"
#include "../SttMesLocalDb.h"

CSttAdjAttrsGrid::CSttAdjAttrsGrid()
{
	//初始化属性
	m_pModuleType = NULL;

	//初始化成员变量
}

CSttAdjAttrsGrid::~CSttAdjAttrsGrid()
{

}


void CSttAdjAttrsGrid::InitGrid()
{
	//m_nAdjustBeginCol = 1;
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(4);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}


void CSttAdjAttrsGrid::InitGridTitle()
{
	CString astrTitle[4] = {_T("编号"),_T("名称"),_T("标识"),_T("数据")};
	CString astrAttrs[4] = {_T(""),_T("name"),_T("id"),_T("value")};
	int nWidth[4]={40,250,150,250};

	CExBaseListGrid::InitGridTitle(astrTitle, nWidth, 4);
	InitGridColAttrs(astrAttrs, 4);
}

void CSttAdjAttrsGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CString strDataID = pData->m_strID;

	//非开关量模块，不显示开关量的属性  shaolei 20210717
	if (m_pModuleType != NULL)
	{
		//以下属性不显示到表格中  20210717  shaolei
		if (strDataID == STT_ADJ_ID_ModuleType || strDataID == STT_ADJ_ID_ChannelNum || strDataID == STT_ADJ_ID_ModulePos
			|| strDataID == STT_ADJ_ID_Model || strDataID == STT_ADJ_ID_SN)
		{
			return;
		}

		//非开关量模块
		if (m_pModuleType->m_strValue != STT_MODULE_TYPE_SWITCH_ID)
		{
			if (strDataID.Find(_T("SwitchIn")) >= 0)
			{
				return;
			}
		}
		else
		{
			if (strDataID == STT_ADJ_ID_UdcMax || strDataID == STT_ADJ_ID_IdcMax || strDataID == STT_ADJ_ID_ChMax
				|| strDataID == STT_ADJ_ID_ChDcMax || strDataID == STT_ADJ_ID_FreCoef || strDataID == STT_ADJ_ID_ModulePower
				|| strDataID == STT_ADJ_ID_ChMergeMode || strDataID == STT_ADJ_ID_fDigitalDelay)
			{
				return;
			}
		}

		//数字模块
		if (m_pModuleType->m_strValue.Find(_T("DIGITAL")) >= 0)
		{
			if (strDataID == STT_ADJ_ID_UdcMax || strDataID == STT_ADJ_ID_IdcMax || strDataID == STT_ADJ_ID_ChMax
				|| strDataID == STT_ADJ_ID_ChDcMax || strDataID == STT_ADJ_ID_FreCoef || strDataID == STT_ADJ_ID_ModulePower
				|| strDataID == STT_ADJ_ID_ChMergeMode)
			{
				return;
			}
		}
		else 
		{
			if (strDataID == STT_ADJ_ID_fDigitalDelay)
			{
				return;
			}
		}
	}

	CDvmData*pDvmData = (CDvmData*)pData;

	Show_Index(pDvmData , nRow, 0);

	long nCol = 1;
	for (nCol=1; nCol < m_nCols; nCol++)
	{
		ShowAttrCol(pDvmData, nRow, nCol);
	}

	nRow++;
}

//////////////////////////////////////////////////////////////////////////
//显示属性、或者是子对象
// void CSttAdjAttrsGrid::ShowAttrCol(CDvmData *pData, const CString &strAttrID, long nRow, long nCol)  	//显示CDvmData的属性
// {
// 	if (strAttrID == CDataMngrXmlRWKeys::ValueKey())
// 	{
// 		if (pData->m_strID == STT_ADJ_ID_ModuleType)
// 		{
// 			CDvmData *pFind = CSttMesLocalDb::FindModuleTypeData(pData->m_strValue);
// 
// 			if (pFind != NULL)
// 			{
// 				Show_StaticString(pData, nRow, nCol, pFind->m_strName);
// 			}
// 			else
// 			{
// 				Show_StaticString(pData, nRow, nCol, pData->m_strValue);
// 			}
// 		}
// 		else
// 		{
// 			Show_String(pData, nRow, nCol, &pData->m_strValue);
// 		}
// 	}
// 	else
// 	{
// 		CXDataGroupGridBase::ShowAttrCol(pData, strAttrID, nRow, nCol);
// 	}
// }
// 

#include "..\SttMesLocalDb.h"
CDataType* CSttAdjAttrsGrid::FindDataType(const CString &strDataType)
{
	return CSttMesLocalDb::FindDataType(strDataType);
}
