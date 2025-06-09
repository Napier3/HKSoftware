#include "SttIecSmvGrid_HarmAnalyze.h"
#include "../../../../Module/SmartCap/XSmartCapMngr.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../SttTestSysGlobalPara.h"
#include "../../../../Module/API/MathApi.h"

#define SmvGrid_HarmAnalyze_MAX_ROW_NUM      29


CSttIecSmvGrid_HarmAnalyze::CSttIecSmvGrid_HarmAnalyze(QWidget* pparent):CSttIecChsGridBase(pparent)
{
	m_pIecRcdFuncWidget = this;
}

CSttIecSmvGrid_HarmAnalyze::~CSttIecSmvGrid_HarmAnalyze()
{

}

void CSttIecSmvGrid_HarmAnalyze::IecRcdFunc(CCapDeviceBase *pCapDevice)
{
	m_pCapDevice = pCapDevice;
	if (pCapDevice == NULL)
	{
		return;
	}
	CDvmDataset *pDvmDataset = pCapDevice->GetDvmDataset();
	ShowDatas(pDvmDataset);
}

void CSttIecSmvGrid_HarmAnalyze::Release()
{
	delete this;
}


void CSttIecSmvGrid_HarmAnalyze::InitGridTitle()
{
	CString astrGridTitle[SmvGrid_HarmAnalyze_MAX_ROW_NUM];
	astrGridTitle[0] = _T("通道描述");
	astrGridTitle[1] = _T("基波输出值(V/A)");
	astrGridTitle[2] = _T("基波实测值(V/A)");
	astrGridTitle[3] = _T("基波误差限值(%)");
	astrGridTitle[4] = _T("基波误差(%)");

	CString strTemp;
	xlang_GetLangStrByFile(strTemp,_T("Harm_Times"));
	CString strNum[24] = {"2","3", "4", "5", "6", "7"
		,"8", "9", "10", "11", "12", "13", "14", "15"
		,"16", "17", "18", "19", "20", "21", "22", "23"
		,"24", "25"};
	for (int i=5; i<SmvGrid_HarmAnalyze_MAX_ROW_NUM;i++)
	{
		astrGridTitle[i]=strNum[i-5] + strTemp;
	}

#ifndef  _PSX_QT_LINUX_

	HDC hd = GetDC(NULL);
	double dDotPix1 = GetDeviceCaps(hd, LOGPIXELSX);
	double dUIShowCoef = dDotPix1 / 96;

	int iGridWidth[SmvGrid_HarmAnalyze_MAX_ROW_NUM]={100, 110*dUIShowCoef, 110*dUIShowCoef, 110*dUIShowCoef, 110, 100, 100, 100, 100, 100
		                                           , 100, 100, 100, 100, 100, 100, 100, 100, 100, 100
		                                           , 100, 100, 100, 100, 100, 100, 100, 100, 100 };
#else

	int iGridWidth[SmvGrid_HarmAnalyze_MAX_ROW_NUM]={100, 110, 110, 110, 110, 100, 100, 100, 100, 100
		, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100
		, 100, 100, 100, 100, 100, 100, 100, 100, 100 };
#endif
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, SmvGrid_HarmAnalyze_MAX_ROW_NUM);
}

void CSttIecSmvGrid_HarmAnalyze::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CDvmData *pChData = (CDvmData*)pData;

	if (bInsertRow)
	{
		insertRow(NULL);
	}
	if (pChData->m_nChange == 0)
	{
		return;
	}

	Show_StaticString(pData, nRow, 0, &pChData->m_strName);
	float fValue = 0;
	if (((pChData->m_strDataType == _T("Curr")) || (pChData->m_strDataType == _T("电流"))) && (pChData->m_strID.Find(_T("Ia2"))) == -1)
	{
		fValue = 1;
	}
	else if (((pChData->m_strDataType == _T("Curr")) || (pChData->m_strDataType == _T("电流"))) && (pChData->m_strID.Find(_T("Ia2"))) != -1)
	{
		fValue = 2;
	}
	else if (((pChData->m_strDataType == _T("Vol")) || (pChData->m_strDataType == _T("电压")))&& (pChData->m_strID.Find(_T("Ua2"))) == -1)
	{
		fValue = 1;
	}
	else if (((pChData->m_strDataType == _T("Vol")) || (pChData->m_strDataType == _T("电压")))&& (pChData->m_strID.Find(_T("Ua2"))) != -1)
	{
		fValue = 2;
	}
	Show_Float(pChData, nRow, 3, 2, &fValue, TRUE, EndEditCell_BaseLimitValue);
	ShowDataEx(pChData, nRow);

	nRow++;
}


void CSttIecSmvGrid_HarmAnalyze::IecRcdFuncUpdate(CCapDeviceBase *pCapDevice)
{
	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
	CXCapPkgBufferMngrInterface *pXCapPkgBufferMngr = pXSttCap_61850->GetSttXCapBufferMngr();
	pXSttCap_61850->UpdateDvmDeviceDatas();

	UpdateDatas();
}

void CSttIecSmvGrid_HarmAnalyze::UpdateData(CExBaseObject *pData, int nRow)
{
	CDvmData *pChData = (CDvmData*)pData;
	ShowDataEx(pChData, nRow);
}

void CSttIecSmvGrid_HarmAnalyze::ShowDataEx(CDvmData *pChData, int nRow)
{
	if (pChData->m_nChange == 0)
	{
		return;
	}
	ShowBaseActualValue(pChData,nRow);
 	ShowAttrValue(pChData, nRow, 2, _T("$Base")); 

	long nHarm = 2;
 	CString strID;
	for (nHarm=2; nHarm <= 25; nHarm++)
	{
		strID.Format(_T("$h%d"), nHarm);
		ShowAttrValue(pChData, nRow, nHarm + 3, strID, 3);
	}
}

void CSttIecSmvGrid_HarmAnalyze::ShowBaseActualValue( CDvmData *pChData, int nRow )
{
	float fValue,fBaseValue,fOutputValue;

	if (((pChData->m_strDataType == _T("Curr")) || (pChData->m_strDataType == _T("电流"))) && (pChData->m_strID.Find(_T("Ia2"))) == -1)
	{
		fOutputValue = g_oSystemParas.m_fINom;
	}
	else if (((pChData->m_strDataType == _T("Curr")) || (pChData->m_strDataType == _T("电流"))) && (pChData->m_strID.Find(_T("Ia2"))) != -1)
	{
		fOutputValue = g_oSystemParas.m_fI0_Std;
	}
	else if (((pChData->m_strDataType == _T("Vol")) || (pChData->m_strDataType == _T("电压")))&& (pChData->m_strID.Find(_T("Ua2"))) == -1)
	{
		fOutputValue = g_oSystemParas.m_fVNom ;
	}
	else if (((pChData->m_strDataType == _T("Vol")) || (pChData->m_strDataType == _T("电压")))&& (pChData->m_strID.Find(_T("Ua2"))) != -1)
	{
		fOutputValue = g_oSystemParas.m_fU0_Std;
	}
	CString strValue,strOutputValue;
	strOutputValue.Format(_T("%.3f"), fOutputValue);
	Show_StaticString(pChData, nRow, 1, strOutputValue);

	//1-实测值/输出值
	CString strBaseID = pChData->m_strID + _T("$Base");
	CDvmValue *pBaseValue = (CDvmValue*)pChData->FindByID(strBaseID);
	if (pBaseValue != NULL)
	{
		fBaseValue = pBaseValue->m_strValue.toFloat();
		fValue = fabs(1 - fBaseValue/fOutputValue) * 100; 
		strValue.Format(_T("%.3f"), fValue);
		Show_StaticString(pChData, nRow, 4, strValue);
	}

// 	CDvmValue *pFind = (CDvmValue*)pChData->FindByID(strBaseID);
// 	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
// 
// 	if (pFind == NULL)
// 	{
// 		Update_StaticString(pChData, nRow, 4, &g_strEmptyString);
// 	}
// 	else
// 	{
// 		strBaseID = pFind->m_strID + _T("$ErrorValue");
// 		CDvmValue *pFindChild = (CDvmValue*)pFind->FindByID(strBaseID);
// 		if (pFindChild == NULL)
// 		{
// 			Update_StaticString(pChData, nRow, 4, &g_strEmptyString);
// 		} 
// 		else
// 		{
// 			double dValue = CString_To_double(pFind->m_strValue);
// 			CString strValue;
// 			strValue.Format(_T("%.3f"), dValue * 100);
// 			Update_StaticString(pChData, nRow, 4, &strValue);
// 		}
// 	}
}

void CSttIecSmvGrid_HarmAnalyze::EndEditCell_BaseLimitValue( int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid )
{
	PEXBASECELLDATA pVCellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVCellData != NULL);
	ASSERT (pVCellData->pString != NULL);

	float fValue =  math_GetValueFromString(pCell->text());

	if (fValue > 0 && fValue<= 999999)
	{
		*(pVCellData->pfValue) = fValue;
	}

	CString strTmp;
	strTmp.Format(_T("%.2f"), *(pVCellData->pfValue));								
	pCell->setText(strTmp);

	CDvmData *pData = (CDvmData*)pVCellData->pObj;
	((CSttIecSmvGrid_HarmAnalyze*)pGrid)->UpdateDataset_MUTestCB(pData->m_strID,strTmp);

	((QExBaseListGridBase*)pGrid)->SetModifiedFlag(pVCellData->pObj);
}


void CSttIecSmvGrid_HarmAnalyze::UpdateDatas()
{
	if (m_pDatas == NULL)
	{
		return;
	}
	CDvmData *pChData = NULL;
	POS pos = m_pDatas->GetHeadPosition();
	int nRowIndex = 0;

	while (pos != NULL)
	{
		pChData = (CDvmData*)m_pDatas->GetNext(pos);

		if (pChData->m_nChange == 0)
		{
			continue;
		}

		UpdateData(pChData, nRowIndex);
		nRowIndex++;
	}
}

void CSttIecSmvGrid_HarmAnalyze::UpdateDataset_MUTestCB(CString strChannelID,CString strValue)
{
	CDvmDataset *m_pDataset = g_theXSmartCapMngr->m_pX61850Cap->m_pDataset_MUTestCB;
	POS pos = m_pDataset->GetHeadPosition();
	CDvmData *pDvmData = NULL;
	CDvmValue *pCurrValue = NULL,*pChildValue = NULL;
	while (pos != NULL)
	{
		pDvmData = (CDvmData *)m_pDataset->GetNext(pos);
		if (pDvmData->m_strID == strChannelID)
		{
			POS pos_value = pDvmData->GetHeadPosition();
			while(pos_value)
			{
				pCurrValue = (CDvmValue *)pDvmData->GetNext(pos_value);
				if (pCurrValue->m_strID.Find(_T("$Base")) >0)
				{
					POS pos_child_value = pCurrValue->GetHeadPosition();
					while(pos_child_value)
					{
						pChildValue = (CDvmValue *)pCurrValue->GetNext(pos_child_value);
						if (pChildValue->m_strID.Find(_T("$ErrorLimit"))>0)
						{
							pChildValue->m_strValue = strValue;
							g_theXSmartCapMngr->m_pX61850Cap->m_pHarmBaseLimitVlaueData[pChildValue->m_strID] = strValue.toFloat();
							return;
						}
					}
				}
			}
		}
	}	
}