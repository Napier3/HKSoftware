// RtMultiVariable.cpp: implementation of the CRtMultiVariable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RtMultiVariable.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
// const char *CRtMultiVariable::g_pszKeyMultiVariable = "multi-variable";
// const char *CRtMultiVariable::g_pszKeyDCAC = "dc-ac";

CRtMultiVariable::CRtMultiVariable()
{
}

CRtMultiVariable::~CRtMultiVariable()
{
}
// 
// //重载方法
// long CRtMultiVariable::ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode)
// {
// 	CRtVariable::ReadOwnXml(oNode);
// 
// 	if (!xml_GetAttibuteValue(g_pszKeyDCAC, oNode, m_strDCAC))
// 	{
// 		debug_trace("\nGet AttibuteValue-DCAC of CRtMultiVariable failed!\n");
// 	}
// 	
// 	return 0;
// }
// 
// const char* CRtMultiVariable::GetXmlElementKey()
// {
// 	return g_pszKeyMultiVariable;
// }
// 
// long CRtMultiVariable::WriteOwnXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oElement)
// {
// 	CRtVariable::WriteOwnXml(oXMLDoc, oElement);
// 
// 	if (m_strDCAC.GetLength() > 0)
// 	{
// 		oElement->setAttribute(_bstr_t(g_pszKeyDCAC), _bstr_t(m_strDCAC));
// 		
// 	}
// 	return 0;
// }
// 
// BOOL CRtMultiVariable::ReadSetsValueXml(MSXML::IXMLDOMNodePtr &oNode)
// {
// 	CRtVariable::ReadSetsValueXml(oNode);
// 	return TRUE;
// }
// 
// BOOL CRtMultiVariable::WriteSetsValueXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oParent)
// {
// 	MSXML::IXMLDOMElementPtr oMultiVariable;
// 	oMultiVariable = oXMLDoc->createElement(_bstr_t(g_pszKeyMultiVariable));
// 
// 	if(oMultiVariable != NULL)
// 	{
// 		oMultiVariable->setAttribute(_bstr_t(g_pszKeyID), _bstr_t(m_strID));
// 		oMultiVariable->setAttribute(_bstr_t(g_pszKeyName), _bstr_t(m_strName));
// 		oMultiVariable->setAttribute(_bstr_t(g_pszKeyType), _bstr_t(RT_GetStringUIBType(m_nType)));
// 		oMultiVariable->setAttribute(_bstr_t(g_pszKeyDCAC), _bstr_t(m_strDCAC));
// 		oMultiVariable->setAttribute(_bstr_t(g_pszKeyVariableUse), m_nVariableUse);
// 	}
// 
// 	CRtChannels *pChans = m_pChannels;
// 
// 	if(pChans != NULL)
// 	{
// 		pChans->WriteSetsValueXml(oXMLDoc, oMultiVariable);
// 	}
// 
// 	CRtDataAttributes *pDataAttrs = m_pDataAttrs;
// 	
// 	if (pDataAttrs != NULL)
// 	{
// 		pDataAttrs->WriteSetsValueXml(oXMLDoc, oMultiVariable);
// 	}
// 	
// 	oParent->appendChild(oMultiVariable);
// 	return TRUE;
// }

BOOL CRtMultiVariable::GetCalFuncByAttrID(const CString &strAttrID, double **ppdValue,
										  double **ppdMutationValue, UINT &nAttrID, 
										  CALFUNC **ppCalFunc, RTCALFUNCPARA &oRtCalFuncPara, BOOL bCalUseRecordBuffer)
{
	long nCount = MAX_CHANNEL_ATTRID_KEYS;
	nAttrID =GetVariableAttributeID(strAttrID.GetString());
	long nIndex = 0;

	if (nAttrID != -1)
	{
		*ppdValue = ( &(m_oCurrValue.dFrequency) + nAttrID);
		*ppdMutationValue = ( &(m_oMutationValue.dFrequency) + nAttrID);
	}
	else
	{
		*ppdValue = NULL;
		*ppdMutationValue = NULL;
	}
	
	memset(&oRtCalFuncPara, 0, sizeof(RTCALFUNCPARA));
	oRtCalFuncPara.pRtChAttrVal = &m_oCurrValue;

	if (m_pChannels != NULL)
	{
		oRtCalFuncPara.nChanCount = m_pChannels->GetCount();
		for(nIndex = 0; nIndex < oRtCalFuncPara.nChanCount ; nIndex ++)
		{
			CRtChannel* pChannel = (CRtChannel*)m_pChannels->GetAt(nIndex);
			CRtVariable* pVariable = pChannel->m_pAttachVariable;
			oRtCalFuncPara.pRtChanAttr[nIndex] = &(pVariable->m_oCurrValue);
		}
	}
	
	switch(nAttrID)
	{
	case MultiVariableAttrID_Impedance :             //0
		*ppCalFunc = RT_CalImpedance    ;//计算阻抗的函数
		break;
	case MultiVariableAttrID_PositiveSequence:       //1
		*ppCalFunc = RT_CalPositiveSequence;
		break;
	case MultiVariableAttrID_NegativeSequence:       //2
		*ppCalFunc = RT_CalNegativeSequence;
		break;
	case MultiVariableAttrID_ZeroSequence:           //3
		*ppCalFunc = RT_CalZeroSequence;
		break;
	case MultiVariableAttrID_ActivePower:            //4
		*ppCalFunc = RT_CalActivePower;
		break;
	case MultiVariableAttrID_ReactivePower:          //5
		*ppCalFunc = RT_CalReactivePower;
		break;
	case MultiVariableAttrID_ApparentPower:          //6
		*ppCalFunc = RT_CalApparentPower;
		break;
	case MultiVariableAttrID_ThreePhaseAverageValue: //7
		*ppCalFunc = RT_CalReserve01Value;
		break;
	case MultiVariableAttrID_PositiveSequencePhase:        //65	
		*ppCalFunc = NULL;
		break;
	case MultiVariableAttrID_NegativeSequencePhase:        //66	
		*ppCalFunc = NULL;
		break;
	case MultiVariableAttrID_ZeroSequencePhase:        //67	
		*ppCalFunc = NULL;
		break;
	case MultiVariableAttrID_Reserve05Value:         //11
		*ppCalFunc = RT_CalReserve05Value;
		break;
	case MultiVariableAttrID_Reserve06Value:         //12
		*ppCalFunc = RT_CalReserve06Value;
		break;
	case MultiVariableAttrID_Reserve07Value:         //13
		*ppCalFunc = RT_CalReserve07Value;
		break;
	case MultiVariableAttrID_Reserve08Value:         //14
		*ppCalFunc = RT_CalReserve08Value;
		break;
// 	case MultiVariableAttrID_Reserve09Value:         //15
// 		*ppCalFunc = RT_CalReserve09Value;
// 		break;
// 	case MultiVariableAttrID_Reserve10Value:         //16
// 		*ppCalFunc = RT_CalReserve10Value;
// 		break;	
	}
	return TRUE;
}

void CRtMultiVariable::AutofitCreateMultiNewChild(const CString & strMultiID, char **szAutoMultiChsName)
{
	CExBaseObject *pNew = NULL;
	
	//创建m_pChannels
	if (m_pChannels == NULL)
	{
		m_pChannels = new CRtChannels();
		ASSERT(m_pChannels != NULL);
		pNew = m_pChannels;
		m_pChannels->SetParent(this);
		AddTail(pNew);
		m_pChannels->AutofitCreateMultiChChild(strMultiID, szAutoMultiChsName);
	}
	else
	{
	}

	//创建m_pDataAttrs
	if (m_pDataAttrs == NULL)
	{
		m_pDataAttrs = new CRtDataAttributes();
		ASSERT(m_pDataAttrs != NULL);
		pNew = m_pDataAttrs;
		m_pDataAttrs->SetParent(this);
		AddTail(pNew);
		m_pDataAttrs->AutofitCreateMultiAttrChild(strMultiID);
	}
	else
	{
	}
}

void CRtMultiVariable::UpdateStrNameByChannels()
{
	if (m_pChannels == NULL)
	{
		return;
	}

	CString strName;
	CRtChannel *pChannel = NULL;
	long nCount = m_pChannels->GetCount();

	for(long nIndex = 0; nIndex < nCount; nIndex++)
	{
		pChannel = (CRtChannel *)m_pChannels->GetAt(nIndex);
		
		if (pChannel != NULL)
		{
			strName += pChannel->m_strID;

			if (nIndex < (nCount - 1))
			{
				strName += "-";
			}
		}
	}

	m_strName = strName;
}

CString CRtMultiVariable::GetUnitString()
{
	CString strUnit = "";
	ASSERT(m_pDataAttrs != NULL);	
	CRtDataAttribute *pData = m_pDataAttrs->FindByAttrID(g_pszChannelKeyAttrID[MultiVariableAttrID_ThreePhaseAverageValue]);
	
	if(pData != NULL)
	{
		strUnit = pData->m_strUnit;
	}
	
	return strUnit;
}
