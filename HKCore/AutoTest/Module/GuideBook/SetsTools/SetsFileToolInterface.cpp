#include "StdAfx.h"
#include "SetsFileToolInterface.h"

CSetsFileToolInterface::CSetsFileToolInterface()
{
#ifndef _SETS_FILE_TOOL_NOT_USE_GB_
	m_pDestCpus = NULL;
	m_pSysParas = NULL;
	m_pDestGlobalDatas = NULL;
#endif
}

CSetsFileToolInterface::~CSetsFileToolInterface()
{
#ifndef _SETS_FILE_TOOL_NOT_USE_GB_
	POS pos = m_oSetsMap.GetHeadPosition();
	CDataSet *pDataset = NULL;

	while (pos != NULL)
	{
		pDataset = (CDataSet *)m_oSetsMap.GetNext(pos);
		pDataset->RemoveAll();
	}
#endif
}

void CSetsFileToolInterface::CreateSetsMapByFile()
{
	
}

#ifndef _SETS_FILE_TOOL_NOT_USE_GB_
void CSetsFileToolInterface::SetCpus(CCpus *pCpus)
{
	m_oSetsMap.RemoveAll();
	POS pos = pCpus->GetHeadPosition();
	CCpu *p = NULL;

	while (pos != NULL)
	{
		p = (CCpu *)pCpus->GetNext(pos);
		AddToSetsMap(p);
	}
}

void CSetsFileToolInterface::GetDataset(const CString &strSrcTypeName, const CString &strGbTypeName, CDvmDataset **ppSrcDatast, CDataSet **ppGbDataset)
{
	*ppSrcDatast = (CDvmDataset*)m_oLogicDeviceFile.FindByName(strSrcTypeName);
	*ppGbDataset = (CDataSet*)m_oSetsMap.FindByName(strGbTypeName);
}

void CSetsFileToolInterface::AddToSetsMap(CCpu *pCpu)
{
	POS pos = pCpu->GetHeadPosition();
	CDataSet *p = NULL;

	while (pos != NULL)
	{
		p = (CDataSet *)pCpu->GetNext(pos);
		AddToSetsMap(p);
	}
}

void CSetsFileToolInterface::AddToSetsMap(CDataSet *pGbDataset)
{
	if (pGbDataset->m_strID.Find(g_strDataSetIDKey[DSID_dsParameter]) >= 0)
	{
		AddToSetsMap(pGbDataset, SETS_TITLE_ID_PARAMETER, g_strDataSetIDKey[DSID_dsParameter]);
	}
	else if (pGbDataset->m_strID.Find(g_strDataSetIDKey[DSID_dsSetting]) >= 0)
	{
		AddToSetsMap(pGbDataset, SETS_TITLE_ID_SETTING, g_strDataSetIDKey[DSID_dsSetting]);
	}
	else if (pGbDataset->m_strID.Find(g_strDataSetIDKey[DSID_dsEna]) >= 0)
	{
		AddToSetsMap(pGbDataset, SETS_TITLE_ID_ENA, g_strDataSetIDKey[DSID_dsEna]);
	}

}

void CSetsFileToolInterface::AddToSetsMap(CDataSet *pGbDataset, const CString &strName, const CString &strID)
{
	CDataSet *pFind = (CDataSet*)m_oSetsMap.FindByID(strID);

	if (pFind == NULL)
	{
		pFind = new CDataSet();
		pFind->m_strName = strName;
		pFind->m_strID = strID;
		m_oSetsMap.AddTail(pFind);
	}

	pFind->Append(pGbDataset);
}
#endif

CString CSetsFileToolInterface::GetDatatype(CDvmDataset *pDataset)
{
	if (pDataset->m_strName == SETS_TITLE_ID_CTRL)
	{
		return _T("BOOL");
	}

	if (pDataset->m_strName == SETS_TITLE_ID_MATRIX)
	{
		return _T("INT");
	}

	
	return _T("");
}

void CSetsFileToolInterface::InitGbDataset()
{
#ifndef _SETS_FILE_TOOL_NOT_USE_GB_   //zhouhj 20210728 
	m_oSetsMap.InitReserved(0);
#endif

	POS pos = m_oLogicDeviceFile.GetHeadPosition();
	CDvmDataset *pSrc = NULL;

	while (pos != NULL)
	{
		pSrc = (CDvmDataset *)m_oLogicDeviceFile.GetNext(pos);
		InitDatasetIDByName(pSrc);
		InitGbDataset(pSrc);
	}
}

void CSetsFileToolInterface::InitDatasetIDByName(CDvmDataset *pDataset)
{
	pDataset->m_strID.Empty();

	if (pDataset->m_strName == SETS_TITLE_ID_CTRL)
	{
		pDataset->m_strID = _T("enable");
		return;
	}

	if (pDataset->m_strName == SETS_TITLE_ID_MATRIX)
	{
		pDataset->m_strID = _T("matr");
		return;
	}
}

#ifndef _SETS_FILE_TOOL_NOT_USE_GB_
// CDataObj* CSetsFileToolInterface::FindDataObj(const CString &strDsID, CDataSet *pDest, const CString &strDataName)
// {
// 	CDataObj *pDestData = NULL;
// 
// 	if (strDsID.GetLength() == 0)
// 	{
// 		pDestData = (CDataObj*)pDest->FindByName(strDataName);
// 		return pDestData;
// 	}
// 
// 	POS pos = pDest->GetHeadPosition();
// 	CDataObj *p = NULL;
// 	CString strTemp;
// 
// 	while (pos != NULL)
// 	{
// 		p = (CDataObj *)pDest->GetNext(pos);
// 		strTemp = p->m_strID;
// 		strTemp.MakeLower();
// 
// 		if (strTemp.Find(strDsID) >= 0 && strDataName == p->m_strName)
// 		{
// 			pDestData = p;
// 			break;
// 		}
// 	}
// 
// 	return pDestData;
// }
CDataObj* CSetsFileToolInterface::FindDataObj(const CString &strDataType, CDataSet *pDest, const CString &strDataName)
{
	CDataObj *pDestData = NULL;
	POS pos = pDest->GetHeadPosition();
	CDataObj *p = NULL;

	if (strDataType.GetLength() == 0)
	{
		while (pos != NULL)
		{
			p = (CDataObj *)pDest->GetNext(pos);

			if (p->m_dwReserved == 1)
			{
				continue;
			}

			if (strDataName == p->m_strName)
			{
				pDestData = p;
				break;
			}
		}

		return pDestData;
	}

	while (pos != NULL)
	{
		p = (CDataObj *)pDest->GetNext(pos);

		if (p->m_dwReserved == 1)
		{
			continue;
		}

		if (strDataName == p->m_strName)
		{
			if (p->CmpDataType(strDataType))
			{
				pDestData = p;
			}

			break;
		}
	}

	return pDestData;
}
#endif

void CSetsFileToolInterface::InitGbDataset(CDvmDataset *pSrc)
{
#ifndef _SETS_FILE_TOOL_NOT_USE_GB_
	CDataSet *pDest = (CDataSet*)m_oSetsMap.FindByName(pSrc->m_strName);

	if (pDest == NULL)
	{
		pDest = (CDataSet*)m_oSetsMap.FindByName(SETS_TITLE_ID_SETTING);
	}

	if (pDest == NULL)
	{
		return;
	}

	POS pos = pSrc->GetHeadPosition();
	CDvmData *pData = NULL;
	CDataObj *pDestData = NULL;
	CString strDataType;// = GetDatatype(pSrc);;
	BOOL bMatr = FALSE;

	if (pSrc->m_strName == SETS_TITLE_ID_MATRIX)
	{
		bMatr = TRUE;
	}

	while (pos != NULL)
	{
		pData = (CDvmData *)pSrc->GetNext(pos);
		//pDestData = (CDataObj*)pDest->FindByName(pData->m_strName);
		pDestData = FindDataObj(strDataType, pDest, pData->m_strName);
		
		if (pDestData != NULL)
		{
			pDestData->m_dwReserved = 1;

			if (bMatr)
			{
				long nValue = 0;
				_stscanf_s((LPCTSTR)pData->m_strValue,_T("%x"),&nValue);
				pDestData->m_strValue.Format(_T("%d"), nValue);
			}
			else
			{
				pDestData->m_strValue = pData->m_strValue;
			}
		}
	}
#endif
}

void CSetsFileToolInterface::Time_S_to_ms()
{
#ifndef _SETS_FILE_TOOL_NOT_USE_GB_
	POS pos = m_oLogicDeviceFile.GetHeadPosition();
	CDvmDataset *pSrc = NULL;

	while (pos != NULL)
	{
		pSrc = (CDvmDataset *)m_oLogicDeviceFile.GetNext(pos);
		Time_S_to_ms(pSrc);
	}
#endif
}

//该函数中，形参pSrc是从定值单中解析的定值，时间定值的单位固定为秒或毫秒
//pDest是从选择的被测装置中，SCD解析的模型中的定值数据集
void CSetsFileToolInterface::Time_S_to_ms(CDvmDataset *pSrc)
{
#ifndef _SETS_FILE_TOOL_NOT_USE_GB_
	CDataSet *pDest = (CDataSet*)m_oSetsMap.FindByName(pSrc->m_strName);

	if (pDest == NULL)	//20231023 luozibing 原为 != 改为 == 
	{
		return;
	}

	POS pos = pSrc->GetHeadPosition();
	CDvmData *pData = NULL;
	CDataObj *pDestData = NULL;
	CString strDataType;
	float fValue;
	long nValue = 0;

	while (pos != NULL)
	{
		pData = (CDvmData *)pSrc->GetNext(pos);
		
		if (pData->m_strUnit == _T("s")
			|| pData->m_strUnit == _T("S"))
		{
			pDestData = (CDataObj*)pDest->FindByName(pData->m_strName);

			if (pDestData != NULL)
			{
				fValue = CString_To_double(pData->m_strValue);
				fValue *= 1000;
				nValue = (long)fValue;

				if (fValue - nValue > 0.5)
				{
					nValue++;
				}

				pDestData->m_strValue.Format(_T("%d"), nValue);

				//需要将单位改掉，才能再次切换回秒
				pData->m_strUnit = _T("ms");
			}
		}
	}
#endif
}

void CSetsFileToolInterface::Time_ms_to_S()
{
#ifndef _SETS_FILE_TOOL_NOT_USE_GB_
	POS pos = m_oLogicDeviceFile.GetHeadPosition();
	CDvmDataset *pSrc = NULL;

	while (pos != NULL)
	{
		pSrc = (CDvmDataset *)m_oLogicDeviceFile.GetNext(pos);
		Time_ms_to_S(pSrc);
	}
#endif
}

void CSetsFileToolInterface::Time_ms_to_S(CDvmDataset *pSrc)
{
#ifndef _SETS_FILE_TOOL_NOT_USE_GB_
	CDataSet *pDest = (CDataSet*)m_oSetsMap.FindByName(pSrc->m_strName);

	if (pDest != NULL)
	{
		return;
	}

	POS pos = pSrc->GetHeadPosition();
	CDvmData *pData = NULL;
	CDataObj *pDestData = NULL;
	CString strDataType;
	float fValue;
	long nValue = 0;

	while (pos != NULL)
	{
		pData = (CDvmData *)pSrc->GetNext(pos);
		CString strUnit = pData->m_strUnit;
		strUnit.MakeLower();

		if (strUnit == _T("ms"))
		{
			pDestData = (CDataObj*)pDest->FindByName(pData->m_strName);

			if (pDestData != NULL)
			{
				fValue = CString_To_double(pData->m_strValue);
				fValue /= 1000;
				pDestData->m_strValue.Format(_T("%.3f"), fValue);

				//需要将单位改掉，才能再次切换回毫秒
				pData->m_strUnit = _T("s");
			}
		}
	}
#endif
}