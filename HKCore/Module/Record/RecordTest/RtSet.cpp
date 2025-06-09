// RtSet.cpp: implementation of the CRtSet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RtSet.h"
#include "RtDataAttribute.h"
#include "RtDataAttributes.h"
#include "RtVariable.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const char *CRtSet::g_pszKeyUse   = "use";
const char *CRtSet::g_pszKeyUnit  = "unit";
const char *CRtSet::g_pszKeyValue = "value";
const char *CRtSet::g_pszKeySet   = "set";
const char *CRtSet::g_pszKeyType  = "type";

const char* CRtSet::g_pszKeyHigh	 = "high";
const char* CRtSet::g_pszKeyLow		 = "low";
const char* CRtSet::g_pszKeyMutation = "mutation";

CRtSet::CRtSet()
{
	m_nUse   = 0;
	m_dValue = 0;
	m_nSratupIndex = 0;
	m_nSetType = 0;
}

CRtSet::~CRtSet()
{
}

//重载的方法
UINT CRtSet::GetClassID()
{
	return RTCLASSID_SET;
}
// 
// long CRtSet::ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode)
// {
// 	CExBaseObject::ReadOwnXml(oNode);
// 
// 	CString str;
// 
// 	if (xml_GetAttibuteValue(g_pszKeyUse, oNode, str))
// 	{
// 		m_nUse = atol(str);
// 	}
// 	else
// 	{
// 		debug_trace(".................");
// 	}
// 
// 	if (xml_GetAttibuteValue(g_pszKeyUnit, oNode, m_strUnit))
// 	{
// 	}
// 	else
// 	{
// 		debug_trace(".................");
// 	}
// 
// 	if (xml_GetAttibuteValue(g_pszKeyValue, oNode, str))
// 	{
// 		m_dValue = atof(str);
// 	}
// 	else
// 	{
// 	}
// 
// 	if (xml_GetAttibuteValue(g_pszKeyType, oNode, m_strType))
// 	{
// 		GetSetLongTypeByStringType();
// 	}
// 	else
// 	{
// 		debug_trace(".................");
// 	}
// 
// 	MSXML::IXMLDOMNodePtr firstChild = NULL;
// 	HRESULT hr = oNode->get_firstChild(&firstChild);
// 	
// 	if (SUCCEEDED(hr) && firstChild != NULL)
// 	{
// 		m_oScript.ReadExpNodes(firstChild);
// 		
// 	}
// 
// 	return 1;
// }
// 
// 
// const char* CRtSet::GetXmlElementKey()
// {
// 	return g_pszKeySet;
// }
// 
// long CRtSet::WriteOwnXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oElement)
// {
// 	CExBaseObject::WriteOwnXml(oXMLDoc, oElement);
// 	CString strTemp;
// 
// 	strTemp.Format("%d",m_nUse);
// 
// 	if (strTemp.GetLength() > 0)
// 	{		
// 		oElement->setAttribute(_bstr_t(g_pszKeyUse), _bstr_t(strTemp));
// 	}
// 
// 	if (m_strUnit.GetLength() > 0)
// 	{
// 		oElement->setAttribute(_bstr_t(g_pszKeyUnit), _bstr_t(m_strUnit));
// 	}
// 
// 	strTemp.Format("%f",m_dValue);
// 	
// 	if (strTemp.GetLength() > 0)
// 	{		
// 		oElement->setAttribute(_bstr_t(g_pszKeyValue), _bstr_t(strTemp));
// 	}
// 
// 	MSXML::IXMLDOMElementPtr oScript = NULL;
// 	oScript = oXMLDoc->createElement(_bstr_t(CRtScript::g_pszKeyScript));
// 	m_oScript.WriteExpNodes(oXMLDoc, oScript);
// 	oElement->appendChild(oScript);
// 
// 	return 0;
// }

//试验相关方法
void CRtSet::SetUse(long nUse)
{
	m_nUse = nUse;
	
	CRtDataAttribute *pDataAttr = (CRtDataAttribute *)GetAncestor(RTCLASSID_DATAATTRIBUTE);
	
	if (pDataAttr != NULL)
	{
		pDataAttr->OnSetUseChanged();
	}	
}

BOOL CRtSet::BuildExpression()
{
	if (!(m_oScript.BuildExpression())) 
	{
		debug_trace("CRtSet Build Expression failed");
	}

	return TRUE;
}

BOOL CRtSet::JudgeStartup(long &nStartup)
{
	double dValue = 0;//dValue是属性值与定值的比较值

	if (m_nUse == 0)
	{
		return FALSE;
	}

	m_oScript.RunExpression(dValue);
	//_JudgeStartUpByValue(dValue, nStartup);
	
	return TRUE;
}

BOOL CRtSet::JudgeStartup(long &nStartup,double* pdAttrValue,double* pdMutationValue)
{
	if (m_nUse == 0 )
	{
		return FALSE;
	}

	double dValue = 0;

	if (m_nSetType == SET_TYPE_HIGH)
	{
		if (pdAttrValue == NULL)
		{
			debug_trace("not define attr value !");
		}
		else 
		{
			if (*pdAttrValue > m_dValue)
			{
				dValue = 1;
			}
		}
	}
	else if (m_nSetType == SET_TYPE_LOW)
	{
		if (pdAttrValue == NULL)
		{
			debug_trace("not define attr value !");
		}
		else 
		{
			if (*pdAttrValue < m_dValue)
			{
				dValue = 1;
			}
		}
	}
	else if (m_nSetType == SET_TYPE_MUTATION)
	{
		if (pdMutationValue == NULL)
		{
			debug_trace("not define attr mutation value !");
		}
		else 
		{
			if (*pdMutationValue > m_dValue)
			{
				dValue = 1;
			}
		}
	} 	
	else
	{
		m_oScript.RunExpression(dValue);
	}

	//_JudgeStartUpByValue(dValue, nStartup);
	return TRUE;
}
// 
// void CRtSet::_JudgeStartUpByValue(double dValue, long &nStartup)
// {
// 	if (dValue > 0.001)
// 	{
// 		//判启动后，用于给在线录波对象发送启动开始点的信息
// 		if (m_nSratupIndex == 0)
// 		{
// 			m_nSratupIndex = GenerateStartupIndex();
// 			CRtSets *pSets = (CRtSets *)GetParent();
// 			CRtDataAttribute *pDataAttr = (CRtDataAttribute *)pSets->GetParent();
// 			CRtDataAttributes *pDataAttrs = (CRtDataAttributes *)pDataAttr->GetParent();
// 			CRtVariable *pVariable = (CRtVariable *)pDataAttrs->GetParent();
// 			
// 			RTSTARTUP oStartup;
// 			strcpy(oStartup.pszVariableID, pVariable->m_strID);//pDataAttr->m_strID
// 			oStartup.dSetValue = m_dValue;
// 			strcpy(oStartup.pszSetID, m_strID);
// 			strcpy(oStartup.pszAttrID, pDataAttr->m_strID);
// 			oStartup.dAttrValue = *(pDataAttr->m_pdValue);
// 			strcpy(oStartup.pszRemark, "");
// 			oStartup.nStartupType = 0;			
// 			oStartup.nIndex = m_nSratupIndex;
// 			oStartup.n64StartUpStartPos = CRtMemBufferMngr::g_pRtMemBufferMngr->m_n64CurrCalIndex;
// 			oStartup.n64StartUpReturnPos = 0;
// 			
// 			Mr_InitRtTime(oStartup.tmReturn);
// 			
// 			if (CMrGpsSysTime::g_pMrGpsSysTime != NULL)
// 			{
// 				CMrGpsSysTime::g_pMrGpsSysTime->GetGpsTime(oStartup.tmStart, oStartup.n64StartUpStartPos);
// 			}
// 			else
// 			{
// 				Mr_InitRtTimeCurrTime(oStartup.tmStart);
// 			}
// 			
// 			AddStartUp(&oStartup);
// 		}
// 		else
// 		{
// 		}
// 		
// 		nStartup = 1;
// 	}
// 	else
// 	{
// 		if (m_nSratupIndex > 0)
// 		{
// 			//用于给在线录波对象发送启动结束点的信息
// 			SetStartupReturnPos(m_nSratupIndex, CRtMemBufferMngr::g_pRtMemBufferMngr->m_n64CurrCalIndex);
// 			
// 			//根据m_nSratupIndex设置返回时间
// 			RTTIME ReturnTime;
// 			
// 			if (CMrGpsSysTime::g_pMrGpsSysTime != NULL)
// 			{
// 				CMrGpsSysTime::g_pMrGpsSysTime->GetGpsTime(ReturnTime, CRtMemBufferMngr::g_pRtMemBufferMngr->m_n64CurrCalIndex);
// 			}
// 			else
// 			{
// 				Mr_InitRtTimeCurrTime(ReturnTime);
// 			}
// 			
// 			SetStartupReturnTime(m_nSratupIndex, ReturnTime);
// 			m_nSratupIndex = 0;
// 		}
// 		else
// 		{
// 		}
// 		
// 		nStartup = 0;
// 	}
// }
// 
// BOOL CRtSet::WriteSetValueXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oParent)
// {
// 	CString strTemp;
// 	MSXML::IXMLDOMElementPtr oSet;
// 
// 	oSet = oXMLDoc->createElement(_bstr_t(g_pszKeySet));
// 	oSet->setAttribute(_bstr_t(g_pszKeyID), _bstr_t(m_strID));
// 	oSet->setAttribute(_bstr_t(g_pszKeyUse), m_nUse);
// 	oSet->setAttribute(_bstr_t(g_pszKeyValue), m_dValue);
// 	oParent->appendChild(oSet);
// 	
// 	return TRUE;
// }
// 
// BOOL CRtSet::ReadSetValueXml(MSXML::IXMLDOMNodePtr &oSet)
// {
// 	CString strSetAttr;
// 	
// 	xml_GetAttibuteValue(g_pszKeyUse, oSet, m_nUse);
// 	xml_GetAttibuteValue(g_pszKeyValue, oSet, strSetAttr);
// 	m_dValue = atof(strSetAttr);
// 	
// 	return TRUE;
// }
// 
// long CRtSet::InsertChildrenTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, BOOL bParentExpand)
// {
// 	m_oScript.InsertTreeCtrl(pTreeCtrl, m_hTreeItem, bParentExpand);
// 	return 0;
// }
// 
// CExBaseObject* CRtSet::RTClone()
// {
// 	CRtSet *pNew = NULL;
// 	pNew = new CRtSet();
// 	RTCloneOwn(pNew);
// 	RTCloneChildren(pNew);
// 	return pNew;
// }
// 
// long CRtSet::RTCloneOwn(CExBaseObject* pDest)
// {
// 	ASSERT(pDest != NULL);
// 	CRtSet *pNew = (CRtSet *)pDest;
// 	pNew->m_strID		= m_strID;
// 	pNew->m_strName		= m_strName;
// 	pNew->m_nUse		= m_nUse;
// 	pNew->m_strUnit		= m_strUnit;
// 	pNew->m_dValue		= m_dValue;
// 	pNew->m_strType		= m_strType;
// 	pNew->m_nSetType    = m_nSetType;
// 	if (!m_oScript.Clone(&(((CRtSet *)pDest)->m_oScript)))
// 	{
// 		debug_trace("Clone Script error!");
// 	}
// 
// 	return 0;
// }

long CRtSet::RTUpdateOwnByAutofit(HDINFO &oHDInfo)
{
	CString strTemp;
	
	if (!oHDInfo.bDCTran)
	{
		//Name
		strTemp.Format(m_strName, oHDInfo.nTranIndex, oHDInfo.nTranChIndex + 1);
		m_strName = strTemp;

		//ID
		strTemp.Format(m_strID, oHDInfo.nTranIndex, oHDInfo.nTranChIndex + 1);
		m_strID = strTemp;
	}
	else
	{
		//Name
		strTemp.Format(m_strName, oHDInfo.nDCUIChIndexInTran);
		m_strName = strTemp;

		//ID
		strTemp.Format(m_strID, oHDInfo.nDCUIChIndexInTran);
		m_strID = strTemp;
	}

	m_oScript.RTUpdateOwnByAutofit(oHDInfo);

	return 0;	
}

void CRtSet::GetSetLongTypeByStringType()
{
	if(_stricmp(m_strType.GetString(),g_pszKeyHigh) == 0)
	{
		m_nSetType = SET_TYPE_HIGH;
	}
	else if (_stricmp(m_strType.GetString(),g_pszKeyLow) == 0)
	{
		m_nSetType = SET_TYPE_LOW;
	}
	else if (_stricmp(m_strType.GetString(),g_pszKeyMutation) == 0)
	{
		m_nSetType = SET_TYPE_MUTATION;
	} 
	else
	{
	}
}
