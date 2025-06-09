// RtDataAttribute.cpp: implementation of the CRtDataAttribute class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RtDataAttribute.h"
#include "../MR1200BaseApp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "RtMultiVariable.h"
#include "RtVariables.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// const char *CRtDataAttribute::g_pszKeyDataAttr = "data-attr";
// const char *CRtDataAttribute::g_pszKeyAttrID   = "attr-id";
// const char *CRtDataAttribute::g_pszKeyUse      = "use";
// const char *CRtDataAttribute::g_pszKeyUnit     = "unit";
// const char *CRtDataAttribute::g_pszKeyBufferID = "buf-id";

CRtDataAttribute::CRtDataAttribute()
{
	m_pdValue      = NULL;
	m_pSets        = NULL;
	m_nAttributeID = 0;
	m_nSpyState    = 0;
	m_nUse         = 0;
	m_pfCalFunc    = NULL;
	m_pAttrBuffer = NULL;
	m_pScript = NULL;
	m_pdMutationValue = NULL;
	m_pAssociateAttr  = NULL;

	for (long nIndex = 0;nIndex < 3; nIndex++)
	{
		m_pnInstUse[nIndex] = NULL;
		m_nInstSet[nIndex]  = 0;
	}

	memset(&m_oCalFuncPara, 0, sizeof(RTCALFUNCPARA));

	m_pClone = NULL;
}

CRtDataAttribute::~CRtDataAttribute()
{
	for (long nIndex = 0;nIndex < 3; nIndex++)
	{
		m_pnInstUse[nIndex] = NULL;
		m_nInstSet[nIndex]  = 0;
	}

	if (m_pAttrBuffer != NULL)
	{
		delete m_pAttrBuffer;
		m_pAttrBuffer = NULL;
	}

	m_pClone = NULL;
}

void CRtDataAttribute::SetUse(long nUse)
{
	m_nUse = nUse;

	if (m_pClone != NULL)
	{
		m_pClone->SetUse(nUse);
	}
}

void CRtDataAttribute::SetSpyState(long nSpyState)
{
	m_nSpyState = nSpyState;

	if (m_pClone != NULL)
	{
		m_pClone->SetUse(nSpyState);
	}
}

#ifdef _record_use_all_mode_
BOOL CRtDataAttribute::ReadSetsValueXml(MSXML::IXMLDOMNodePtr &oNode)
{
	xml_GetAttibuteValue(_bstr_t(g_pszKeyUse), oNode, m_nUse);
	xml_GetAttibuteValue(_bstr_t(g_pszKeyUnit), oNode, m_strUnit);

	if (m_pSets == NULL)
	{
		return FALSE;
	}

	MSXML::IXMLDOMNodePtr oSets = oNode->selectSingleNode(_bstr_t(CRtSets::g_pszKeySets));

	if(oSets == NULL)
	{
		return FALSE;
	}

	MSXML::IXMLDOMNodeListPtr &oChildNodes = oSets->GetchildNodes();

	if(oChildNodes == NULL)
	{
		return FALSE;
	}		

	if (!(m_pSets->ReadSetsValueXml(oChildNodes)))
	{
		debug_trace("CRtDataAttribute Read SetsValueXml failed!");
	}

	return TRUE;
}


BOOL CRtDataAttribute::WriteSetsValueXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oParent)
{
	MSXML::IXMLDOMElementPtr oDataAttr;
	oDataAttr = oXMLDoc->createElement(_bstr_t(g_pszKeyDataAttr));
	oDataAttr->setAttribute(_bstr_t(g_pszKeyID), _bstr_t(m_strID));
	oDataAttr->setAttribute(_bstr_t(g_pszKeyUse), m_nUse);
	oDataAttr->setAttribute(_bstr_t(g_pszKeyUnit), _bstr_t(m_strUnit));

	if (m_pSets != NULL)
	{
		m_pSets->WriteSetsValueXml(oXMLDoc, oDataAttr);
	}
	
	oParent->appendChild(oDataAttr);
	
	return TRUE;
}
#endif

//如果定义了脚本，则执行脚本计算功能，否则，调用计算函数进行计算
void CRtDataAttribute::InitCalFuncPara(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos)
{
	m_oCalFuncPara.nBuffer1Len    = pRtAttrCalBufPos->nBuffer1Len;
	m_oCalFuncPara.nBuffer1Pos    = pRtAttrCalBufPos->nBuffer1Pos;
	m_oCalFuncPara.nBuffer2Len    = pRtAttrCalBufPos->nBuffer2Len;
	m_oCalFuncPara.nBuffer2Pos    = pRtAttrCalBufPos->nBuffer2Pos;
	m_oCalFuncPara.nDataLength    = pRtAttrCalBufPos->nDataLength;
	m_oCalFuncPara.nBufferLength  = pRtAttrCalBufPos->nBufferLength;
	m_oCalFuncPara.nDftBuffer1Len = pRtAttrCalBufPos->nDftBuffer1Len;
	m_oCalFuncPara.nDftBuffer1Pos = pRtAttrCalBufPos->nDftBuffer1Pos;
	m_oCalFuncPara.nDftBuffer2Len = pRtAttrCalBufPos->nDftBuffer2Len;
	m_oCalFuncPara.nDftBuffer2Pos = pRtAttrCalBufPos->nDftBuffer2Pos;
	
	long nChIndex = m_oCalFuncPara.nChIndex;
	ASSERT (nChIndex >= 0);

	CRecordTest *pRecordTest = (CRecordTest*)GetAncestor(RTCLASSID_RECORDTEST);

	m_oCalFuncPara.dCeofValue = pRecordTest->g_pCoefValue[nChIndex];
	m_oCalFuncPara.dZeroValue = pRecordTest->g_pZeroValue[nChIndex];
	m_oCalFuncPara.dwSampleRate = pRecordTest->g_nSampleRate;
	m_oCalFuncPara.pCalLenPara = &pRecordTest->m_oRECORD_CAL_LEN_PARA;
}
void CRtDataAttribute::InitCalFuncPara()
{
	long nChIndex = m_oCalFuncPara.nChIndex;
	ASSERT (nChIndex >= 0);

	CRecordTest *pRecordTest = (CRecordTest*)GetAncestor(RTCLASSID_RECORDTEST);

	m_oCalFuncPara.dCeofValue = pRecordTest->g_pCoefValue[nChIndex];
	m_oCalFuncPara.dZeroValue = pRecordTest->g_pZeroValue[nChIndex];
	m_oCalFuncPara.dwSampleRate = pRecordTest->g_nSampleRate;
	m_oCalFuncPara.pCalLenPara = &pRecordTest->m_oRECORD_CAL_LEN_PARA;
}

void CRtDataAttribute::CalValues(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, BOOL bCal, BOOL bCalUseRecordBuffer)
{	
	if (! ( (m_nUse == 1) || (m_nSpyState ==1) ) )
	{
		return;
	}

	if (!bCalUseRecordBuffer)
	{
		//if (m_oCalFuncPara.pnBuffer == NULL)
		if (cal_para_is_buffer_null(m_oCalFuncPara))
		{
			return;
		}
	}


	if (m_pAttrBuffer != NULL)//如果定义了属性缓存，则需要计算属性值
	{
		if (m_pAssociateAttr == NULL)
		{//非关联的属性，例如谐波相位，关联到谐波有效值计算，避免多次计算
			if (m_pScript == NULL)
			{
				if (m_pfCalFunc != NULL && bCal)
				{
					InitCalFuncPara(pRtAttrCalBufPos);
					m_pfCalFunc(&m_oCalFuncPara);
				}
				else
				{
					*m_pdValue = 0;
				}
			}
			else
			{
				m_pScript->RunExpression(*m_pdValue);
			}
		}
		
		if (g_bAddDataToBuffer)
		{
			m_pAttrBuffer->AddValue((float)(*m_pdValue));//添加到属性缓存中
		}
	}
	else
	{
		if (m_pfCalFunc != NULL)
		{
			if (m_pAssociateAttr == NULL)
			{
				if (m_pScript == NULL)
				{
					InitCalFuncPara(pRtAttrCalBufPos);
					m_pfCalFunc(&m_oCalFuncPara);
				}
				else
				{
					m_pScript->RunExpression(*m_pdValue);
				}
			}
		}
	}
}

void CRtDataAttribute::CalValues_Quick(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, BOOL bCal, BOOL bCalUseRecordBuffer)
{	
	if (! ( (m_nUse == 1) || (m_nSpyState ==1) ) )
	{
		return;
	}

	if (!bCalUseRecordBuffer)
	{
		//if (m_oCalFuncPara.pnBuffer == NULL)
		if (cal_para_is_buffer_null(m_oCalFuncPara))
		{
			return;
		}
	}

	ASSERT (m_pAttrBuffer != NULL);
	ASSERT (m_pfCalFunc != NULL);

	if (m_pAttrBuffer == NULL || m_pfCalFunc == NULL/* || m_pAssociateAttr == NULL*/)
	{
		return;
	}

	DWORD dwAttrCalUsePoints = rcd_CalCyclePoints(pRtAttrCalBufPos->dwSampleRate, 50, g_bCarry_For_AttrCalUsePoints);

	InitCalFuncPara(pRtAttrCalBufPos);
	long nIndex=0; 
	long nBufLen = pRtAttrCalBufPos->nBufferLength;
	long nOffset = m_oCalFuncPara.nBuffer1Len;

	for (nIndex=0; nIndex<nBufLen; nIndex++)
	{
		m_oCalFuncPara.nDftBuffer1Pos = nIndex;
		m_pfCalFunc(&m_oCalFuncPara);

		if (g_bAddDataToBuffer)
		{
			m_pAttrBuffer->AddValue((float)(*m_pdValue));//添加到属性缓存中
		}

		if (nIndex+nOffset >= nBufLen)
		{
			break;
		}
	}

	if (g_bAddDataToBuffer)
	{
		for (; nIndex<nBufLen-1; nIndex++)
			m_pAttrBuffer->AddValue((float)(*m_pdValue));
	}
}

void CRtDataAttribute::CalValues_PeakVellay(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, BOOL bCal, BOOL bCalUseRecordBuffer)
{	
	if (!bCalUseRecordBuffer)
	{
		//if (m_oCalFuncPara.pnBuffer == NULL)
		if (cal_para_is_buffer_null(m_oCalFuncPara))
		{
			return;
		}
	}

	ASSERT (m_pfCalFunc != NULL);

	if (m_pfCalFunc == NULL)
	{
		return;
	}

	InitCalFuncPara(pRtAttrCalBufPos);
	long nIndex=0; 
	long nBufLen = pRtAttrCalBufPos->nBufferLength;
	long nOffset = m_oCalFuncPara.nBuffer1Len;

	m_pfCalFunc(&m_oCalFuncPara);
}

void CRtDataAttribute::CalFaultValues(long nBeginPos, long nLen, long nCyclePoints)
{
	CRtDataAttributes *pParent = (CRtDataAttributes*)GetParent();
	ASSERT( pParent != NULL );
	CRtDataAttribute *pSrcAttr = NULL;

	pSrcAttr = pParent->FindFaultSrcAttr(m_nAttributeID);

	if (pSrcAttr == NULL)
	{
		return;
	}

//	ASSERT (m_pAttrBuffer != NULL);

	if (m_pAttrBuffer == NULL)
	{
		return;
	}

	if (nLen <= 0)
	{
		nLen = m_pAttrBuffer->GetBufferLength();
	}

	float *pSrcBuf = pSrcAttr->m_pAttrBuffer->GetBuffer_float();
	float *pFaultBuf = m_pAttrBuffer->GetBuffer_float();
	long nBuffLen = m_pAttrBuffer->GetBufferLength();
	long nEnd = nBeginPos + nLen;
	long nIndex = 0;

	if (pSrcBuf == NULL || pFaultBuf == NULL || nBeginPos >= nBuffLen)
	{
		return;
	}

	nEnd = min(nEnd, nBuffLen);
	float *pSrcCurr = pSrcBuf;
	float *pFaultCurr = pFaultBuf;
	float *pSrcNext = pSrcCurr + nCyclePoints;
	float *pSrcEnd = pSrcCurr + nEnd;

	for (nIndex=nBeginPos; nIndex<nEnd; nIndex++)
	{
		if (pSrcNext >= pSrcEnd)
		{
			break;
		}

		*pFaultCurr = *pSrcNext - *pSrcCurr;
		pFaultCurr++;
		pSrcCurr++;
		pSrcNext++;
	}

	//处理最后一些点  //2020-12-19  lijunqing
	float fLast = *(pFaultCurr - 1);
	while (nIndex < nEnd)
	{
		*pFaultCurr = fLast;
		nIndex++;
	}
}

void CRtDataAttribute::AddValueToAttrBuffer()
{
	if (m_pAttrBuffer != NULL)
	{
		m_pAttrBuffer->AddValue((float)(*m_pdValue));//添加到属性缓存中
	}
}

BOOL CRtDataAttribute::JudgeStartup(long &nStartup)
{
	if (m_pSets == NULL)
	{
		return TRUE;
	}
	
	if (m_nUse == 0)
	{
		return FALSE;
	}

// 	if (!(m_pSets->JudgeStartup(nStartup))) 
// 	{
// 		debug_trace("CRtDataAttribute Judge Startup failed!");
// 	}
	if (!(m_pSets->JudgeStartup(nStartup , m_pdValue , m_pdMutationValue))) 
	{
		debug_trace("CRtDataAttribute Judge Startup failed!");
	}

	return TRUE;
}

void CRtDataAttribute::OnSetUseChanged()
{
	if (m_pSets != NULL)
	{
		m_pSets->IsSetsUsed();
	}
}


double* CRtDataAttribute::GetValueRefByID(const CString &strID)
{
	double *pdValue = NULL;
	
	if (m_strID == strID)
	{
		pdValue = m_pdValue;
	}
	else
	{
		if (m_pSets != NULL)
		{
			CRtSet *pSet = NULL;
			pSet = (CRtSet *)m_pSets->FindByID(strID);

			if (pSet != NULL)
			{
				pdValue = &(pSet->m_dValue);
			}
			else
			{
			}
		}
	}

	return pdValue;
}

double* CRtDataAttribute::GetAttrValueRefByID(const CString &strID)
{
	double *pdValue = NULL;
	
	if (m_strID == strID)
	{
		pdValue = m_pdValue;
	}
	else
	{
	}
	
	return pdValue;
}

double* CRtDataAttribute::GetMutationValueRefByID(const CString &strID)
{
	double *pdValue = NULL;
	
	if (m_strID == strID)
	{
		pdValue = m_pdMutationValue;
	}
	else
	{
		
	}
	
	return pdValue;
}

void CRtDataAttribute::InitBufferMngr(CRtMemBufferMngr *pRtMemBufferMngr)
{
	if (m_strBufferID.GetLength() > 0)
	{
		m_pAttrBuffer = pRtMemBufferMngr->AddMR1200AttrBuffer(m_strBufferID);
	}	
}

BOOL CRtDataAttribute::BuildExpression()
{
	if (m_pSets == NULL)
	{
		return TRUE;
	}
	
	if (!(m_pSets->BuildExpression()))
	{
		debug_trace("CRtDataAttribute Build Expression failed!");
	}

	return TRUE;
}

BOOL CRtDataAttribute::InitDataAttributeCalFunc(BOOL bCalUseRecordBuffer)
{
	CRtVariable *pAncestor = (CRtVariable *)m_pParent->GetParent();
	ASSERT (pAncestor != NULL);
	UINT nClassID = pAncestor->GetClassID();
	
	if (pAncestor != NULL)
	{
		pAncestor->GetCalFuncByAttrID(m_strID, &m_pdValue, &m_pdMutationValue, m_nAttributeID, &m_pfCalFunc, m_oCalFuncPara, bCalUseRecordBuffer);
	
		if (m_pScript != NULL)
		{
			m_pScript->BuildExpression();
		}
	}
	

	//设置瞬时值的信息
	//先将所有的瞬时值的设置设置成NULL
	long nIndex = 0;
	for (nIndex = 0; nIndex < 3; nIndex++)
	{
		m_pnInstUse[nIndex] = NULL;
	}

	if (SingleVariableAttrID_InstValue == m_nAttributeID)
	{
		AnalogInstSet();
	}
	else if ( BinaryVariableAttrID_Raise == m_nAttributeID)
	{
		m_pnInstUse[0] = &m_nUse;
	}
	else if (BinaryVariableAttrID_Fall == m_nAttributeID)
	{
		m_pnInstUse[1] = &m_nUse;
	} 
	else
	{
	}

	return TRUE;
}

UINT CRtDataAttribute::GetClassID()
{
	return RTCLASSID_DATAATTRIBUTE;
}
// 
// #ifdef _record_use_all_mode_
// long CRtDataAttribute::ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode)
// {
// 	CExBaseObject::ReadOwnXml(oNode);
// 	CString str;
// 
// 	xml_GetAttibuteValue(g_pszKeyUse, oNode, m_nUse);
// 	xml_GetAttibuteValue(g_pszKeyUnit, oNode, m_strUnit);
// 	xml_GetAttibuteValue(g_pszKeyAttrID, oNode, m_strID);
// 	xml_GetAttibuteValue(g_pszKeyBufferID, oNode, m_strBufferID);
// 	
// 	m_nAttributeID = GetVariableAttributeID(m_strID);
// 	return 1;
// }
// #endif
// 
// CExBaseObject* CRtDataAttribute::CreateNewChild()
// {
// 	return NULL;
// }
// 
// CExBaseObject* CRtDataAttribute::CreateNewChild(LPCTSTR pszClassID)
// {
// 	CExBaseObject* pNew = NULL;
// 
// #ifdef _record_use_all_mode_
// 
// 	if(strcmp(pszClassID , CRtSets::g_pszKeySets)==0)
// 	{
// 		ASSERT (m_pSets == NULL);
// 
// 		if (m_pSets == NULL)
// 		{
// 			m_pSets = new CRtSets();
// 			pNew = m_pSets;
// 		}
// 	}
// 	else if (strcmp(pszClassID, CRtScriptBase::g_pszKeyScript) == 0)
// 	{
// 		ASSERT (m_pScript == NULL);
// 
// 		if (m_pScript == NULL)
// 		{
// 			m_pScript = new CRtAttrScript();
// 			pNew = m_pScript;
// 		}
// 	}
// #endif
// 
// 	return pNew;
// }
// 
// CExBaseObject* CRtDataAttribute::CreateNewChild(long nClassID)
// {
// 	return NULL;
// }
// 
// #ifdef _record_use_all_mode_
// const char* CRtDataAttribute::GetXmlElementKey()
// {
// 	return g_pszKeyDataAttr;
// }
// #endif

BOOL CRtDataAttribute::IsHarmPhase()
{
	BOOL bIsHarPhase = FALSE;

	if (m_nAttributeID == SingleVariableAttrID_FundPhase)
	{
		bIsHarPhase = TRUE;
	}
	else if ( (m_nAttributeID >= SingleVariableAttrID_Harm02Phase) && (m_nAttributeID <= SingleVariableAttrID_Harm25Phase))
	{
		bIsHarPhase = TRUE;
	}
	else{}

	return bIsHarPhase;
}

// 
// #ifdef _record_use_all_mode_
// long CRtDataAttribute::WriteOwnXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oElement)
// {
// 	CExBaseObject::WriteOwnXml(oXMLDoc, oElement);
// 
// 	CString strTemp;
// 
// 	if (m_strID.GetLength() > 0)
// 	{
// 		oElement->setAttribute(_bstr_t(g_pszKeyAttrID), _bstr_t(m_strID));
// 	}
// 
// 	strTemp.Format("%d",m_nUse);
// 
// 	if (strTemp.GetLength() > 0)
// 	{		
// 		oElement->setAttribute(_bstr_t(g_pszKeyUse), _bstr_t(strTemp));
// 	}
// 
// 	
// 	if (m_strUnit.GetLength() > 0)
// 	{
// 		oElement->setAttribute(_bstr_t(g_pszKeyUnit), _bstr_t(m_strUnit));
// 	}
// 	
// 	return 0;
// }
// #endif
// 
// //树形控件相关的操作
// void CRtDataAttribute::InsertTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, BOOL bParentExpand, HTREEITEM hAfter)
// {
// #ifdef _record_use_all_mode_
// 	CString strItem;
// 
// 	if (m_strBufferID.GetLength() > 0)
// 	{
// 		strItem.Format("%s : attr-buf-id= [%s]", m_strName, m_strBufferID);
// 	}
// 	else
// 	{
// 		strItem = m_strName;
// 	}
// 	
// 	m_hTreeItem = pTreeCtrl->InsertItem(strItem, 0, 0, htiParent, hAfter);
// 	pTreeCtrl->SetItemData(m_hTreeItem,(DWORD)this);
// 	
// 	InsertChildrenTreeCtrl(pTreeCtrl, m_hTreeItem, bParentExpand);
// #endif
// }
// 
// CExBaseObject* CRtDataAttribute::RTClone()
// {
// 	CRtDataAttribute *pDest = NULL;
// #ifdef _record_use_all_mode_
// 	pDest = new CRtDataAttribute();
// 	RTCloneOwn(pDest);
// 	RTCloneChildren(pDest);
// 	pDest->InitAfterClone();
// #endif
// 	return pDest; 
// }
// 
// long CRtDataAttribute::RTCloneOwn(CExBaseObject* pDest)
// {
// 	ASSERT(pDest != NULL);
// 	CRtDataAttribute *pAttribute	= (CRtDataAttribute *)pDest;
// 	pAttribute->m_strName			= m_strName;
// 	pAttribute->m_strID				= m_strID;
// 	pAttribute->m_strBufferID		= m_strBufferID;
// 	pAttribute->m_strUnit			= m_strUnit;
// 	pAttribute->m_nUse				= m_nUse;
// 	pAttribute->m_strID	= m_strID;
// 	pAttribute->m_nAttributeID		= m_nAttributeID;
// 	return 0;
// }
// 
// void CRtDataAttribute::InitAfterClone()
// {
// 	CExBaseObject *pNew = NULL;
// 
// #ifdef _record_use_all_mode_
// 	POS pos  = GetHeadPosition();
// 
// 	while (pos != NULL)
// 	{
// 		pNew = (CExBaseObject*)GetNext(pos);
// 		long nClassID = pNew->GetClassID();
// 
// 		switch(nClassID)
// 		{
// 		case RTCLASSID_SETS:
// 			m_pSets = (CRtSets*)pNew;
// 			break;
// 		case CLASSID_BASECLASS:
// 			m_pScript = (CRtAttrScript*)pNew;
// 			break;
// 		default:
// 			break;
// 		}
// 	}
// #endif
// }

void CRtDataAttribute::InitByAttrID(const CString &strMultiID, long nAttrID)
{
	m_nAttributeID = nAttrID;
	m_strID = g_pszChannelKeyAttrID[nAttrID];
	m_strID = m_strID;
	m_strUnit = InitMultiAttrUnit(strMultiID, nAttrID);
	m_nUse = 0;
	m_nSpyState = 0;
}

void CRtDataAttribute::CreateMultiAttrSets()
{	
	ASSERT (m_pSets == NULL);
	
	if (m_pSets == NULL)
	{
		m_pSets = new CRtSets();		
		ASSERT(m_pSets != NULL);

		m_pSets->CreateMultiAttrSets(m_strID);
		m_pSets->SetParent(this);
		AddTail(m_pSets);
	}
}

CString CRtDataAttribute::InitMultiAttrUnit(const CString &strMultiID, long nAttrID)
{
	CString strUnit = "";

	long nLen = 0;
	nLen = strMultiID.GetLength();
	
	if (nLen == 0)
	{
		return strUnit;
	}
	
	if (_stricmp(strMultiID.GetString(), U3) == 0)
	{
		if ((nAttrID == MultiVariableAttrID_PositiveSequence) || 
			(nAttrID == MultiVariableAttrID_NegativeSequence) || 
			(nAttrID == MultiVariableAttrID_ZeroSequence))
		{
			strUnit = "V";
		}
	}
	else if (_stricmp(strMultiID.GetString(), I3) == 0)
	{
		if ((nAttrID == MultiVariableAttrID_PositiveSequence) || 
			(nAttrID == MultiVariableAttrID_NegativeSequence) || 
			(nAttrID == MultiVariableAttrID_ZeroSequence))
		{
			strUnit = "A";
		}
	}
	else if (_stricmp(strMultiID.GetString(), UI) == 0)
	{
		if (nAttrID == MultiVariableAttrID_ActivePower)
		{
			strUnit = "W";
		}
		else if (nAttrID == MultiVariableAttrID_Impedance)
		{
			strUnit = "Ω";
		}
		else
		{
		}
	}
	else
	{
	}

	return strUnit;
}

long CRtDataAttribute::RTUpdateOwnByAutofit(HDINFO &oHDInfo)
{
	CString strTemp;
	CExBaseObject *pParent = (CExBaseObject *)GetParent();
	CExBaseObject *ppParent = (CExBaseObject *)pParent->GetParent();
	ASSERT(pParent != NULL);
	ASSERT(ppParent != NULL);
	
	if ((ppParent->GetClassID() == RTCLASSID_SINGLEVARIABLE))
	{
		if (!oHDInfo.bDCTran)
		{			
			//Name 
			strTemp.Format(m_strName, oHDInfo.nTranIndex, oHDInfo.nTranChIndex + 1);
			m_strName = strTemp;

			//ID
			strTemp.Format(m_strID, oHDInfo.nTranIndex, oHDInfo.nTranChIndex + 1);
			m_strID = strTemp;
			
			//m_strBufferID
			strTemp.Format(m_strBufferID, oHDInfo.nTranIndex, oHDInfo.nTranChIndex + 1);
			m_strBufferID = strTemp;
		}
		else
		{
			//Name 
			strTemp.Format(m_strName, oHDInfo.nDCUIChIndexInTran);
			m_strName = strTemp;

			//ID
			strTemp.Format(m_strID, oHDInfo.nDCUIChIndexInTran);
			m_strID = strTemp;
			
			//m_strBufferID
			strTemp.Format(m_strBufferID, oHDInfo.nDCUIChIndexInTran);
			m_strBufferID = strTemp;
		}

	}
	else if ((ppParent->GetClassID() == RTCLASSID_BINARYVARIABLE))
	{
		long nIndex = oHDInfo.nTranIndex * oHDInfo.nTranBinaryChCount + oHDInfo.nTranChIndex;

		//Name 
		strTemp.Format(m_strName, nIndex + 1);
		m_strName = strTemp;
		
		//ID
		m_strID = strTemp;

	}
	else
	{
	}
	
	return 0;
}


CString CRtDataAttribute::GetHarmNumID()
{
	CString str = "";
	int nHarm = 0;

	if (IsHarmValueAttr())
	{
		if (IsFundValueAttr())
		{
			nHarm = 1;
		}
		else
		{
			str = m_strID;
			int nLen = str.GetLength();
			nLen -= 5;
			str = str.Left(nLen);
			nLen -= 4;
			str = str.Right(nLen);
			nHarm = atoi(str.GetString());
		}

		str.Format("%d", nHarm);
	}
	else
	{

	}

	return str;
}

CString CRtDataAttribute::GetAttrName()
{
	CString strAttrName = "";
	long nFindIndex = -1;

	for (long nIndex = 0; nIndex< MAX_CHANNEL_ATTRID_KEYS; nIndex++)
	{
		if (_stricmp(m_strID.GetString() , g_pszChannelKeyAttrID[nIndex]) == 0)
		{
			nFindIndex = nIndex;
			break;
		}
	}

	if (nFindIndex >= 0)
	{
#ifdef _record_use_all_mode_
		CString str = gs_strLanguage_AttrName[nFindIndex];
#endif
	}

	return strAttrName;
}
/*
long CRtDataAttribute::JudegeStartupInst(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos)
{
	long nStartUp = 0;
	if (SingleVariableAttrID_InstValue == m_nAttributeID)
	{
		
	}
	else if ( BinaryVariableAttrID_Raise == m_nAttributeID)
	{
		
	}
	else if (BinaryVariableAttrID_Fall == m_nAttributeID)
	{
		
	} 
	else
	{
	}

	return nStartUp;
}
*/
BOOL CRtDataAttribute::JudgeStartupAnalogInst(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, long &nStartup)
{
	if (m_nUse == 0)
	{
		return FALSE;
	}

	long nBeginPos1  = pRtAttrCalBufPos->nBuffer1Pos;
	long nBufferLen1 = pRtAttrCalBufPos->nBuffer1Len;
	long nBeginPos2  = pRtAttrCalBufPos->nBuffer2Pos;
	long nBufferLen2 = pRtAttrCalBufPos->nBuffer2Len; 
	long nBufferLen  = pRtAttrCalBufPos->nBufferLength;
	unsigned short* pBuffer = m_oCalFuncPara.pnBuffer;
	JudgeStartupAnalogInstHigh(nBeginPos1,nBufferLen1,nBeginPos2,nBufferLen2,nBufferLen,pBuffer,nStartup);
	JudgeStartupAnalogInstLow(nBeginPos1,nBufferLen1,nBeginPos2,nBufferLen2,nBufferLen,pBuffer,nStartup);
	JudgeStartupAnalogInstMutation(nBeginPos1,nBufferLen1,nBeginPos2,nBufferLen2,nBufferLen,pBuffer,nStartup);
	return TRUE;
}

BOOL CRtDataAttribute::JudgeStartupBinaryInst(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, long &nStartup)
{
	if (m_nUse == 0)
	{
		return FALSE;
	}

	long nBeginPos1  = pRtAttrCalBufPos->nBuffer1Pos;
	long nBufferLen1 = pRtAttrCalBufPos->nBuffer1Len;
	long nBeginPos2  = pRtAttrCalBufPos->nBuffer2Pos;
	long nBufferLen2 = pRtAttrCalBufPos->nBuffer2Len; 
	long nBufferLen  = pRtAttrCalBufPos->nBufferLength;
	unsigned short* pBuffer = m_oCalFuncPara.pnBuffer;
	short nLastData = GetOldData(nBeginPos1,nBufferLen,pBuffer);
	long nBinaryBitIndex = m_oCalFuncPara.nBinaryBitIndex;

	JudgeStartupBinaryInstJumpUp(nBinaryBitIndex,nLastData,nBeginPos1,nBufferLen1,nBeginPos2,nBufferLen2,nBufferLen,pBuffer,nStartup);
//	JudgeStartupBinaryInstJumpDown(nBinaryBitIndex,nLastData,nBeginPos1,nBufferLen1,nBeginPos2,nBufferLen2,nBufferLen,pBuffer,nStartup);
	return TRUE;
}

short CRtDataAttribute::GetOldData(long nBegin,long nBufferLen,unsigned short* pnBuffer)
{
	short nOldData = 0;

	if (nBegin > 0)
	{
		nOldData = (short)pnBuffer[nBegin - 1];
	}
	else
	{
		nOldData = (short)pnBuffer[nBufferLen - 1];
	}

	return nOldData;
}

void CRtDataAttribute::AnalogInstSet()
{
	CRtSet* pSet = NULL;	
	double dSetValue = 0;
	double dCoef = m_oCalFuncPara.dCeofValue;
	double dZero = m_oCalFuncPara.dZeroValue;
	if (m_pSets != NULL)
	{
		POS pos  = m_pSets->GetHeadPosition();

		while(pos != NULL)
		{
			pSet = (CRtSet*)m_pSets->GetNext(pos);

			if (pSet != NULL)
			{
				dSetValue = (pSet->m_dValue + dZero)/ dCoef;
				if (dSetValue > 32767)
				{
					dSetValue = 32767;
				}
				else if (dSetValue < -32768)
				{
					dSetValue = -32768;
				}
				else
				{
				}

				if (_stricmp(pSet->m_strType.GetString(), CRtSet::g_pszKeyHigh) == 0)
				{
					m_pnInstUse[0] = &(pSet->m_nUse);
					m_nInstSet[0] = (short)dSetValue;
				}
				else if (_stricmp(pSet->m_strType.GetString(), CRtSet::g_pszKeyLow) == 0)
				{
					m_pnInstUse[1] = &(pSet->m_nUse);
					m_nInstSet[1] = (short)dSetValue;
				}
				else if (_stricmp(pSet->m_strType.GetString(), CRtSet::g_pszKeyMutation) == 0)
				{
					m_pnInstUse[2] = &(pSet->m_nUse);
					m_nInstSet[2] = (short)dSetValue;
				} 
				else
				{
				}
			}
		}
	}

}

void CRtDataAttribute::JudgeStartupAnalogInstHigh(long nBegin1,long nLen1,long nBegin2,long nLen2,long nBufferLen,unsigned short* pnBuffer,long &nStartup)
{
	if (nStartup == 1)
	{
		return;
	}

	if (m_pnInstUse[0] != NULL)
	{
		if (*m_pnInstUse[0] == 1)
		{
			short nSetValue = m_nInstSet[0];
			short *pTemp = (SHORT*)&(pnBuffer[nBegin1]);
			short *pEnd = pTemp + nLen1;

			while (pTemp < pEnd)
			{
				if ((0 - *pTemp) > nSetValue)
				{
					nStartup = 1;
					break;
				}

				pTemp++;
			}

			if (nStartup == 0)
			{
				if ((nBegin2 >= 0) && (nLen2 >= 0))
				{
					pTemp = (SHORT*)&(pnBuffer[nBegin2]);
					pEnd = pTemp + nLen2;
					
					while (pTemp < pEnd)
					{
						if ((0 - *pTemp) > nSetValue)//反向放大器
						{
							nStartup = 1;
							break;
						}
						
						pTemp++;
					}
 				}
			}
			
			SetStartupPos((long)(pTemp- (short*)pnBuffer),nStartup);
		}
	}
	else
	{
		debug_trace("not have high instance set");
	}
}

void CRtDataAttribute::JudgeStartupAnalogInstLow(long nBegin1,long nLen1,long nBegin2,long nLen2,long nBufferLen,unsigned short* pnBuffer,long &nStartup)
{
	if (nStartup == 1)
	{
		return;
	}
	
	if (m_pnInstUse[1] != NULL)
	{
		if (*m_pnInstUse[1] == 1)
		{
			short nSetValue = m_nInstSet[1];
			short *pTemp = (SHORT*)&(pnBuffer[nBegin1]);
			short *pEnd = pTemp + nLen1;
			
			while (pTemp < pEnd)
			{
				if ((0 - *pTemp) <= nSetValue)
				{
					nStartup = 1;
					break;
				}
				
				pTemp++;
			}

			if (nStartup == 0)
			{
				if ((nBegin2 >= 0) && (nLen2 >= 0))
				{
					short *pTemp = (SHORT*)&(pnBuffer[nBegin2]);
					short *pEnd = pTemp + nLen2;
					
					while (pTemp < pEnd)
					{
						if ((0 - *pTemp) <= nSetValue)
						{
							nStartup = 1;
							break;
						}
						
						pTemp++;
					}

				}
			}
			
			SetStartupPos((long)(pTemp-(short*)pnBuffer),nStartup);
		}
	}
	else
	{
		debug_trace("not have low instance set");
	}
}

void CRtDataAttribute::JudgeStartupAnalogInstMutation(long nBegin1,long nLen1,long nBegin2,long nLen2,long nBufferLen,unsigned short* pnBuffer,long &nStartup)
{
	if (nStartup == 1)
	{
		return;
	}
	
	short nLastData = GetOldData(nBegin1,nBufferLen,pnBuffer);
	short nOldData = nLastData;

	if (m_pnInstUse[2] != NULL)
	{
		if (*m_pnInstUse[2] == 1)
		{
			short nSetValue = m_nInstSet[2];
			int iVal = 0;
			short *pTemp = (SHORT*)&(pnBuffer[nBegin1]);
			short *pEnd = pTemp + nLen1-1;
			
			while (pTemp < pEnd)
			{
				iVal = *(pTemp+1) - *pTemp; //0 - *pTemp -( 0 - *(pTemp+1) )

				if (iVal < 0)
				{
					iVal = -iVal;
				}

				if (iVal > nSetValue)
				{
					nStartup = 1;
					break;
				}
				
				pTemp++;
			}
		
			if (nStartup == 0)
			{
				if ((nBegin2 >= 0) && (nLen2 >= 0))
				{
					pTemp = (SHORT*)&(pnBuffer[nBegin2]);
					pEnd = pTemp + nLen2-1;
					
					while (pTemp < pEnd)
					{
						iVal = *pTemp-*(pTemp+1);
						
						if (iVal < 0)
						{
							iVal = -iVal;
						}

						if (iVal > nSetValue)
						{
							nStartup = 1;
							break;
						}
						
						pTemp++;
					}
				}
			}
			
			SetStartupPos((long)(pTemp-(short*)pnBuffer),nStartup);
		}
	}
	else
	{
		debug_trace("not have mutation instance set");
	}
}

void CRtDataAttribute::JudgeStartupBinaryInstJumpUp(long nBitIndex,short nOldData,long nBegin1,long nLen1,long nBegin2,long nLen2,long nBufferLen,unsigned short* pnBuffer,long &nStartup)
{
	if (nStartup == 1)
	{
		return;
	}

	unsigned short nLastData = nOldData;

	if (m_pnInstUse[0] != NULL)
	{
		if (*m_pnInstUse[0] == 1)
		{
			long nIndex = 0;
			long nEnd1 = nBegin1 + nLen1;
			unsigned short nData = 0;
			//使处理本位之外的所有位为0
			unsigned short nBitValue = 1;
			nBitValue = nBitValue << nBitIndex; 
			nLastData &= nBitValue;

			unsigned short *pTemp = pnBuffer + nBegin1;
			unsigned short *pEnd = pTemp + nLen1;

			if (nLastData == 0 )
			{
				nLastData = (*pTemp & nBitValue);

				if (nLastData > 0)
				{
					nStartup = 1;
					return;
				}
			}
			else
			{
				nLastData = (*pTemp & nBitValue);
			}

			while (pTemp < pEnd)
			{
				if (nLastData == 0)
				{
					nLastData = (*pTemp & nBitValue);
					
					if (nLastData > 0)
					{
						nStartup = 1;
						break;
					}
				}
				else
				{
					nLastData = (*pTemp & nBitValue);
				}

				pTemp++;
			}
					
			if (nStartup == 0)
			{
				if ((nBegin2 >= 0) && (nLen2 >= 0))
				{
					pTemp = pnBuffer + nBegin2;
					pEnd = pTemp + nLen2;
					
					if (nLastData == 0 )
					{
						nLastData = (*pTemp & nBitValue);
						
						if (nLastData > 0)
						{
							nStartup = 1;
							return;
						}
					}
					else
					{
						nLastData = (*pTemp & nBitValue);
					}
					
					while (pTemp < pEnd)
					{
						if (nLastData == 0)
						{
							nLastData = (*pTemp & nBitValue);
							
							if (nLastData > 0)
							{
								nStartup = 1;
								break;
							}
						}
						else
						{
							nLastData = (*pTemp & nBitValue);
						}

						pTemp++;
					}
				}
			}

			SetStartupPos((long)(pTemp-pnBuffer),nStartup);
		}			
	}
	else
	{
		debug_trace("not have binary jump up attr");
	}
}

void CRtDataAttribute::JudgeStartupBinaryInstJumpDown(long nBitIndex,short nOldData,long nBegin1,long nLen1,long nBegin2,long nLen2,long nBufferLen,unsigned short* pnBuffer,long &nStartup)
{
	if (nStartup == 1)
	{
		return;
	}

	short nLastData = nOldData;
	
	if (m_pnInstUse[1] != NULL)
	{
		if (*m_pnInstUse[1] == 1)
		{
			long nIndex = 0;
			long nEnd1 = nBegin1 + nLen1;
			unsigned short nData = 0;
			//使处理本位之外的所有位为0
			unsigned short nBitValue = 1;
			nBitValue = nBitValue << nBitIndex; 
			nLastData &= nBitValue;
			
			for (nIndex = nBegin1; nIndex < nEnd1; nIndex++)
			{
				nData = pnBuffer[nIndex];
				nData &= nBitValue;
				
				if ((nData == 0) && (nLastData > 0))
				{
					nStartup = 1;
					break;
				}
				else
				{
					nLastData = nData;
				}
			}
			
			if (nStartup == 0)
			{
				if ((nBegin2 >= 0) && (nLen2 >= 0))
				{
					long nEnd2 = nBegin2 + nLen2;
					
					for (nIndex = nBegin2; nIndex < nEnd2; nIndex++)
					{
						nData = pnBuffer[nIndex];
						nData &= nBitValue;
						
						if ((nData > 0) && (nLastData == 0))
						{
							nStartup = 1;
							break;
						}
						else
						{
							nLastData = nData;
						}
					}
				}
			}

			SetStartupPos(nIndex,nStartup);
		}
	}
	else
	{
		debug_trace("not have binary jump down attr");
	}
}

void CRtDataAttribute::CloneRtDataAttribute(CRtDataAttribute* pSrc)
{
	pSrc->m_pClone = this;
	m_nUse = pSrc->GetUse();
	m_nSpyState = pSrc->GetSpyState();
	m_strID = pSrc->m_strID;
	m_nAttributeID = pSrc->m_nAttributeID;
	m_strID = pSrc->m_strID;
	m_strName = pSrc->m_strName;
	m_strUnit = pSrc->m_strUnit;
}

double* CRtDataAttribute::GetCalValue()
{
	double* pdValue = NULL;
	
	if (g_theRecordApp.IsInRecordHoldState())
	{
		if (m_pClone != NULL)
		{
			pdValue = m_pClone->m_pdValue;
		}
	}
	else
	{
		pdValue = m_pdValue;
	}
	
	return pdValue;
}

void CRtDataAttribute::SetStartupPos(long nPos,long nStartup)
{
	if (nStartup == 1)
	{
		CRtVariables* pVariables =(CRtVariables*)GetAncestor(RTCLASSID_VARIABLES);
		ASSERT(pVariables != NULL);
		if (pVariables != NULL)
		{
			pVariables->SetStartupPos(nPos);
		}
	}
}

void CRtDataAttribute::ChangeToMilliUnit()
{
	char ch = m_strUnit.GetAt(0);

	if (ch != 'm' && ch != 'M')
	{			
		m_strUnit = _T("m") + m_strUnit;		
	}
}

void CRtDataAttribute::ChangeToUnit()
{
// 	if (_stricmp(m_strUnit.Left(1), "m") == 0)
// 	{			
// 		m_strUnit.Format("%s", m_strUnit.Right(1));		
// 	}

	m_strUnit.Format("%s", m_strUnit.Right(1).GetString());		
}


void CRtDataAttribute::InitAttrBuffer(long nPoints)
{
	if (m_nUse == 0)
	{
		return;
	}

	if (m_pAttrBuffer == NULL)
	{
		m_pAttrBuffer = new CMemBuffer_Float();
		m_pAttrBuffer->SetBufferLength(nPoints);
	}
}

