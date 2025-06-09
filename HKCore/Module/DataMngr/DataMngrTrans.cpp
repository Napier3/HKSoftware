
#include "stdafx.h"
#include "DataMngrTrans.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

void Append_Datas(CExBaseList *pDestDatas, CDvmDataset *pSrcDatas, BOOL bAddSame)
{
	POS posSrc = pSrcDatas->GetHeadPosition();
	CDvmData *pSrcData = NULL;
	CShortData *pNew = NULL;

	if (bAddSame)
	{
		while (posSrc != NULL)
		{
			pSrcData = (CDvmData *)pSrcDatas->GetNext(posSrc);
			pNew = new CShortData();
			Copy_Data(pNew, pSrcData);
			pDestDatas->AddNewChild(pNew);
		}
	}
	else
	{
		while (posSrc != NULL)
		{
			pSrcData = (CDvmData *)pSrcDatas->GetNext(posSrc);
			pNew = (CShortData*)pDestDatas->FindByID(pSrcData->m_strID);

			if (pNew == NULL)
			{
				pNew = new CShortData();
				pDestDatas->AddNewChild(pNew);
			}

			Copy_Data(pNew, pSrcData);
		}
	}
}

void Append_Datas(CExBaseList *pDestDvmDataset, CExBaseList *pSrcDatas, BOOL bAddSame)
{
	POS posSrc = pSrcDatas->GetHeadPosition();
	CShortData *pSrcData = NULL;
	CDvmData *pNew = NULL;

	if (bAddSame)
	{
		while (posSrc != NULL)
		{
			pSrcData = (CShortData *)pSrcDatas->GetNext(posSrc);
			pNew = new CDvmData();
			Copy_Data(pNew, pSrcData);
			pDestDvmDataset->AddNewChild(pNew);
		}
	}
	else
	{
		while (posSrc != NULL)
		{
			pSrcData = (CShortData *)pSrcDatas->GetNext(posSrc);
			pNew = (CDvmData *)pDestDvmDataset->FindByID(pSrcData->m_strID);

			if (pNew == NULL)
			{
				pNew = new CDvmData();
				Copy_Data(pNew, pSrcData);
				pDestDvmDataset->AddNewChild(pNew);
			}
		}
	}
}

void DvmDatas_to_ShortDatas(CExBaseList *pSrcDatas, CExBaseList *pDestDatas)
{
    POS pos = pSrcDatas->GetHeadPosition();
    CShortData *pNew = NULL;
    CDvmData *p = NULL;

    while (pos != NULL)
    {
        p = (CDvmData *)pSrcDatas->GetNext(pos);
        pNew = new CShortData();
        Copy_Data(pNew, p);
        pDestDatas->AddNewChild(pNew);
    }
}

void ShortDatas_to_DvmDatas(CExBaseList *pSrcDatas, CExBaseList *pDestDatas)
{
    POS pos = pSrcDatas->GetHeadPosition();
    CDvmData *pNew = NULL;
    CShortData *p = NULL;

    while (pos != NULL)
    {
        p = (CShortData *)pSrcDatas->GetNext(pos);
        pNew = new CDvmData();
        Copy_Data(pNew, p);
        pDestDatas->AddNewChild(pNew);
    }
}

void SetVal_DvmDatas_by_ShortDatas(CExBaseList *pSrcDatas, CExBaseList *pDestDatas)
{
    POS pos = pSrcDatas->GetHeadPosition();
    CShortData *pDest = NULL;
    CDvmData *p = NULL;

    while (pos != NULL)
    {
        p = (CDvmData *)pSrcDatas->GetNext(pos);
        pDest = (CShortData*)pDestDatas->FindByID(p->m_strID);

        if (pDest != NULL)
        {
            pDest->m_strValue = p->m_strValue;
        }
    }
}

void SetVal_ShortDatas_by_DvmDatas(CExBaseList *pSrcDatas, CExBaseList *pDestDatas)
{
    POS pos = pSrcDatas->GetHeadPosition();
    CShortData *pDest = NULL;
    CDvmData *p = NULL;

    while (pos != NULL)
    {
        p = (CDvmData *)pSrcDatas->GetNext(pos);
        pDest = (CShortData*)pDestDatas->FindByID(p->m_strID);

        if (pDest != NULL)
        {
            pDest->m_strValue = p->m_strValue;
        }
    }
}


void Copy_Data(CShortData *pDestData, CDvmData *pSrcDvmData)
{
	pDestData->m_strName = pSrcDvmData->m_strName;
	pDestData->m_strID = pSrcDvmData->m_strID;
	pDestData->m_strValue = pSrcDvmData->m_strValue;
	pDestData->m_strDataTypeID = pSrcDvmData->m_strDataType;
	pDestData->m_strFormat = pSrcDvmData->m_strFormat;
	pDestData->m_strUnit = pSrcDvmData->m_strUnit;
	pDestData->m_dTime = pSrcDvmData->m_dTime;
}


void Copy_Data(CDvmData *pDestDvmData, CShortData *pSrcData)
{
	pDestDvmData->m_strName = pSrcData->m_strName;
	pDestDvmData->m_strID = pSrcData->m_strID;
	pDestDvmData->m_strValue = pSrcData->m_strValue;
	pDestDvmData->m_strDataType = pSrcData->m_strDataTypeID;
	pDestDvmData->m_strFormat = pSrcData->m_strFormat;
	pDestDvmData->m_strUnit = pSrcData->m_strUnit;
	pDestDvmData->m_dTime = pSrcData->m_dTime;
}


CDvmData* dvm_AddValuesToDataset(CValues *pValues, CDvmDataset *pDataDef, CDvmDataset *pDsDest)
{
	if (!dvm_ValidateValuesByDef(pValues, pDataDef))
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("数据与定义不一致"));
		return NULL;
	}

	CDvmData *pDvmData = dvm_FindDataInDataset(pValues, pDsDest);

	if (pDvmData != NULL)
	{
		return pDvmData;
	}

	pDvmData = new CDvmData();
	pDsDest->AddNewChild(pDvmData);
	dvm_SetDvmData(pValues, pDvmData);

	return pDvmData;
}

BOOL dvm_ValidateValuesByDef(CValues *pValues, CDvmDataset *pDataDef)
{
	POS pos = pValues->GetHeadPosition();
	CValue *pValue = NULL;
	BOOL bTrue = TRUE;

	while (pos != NULL)
	{
		pValue = (CValue *)pValues->GetNext(pos);

		if (pDataDef->FindByID(pValue->m_strID) == NULL)
		{
			bTrue = FALSE;
			break;
		}
	}

	return bTrue;
}

CDvmData* dvm_FindDataInDataset(CValues *pValues, CDvmDataset *pDsDest)
{
	CDvmData *p = NULL, *pFind = NULL;
	POS pos = pDsDest->GetHeadPosition();

	while (pos != NULL)
	{
		p = (CDvmData *)pDsDest->GetNext(pos);

		if (dvm_IsSameData(pValues, p))
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

BOOL dvm_IsSameData(CValues *pValues, CDvmData *pDvmData)
{
	POS pos = pValues->GetHeadPosition();
	CValue *pValue = NULL;
	BOOL bTrue = TRUE;
	CDvmValue *pDvmValue = NULL;

	while (pos != NULL)
	{
		pValue = (CValue *)pValues->GetNext(pos);
		pDvmValue = (CDvmValue*)pDvmData->FindByID(pValue->m_strID);

		if (pDvmValue == NULL)
		{
			bTrue = FALSE;
			break;
		}

		if (pValue->m_strValue != pDvmValue->m_strValue)
		{
			bTrue = FALSE;
			break;
		}
	}

	return bTrue;
}

void dvm_SetDvmData(CValues *pValues, CDvmData *pDvmData)
{
	POS pos = pValues->GetHeadPosition();
	CValue *pValue = NULL;
	BOOL bTrue = TRUE;
	CDvmValue *pDvmValue = NULL;

	while (pos != NULL)
	{
		pValue = (CValue *)pValues->GetNext(pos);
		pDvmValue = pDvmData->AddValue(pValue->m_strID, pValue->m_strValue);
		pDvmValue->m_strName = pDvmValue->m_strID;
		pDvmData->m_strName = pValue->m_strName;

		if (pValue->m_strID == CDataMngrXmlRWKeys::g_pXmlKeys->m_strNameKey)
		{
			pDvmData->m_strName = pValue->m_strValue;
		}
		else if (pValue->m_strID == CDataMngrXmlRWKeys::g_pXmlKeys->m_strIDKey)
		{
			pDvmData->m_strID = pValue->m_strValue;
		}
		else if (pValue->m_strID == CDataMngrXmlRWKeys::ValueKey())
		{
			pDvmData->m_strValue = pValue->m_strValue;
		}
	}
}

BOOL dvm_IsSameDataset_id_value(CDvmDataset *pSrc, CDvmDataset *pDest)
{
	POS pos = pSrc->GetHeadPosition();
	CDvmData *p = NULL, *pFind = NULL;

	while (pos != NULL)
	{
		p = (CDvmData *)pSrc->GetNext(pos);
		pFind = (CDvmData *)pDest->FindByID(p->m_strID);

		if (pFind == NULL)
		{
			return FALSE;
		}

		if (pFind->m_strValue != p->m_strValue)
		{
			return FALSE;
		}

		if (!dvm_IsSameData_id_value(p, pFind))
		{
			return FALSE;
		}
	}

	return TRUE;
}

BOOL dvm_IsSameData_id_value(CDvmData *pSrc, CDvmData *pDest)
{
	POS pos = pSrc->GetHeadPosition();
	CDvmValue *p = NULL, *pFind = NULL;

	while (pos != NULL)
	{
		p = (CDvmValue *)pSrc->GetNext(pos);
		pFind = (CDvmValue *)pDest->FindByID(p->m_strID);

		if (pFind == NULL)
		{
			return FALSE;
		}

		if (pFind->m_strValue != p->m_strValue)
		{
			return FALSE;
		}
	}

	return TRUE;
}

CDvmDataset* dvm_FindDsByDatas(CDvmLogicDevice *pLdevice, CDvmDataset *pSrcDs)
{
	POS pos = pLdevice->GetHeadPosition();
	CDvmDataset *p = NULL, *pFind = NULL;

	while (pos != NULL)
	{
		p = (CDvmDataset *)pLdevice->GetNext(pos);

		if (dvm_IsSameDataset_id_value(p, pSrcDs))
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

//2021-2-23  lijunqing
void DvmDataset_to_Values(CDvmDataset *pSrc, CValues *pValues)
{
	DvmDatas_to_Values((CExBaseList*)pSrc, pValues);
}

//2022-7-24  lijunqing
void DvmDatas_to_Values(CExBaseList *pSrc, CValues *pValues)
{
	POS pos = pSrc->GetHeadPosition();
	CDvmData *p = NULL;

	while (pos != NULL)
	{
		p = (CDvmData *)pSrc->GetNext(pos);
		pValues->AddValue(p->m_strID, p->m_strValue);
	}
}

