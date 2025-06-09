//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DvmDataset.cpp  CDvmDatasetSort


#include "stdafx.h"
#include "DvmDatasetSort.h"
#include "../GpsPcTime/GpsPcTime.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CDvmDatasetSort::CDvmDatasetSort()
{
	m_pDvmDataset = NULL;
}

CDvmDatasetSort::~CDvmDatasetSort()
{
	
}

void CDvmDatasetSort::SortByAttrValue_t(CDvmDataset *pDataset)
{
	m_pDvmDataset = pDataset;
	long nCount = m_pDvmDataset->GetCount();

	if (nCount < 2)
	{
		return;
	}

	PDVMDATASORT pDataSort = (PDVMDATASORT)::malloc(nCount * sizeof(DVMDATASORT));
	PDVMDATASORT pCurr = pDataSort;
	POS pos = pDataset->GetHeadPosition();
	CDvmData *pData = NULL;
	BOOL bTrue = TRUE;

	while (pos != NULL)
	{
		pData = (CDvmData *)pDataset->GetNext(pos);
		
		if (!InitDvmStruct(pCurr, pData))
		{
			bTrue = FALSE;
			break;
		}

		pCurr++;
	}

	if (bTrue)
	{
		Sort(pDataSort, nCount);
		pDataset->RemoveAll();

		for (long i=0; i<nCount; i++)
		{
			pDataset->AddTail(pDataSort[i].pData);
		}
	}

	::free(pDataSort);
}

BOOL CDvmDatasetSort::InitDvmStruct(PDVMDATASORT pSort, CDvmData *pDvmData)
{
	CDvmValue *pFind = NULL;

	pFind = FindValue(pDvmData, _T("$t"));

	if (pFind == NULL)
	{
		return FALSE;
	}

	CGpsPcTime tm;
	tm.FromString(pFind->m_strValue);
	pSort->pData = pDvmData;
	pSort->tm64Value = tm.GetTime_Int64();

	return TRUE;
}

CDvmValue* CDvmDatasetSort::FindValue(CDvmData *pDvmData, const CString &strID)
{
	POS pos = pDvmData->GetHeadPosition();
	CDvmValue *p = NULL, *pFind = NULL;
	long nLen = strID.GetLength();

	while (pos != NULL)
	{
		p = (CDvmValue *)pDvmData->GetNext(pos);

		if (p->m_strID.Right(nLen) == strID)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

BOOL CDvmDatasetSort::Sort(PDVMDATASORT pSort, long nCount)
{
	long i=0, j=0;
	DVMDATASORT data;

	for (i=0; i<nCount-1; i++)
	{
		for (j=i+1; j<nCount; j++)
		{
			if (pSort[i].tm64Value > pSort[j].tm64Value)
			{
				data = pSort[j];
				pSort[j] = pSort[i];
				pSort[i] = data;
			}
		}
	}

	return TRUE;
}

