#include "StdAfx.h"
#include "IecCfgGoutDataGrid.h"

#include "..\XLanguageResourceIec.h"//20161014

//////////////////////////////////////////////////////////////////////////
//CStCfgGridBase

CIecCfgGoutDataGrid::CIecCfgGoutDataGrid(long nUseType)
{
	m_nUseType = nUseType;
}


CIecCfgGoutDataGrid::~CIecCfgGoutDataGrid(void)
{
	
}

void CIecCfgGoutDataGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);

	if (m_nUseType == IEC_CFG_DEVICE_USE_TYPE_AT02D)
	{
		SetColumnCount(IECCFG_COLS_GOUTDATA_AT02D);
	}
	else if (m_nUseType == IEC_CFG_DEVICE_USE_TYPE_ISmartTest)
	{
		SetColumnCount(IECCFG_COLS_GOUTDATA_ISmartTest);
	} 
	else
	{
		SetColumnCount(IECCFG_COLS_GOUTDATA);
	} 

	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CIecCfgGoutDataGrid::InitGridTitle()
{
	if (m_nUseType == IEC_CFG_DEVICE_USE_TYPE_AT02D)
	{
		CString cTempStr[IECCFG_COLS_GOUTDATA_AT02D]={
			g_sLtxt_SICDGSerial,g_sLtxt_SICDSelect,g_sLtxt_SICDIED,g_sLtxt_SICDDesMAC,
			g_sLtxt_SourceMAC,//_T("序号"),_T("选择"), _T("控制块所在IED"),_T("目标MAC"),_T("源MAC"),
			_T("APPID"), _T("TCI Priority"), _T("TCI VID"),
			g_sLtxt_OutputSel,_T("AT02D光口"),g_sLtxt_Description,g_sLtxt_SICDChaNO,
			g_sLtxt_VersionNumber,g_sLtxt_TestMark,//_T("输出口选择"), _T("描述"), _T("通道数"), _T("版本号"),_T("测试标记"),
			_T("gocbRef"), _T("datSet"),_T("goID"), _T("ndsCom"),
			_T("最短传输时间(ms)"),_T("稳定条件下重传时间(ms)"),_T("组间延时(ms)"),//_T("最短传输时间"),_T("稳定条件下重传时间"),_T("组间延时")
			g_sLtxt_TimeQualty,_T("允许生存时间(ms)")//,_T("时间品质"), _T("允许生存时间")
		};
		int iWidth[IECCFG_COLS_GOUTDATA_AT02D]={60,60, 160,160,90, 100, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80};

		CIecCfgDataGridBase::InitGridTitle(cTempStr, iWidth, IECCFG_COLS_GOUTDATA_AT02D);
	}	
	else if (m_nUseType == IEC_CFG_DEVICE_USE_TYPE_ISmartTest)
	{
		CString cTempStr[IECCFG_COLS_GOUTDATA_ISmartTest]={
			g_sLtxt_SICDGSerial,g_sLtxt_SICDSelect,g_sLtxt_SICDIED,
			_T("输出口选择"),g_sLtxt_TestMark,
			g_sLtxt_SICDDesMAC,
			g_sLtxt_SourceMAC,//_T("序号"),_T("选择"), _T("控制块所在IED"),_T("目标MAC"),_T("源MAC"),
			_T("APPID"), _T("TCI Priority"), _T("TCI VID"),
			g_sLtxt_Description,g_sLtxt_SICDChaNO,
			g_sLtxt_VersionNumber,//_T("输出口选择"), _T("描述"), _T("通道数"), _T("版本号"),
			_T("gocbRef"), _T("datSet"),_T("goID"), _T("ndsCom"),
			_T("最短传输时间(ms)"),_T("稳定条件下重传时间(ms)"),_T("组间延时(ms)"),//_T("最短传输时间"),_T("稳定条件下重传时间"),_T("组间延时")
			g_sLtxt_TimeQualty,_T("允许生存时间(ms)")//,_T("时间品质"), _T("允许生存时间(ms)")
		};
		int iWidth[IECCFG_COLS_GOUTDATA_ISmartTest]={60,60, 160,80,80,90, 100, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80};

		CIecCfgDataGridBase::InitGridTitle(cTempStr, iWidth, IECCFG_COLS_GOUTDATA_ISmartTest);
	}
	else
	{
		CString cTempStr[IECCFG_COLS_GOUTDATA]={
			g_sLtxt_SICDGSerial,g_sLtxt_SICDSelect,g_sLtxt_SICDIED,g_sLtxt_SICDDesMAC,
			g_sLtxt_SourceMAC,//_T("序号"),_T("选择"), _T("控制块所在IED"),_T("目标MAC"),_T("源MAC"),
			_T("APPID"), _T("TCI Priority"), _T("TCI VID"),
			g_sLtxt_OutputSel,g_sLtxt_Description,g_sLtxt_SICDChaNO,
			g_sLtxt_VersionNumber,g_sLtxt_TestMark,//_T("输出口选择"), _T("描述"), _T("通道数"), _T("版本号"),_T("测试标记"),
			_T("gocbRef"), _T("datSet"),_T("goID"), _T("ndsCom"),
			_T("最短传输时间(ms)"),_T("稳定条件下重传时间(ms)"),_T("组间延时(ms)"),//_T("最短传输时间"),_T("稳定条件下重传时间"),_T("组间延时")
			g_sLtxt_TimeQualty,_T("允许生存时间(ms)")//,_T("时间品质"), _T("允许生存时间(ms)")
		};
		int iWidth[IECCFG_COLS_GOUTDATA]={60,60, 160,160,90, 100, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80};

		CIecCfgDataGridBase::InitGridTitle(cTempStr, iWidth, IECCFG_COLS_GOUTDATA);
	}

}	


void CIecCfgGoutDataGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();

	if (nClassID != CFGCLASSID_CIECCFGGOUTDATA)
	{
		return;
	}

	CIecCfgDataGridBase::ShowData(pData, nRow, bInsertRow);

	CIecCfgGoutData *pIecCfgGOUTData = (CIecCfgGoutData*)pData;

	if (m_nUseType == IEC_CFG_DEVICE_USE_TYPE_ISmartTest)
	{
		CString strTmp;
		Show_StaticString(pData, nRow, 2,    &pIecCfgGOUTData->m_strgocbIED/*m_strIedRefDesc*/);
		Show_Fiber(pData, nRow, 3,    &pIecCfgGOUTData->m_nFiberIndex);
		Show_Check(pData, nRow, 4,    &pIecCfgGOUTData->m_bTest);
		Show_StaticString(pData, nRow, 5, &pIecCfgGOUTData->m_strDestAddress);
		Show_StaticString(pData, nRow, 6,  &pIecCfgGOUTData->m_strSrcAddress);
		strTmp.Format(_T("0X%04X"),pIecCfgGOUTData->m_dwAppID);
		Show_StaticString(pData, nRow, 7, strTmp);
		Show_Long(pData, nRow, 8,    &pIecCfgGOUTData->m_dwVLandPriority,FALSE,_T(""),EndEditCell_Priority);
		strTmp.Format(_T("0X%03X"),pIecCfgGOUTData->m_dwVLandID);
		Show_StaticString(pData, nRow, 9,    strTmp);//VlanID改为2个字节,实际只用到16进制3位  zhouhj 20211030

		Show_StaticString(pData, nRow, 10,    &pIecCfgGOUTData->m_strIedRefDesc/*m_strgocbIED*/);
		Show_Long(pData, nRow, 11,  &pIecCfgGOUTData->m_nChannelNum,FALSE);
		Show_Long(pData, nRow, 12,    (long*)&pIecCfgGOUTData->m_dwVersion, FALSE);
		
		Show_StaticString(pData, nRow, 13,    &pIecCfgGOUTData->m_strgocbRef);
		Show_StaticString(pData, nRow, 14,    &pIecCfgGOUTData->m_strDataSet);
		Show_StaticString(pData, nRow, 15,    &pIecCfgGOUTData->m_strGooseId);
		Show_Long(pData, nRow, 16,    &pIecCfgGOUTData->m_bNdsCom,FALSE);
		Show_Long(pData, nRow, 17,    &pIecCfgGOUTData->m_nT1, FALSE,_T(""),EndEditCell_GoutLongTime);
		Show_Long(pData, nRow, 18,    &pIecCfgGOUTData->m_nT0,FALSE,_T(""),EndEditCell_GoutLongTime);
		Show_Long(pData, nRow, 19,    &pIecCfgGOUTData->m_nTGroup,FALSE,_T(""),EndEditCell_GoutLongTime);
		Show_StaticString(pData, nRow, 20,    &pIecCfgGOUTData->m_strTQuality);
		Show_Long(pData, nRow, 21,    &pIecCfgGOUTData->m_nLiveTime,FALSE,_T(""),EndEditCell_GoutLongTime);
		SetRowFgClr(nRow,4,21,RGB(128,128,128));
		nRow++;
		return;
	} 

	Show_StaticString(pData, nRow, IECCFG_COL_ID_GOUTDATA_CTRLREF,    &pIecCfgGOUTData->m_strgocbIED/*m_strIedRefDesc*/);
	Show_Mac(pData, nRow, IECCFG_COL_ID_GOUTDATA_DEST_MAC, &pIecCfgGOUTData->m_strDestAddress);
	Show_Mac(pData, nRow, IECCFG_COL_ID_GOUTDATA_SRC_MAC,  &pIecCfgGOUTData->m_strSrcAddress);
	Show_Hex(pData, nRow, IECCFG_COL_ID_GOUTDATA_APPID,    &pIecCfgGOUTData->m_dwAppID, 2);
	Show_Long(pData, nRow, IECCFG_COL_ID_GOUTDATA_PRIO,    &pIecCfgGOUTData->m_dwVLandPriority,TRUE,_T(""),EndEditCell_Priority);
	Show_VlanID(pData, nRow, IECCFG_COL_ID_GOUTDATA_VID,    &pIecCfgGOUTData->m_dwVLandID,2);//VlanID改为2个字节,实际只用到16进制3位  zhouhj 20211030
	Show_Fiber(pData, nRow, IECCFG_COL_ID_GOUTDATA_PORT,    &pIecCfgGOUTData->m_nFiberIndex);

	if (m_nUseType == IEC_CFG_DEVICE_USE_TYPE_AT02D)
	{
		Show_Fiber2(pData, nRow, IECCFG_COL_ID_GOUTDATA_PORT+1,    &pIecCfgGOUTData->m_nFiber2Index);
		Show_String(pData, nRow, IECCFG_COL_ID_GOUTDATA_DESC+1,    &pIecCfgGOUTData->m_strIedRefDesc/*m_strgocbIED*/);
		Show_ChNum(pData, nRow, IECCFG_COL_ID_GOUTDATA_CHNUM+1,  &pIecCfgGOUTData->m_nChannelNum);
		Show_Hex(pData, nRow, IECCFG_COL_ID_GOUTDATA_VERS+1,    &pIecCfgGOUTData->m_dwVersion, 2);
		Show_Check(pData, nRow, IECCFG_COL_ID_GOUTDATA_TEST+1,    &pIecCfgGOUTData->m_bTest);
		Show_String(pData, nRow, IECCFG_COL_ID_GOUTDATA_GCREF+1,    &pIecCfgGOUTData->m_strgocbRef);
		Show_String(pData, nRow, IECCFG_COL_ID_GOUTDATA_DTSET+1,    &pIecCfgGOUTData->m_strDataSet);
		Show_String(pData, nRow, IECCFG_COL_ID_GOUTDATA_GOID+1,    &pIecCfgGOUTData->m_strGooseId);
		Show_Check(pData, nRow, IECCFG_COL_ID_GOUTDATA_NDS+1,    &pIecCfgGOUTData->m_bNdsCom);
		Show_Long(pData, nRow, IECCFG_COL_ID_GOUTDATA_T1+1,    &pIecCfgGOUTData->m_nT1,TRUE,_T(""),EndEditCell_GoutLongTime);
		Show_Long(pData, nRow, IECCFG_COL_ID_GOUTDATA_T0+1,    &pIecCfgGOUTData->m_nT0,TRUE,_T(""),EndEditCell_GoutLongTime);
		Show_Long(pData, nRow, IECCFG_COL_ID_GOUTDATA_T2+1,    &pIecCfgGOUTData->m_nTGroup,TRUE,_T(""),EndEditCell_GoutLongTime);
		Show_String(pData, nRow, IECCFG_COL_ID_GOUTDATA_TQ+1,    &pIecCfgGOUTData->m_strTQuality);
		Show_Long(pData, nRow, IECCFG_COL_ID_GOUTDATA_OTHER+1,    &pIecCfgGOUTData->m_nLiveTime,TRUE,_T(""),EndEditCell_GoutLongTime);
	}
	else
	{
		Show_String(pData, nRow, IECCFG_COL_ID_GOUTDATA_DESC,    &pIecCfgGOUTData->m_strIedRefDesc/*m_strgocbIED*/);
		Show_ChNum(pData, nRow, IECCFG_COL_ID_GOUTDATA_CHNUM,  &pIecCfgGOUTData->m_nChannelNum);
		Show_Hex(pData, nRow, IECCFG_COL_ID_GOUTDATA_VERS,    &pIecCfgGOUTData->m_dwVersion, 2);
		Show_Check(pData, nRow, IECCFG_COL_ID_GOUTDATA_TEST,    &pIecCfgGOUTData->m_bTest);
		Show_String(pData, nRow, IECCFG_COL_ID_GOUTDATA_GCREF,    &pIecCfgGOUTData->m_strgocbRef);
		Show_String(pData, nRow, IECCFG_COL_ID_GOUTDATA_DTSET,    &pIecCfgGOUTData->m_strDataSet);
		Show_String(pData, nRow, IECCFG_COL_ID_GOUTDATA_GOID,    &pIecCfgGOUTData->m_strGooseId);
		Show_Check(pData, nRow, IECCFG_COL_ID_GOUTDATA_NDS,    &pIecCfgGOUTData->m_bNdsCom);
		Show_Long(pData, nRow, IECCFG_COL_ID_GOUTDATA_T1,    &pIecCfgGOUTData->m_nT1, TRUE,_T(""),EndEditCell_GoutLongTime);
		Show_Long(pData, nRow, IECCFG_COL_ID_GOUTDATA_T0,    &pIecCfgGOUTData->m_nT0,TRUE,_T(""),EndEditCell_GoutLongTime);
		Show_Long(pData, nRow, IECCFG_COL_ID_GOUTDATA_T2,    &pIecCfgGOUTData->m_nTGroup,TRUE,_T(""),EndEditCell_GoutLongTime);
		Show_String(pData, nRow, IECCFG_COL_ID_GOUTDATA_TQ,    &pIecCfgGOUTData->m_strTQuality);
		Show_Long(pData, nRow, IECCFG_COL_ID_GOUTDATA_OTHER,    &pIecCfgGOUTData->m_nLiveTime,TRUE,_T(""),EndEditCell_GoutLongTime);
	} 

	nRow++;
}

void CIecCfgGoutDataGrid::EndEditCell_GoutLongTime(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVCellData != NULL);
	ASSERT (pVCellData->pString != NULL);

	long nValue =  CString_To_long(pCell->szText);

	if (nValue>500000)
	{
		nValue = 500000;
	}

	if (nValue<1)
	{
		nValue = 1;
	}

	*(pVCellData->pnValue) = nValue;
	pCell->szText.Format(_T("%d"), *(pVCellData->pnValue));
	pGrid->RedrawCell(nRow, nCol);
	((CExBaseListGrid*)pGrid)->SetModifiedFlag(pVCellData->pObj);
	((CExBaseListGrid*)pGrid)->DataViewOptr_DataChanged(nRow, nCol);
	((CExBaseListGrid*)pGrid)->SetModifiedFlag(pVCellData->pObj);
}





