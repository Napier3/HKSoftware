#include "StdAfx.h"
#include "GbtDataBatchValueRangeRamp.h"
#include "..\..\XLanguageResourceAts.h"

CGbtDataBatchValueRangeRamp::CGbtDataBatchValueRangeRamp(void)
{
	SetAutoNameID(TRUE);
	m_strName = g_sLangTxt_DataBatch/*L"数据集遍历批量"*/;
}

CGbtDataBatchValueRangeRamp::~CGbtDataBatchValueRangeRamp(void)
{
	
}

void CGbtDataBatchValueRangeRamp::SetGbtBatchItemGroups(CGbtBatchItemGroups *pBatchItemGroups)
{
	ASSERT (pBatchItemGroups != NULL);

	if (pBatchItemGroups == NULL)
	{
		return;
	}

	m_pBatchItemGroups = pBatchItemGroups;
	InitGbtDatasRampObj();
}

void CGbtDataBatchValueRangeRamp::InitGbtDatasRampObj()
{
	ASSERT (m_pBatchItemGroups != NULL);
	ASSERT (m_pBatchItemGroups->m_pGbtBatchItemGroupRef != NULL);
	ASSERT (m_pBatchItemGroups->m_pGbtBatchItemGroupRef->GetClassID() == GBTWZDCLASSID_BATCHGBTDATAGROUP);

	CGbtBatchGbtDataGroup *pGbtDatasGroup = (CGbtBatchGbtDataGroup*)m_pBatchItemGroups->m_pGbtBatchItemGroupRef;
	POS pos = pGbtDatasGroup->GetHeadPosition();
	CGbtBatchGbtDataRef *pBatchGbtData = NULL;
	CGbtDataTraverseObj *pNew = NULL;

	while (pos != NULL)
	{
		pBatchGbtData = (CGbtBatchGbtDataRef *)pGbtDatasGroup->GetNext(pos);
		pNew = CGbtDataTraverseObj::_New(pBatchGbtData);
		AddNewChild(pNew);
	}
}

void CGbtDataBatchValueRangeRamp::Batch()
{
	CGbtDataTraverseObj *pGbtDataTraverseObj = NULL;
	pGbtDataTraverseObj = (CGbtDataTraverseObj *)GetHead();

	m_pBatchItemGroups->SetBatchItemGroupCount(pGbtDataTraverseObj->m_nSteps);
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pGbtDataTraverseObj = (CGbtDataTraverseObj *)GetNext(pos);
		Batch(pGbtDataTraverseObj);
	}

	InitNameIDAuto();
}

void CGbtDataBatchValueRangeRamp::InitNameIDAuto()
{
	if (!m_bAutoNameID)
	{
		return;
	}

	POS pos = m_pBatchItemGroups->GetHeadPosition();
	CGbtBatchItemGroup *pGroup = NULL;

	while (pos != NULL)
	{
		pGroup = (CGbtBatchItemGroup *)m_pBatchItemGroups->GetNext(pos);
		InitNameIDAuto(pGroup);
	}

}

void CGbtDataBatchValueRangeRamp::InitNameIDAuto(CGbtBatchItemGroup *pGroup)
{
	POS pos = pGroup->GetHeadPosition();
	CGbtBatchGbtDataRef *pGbtDataRef = NULL;
	CString strName, strID;

	while (pos != NULL)
	{
		pGbtDataRef = (CGbtBatchGbtDataRef *)pGroup->GetNext(pos);
		strName.AppendFormat(_T("%s=%s;"), pGbtDataRef->m_strName, pGbtDataRef->m_strGbtDataValue);
		strID.AppendFormat(_T("%s%s_"), pGbtDataRef->m_strID, pGbtDataRef->m_strGbtDataValue);
	}

	strName = strName.Left(strName.GetLength() - 1);
	strID = strID.Left(strID.GetLength() - 1);
	strID.Replace(_T("i_"), _T(""));
	strID.Replace(_T("."), _T(""));

	pGroup->m_strName = strName;
	pGroup->m_strID   = strID;
}

void CGbtDataBatchValueRangeRamp::Batch(CGbtDataTraverseObj *pGbtDataTraverseObj)
{
	long nIndex = 0;
	POS pos = m_pBatchItemGroups->GetHeadPosition();
	CGbtBatchItemGroup *pGroup = NULL;

	while (pos != NULL)
	{
		pGroup = (CGbtBatchItemGroup *)m_pBatchItemGroups->GetNext(pos);
		Batch(pGbtDataTraverseObj, pGroup, nIndex);
		nIndex++;
	}
}

void CGbtDataBatchValueRangeRamp::Batch(CGbtDataTraverseObj *pGbtDataTraverseObj, CGbtBatchItemGroup *pGroup, long nIndex)
{
	CGbtBatchGbtDataRef *pGbtDataRef = (CGbtBatchGbtDataRef*)pGroup->FindByID(pGbtDataTraverseObj->m_pDataRef->m_strID);
	ASSERT (pGbtDataRef != NULL);

	if (pGbtDataRef == NULL)
	{
		return;
	}

	double dValue = pGbtDataTraverseObj->m_dBeginVal + pGbtDataTraverseObj->m_dStep * nIndex;
	pGbtDataRef->m_strGbtDataValue.Format(_T("%f"), dValue);
	ChopFloatString(pGbtDataRef->m_strGbtDataValue, 3);
}
