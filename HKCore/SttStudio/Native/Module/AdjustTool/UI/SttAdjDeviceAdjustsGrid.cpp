//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权?


#include "stdafx.h"
#include "SttAdjDeviceAdjustsGrid.h"
#include "..\SttAdjDevice.h"
#include "..\SttAdjModule.h"

#define ADJ_DV_COL_ModuleType  1
#define ADJ_DV_COL_ModulePos  2
#define ADJ_DV_COL_Temperature  3
#define ADJ_DV_COL_Channel1      4
#define ADJ_DV_COL_Channel2      5
#define ADJ_DV_COL_GearValue  6
#define ADJ_DV_COL_Coef  7
#define ADJ_DV_COL_Zero  8
#define ADJ_DV_COL_Angle  9
#define ADJ_DV_COLS  10

CSttAdjDeviceAdjustsGrid::CSttAdjDeviceAdjustsGrid()
{
	//初始化属性

	//初始化成员变量
	m_strChildDataTypeID = STT_ADJ_DATA_TYPE_GearAdjust;
}

CSttAdjDeviceAdjustsGrid::~CSttAdjDeviceAdjustsGrid()
{

}


void CSttAdjDeviceAdjustsGrid::InitGrid()
{
	//m_nAdjustBeginCol = 1;
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(ADJ_DV_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}


void CSttAdjDeviceAdjustsGrid::InitGridTitle()
{
	CString astrTitle[ADJ_DV_COLS] = {_T("编号"),_T("模块类型"),  _T("模块位置"), _T("温区"),         _T("通道"), _T(""), _T("档位值"),   _T("幅值系数"), _T("零漂"), _T("相位校准")};
	CString astrAttrs[ADJ_DV_COLS] = {_T(""),      _T("ModuleType"), _T("ModulePos"),_T("Temperature"), _T(""),       _T(""), _T("GearValue"), _T("Coef"),         _T("Zero"),   _T("Angle")};
	int nWidth[ADJ_DV_COLS]={60,120, 120, 120,120,120, 120, 200,200,200};

	CExBaseListGrid::InitGridTitle(astrTitle, nWidth, ADJ_DV_COLS);
	InitGridColAttrs(astrAttrs, ADJ_DV_COLS);
}


#include "..\SttMesLocalDb.h"
CDataType* CSttAdjDeviceAdjustsGrid::FindDataType(const CString &strDataType)
{
	return CSttMesLocalDb::FindDataType(strDataType);
}

void CSttAdjDeviceAdjustsGrid::ShowAdjDevice(CDataGroup *pAdjDevice)
{
	CSttAdjDevice oDevice;
	oDevice.AttatchAdjRef(pAdjDevice);
	CExBaseList listModule;
	oDevice.GetAllModules(&listModule);
	POS pos = listModule.GetHeadPosition();
	long nRowIndex = 1;
	CDataGroup *pModule = NULL;
	AddAdjRows(nRowIndex);

	while (pos != NULL)
	{
		pModule = (CDataGroup *)listModule.GetNext(pos);
		ShowAdjModule(pModule, nRowIndex);
	}

	SetRowCount(nRowIndex);

	listModule.RemoveAll();
	oDevice.DettachAdjRef(FALSE);
}

long CSttAdjDeviceAdjustsGrid::ShowAdjModule(CDataGroup *pAdjModule, long &nRowIndex)
{
	long nRows = 0;
	CSttAdjModule oModule;

	oModule.AttatchAdjRef(pAdjModule);

	CDataGroup *pAttrs = (CDataGroup*)oModule.GetModuleAttrs();
	ShowAttrCol(pAttrs, nRowIndex, ADJ_DV_COL_ModuleType);  //模块类型
	ShowAttrCol(pAttrs, nRowIndex, ADJ_DV_COL_ModulePos);  //模块位置

	CDataGroup *pAdjParas = oModule.GetAdjustParas();
	CExBaseList listTrange;
	pAdjParas->SelectAllGroups(listTrange, STT_ADJ_DATA_TYPE_TRange);
	POS pos = listTrange.GetHeadPosition();
	CDataGroup *pTrange = NULL;
	long nRowBegin = nRowIndex;

	while (pos != NULL)
	{
		pTrange = (CDataGroup *)listTrange.GetNext(pos);
		nRows += ShowAdjTemprature(pTrange, nRowIndex);
	}

	if (nRows > 1)
	{
		Merge(nRowBegin, ADJ_DV_COL_ModuleType, nRowIndex-1, ADJ_DV_COL_ModuleType);
		Merge(nRowBegin, ADJ_DV_COL_ModulePos, nRowIndex-1, ADJ_DV_COL_ModulePos);
	}

	listTrange.RemoveAll();
	return nRows;
}

long CSttAdjDeviceAdjustsGrid::ShowAdjTemprature(CDataGroup *pTemprature, long &nRowIndex)
{
	long nRows = 0;
	long nRowBegin = nRowIndex;

	ShowAttrCol(pTemprature, nRowIndex, ADJ_DV_COL_Temperature);  //温度

	//STT_ADJ_ID_Ch_Idc
	CDataGroup *pChDC = (CDataGroup*)pTemprature->FindByID(STT_ADJ_ID_Ch_Idc);
	nRows += ShowAdjChannel_DC(pChDC, nRowIndex);

	pChDC = (CDataGroup*)pTemprature->FindByID(STT_ADJ_ID_Ch_Udc);
	nRows += ShowAdjChannel_DC(pChDC, nRowIndex);

	CExBaseList listCh;
	pTemprature->SelectAllGroups(listCh, STT_ADJ_DATA_TYPE_ChannelAdj);
	POS pos = listCh.GetHeadPosition();
	CDataGroup *pTrange = NULL;

	while (pos != NULL)
	{
		pTrange = (CDataGroup *)listCh.GetNext(pos);
		nRows += ShowAdjChannel(pTrange, nRowIndex);
	}

	if (nRows > 1)
	{
		Merge(nRowBegin, ADJ_DV_COL_Temperature, nRowIndex-1, ADJ_DV_COL_Temperature);
	}

	listCh.RemoveAll();

	return nRows;
}

long CSttAdjDeviceAdjustsGrid::ShowAdjChannel_DC(CDataGroup *pChDC, long &nRowIndex)
{
	long nRows = 0;
	long nRowBegin = nRowIndex;

	Show_StaticString(pChDC, nRowIndex, ADJ_DV_COL_Channel1, pChDC->m_strID);
	nRows = ShowAdjChWave(pChDC, nRowIndex);

	if (nRows > 1)
	{
		Merge(nRowBegin, ADJ_DV_COL_Channel1, nRowIndex-1, ADJ_DV_COL_Channel1);
	}

	return nRows;
}

long CSttAdjDeviceAdjustsGrid::ShowAdjChannel(CDataGroup *pChannel, long &nRowIndex)
{
	long nRows = 0;
	long nRowBegin = nRowIndex;

	Show_StaticString(pChannel, nRowIndex, ADJ_DV_COL_Channel1, pChannel->m_strName);
	
	CDataGroup *pWave = NULL;
	CExBaseList listWave;
	pChannel->SelectAllGroups(listWave, STT_ADJ_DATA_TYPE_ChWaveAdj);
	POS pos = listWave.GetHeadPosition();

	while (pos != NULL)
	{
		pWave = (CDataGroup *)listWave.GetNext(pos);
		nRows += ShowAdjChWave(pWave, nRowIndex);
	}
	
	if (nRows > 1)
	{
		Merge(nRowBegin, ADJ_DV_COL_Channel1, nRowIndex-1, ADJ_DV_COL_Channel1);
	}

	listWave.RemoveAll();
	return nRows;
}

long CSttAdjDeviceAdjustsGrid::ShowAdjChWave(CDataGroup *pChWave, long &nRowIndex)
{
	long nRows = 0;
	long nRowBegin = nRowIndex;

	Show_StaticString(pChWave, nRowIndex, ADJ_DV_COL_Channel2, pChWave->m_strName);

	CExBaseList listGear;
	pChWave->SelectAllGroups(listGear, STT_ADJ_HD_GEAR_DATA_TYPE);
	POS pos = listGear.GetHeadPosition();
	CDataGroup *pGear = NULL;

	while (pos  != NULL)
	{
		pGear = (CDataGroup *)listGear.GetNext(pos);
		nRows += ShowAdjChWaveGear(pGear, nRowIndex);
	}

	if (nRows > 1)
	{
		Merge(nRowBegin, ADJ_DV_COL_Channel2, nRowIndex-1, ADJ_DV_COL_Channel2);
	}

	listGear.RemoveAll();
	return nRows;
}

long CSttAdjDeviceAdjustsGrid::ShowAdjChWaveGear(CDataGroup *pChWaveGear, long &nRowIndex)
{
	AddAdjRows(nRowIndex);
	long nRows = 1;

	Show_Index(pChWaveGear, nRowIndex, 0);
	ShowAttrCol(pChWaveGear, nRowIndex, ADJ_DV_COL_GearValue);

	CDataGroup *AdjustItem = (CDataGroup*)pChWaveGear->FindByDataType(STT_ADJ_DATA_TYPE_AdjustItem);

	ShowAttrCol(AdjustItem, nRowIndex, ADJ_DV_COL_Coef);
	ShowAttrCol(AdjustItem, nRowIndex, ADJ_DV_COL_Zero);
	ShowAttrCol(AdjustItem, nRowIndex, ADJ_DV_COL_Angle);

	nRowIndex++;

	return nRows;
}

void CSttAdjDeviceAdjustsGrid::AddAdjRows(long nRowIndex)
{
	if (m_nRows <= nRowIndex+1)
	{
		SetRowCount(m_nRows + 100);
	}
}

