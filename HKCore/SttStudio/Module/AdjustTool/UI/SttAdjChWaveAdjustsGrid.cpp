//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权?


#include "stdafx.h"
#include "SttAdjChWaveAdjustsGrid.h"
#include "..\SttAdjBase.h"
#ifndef NOT_USE_XLANGUAGE
#include "..\..\..\Local\SttAdjMain\XLanguageResource_SttAdjMain.h"
#endif

CSttAdjChWaveAdjustsGrid::CSttAdjChWaveAdjustsGrid()
{
	//初始化属性

	//初始化成员变量
	m_strChildDataTypeID = STT_ADJ_DATA_TYPE_GearAdjust;
}

CSttAdjChWaveAdjustsGrid::~CSttAdjChWaveAdjustsGrid()
{

}


void CSttAdjChWaveAdjustsGrid::InitGrid()
{
	//m_nAdjustBeginCol = 1;
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(6);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}


void CSttAdjChWaveAdjustsGrid::InitGridTitle()
{
#ifndef NOT_USE_XLANGUAGE
	CString astrTitle[6] = {/*_T("编号")*/g_sLangTxt_Index,/*_T("档位")*/g_sLangTxt_SttAdjMain_Gear, 
		/*_T("档位值")*/g_sLangTxt_SttAdjMain_GearVal,/* _T("幅值系数")*/g_sLangTxt_SttAdjMain_AmpFactor,
		/*_T("零漂")*/g_sLangTxt_SttAdjMain_ZeroDrift,/*_T("相位校准")*/g_sLangTxt_SttAdjMain_AngCalib};
#else
	CString astrTitle[6] = {_T("编号"),_T("档位"), _T("档位值"), _T("幅值系数"),_T("零漂"),_T("相位校准")};
#endif
	CString astrAttrs[6] = {_T(""),_T("GearValue"),  _T("GearValue"), _T("Coef"),_T("Zero"), _T("Angle")};
	int nWidth[6]={40,120, 120, 120,120,120};

	CExBaseListGrid::InitGridTitle(astrTitle, nWidth, 6);
	InitGridColAttrs(astrAttrs, 6);
}

void CSttAdjChWaveAdjustsGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (pData->GetClassID() != DTMCLASSID_CDATAGROUP)
	{
		return;
	}

	CDataGroup *pGear = (CDataGroup*)pData;
	CDvmData *pDvmData = (CDvmData *)pGear->FindByID(_T("GearValue"));
	Show_Index(pData, nRow, 0);
	Show_StaticString(pData, nRow, 1, pGear->m_strName);
	Show_String(pData, nRow, 2,  &pDvmData->m_strValue);

	CDataGroup *AdjustItem = (CDataGroup*)pGear->FindByDataType(STT_ADJ_DATA_TYPE_AdjustItem);

	if (AdjustItem != NULL)
	{
		CDvmData *pCoefData = (CDvmData *)AdjustItem->FindByID(_T("Coef"));
		CDvmData *pZeroData = (CDvmData *)AdjustItem->FindByID(_T("Zero"));
		CDvmData *pAngleData = (CDvmData *)AdjustItem->FindByID(_T("Angle"));
		if (pCoefData != NULL && pZeroData != NULL && pAngleData != NULL)
		{
			double dCoefData = CString_To_double(pCoefData->m_strValue);
			pCoefData->m_strValue.Format(_T("%.6f"), dCoefData);
			double dZeroData = CString_To_double(pZeroData->m_strValue);
			pZeroData->m_strValue.Format(_T("%.8f"), dZeroData);
			double dAngleData = CString_To_double(pAngleData->m_strValue);
			pAngleData->m_strValue.Format(_T("%.8f"), dAngleData);

			Show_String(AdjustItem, nRow, 3, &pCoefData->m_strValue);
			Show_String(AdjustItem, nRow, 4, &pZeroData->m_strValue);
			Show_String(AdjustItem, nRow, 5, &pZeroData->m_strValue);
		}
	}

	nRow++;
}

CSttAdjChWaveAdjustsGrid2::CSttAdjChWaveAdjustsGrid2()
{
	//初始化属性

	//初始化成员变量
	m_strChildDataTypeID = STT_ADJ_DATA_TYPE_GearAdjust;
}

CSttAdjChWaveAdjustsGrid2::~CSttAdjChWaveAdjustsGrid2()
{

}


void CSttAdjChWaveAdjustsGrid2::InitGrid()
{
	//m_nAdjustBeginCol = 1;
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(5);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}


void CSttAdjChWaveAdjustsGrid2::InitGridTitle()
{
#ifndef NOT_USE_XLANGUAGE
	CString astrTitle[5] = {/*_T("编号")*/g_sLangTxt_Index,/*_T("档位")*/g_sLangTxt_SttAdjMain_Gear,
		/* _T("档位值")*/g_sLangTxt_SttAdjMain_GearVal, /*_T("幅值系数")*/g_sLangTxt_SttAdjMain_AmpFactor,/*_T("零漂")*/g_sLangTxt_SttAdjMain_ZeroDrift};
#else
	CString astrTitle[5] = {_T("编号"),_T("档位"), _T("档位值"), _T("幅值系数"),_T("零漂")};
#endif
	CString astrAttrs[5] = {_T(""),_T("GearValue"),  _T("GearValue"), _T("Coef"),_T("Zero")};
	int nWidth[5]={40,120, 120, 120,120};

	CExBaseListGrid::InitGridTitle(astrTitle, nWidth, 5);
	InitGridColAttrs(astrAttrs, 5);
}

void CSttAdjChWaveAdjustsGrid2::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (pData->GetClassID() != DTMCLASSID_CDATAGROUP)
	{
		return;
	}

	CDataGroup *pGear = (CDataGroup*)pData;
	CDvmData *pDvmData = (CDvmData *)pGear->FindByID(_T("GearValue"));
	Show_Index(pData, nRow, 0);
	Show_StaticString(pData, nRow, 1, pGear->m_strName);
	Show_String(pData, nRow, 2, &pDvmData->m_strValue);

	CDataGroup *AdjustItem = (CDataGroup*)pGear->FindByDataType(STT_ADJ_DATA_TYPE_AdjustItem);

	if (AdjustItem != NULL)
	{
		CDvmData *pCoefData = (CDvmData *)AdjustItem->FindByID(_T("Coef"));
		CDvmData *pZeroData = (CDvmData *)AdjustItem->FindByID(_T("Zero"));
		if (pCoefData != NULL && pZeroData != NULL)
		{
			double dCoefData = CString_To_double(pCoefData->m_strValue);
			pCoefData->m_strValue.Format(_T("%.6f"), dCoefData);
			double dZeroData = CString_To_double(pZeroData->m_strValue);
			pZeroData->m_strValue.Format(_T("%.8f"), dZeroData);

			Show_String(AdjustItem, nRow, 3, &pCoefData->m_strValue);
			Show_String(AdjustItem, nRow, 4, &pZeroData->m_strValue);
		}
	}
	nRow++;
}


CSttAdjChWaveAdjustsGrid3::CSttAdjChWaveAdjustsGrid3()
{
	//初始化属性

	//初始化成员变量
	m_strChildDataTypeID = STT_ADJ_DATA_TYPE_GearAdjust;
}

CSttAdjChWaveAdjustsGrid3::~CSttAdjChWaveAdjustsGrid3()
{

}


void CSttAdjChWaveAdjustsGrid3::InitGrid()
{
	//m_nAdjustBeginCol = 1;
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(6);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}


void CSttAdjChWaveAdjustsGrid3::InitGridTitle()
{
#ifndef NOT_USE_XLANGUAGE 
	CString astrTitle[6] = {/*_T("编号")*/g_sLangTxt_Index,/*_T("档位")*/g_sLangTxt_SttAdjMain_Gear, /*_T("档位值")*/g_sLangTxt_SttAdjMain_GearVal, /*_T("幅值系数")*/g_sLangTxt_SttAdjMain_AmpFactor,/*_T("零漂")*/g_sLangTxt_SttAdjMain_ZeroDrift,/*_T("硬件零漂")*/g_sLangTxt_SttAdjMain_HardWareZeroDrift};
#else
	CString astrTitle[6] = {_T("编号"),_T("档位"), _T("档位值"), _T("幅值系数"),_T("零漂"),_T("硬件零漂")};
#endif
	CString astrAttrs[6] = {_T(""),_T("GearValue"),  _T("GearValue"), _T("Coef"),_T("Zero"),_T("Angle")};
	int nWidth[6]={40,120, 80, 120,120,120};

	CExBaseListGrid::InitGridTitle(astrTitle, nWidth, 6);
	InitGridColAttrs(astrAttrs, 6);
}

void CSttAdjChWaveAdjustsGrid3::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (pData->GetClassID() != DTMCLASSID_CDATAGROUP)
	{
		return;
	}

	CDataGroup *pGear = (CDataGroup*)pData;
	CDvmData *pDvmData = (CDvmData *)pGear->FindByID(_T("GearValue"));
	Show_Index(pData, nRow, 0);
	Show_StaticString(pData, nRow, 1, pGear->m_strName);
	Show_String(pData, nRow, 2, &pDvmData->m_strValue);

	CDataGroup *AdjustItem = (CDataGroup*)pGear->FindByDataType(STT_ADJ_DATA_TYPE_AdjustItem);

	if (AdjustItem != NULL)
	{
		CDvmData *pCoefData = (CDvmData *)AdjustItem->FindByID(_T("Coef"));
		if (pCoefData != NULL)
		{
			double dCoefData = CString_To_double(pCoefData->m_strValue);
			pCoefData->m_strValue.Format(_T("%.6f"), dCoefData);
			Show_String(AdjustItem, nRow, 3, &pCoefData->m_strValue);
		}
		CDvmData *pZeroData = (CDvmData *)AdjustItem->FindByID(_T("Zero"));
		if (pZeroData != NULL)
		{
			double dZeroData = CString_To_double(pZeroData->m_strValue);
			pZeroData->m_strValue.Format(_T("%.8f"), dZeroData);
			Show_String(AdjustItem, nRow, 4, &pZeroData->m_strValue);
		}
		CDvmData *pAngleData = (CDvmData *)AdjustItem->FindByID(_T("Angle"));
		if (pZeroData != NULL)
		{
			double dAngleData = CString_To_double(pAngleData->m_strValue);
			pAngleData->m_strValue.Format(_T("%.6f"), dAngleData);
			CDvmData *pHarmData = (CDvmData *)(pGear->GetParent());
			if(pHarmData->m_strID == _T("Harm0"))//直流显示该列
			{
				Show_String(AdjustItem, nRow, 5, &pAngleData->m_strValue);
			}
			else
			{
				Show_StaticString(AdjustItem, nRow, 5, _T("-"));
			}
		}
	}
	nRow++;
}
