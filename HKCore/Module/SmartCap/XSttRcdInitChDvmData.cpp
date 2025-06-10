#include "stdafx.h"
#include "XSttRcdInitChDvmData.h"
#include "../API/GlobalConfigApi.h"

long g_nXSttRcdInitChDvmData_Harm = 31;

void XSttRcdInitChDvmData_Base(CDvmValue *pDvmValue)
{
 	CDvmValue *pChildValue = new CDvmValue;
	pChildValue->m_strName = _T("输出值");
	pChildValue->m_strID = pDvmValue->m_strID + _T("$OutPutValue");
	pChildValue->m_strDataType = _T("FLOAT");
	pChildValue->m_strValue = _T("");
	pDvmValue->AddNewChild(pChildValue);
	
	pChildValue = new CDvmValue;
	pChildValue->m_strName = _T("基波实测值");
	pChildValue->m_strID = pDvmValue->m_strID + _T("$ActualValue");
	pChildValue->m_strDataType = _T("FLOAT");
	pChildValue->m_strValue = _T("");
	pDvmValue->AddNewChild(pChildValue);

	pChildValue = new CDvmValue;
	pChildValue->m_strName = _T("测试次数");
	pChildValue->m_strID = pDvmValue->m_strID + _T("$TestCount");
	pChildValue->m_strDataType = _T("long");
	pChildValue->m_strValue = _T("0");
	pDvmValue->AddNewChild(pChildValue);

	pChildValue = new CDvmValue;
	pChildValue->m_strName = _T("误差限值");
	pChildValue->m_strID = pDvmValue->m_strID + _T("$ErrorLimit");
	pChildValue->m_strDataType = _T("FLOAT");
	pChildValue->m_strValue = _T("0.05");
	pDvmValue->AddNewChild(pChildValue);

	pChildValue = new CDvmValue;
	pChildValue->m_strName = _T("基波误差");
	pChildValue->m_strID = pDvmValue->m_strID + _T("$ErrorValue");
	pChildValue->m_strDataType = _T("FLOAT");
	pChildValue->m_strValue = _T("");
	pDvmValue->AddNewChild(pChildValue);

	pChildValue = new CDvmValue;
	pChildValue->m_strName = _T("测试结果描述");
	pChildValue->m_strID = pDvmValue->m_strID + _T("$RltDesc");
	pChildValue->m_strDataType = _T("string");
	pChildValue->m_strValue = _T("合格");
	pDvmValue->AddNewChild(pChildValue);
}

void XSttRcdInitChDvmData_MaxMinValuesMU(CDvmValue *pDvmValue)
{
	CDvmValue *pChildValue = new CDvmValue;
	pChildValue->m_strName = _T("最大值");
	pChildValue->m_strID = pDvmValue->m_strID + STT_RcdInit_DL_MaxValue/* _T("$MaxValue")*/;
	pChildValue->m_strDataType = _T("FLOAT");
	pChildValue->m_strValue = _T("");
	pDvmValue->AddNewChild(pChildValue);

	//chenling 2024.5.13 
	pChildValue = new CDvmValue;
	if(pDvmValue->m_strID.Find(STT_RcdInit_DL_RatError) >= 0)
	{	
		pChildValue->m_strName = _T("最大幅值");
		pChildValue->m_strID = pDvmValue->m_strID + STT_RcdInit_DL_MaxMagValue;//最大幅值
	}
	else if (pDvmValue->m_strID.Find(STT_RcdInit_DL_AngError) >= 0)
	{
		pChildValue->m_strName = _T("最大相位");
		pChildValue->m_strID = pDvmValue->m_strID + STT_RcdInit_DL_MaxAngValue;//最大相位
	}
	else if (pDvmValue->m_strID.Find(STT_RcdInit_DL_CompError) >= 0)
	{
		pChildValue->m_strName = _T("最大幅值");
		pChildValue->m_strID = pDvmValue->m_strID + STT_RcdInit_DL_MaxMagValue;
		pChildValue->m_strDataType = _T("FLOAT");
		pChildValue->m_strValue = _T("");
		pDvmValue->AddNewChild(pChildValue);
		
		pChildValue = new CDvmValue;
		pChildValue->m_strName = _T("最大相位");
		pChildValue->m_strID = pDvmValue->m_strID + STT_RcdInit_DL_MaxAngValue;
	}
	pChildValue->m_strDataType = _T("FLOAT");
	pChildValue->m_strValue = _T("");
	pDvmValue->AddNewChild(pChildValue);

	//误差极限
	pChildValue = new CDvmValue;
	pChildValue->m_strName = _T("误差限值");
	pChildValue->m_strID = pDvmValue->m_strID + STT_RcdInit_DL_ErrorLimit;
	pChildValue->m_strDataType = _T("FLOAT");
	pChildValue->m_strValue = _T("");
	pDvmValue->AddNewChild(pChildValue);


	pChildValue = new CDvmValue;
	pChildValue->m_strName = _T("最小值");
	pChildValue->m_strID = pDvmValue->m_strID + STT_RcdInit_DL_MinValue/*_T("$MinValue")*/;
	pChildValue->m_strDataType = _T("FLOAT");
	pChildValue->m_strValue = _T("");
	pDvmValue->AddNewChild(pChildValue);

	pChildValue = new CDvmValue;
	pChildValue->m_strName = _T("平均值");
	pChildValue->m_strID = pDvmValue->m_strID + STT_RcdInit_DL_AverageValue/*_T("$AverageValue")*/;
	pChildValue->m_strDataType = _T("FLOAT");
	pChildValue->m_strValue = _T("");
	pDvmValue->AddNewChild(pChildValue);

	pChildValue = new CDvmValue;
	pChildValue->m_strName = _T("测试次数");
	pChildValue->m_strID = pDvmValue->m_strID + STT_RcdInit_DL_TestCount/*_T("$TestCount")*/;
	pChildValue->m_strDataType = _T("long");
	pChildValue->m_strValue = _T("0");
	pDvmValue->AddNewChild(pChildValue);

	pChildValue = new CDvmValue;
	pChildValue->m_strName = _T("测试结果");
	pChildValue->m_strID = pDvmValue->m_strID + STT_RcdInit_DL_Result/*_T("$Result")*/;
	pChildValue->m_strDataType = _T("long");
	pChildValue->m_strValue = _T("0");
	pDvmValue->AddNewChild(pChildValue);

	pChildValue = new CDvmValue;
	pChildValue->m_strName = _T("误差范围");
	pChildValue->m_strID = pDvmValue->m_strID + STT_RcdInit_DL_StdErrorValue;
	pChildValue->m_strDataType = _T("FLOAT");
	pChildValue->m_strValue = _T("100");
	pDvmValue->AddNewChild(pChildValue);

	pChildValue = new CDvmValue;
	pChildValue->m_strName = _T("测试结果描述");
	pChildValue->m_strID = pDvmValue->m_strID + STT_RcdInit_DL_RltDesc;
	pChildValue->m_strDataType = _T("string");
	pChildValue->m_strValue = _T("合格");
	pDvmValue->AddNewChild(pChildValue);
}

void XSttRcdInitChDvmData(CDvmData *pChDvmData, long nHarm, BOOL bIecTest)
{
	CDvmValue *pDvmValue = NULL;
	CString strID = pChDvmData->m_strID + _T("$");

	pDvmValue = new CDvmValue;
	pDvmValue->m_strName = _T("幅值");
	pDvmValue->m_strID = strID + _T("mag");
	pDvmValue->m_strDataType = _T("FLOAT");
	pDvmValue->m_strValue = _T("0.00");
	pChDvmData->AddNewChild(pDvmValue);

	if (pChDvmData->m_strDataType == _T("时间") || pChDvmData->m_strDataType == _T("UTCTime"))
	{
		return;
	}

	pDvmValue = new CDvmValue;
	pDvmValue->m_strName = _T("相位");
	pDvmValue->m_strID = strID + _T("ang");
	pDvmValue->m_strDataType = _T("FLOAT");
	pDvmValue->m_strValue = _T("0.00");
	pChDvmData->AddNewChild(pDvmValue);
	pDvmValue = new CDvmValue;
	pDvmValue->m_strName = _T("频率");
	pDvmValue->m_strID = strID + _T("freq");
	pDvmValue->m_strDataType = _T("FLOAT");
	pDvmValue->m_strValue = _T("50.00");
	pChDvmData->AddNewChild(pDvmValue);

	//2022-5-16  lijunqing
	pDvmValue = new CDvmValue;
	pDvmValue->m_strName = _T("平均值");
	pDvmValue->m_strID = strID + _T("avg");
	pDvmValue->m_strDataType = _T("FLOAT");
	pDvmValue->m_strValue = _T("0.00");
	pChDvmData->AddNewChild(pDvmValue);

	if (nHarm > 0)
	{
		pDvmValue = new CDvmValue;
		pDvmValue->m_strName = _T("直流分量");
		pDvmValue->m_strID = strID + _T("DC");
		pDvmValue->m_strDataType = _T("FLOAT");
		pDvmValue->m_strValue = _T("0.00");
		pChDvmData->AddNewChild(pDvmValue);

		pDvmValue = new CDvmValue;
		pDvmValue->m_strName = _T("基波");
		pDvmValue->m_strID = _T("Base");
		pDvmValue->m_strID = strID + pDvmValue->m_strID;
		pDvmValue->m_strDataType = _T("FLOAT");
		pDvmValue->m_strValue = _T("0.00");
		pChDvmData->AddNewChild(pDvmValue);
		XSttRcdInitChDvmData_Base(pDvmValue);


		for (int nHarmIndex = 2;nHarmIndex<=nHarm; nHarmIndex++)
		{
			pDvmValue = new CDvmValue;
			pDvmValue->m_strName.Format(_T("%d次谐波"),nHarmIndex);
			pDvmValue->m_strID.Format(_T("h%d"), nHarmIndex);
			pDvmValue->m_strID = strID + pDvmValue->m_strID;
			pDvmValue->m_strDataType = _T("FLOAT");
			pDvmValue->m_strValue = _T("0.00");
			pChDvmData->AddNewChild(pDvmValue);
		}
	}

	if (!bIecTest)
	{
		return;
	}

	pDvmValue = new CDvmValue;
	pDvmValue->m_strName = _T("比差");
	pDvmValue->m_strID = strID + _T("RatError");
	pDvmValue->m_strDataType = _T("FLOAT");
	pDvmValue->m_strValue = _T("0.00");
	pChDvmData->AddNewChild(pDvmValue);
	XSttRcdInitChDvmData_MaxMinValuesMU(pDvmValue);

	pDvmValue = new CDvmValue;
	pDvmValue->m_strName = _T("角差");
	pDvmValue->m_strID = strID + _T("AngError");
	pDvmValue->m_strDataType = _T("FLOAT");
	pDvmValue->m_strValue = _T("0.00");
	pChDvmData->AddNewChild(pDvmValue);
	XSttRcdInitChDvmData_MaxMinValuesMU(pDvmValue);

	pDvmValue = new CDvmValue;
	pDvmValue->m_strName = _T("频差");
	pDvmValue->m_strID = strID + _T("FreqError");
	pDvmValue->m_strDataType = _T("FLOAT");
	pDvmValue->m_strValue = _T("0.00");
	pChDvmData->AddNewChild(pDvmValue);

	pDvmValue = new CDvmValue;
	pDvmValue->m_strName = _T("检修状态值");
	pDvmValue->m_strID = strID + _T("TestValue");//QualityValue
	pDvmValue->m_strDataType = _T("LONG");
	pDvmValue->m_strValue = _T("0");
	pChDvmData->AddNewChild(pDvmValue);

	pDvmValue = new CDvmValue;
	pDvmValue->m_strName = _T("复合误差");
	pDvmValue->m_strID = strID + _T("CompError");
	pDvmValue->m_strDataType = _T("FLOAT");
	pDvmValue->m_strValue = _T("0.00");
	pChDvmData->AddNewChild(pDvmValue);
	XSttRcdInitChDvmData_MaxMinValuesMU(pDvmValue);
}

//////////////////////////////////////////////////////////////////////////
//报文一致性测试
void XSttRcdInit_ValuesID(CExBaseList *pList, const CString &strID)
{
	CExBaseList *p = NULL;
	POS pos = pList->GetHeadPosition();

	while (pos != NULL)
	{
		p = (CExBaseList*)pList->GetNext(pos);
		p->m_strID = strID + p->m_strID;

		if (p->GetCount() > 0)
		{
			XSttRcdInit_ValuesID(p, strID);
		}
	}
}



void XSttRcdInitSv_FromCfgFile(CDvmData *pSV, const CString &strID, const CString &strCfgFile)
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += strCfgFile;
	pSV->DeleteAll();
	pSV->OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);

	pSV->m_strID = strID;
	pSV->m_strName = strID;
	XSttRcdInit_ValuesID(pSV, strID + _T("$"));
}


//SV报文一致性分析
void XSttRcdInitSv_PkgAnalyze(CDvmData *pSV, const CString &strID)
{
	XSttRcdInitSv_FromCfgFile(pSV, strID, _T("SttRcdSv_PkgAnalyze.xml"));
}

//SV报文异常分析
void XSttRcdInitSv_PkgError(CDvmData *pSV, const CString &strID)
{
	XSttRcdInitSv_FromCfgFile(pSV, strID, _T("SttRcdSv_SVPkgError.xml"));
}

BOOL XSttRcdInitDouble_FromDataset(CDvmDataset *pDataset,const CString &strDataID,double &dValue)
{
	if (pDataset == NULL)
	{
		return FALSE;
	}

	CDvmData *pCurrData = (CDvmData*)pDataset->FindByID(strDataID);

	if (pCurrData == NULL)
	{
		return FALSE;
	}

	dValue = CString_To_double(pCurrData->m_strValue);
	return TRUE;
}

BOOL XSttRcdInitDouble_FromValue(CDvmValue *pValue,const CString &strValueID,double &dValue)
{
	if (pValue == NULL)
	{
		return FALSE;
	}

	CDvmValue *pChildValue = (CDvmValue*)pValue->FindByID(strValueID);

	if (pChildValue == NULL)
	{
		return FALSE;
	}

	dValue = CString_To_double(pChildValue->m_strValue);
	return TRUE;
}
