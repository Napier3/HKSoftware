//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权?


#include "stdafx.h"
#include "SttAdjChMapGrid.h"
#include "..\SttAdjBase.h"
#include "..\SttMesLocalDb.h"
#include "..\..\..\Local\SttAdjMain\XLanguageResource_SttAdjMain.h"

CSttAdjHdChDefGrid::CSttAdjHdChDefGrid()
{
	//初始化属性

	//初始化成员变量
	m_strChildDataTypeID = STT_ADJ_DATA_TYPE_HdCh;
}

CSttAdjHdChDefGrid::~CSttAdjHdChDefGrid()
{

}


void CSttAdjHdChDefGrid::InitGrid()
{
	//m_nAdjustBeginCol = 1;
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(10);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}


void CSttAdjHdChDefGrid::InitGridTitle()
{
#ifndef NOT_USE_XLANGUAGE
	CString astrTitle[10] = {/*_T("编号")*/g_sLangTxt_Index,/*_T("名称")*/g_sLangTxt_SttAdjMain_Name,/*_T("通道ID")*/g_sLangTxt_SttAdjMain_ChannelID,/*_T("通道编号")*/g_sLangTxt_SttAdjMain_ChannelIndex,
		/*_T("工作模式")*/g_sLangTxt_SttAdjMain_WorkMode,/*_T("电气类型")*/g_sLangTxt_SttAdjMain_MacroType,/*_T("通道映射")*/g_sLangTxt_SttAdjMain_ChannelMap,
		/*_T("交流最大值")*/g_sLangTxt_SttAdjMain_MaxValueAC,/*_T("直流最大值")*/g_sLangTxt_SttAdjMain_MaxValueDC,/*_T("通道采集映射位置")*/g_sLangTxt_SttAdjMain_ChAcqMap};
#else
	CString astrTitle[10] = {_T("编号"),_T("名称"),_T("通道ID"),_T("通道编号"),_T("工作模式"),_T("电气类型"),_T("通道映射"),_T("交流最大值"),_T("直流最大值"), _T("通道采集映射位置")};
#endif
	CString astrAttrs[10] = {_T(""),_T("Name"), _T("ID"), _T("Index"), _T("WorkMode"), _T("EeType"), _T("ChRsIndex"), _T("ChACMaxValue"), _T("ChDCMaxValue"), _T("ChMeasPos")};
	int nWidth[10]={40,110,90,90, 90, 90, 90, 90, 90, 120};

	CExBaseListGrid::InitGridTitle(astrTitle, nWidth, 10);
	InitGridColAttrs(astrAttrs, 10);
}

void CSttAdjHdChDefGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (pData->GetClassID() != DTMCLASSID_CDATAGROUP)
	{
		return;
	}

	CDataGroup *pChMap = (CDataGroup*)pData;
	Show_Index(pData, nRow, 0);
	Show_StaticString(pData, nRow, 1, pData->m_strName);
	//Show_StaticString(pData, nRow, 2, pData->m_strID);

	for (long nCol=2; nCol<m_nCols; nCol++)
	{
		ShowAttrCol(pChMap, nRow, nCol);
	}

	nRow++;
}

CDataType* CSttAdjHdChDefGrid::FindDataType(const CString &strDataType)
{
	return CSttMesLocalDb::FindDataType(strDataType);
}