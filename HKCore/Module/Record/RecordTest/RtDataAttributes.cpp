// RtDataAttributes.cpp: implementation of the CRtDataAttributes class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RtDataAttributes.h"
#include "RtVariable.h"
#include "RtVariables.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const char *CRtDataAttributes::g_pszKeyDataAttrs = "data-attrs";

CRtDataAttributes::CRtDataAttributes()
{
	m_strName = "RtDataAttributes";
	m_strID = m_strName;
	m_nStaticAttrs = 0;

	memset(m_paDataAttributes, 0, (MAX_CHANNEL_ATTRID_KEYS+1) * sizeof(void*));

	m_pClone = NULL;
}

void CRtDataAttributes::ResetUseAndSpy()
{
	CRtDataAttribute *pDataAttr = NULL;
	POS pos  = NULL;
	long nIndex = 0;
	pos = GetHeadPosition();
	
	while (pos != NULL)
	{
		pDataAttr = (CRtDataAttribute *)GetNext(pos);

		pDataAttr->SetUse(0);
		pDataAttr->SetSpyState(0);
		pDataAttr->m_pSets->ResetUse();
		nIndex++;
	}
}

void CRtDataAttributes::ResetAttrSpyState()
{
	CRtDataAttribute *pDataAttr = NULL;
	POS pos  = NULL;
	pos = GetHeadPosition();
	
	while (pos != NULL)
	{
		pDataAttr = (CRtDataAttribute *)GetNext(pos);
		pDataAttr->SetSpyState(0);
	}
}

CRtDataAttributes::~CRtDataAttributes()
{
	m_pClone = NULL; 
}
// 
// BOOL CRtDataAttributes::ReadSetsValueXml(MSXML::IXMLDOMNodeListPtr &oNodes)
// {
// 	int nCount = oNodes->Getlength();
// 	int nIndex = 0;
// 	MSXML::IXMLDOMNodePtr oNode = NULL;	
// 	CString strAttrID;	
// 	CRtDataAttribute *pDataAttr = NULL;
// 	
// 	for(nIndex = 0; nIndex < nCount; nIndex++)
// 	{
// 		oNode = oNodes->Getitem(nIndex);
// 		xml_GetAttibuteValue(CRtDataAttribute::g_pszKeyID, oNode, strAttrID);	
// 		pDataAttr = (CRtDataAttribute*)FindByID(strAttrID);	
// 		
// 		if (pDataAttr != NULL)
// 		{
// 			pDataAttr->ReadSetsValueXml(oNode);
// 		}
// 	}
// 
// 	return TRUE;
// }
// 
// BOOL CRtDataAttributes::WriteSetsValueXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oParent)
// {
// 	MSXML::IXMLDOMElementPtr oDataAttrs;
// 	oDataAttrs = oXMLDoc->createElement(_bstr_t(g_pszKeyDataAttrs));
// 	
// 	CRtDataAttribute *pDataAttr = NULL;
// 	POS pos  = GetHeadPosition();
// 
// 	while (pos != NULL)
// 	{
// 		pDataAttr = (CRtDataAttribute*)GetNext(pos);
// 
// 		if (pDataAttr != NULL)
// 		{
// 			pDataAttr->WriteSetsValueXml(oXMLDoc, oDataAttrs);
// 		}
// 	}
// 
// 	oParent->appendChild(oDataAttrs);
// 
// 	return TRUE;
// }

CRtDataAttribute* CRtDataAttributes::FindByAttrID(const char* pstrAttrID)
{
	CRtDataAttribute *pDataAttr = NULL;
	CRtDataAttribute *pFind = NULL;
	POS pos  = GetHeadPosition();
	
	while (pos != NULL)
	{
		pDataAttr = (CRtDataAttribute*)GetNext(pos);
		
		if (pDataAttr != NULL)
		{
			if (_stricmp(pDataAttr->m_strID.GetString(), pstrAttrID) == 0)
			{
				pFind = pDataAttr;
				break;
			}
		}
	}
	
	return pFind;
}

CRtDataAttribute* CRtDataAttributes::FindByAttrID(UINT nAttrID)
{
	CRtDataAttribute *pDataAttr = NULL;
	CRtDataAttribute *pFind = NULL;
	POS pos  = GetHeadPosition();

	while (pos != NULL)
	{
		pDataAttr = (CRtDataAttribute*)GetNext(pos);

		if (pDataAttr != NULL)
		{
			if (pDataAttr->m_nAttributeID == nAttrID)
			{
				pFind = pDataAttr;
				break;
			}
		}
	}

	return pFind;
}

void CRtDataAttributes::CalValues(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, BOOL bCal, BOOL bCalUseRecordBuffer)
{
	CRtDataAttribute **pDataAttr = &m_paDataAttributes[m_nStaticAttrs];

	while (*pDataAttr != NULL)
	{
		(*pDataAttr)->CalValues(pRtAttrCalBufPos, bCal, bCalUseRecordBuffer);
		pDataAttr++;
	}
}

void CRtDataAttributes::CalStaticValues_Quick(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, BOOL bAddFrequency, BOOL bCalUseRecordBuffer)
{
	CRtDataAttribute *pDataAttr = NULL;

	long nIndex = 0;

	for (nIndex=1; nIndex<m_nStaticAttrs; nIndex++)
	{
		m_paDataAttributes[nIndex]->CalValues_Quick(pRtAttrCalBufPos, TRUE, bCalUseRecordBuffer);
	}

	if (m_nStaticAttrs > 0 && bAddFrequency)
	{
		m_paDataAttributes[0]->AddValueToAttrBuffer();
	}
}

void CRtDataAttributes::CalValues_PeakVellay(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, BOOL bAddFrequency, BOOL bCalUseRecordBuffer)
{
	CRtDataAttribute *pDataAttr = NULL;

	m_paDataAttributes[SingleVariableAttrID_PeakValue]->CalValues_PeakVellay(pRtAttrCalBufPos, TRUE, bCalUseRecordBuffer);
	m_paDataAttributes[SingleVariableAttrID_VellayValue]->CalValues_PeakVellay(pRtAttrCalBufPos, TRUE, bCalUseRecordBuffer);
}

void CRtDataAttributes::CalStaticValues(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, BOOL bAddFrequency, BOOL bCalUseRecordBuffer)
{
	CRtDataAttribute *pDataAttr = NULL;

	long nIndex = 0;

	for (nIndex=1; nIndex<m_nStaticAttrs; nIndex++)
	{
		m_paDataAttributes[nIndex]->CalValues(pRtAttrCalBufPos, TRUE, bCalUseRecordBuffer);
	}

	if (m_nStaticAttrs > 0 && bAddFrequency)
	{
		m_paDataAttributes[0]->AddValueToAttrBuffer();
	}

}

void CRtDataAttributes::InitCalFuncPara()
{
	CRtDataAttribute *pDataAttr = NULL;
	POS pos  = NULL;
	pos = GetHeadPosition();

	while (pos != NULL)
	{
		pDataAttr = (CRtDataAttribute*)GetNext(pos);
		pDataAttr->InitCalFuncPara();
	}
}

void CRtDataAttributes::CalFrequncy(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, BOOL bCalUseRecordBuffer)
{
	if (*m_paDataAttributes != NULL)
	{
		//2022-5-5  lijunqing : reset value
		*((*m_paDataAttributes)->m_oCalFuncPara.pnFreqZeroPosCount) = 0;

		(*m_paDataAttributes)->CalValues(pRtAttrCalBufPos, TRUE, bCalUseRecordBuffer);
	}
}

void CRtDataAttributes::CalInstValue(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos,BOOL bCalUseRecordBuffer)
{
	CRtDataAttribute **pDataAttr = &m_paDataAttributes[m_nStaticAttrs];
	
	while (*pDataAttr != NULL)
	{
		if ((*pDataAttr)->IsInstAttr())
		{
			(*pDataAttr)->CalValues(pRtAttrCalBufPos, TRUE, bCalUseRecordBuffer);
			break;
		}

		pDataAttr++;
	}
}

BOOL CRtDataAttributes::JudgeStartup(long &nStartup)
{
	CRtDataAttribute *pDataAttr = NULL;
	POS pos  = NULL;
	pos = GetHeadPosition();
	
	while (pos != NULL)
	{
		pDataAttr = (CRtDataAttribute*)GetNext(pos);
		pDataAttr->JudgeStartup(nStartup);
	}

	return TRUE;
}


void CRtDataAttributes::CalFaultValues(long nBeginPos, long nLen, long nCyclePoints)
{
	CRtDataAttribute *pDataAttr = NULL;
	POS pos  = NULL;
	pos = GetHeadPosition();

	while (pos != NULL)
	{
		pDataAttr = (CRtDataAttribute*)GetNext(pos);
		pDataAttr->CalFaultValues(nBeginPos, nLen, nCyclePoints);
	}
}

// #define  SingleVariableAttrID_Frequancy                      0
// #define  SingleVariableAttrID_EffecValue                     1
// #define  SingleVariableAttrID_EffecPhase                     2
// #define  SingleVariableAttrID_FundValue                      3

//#define  SingleVariableAttrID_DeltaEffecValue        74
//#define  SingleVariableAttrID_DeltaFundValue        75

CRtDataAttribute* CRtDataAttributes::FindFaultSrcAttr(UINT nAttrID)
{
	CRtDataAttribute *pFind = NULL;
	UINT nAttrIDFind = 0xFFFFFFFF;

	if (SingleVariableAttrID_DeltaEffecValue == nAttrID)
	{
		nAttrIDFind = SingleVariableAttrID_EffecValue;
	}
	else if (SingleVariableAttrID_DeltaFundValue == nAttrID)
	{
		nAttrIDFind = SingleVariableAttrID_FundValue;
	}

	if (nAttrIDFind == 0xFFFFFFFF)
	{
		return NULL;
	}

	return FindByAttrID(nAttrIDFind);
}

double* CRtDataAttributes::GetValueRefByID(const CString &strID)
{
	double *pdValue = NULL;
	CRtDataAttribute *pDataAttr = NULL;

	POS pos  = NULL;
	pos = GetHeadPosition();

	while (pos != NULL)
	{
		pDataAttr = (CRtDataAttribute*)GetNext(pos);
		pdValue = pDataAttr->GetValueRefByID(strID);

		if (pdValue !=NULL)
		{
			break;
		}
	}
	
	return pdValue;
}

double* CRtDataAttributes::GetAttrValueRefByID(const CString &strID)
{
	double *pdValue = NULL;
	CRtDataAttribute *pDataAttr = NULL;
	
	POS pos  = NULL;
	pos = GetHeadPosition();
	
	while (pos != NULL)
	{
		pDataAttr = (CRtDataAttribute*)GetNext(pos);
		pdValue = pDataAttr->GetAttrValueRefByID(strID);
		
		if (pdValue !=NULL)
		{
			break;
		}
	}
	
	return pdValue;
}


double* CRtDataAttributes::GetMutationValueRefByID(const CString &strID)
{
	double *pdValue = NULL;
	CRtDataAttribute *pDataAttr = NULL;
	
	POS pos  = NULL;
	pos = GetHeadPosition();
	
	while (pos != NULL)
	{
		pDataAttr = (CRtDataAttribute*)GetNext(pos);
		pdValue = pDataAttr->GetMutationValueRefByID(strID);
		
		if (pdValue !=NULL)
		{
			break;
		}
	}
	
	return pdValue;
}

void CRtDataAttributes::InitBufferMngr(CRtMemBufferMngr *pRtMemBufferMngr)
{
	CRtDataAttribute *pDataAtrr = NULL;
	POS pos  = GetHeadPosition();
	
	while (pos != NULL) 
	{
		pDataAtrr = (CRtDataAttribute*)GetNext(pos);
		pDataAtrr->InitBufferMngr(pRtMemBufferMngr);
	}
}

void CRtDataAttributes::AdjustStaticAttrs()
{
	m_nStaticAttrs = 0;
	AddStaticAttr(g_pszChannelKeyAttrID[SingleVariableAttrID_Frequancy], "Hz", SingleVariableAttrID_Frequancy);
	AddStaticAttr(g_pszChannelKeyAttrID[SingleVariableAttrID_EffecValue], "", SingleVariableAttrID_EffecValue);
	AddStaticAttr(g_pszChannelKeyAttrID[SingleVariableAttrID_EffecPhase], "", SingleVariableAttrID_EffecPhase);
	AddStaticAttr(g_pszChannelKeyAttrID[SingleVariableAttrID_FundValue], "", SingleVariableAttrID_FundValue);
	AddStaticAttr(g_pszChannelKeyAttrID[SingleVariableAttrID_FundPhase], "", SingleVariableAttrID_FundPhase);


	CRtDataAttribute *pDataAttr = NULL;
	POS pos  = NULL;
	pos = GetHeadPosition();
	long nIndex = 0;

	while (pos != NULL)
	{
		pDataAttr = (CRtDataAttribute*)GetNext(pos);
		m_paDataAttributes[nIndex] = pDataAttr;
		nIndex++;
	}
}

CRtDataAttribute* CRtDataAttributes::FindAttr(const CString &pszAttrID)
{
	CRtDataAttribute *p = NULL;
	CRtDataAttribute *pFind = NULL;
	POS pos  = GetHeadPosition();
	
	while (pos != NULL) 
	{
		p = (CRtDataAttribute*)GetNext(pos);
		
		if (p->m_strID == pszAttrID)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

CRtDataAttribute* CRtDataAttributes::FindAttr(UINT nAttrID)
{
	CRtDataAttribute *p = NULL;
	CRtDataAttribute *pFind = NULL;
	POS pos  = GetHeadPosition();
	
	while (pos != NULL) 
	{
		p = (CRtDataAttribute*)GetNext(pos);
		
		if (p->m_nAttributeID == nAttrID)
		{
			pFind = p;
			break;
		}
	}
	
	return pFind;
}

void CRtDataAttributes::AddStaticAttr(const CString &pszAttrID, const CString &pszUnit, long nIndex)
{
	CRtDataAttribute *pAttr = FindAttr(pszAttrID);

	if (pAttr == NULL)
	{
		CRtVariable *pVariable = (CRtVariable*)GetAncestor(RTCLASSID_VARIABLE);
		pVariable = (CRtVariable*)GetParent();
		ASSERT (pVariable != NULL);
		CString strName, strID;

		pAttr = new CRtDataAttribute();
		pAttr->m_strName =  pVariable->m_strID + pszAttrID;
		pAttr->m_strID = pVariable->m_strID + pszAttrID;
		pAttr->m_strID = pszAttrID;
		pAttr->SetUse(1);
		AddTail(pAttr);
		pAttr->SetParent(this);
	}
	
	POS pos1 = Find(pAttr);
	POS pos2 = FindIndex(nIndex);
	ChangePosition(pos1, pos2);
	m_nStaticAttrs++;
}

BOOL CRtDataAttributes::BuildExpression()
{
	CRtDataAttribute *pDataAtrr = NULL;
	POS pos  = GetHeadPosition();
	
	while (pos != NULL) 
	{
		pDataAtrr = (CRtDataAttribute*)GetNext(pos);
		
		if (pDataAtrr->BuildExpression()) 
		{
			//break;		
		}
		else
		{
			debug_trace("CRtDataAttributes Build Expression failed!");
		}
	}
	return TRUE;
}

BOOL CRtDataAttributes::InitDataAttributeCalFunc(BOOL bCalUseRecordBuffer)
{
	CRtDataAttribute *pDataAtrr = NULL;
	POS pos  = GetHeadPosition();
	
	while (pos != NULL) 
	{
		pDataAtrr = (CRtDataAttribute*)GetNext(pos);
		
		if (pDataAtrr != NULL) 
		{
			pDataAtrr->InitDataAttributeCalFunc(bCalUseRecordBuffer);	
			
			//初始化CRtVariables的各种属性链表
			InitVariablesAttrList(pDataAtrr);
		}
	}

	InitAssociateAttrs();
	
	return TRUE;
}

void CRtDataAttributes::InitVariablesAttrList(CRtDataAttribute *pAttr)
{
	ASSERT(pAttr != NULL);
	CRtVariables *pVaribles = NULL;
	pVaribles = (CRtVariables *)GetAncestor(RTCLASSID_VARIABLES);

	if (pAttr->IsInstAttr())
	{
		pVaribles->m_listAnalogInstAttrs.AddTail(pAttr);
	}
	else if (pAttr->IsBinaryAttr())
	{
		pVaribles->m_listBinaryInstAttrs.AddTail(pAttr);
	}
	else
	{
		pVaribles->m_listAnalogAttrs.AddTail(pAttr);
	}
}

long CRtDataAttributes::GetAttrCountWithSets()
{
	long nCount = 0;
	CRtDataAttribute *pAttr = NULL;
	POS pos  = GetHeadPosition();

	while(pos != NULL)
	{
		pAttr = (CRtDataAttribute *)GetNext(pos);

		if (pAttr != NULL)
		{
			if ((pAttr->m_pSets != NULL) && (pAttr->m_pSets->GetCount() > 0))
			{
				nCount++;
			}
		}
	}

	return nCount;
}

UINT CRtDataAttributes::GetClassID()
{
	return RTCLASSID_DATAATTRIBUTES;
}
// 
// long CRtDataAttributes::ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode)
// {
// 	return 0;
// }
// 
// CExBaseObject* CRtDataAttributes::CreateNewChild()
// {
// 	return NULL;
// }
// 
// CExBaseObject* CRtDataAttributes::CreateNewChild(LPCTSTR pszClassID)
// {
// 	CRtDataAttribute *pNode = NULL;
// 
// 	if (strcmp(pszClassID,CRtDataAttribute::g_pszKeyDataAttr)==0) 
// 	{ 
// 		pNode =new CRtDataAttribute();
// 	}
// 
// 	return pNode;
// }
// 
// CExBaseObject* CRtDataAttributes::CreateNewChild(long nClassID)
// {
// 	return NULL;
// }
// 
// const char* CRtDataAttributes::GetXmlElementKey()
// {
// 	return g_pszKeyDataAttrs;
// }
// 
// long CRtDataAttributes::WriteOwnXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oElement)
// {
// 	return 0;
// }

void CRtDataAttributes::InitAssociateAttrs()
{
	CRtDataAttribute *pDataAtrr = NULL;
	POS pos  = GetHeadPosition();
	
	while (pos != NULL) 
	{
		pDataAtrr = (CRtDataAttribute*)GetNext(pos);
		InitAssociateAttr(pDataAtrr);
	}
}

void CRtDataAttributes::InitAssociateAttr(CRtDataAttribute *pAttr)
{
	UINT nAssociateAttrID = -1;
	UINT nAttrID = pAttr->m_nAttributeID;
	
	switch(nAttrID)
	{
	case SingleVariableAttrID_EffecPhase:             //1
		nAssociateAttrID = SingleVariableAttrID_EffecValue;
		break;
	case SingleVariableAttrID_FundPhase:            //3
		nAssociateAttrID = SingleVariableAttrID_FundValue;
		break;
	case SingleVariableAttrID_Harm02Phase:        //32
		nAssociateAttrID = SingleVariableAttrID_Harm02Value;
		break;
	case SingleVariableAttrID_Harm03Phase:        //33
		nAssociateAttrID = SingleVariableAttrID_Harm03Value;
		break;
	case SingleVariableAttrID_Harm04Phase:        //34
		nAssociateAttrID = SingleVariableAttrID_Harm04Value;
		break;
	case SingleVariableAttrID_Harm05Phase:        //35
		nAssociateAttrID = SingleVariableAttrID_Harm05Value;
		break;
	case SingleVariableAttrID_Harm06Phase:        //36
		nAssociateAttrID = SingleVariableAttrID_Harm06Value;
		break;
	case SingleVariableAttrID_Harm07Phase:        //37
		nAssociateAttrID = SingleVariableAttrID_Harm07Value;
		break;
	case SingleVariableAttrID_Harm08Phase:        //38
		nAssociateAttrID = SingleVariableAttrID_Harm08Value;
		break;
	case SingleVariableAttrID_Harm09Phase:        //39
		nAssociateAttrID = SingleVariableAttrID_Harm09Value;
		break;
	case SingleVariableAttrID_Harm10Phase:        //40
		nAssociateAttrID = SingleVariableAttrID_Harm10Value;
		break;
	case SingleVariableAttrID_Harm11Phase:        //41
		nAssociateAttrID = SingleVariableAttrID_Harm11Value;
		break;
	case SingleVariableAttrID_Harm12Phase:        //42
		nAssociateAttrID = SingleVariableAttrID_Harm12Value;
		break;
	case SingleVariableAttrID_Harm13Phase:        //43
		nAssociateAttrID = SingleVariableAttrID_Harm13Value;
		break;
	case SingleVariableAttrID_Harm14Phase:        //44
		nAssociateAttrID = SingleVariableAttrID_Harm14Value;
		break;
	case SingleVariableAttrID_Harm15Phase:        //45
		nAssociateAttrID = SingleVariableAttrID_Harm15Value;
		break;
	case SingleVariableAttrID_Harm16Phase:        //46
		nAssociateAttrID = SingleVariableAttrID_Harm16Value;
		break;
	case SingleVariableAttrID_Harm17Phase:        //47
		nAssociateAttrID = SingleVariableAttrID_Harm17Value;
		break;
	case SingleVariableAttrID_Harm18Phase:        //48
		nAssociateAttrID = SingleVariableAttrID_Harm18Value;
		break;
	case SingleVariableAttrID_Harm19Phase:        //49
		nAssociateAttrID = SingleVariableAttrID_Harm19Value;
		break;
	case SingleVariableAttrID_Harm20Phase:        //50
		nAssociateAttrID = SingleVariableAttrID_Harm20Value;
		break;
	case SingleVariableAttrID_Harm21Phase:        //51
		nAssociateAttrID = SingleVariableAttrID_Harm21Value;
		break;
	case SingleVariableAttrID_Harm22Phase:        //52
		nAssociateAttrID = SingleVariableAttrID_Harm22Value;
		break;
	case SingleVariableAttrID_Harm23Phase:        //53
		nAssociateAttrID = SingleVariableAttrID_Harm23Value;
		break;
	case SingleVariableAttrID_Harm24Phase:        //54
		nAssociateAttrID = SingleVariableAttrID_Harm24Value;
		break;
	case SingleVariableAttrID_Harm25Phase:        //55	
		nAssociateAttrID = SingleVariableAttrID_Harm25Value;
		break;
	
	case MultiVariableAttrID_PositiveSequencePhase:        //65	
		nAssociateAttrID = MultiVariableAttrID_PositiveSequence;
		break;
	case MultiVariableAttrID_NegativeSequencePhase:        //66	
		nAssociateAttrID = MultiVariableAttrID_NegativeSequence;
		break;
	case MultiVariableAttrID_ZeroSequencePhase:        //67	
		nAssociateAttrID = MultiVariableAttrID_ZeroSequence;
		break;
	default:
		break;
	}

	if (nAssociateAttrID != -1)
	{
		pAttr->m_pAssociateAttr = FindAttr(nAssociateAttrID);
	}
}
// 
// CExBaseObject* CRtDataAttributes::RTClone()
// {
// 	CRtDataAttributes *pDest = NULL;
// 	pDest = new CRtDataAttributes();
// 	RTCloneOwn(pDest);
// 	RTCloneChildren(pDest);
// 	return pDest;
// }

void CRtDataAttributes::AutofitCreateMultiAttrChild(const CString &strMultiID)
{
	long nLen = 0;
	nLen = strMultiID.GetLength();

	if (nLen == 0)
	{
		return;
	}

	if ((_stricmp(strMultiID.GetString(), U3) == 0) || (_stricmp(strMultiID.GetString(), I3) == 0))
	{
		CreateSequenceAttrs(strMultiID);
	}
	else if ((_stricmp(strMultiID.GetString(), UI) == 0))
	{
		CreateAttrsWithUI(strMultiID);
	}
	else
	{
	}
}

void CRtDataAttributes::CreateSequenceAttrs(const CString &strMultiID)
{
	CRtDataAttribute *pNew = NULL;

	//创建正序分量
	pNew = CreateMultiAttrByAttrID(strMultiID, MultiVariableAttrID_PositiveSequence);
	ASSERT(pNew != NULL);

	//创建负序分量
	pNew = CreateMultiAttrByAttrID(strMultiID, MultiVariableAttrID_NegativeSequence);
	ASSERT(pNew != NULL);

	//创建零序分量
	pNew = CreateMultiAttrByAttrID(strMultiID, MultiVariableAttrID_ZeroSequence);
	ASSERT(pNew != NULL);
}

void CRtDataAttributes::CreateAttrsWithUI(const CString &strMultiID)
{
	CRtDataAttribute *pNew = NULL;

	//创建有功功率
	pNew = CreateMultiAttrByAttrID(strMultiID, MultiVariableAttrID_ActivePower);
	ASSERT(pNew != NULL);

	//创建阻抗
	pNew = CreateMultiAttrByAttrID(strMultiID, MultiVariableAttrID_Impedance);
	ASSERT(pNew != NULL);
}

CRtDataAttribute* CRtDataAttributes::CreateMultiAttrByAttrID(const CString &strMultiID, long nAttrID)
{
	CRtDataAttribute *pNew = NULL;
	
	pNew = new CRtDataAttribute();
	
	if (pNew != NULL)
	{
		pNew->InitByAttrID(strMultiID, nAttrID);
		pNew->CreateMultiAttrSets();
		pNew->SetParent(this);
		AddTail(pNew);
	}

	return pNew;
}

double* CRtDataAttributes::GetValueByAttrID(UINT nAttrID)
{
	double* pValue = NULL;
	CRtDataAttribute* pAttr = FindAttr(nAttrID);
	pValue = pAttr->m_pdValue;

	return pValue;
}

void CRtDataAttributes::SetAttr(CRtDataAttribute* pAttr,long nIndex)
{
	m_paDataAttributes[nIndex]	= pAttr;
}

void CRtDataAttributes::AdjustMultiVariableAttrs()
{
	m_nStaticAttrs = 0;
	long nIndex = 0;

	CRtDataAttribute *pDataAttr = NULL;
	POS pos  = NULL;
	pos = GetHeadPosition();
	
	while (pos != NULL)
	{
		pDataAttr = (CRtDataAttribute*)GetNext(pos);
		m_paDataAttributes[nIndex] = pDataAttr;
		nIndex++;
	}
}

// long CRtDataAttributes::GetAllAttrSetCount()
// {
// 	CRtDataAttribute *pDataAttr = NULL;
// 	POS pos  = GetHeadPosition();
// 	long nSetCount = 0;
// 
// 	while (pos != NULL)
// 	{
// 		pDataAttr = (CRtDataAttribute *)GetNext(pos);
// 		ASSERT(pDataAttr != NULL);
// 		
// 		if (!pDataAttr->IsHarmPhase())
// 		{
// 			if (pDataAttr->m_pSets != NULL)
// 			{
// 				nSetCount += pDataAttr->m_pSets->GetCount();
// 			}
// 		}
// 	}
// 
// 	return nSetCount;
// }

long CRtDataAttributes::GetAllAttrSetCountForSetGrid()
{
	CRtDataAttribute *pDataAttr = NULL;
	POS pos  = GetHeadPosition();
	long nSetCount = 0;
	
	while (pos != NULL)
	{
		pDataAttr = (CRtDataAttribute *)GetNext(pos);
		ASSERT(pDataAttr != NULL);
		
		if (pDataAttr->IsAttrNeededByOnline())
		{
			if (pDataAttr->m_pSets != NULL)
			{
				nSetCount += pDataAttr->m_pSets->GetCount();
			}
		}
	}
	
	return nSetCount;
}

long CRtDataAttributes::GetEffFreInstSetCountForSetGrid()
{
	CRtDataAttribute *pDataAttr = NULL;
	POS pos  = GetHeadPosition();
	long nSetCount = 0;
	
	while (pos != NULL)
	{
		pDataAttr = (CRtDataAttribute *)GetNext(pos);
		ASSERT(pDataAttr != NULL);
		
		if (pDataAttr->IsAttrNeededByOscigraph())
		{
			if (pDataAttr->m_pSets != NULL)
			{
				nSetCount += pDataAttr->m_pSets->GetCount();
			}
		}
	}
	
	return nSetCount;
}

void CRtDataAttributes::CloneRtDataAttributes(CRtDataAttributes* pSrc)
{
	pSrc->m_pClone = this;
	POS pos  = pSrc->GetHeadPosition();

	while(pos != NULL)
	{
		CRtDataAttribute* pAttr = (CRtDataAttribute*)pSrc->GetNext(pos);
		CRtDataAttribute* pNew  = new CRtDataAttribute();
		pNew->SetParent(this);
		pNew->CloneRtDataAttribute(pAttr);			
		AddTail(pNew);
	}

	AdjustStaticAttrs();
}


void CRtDataAttributes::InitAttrsBuffer(long nPoints)
{
	POS pos  = GetHeadPosition();
	CRtDataAttribute* pAttr = NULL;

	while(pos != NULL)
	{
		pAttr = (CRtDataAttribute*)GetNext(pos);
		pAttr->InitAttrBuffer(nPoints);
	}

}


void CRtDataAttributes::SetAttrUse(UINT nAttrID, long nUse)
{
	POS pos  = GetHeadPosition();
	CRtDataAttribute* pAttr = NULL;

	while(pos != NULL)
	{
		pAttr = (CRtDataAttribute*)GetNext(pos);
		
		if (pAttr->m_nAttributeID == nAttrID)
		{
			pAttr->SetUse(nUse);
		}
	}
}

