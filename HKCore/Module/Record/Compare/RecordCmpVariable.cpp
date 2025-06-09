// RecordCmpVariable.cpp: implementation of the CRecordCmpVariable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RecordCmpVariable.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//
CRecordCmpVariable::CRecordCmpVariable(CRtSingleVariable *pVariable1, CRtSingleVariable *pVariable2
										 , long nSampleRate1, long nSampleRate2, float fSetValForFind, float fSetValForCmp)
{
	m_nAllignPosition1 = 0;
	m_nAllignPosition2 = 0;

	m_pRtVariable1 = pVariable1;
	m_pRtVariable2 = pVariable2;

#ifdef RCD_CMP_USE_EffecValue
	CRtDataAttribute *pAttr1 = pVariable1->m_pDataAttrs->FindByAttrID(SingleVariableAttrID_DeltaEffecValue);
	CRtDataAttribute *pAttr2 = pVariable2->m_pDataAttrs->FindByAttrID(SingleVariableAttrID_DeltaEffecValue);
	CRtDataAttribute *pAttr1_V = pVariable1->m_pDataAttrs->FindByAttrID(SingleVariableAttrID_EffecValue);
	CRtDataAttribute *pAttr2_V = pVariable2->m_pDataAttrs->FindByAttrID(SingleVariableAttrID_EffecValue);
#else
	CRtDataAttribute *pAttr1 = pVariable1->m_pDataAttrs->FindByAttrID(SingleVariableAttrID_DeltaFundValue);
	CRtDataAttribute *pAttr2 = pVariable2->m_pDataAttrs->FindByAttrID(SingleVariableAttrID_DeltaFundValue);
	CRtDataAttribute *pAttr1_V = pVariable1->m_pDataAttrs->FindByAttrID(SingleVariableAttrID_FundValue);
	CRtDataAttribute *pAttr2_V = pVariable2->m_pDataAttrs->FindByAttrID(SingleVariableAttrID_FundValue);
#endif

	CRecordCmpBuffer *pNew = new CRecordCmpBuffer();
	pNew->SetBuffer(pAttr1_V->m_pAttrBuffer, pAttr2_V->m_pAttrBuffer);

	pNew->RcdCmp(pAttr1->m_pAttrBuffer, pAttr2->m_pAttrBuffer, nSampleRate1, nSampleRate2, fSetValForFind, fSetValForCmp);
	AddNewChild(pNew);
	CString strID;
	strID.Format(_T("%s:%s"), pVariable1->m_strID, pVariable2->m_strID);
	pNew->LogRcdCmp(pVariable1->m_strID);

	pNew->GetAllignPosition(m_nAllignPosition1, m_nAllignPosition2);
	
}

CRecordCmpVariable::~CRecordCmpVariable()
{
	
}

BOOL CRecordCmpVariable::GetAlignPosVariable2(long &nAlignPos)
{
	POS pos = GetHeadPosition();
	CRecordCmpBuffer *p = NULL;
	BOOL bRet = FALSE;

	while (pos != NULL)
	{
		p = (CRecordCmpBuffer *)GetNext(pos);

		if (p->GetAlignPosVariable2(nAlignPos))
		{
			bRet = TRUE;
		}
	}

	return bRet;
}
