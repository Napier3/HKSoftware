// RtSets.cpp: implementation of the CRtSets class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RtSets.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#include "RtDataAttribute.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
const char *CRtSets::g_pszKeySets = "sets";

CRtSets::CRtSets()
{
	m_strName = "RtSets";
	m_strID = m_strName;
}

CRtSets::~CRtSets()
{
}

//重载的方法
UINT CRtSets::GetClassID()
{
	return RTCLASSID_SETS;
}
// 
// long CRtSets::ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode)
// {
// 	return 0;
// }
// 
// CExBaseObject* CRtSets::CreateNewChild()
// {
// 	return NULL;
// }
// 
// CExBaseObject* CRtSets::CreateNewChild(LPCTSTR pszClassID)
// {
// 	CExBaseObject *pNode = NULL;
// 
// 	if (strcmp(pszClassID, CRtSet::g_pszKeySet) == 0)
// 	{
// 		pNode = new CRtSet();
// 	}
// 
// 	return pNode;
// }
// 
// CExBaseObject* CRtSets::CreateNewChild(long nClassID)
// {
// 	return NULL;
// }
// 
// const char* CRtSets::GetXmlElementKey()
// {
// 	return g_pszKeySets;
// }
// 
// long CRtSets::WriteOwnXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oElement)
// {
// 	return 0;
// }
// 
// //试验相关方法
// BOOL CRtSets::ReadSetsValueXml(MSXML::IXMLDOMNodeListPtr &oNodes)
// {
// 	int nCount = oNodes->Getlength();
// 	int nIndex = 0;
// 	MSXML::IXMLDOMNodePtr oNode = NULL;		
// 	CRtSet *pSet = NULL;
// 	CString strID;
// 	
// 	for(nIndex = 0; nIndex < nCount; nIndex++)
// 	{
// 		oNode = oNodes->Getitem(nIndex);
// 		xml_GetAttibuteValue(CRtSet::g_pszKeyID, oNode, strID);
// 		pSet = (CRtSet *)FindByID(strID);
// 
// 		if (pSet != NULL)
// 		{
// 			pSet->ReadSetValueXml(oNode);	
// 		}		
// 	}
// 
// 	return TRUE;
// }
// 
// BOOL CRtSets::WriteSetsValueXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oParent)
// {
// 	MSXML::IXMLDOMElementPtr oSets;
// 	oSets = oXMLDoc->createElement(_bstr_t(g_pszKeySets));
// 	
// 	CRtSet *pSet = NULL;
// 	POS pos  = GetHeadPosition();
// 
// 	while (pos != NULL)
// 	{
// 		pSet = (CRtSet *)GetNext(pos);
// 
// 		if (pSet != NULL) 
// 		{
// 			pSet->WriteSetValueXml(oXMLDoc, oSets);
// 		}
// 	}
// 	
// 	oParent->appendChild(oSets);
// 	return TRUE;
// }

BOOL CRtSets::JudgeStartup(long &nStartup)
{
	CRtSet *pSet = NULL;
	POS pos  = GetHeadPosition();

	while (pos != NULL)
	{
		pSet = (CRtSet *)GetNext(pos);
		
		if (pSet != NULL)
		{
			pSet->JudgeStartup(nStartup);
		}
	}

	return TRUE;
}

BOOL CRtSets::JudgeStartup(long &nStartup,double* pdAttrValue,double* pdMutationValue)
{
	long nStartupTemp = nStartup;
	CRtSet *pSet = NULL;
	POS pos  = GetHeadPosition();
	
	while (pos != NULL)
	{
		pSet = (CRtSet *)GetNext(pos);
		
		if (pSet != NULL)
		{
			pSet->JudgeStartup(nStartupTemp , pdAttrValue , pdMutationValue);

			if (nStartupTemp == 1)
			{
				nStartup = 1;
			}
		}
	}

	return TRUE;
}

BOOL CRtSets::BuildExpression()
{
	CRtSet *pSet = NULL;
	POS pos  = GetHeadPosition();

	while (pos != NULL) 
	{
		pSet = (CRtSet *)GetNext(pos);
		
		if (pSet->BuildExpression()) 
		{
			//break;		
		}
		else
		{
			debug_trace("CRtSets Build Expression failed!");
		}
		
	}

	return TRUE;
}

void CRtSets::IsSetsUsed()
{
	long nUse = 0;	
	long nIndex = 0;
	CRtSet *pSet = NULL;

	CRtDataAttribute *pDataAttr = (CRtDataAttribute *)GetParent();	
	POS pos  = GetHeadPosition();
	
	while (pos != NULL)
	{
		pSet = (CRtSet *)GetNext(pos);
		
		if (pSet->m_nUse > 0)
		{
			nUse = 1;
			break;
		}
		
	}
	
	if (nUse > 0 || pDataAttr->GetSpyState() > 0)
	{
		pDataAttr->SetUse(1);
	}
	else
	{
		pDataAttr->SetUse(0);
	}
}
// 
// CExBaseObject* CRtSets::RTClone()
// {
// 	CRtSets *pNew = NULL;
// 	pNew = new CRtSets();
// 	RTCloneOwn(pNew);
// 	RTCloneChildren(pNew);
// 	return pNew;
// }

void CRtSets::ResetUse()
{
	CRtSet *pSet = NULL;
	POS pos  = GetHeadPosition();
	
	while (pos != NULL)
	{
		pSet = (CRtSet *)GetNext(pos);
		
		if (pSet != NULL)
		{
			pSet->SetUse(0);
		}		
	}
}

CRtSet* CRtSets::FindSetByType(const char* strType)
{
	CRtSet* pSet = NULL;
	CRtSet* pFind = NULL;

	POS pos  = GetHeadPosition();
	
	while (pos != NULL)
	{
		pSet = (CRtSet *)GetNext(pos);
		
		if (pSet != NULL)
		{
			if (_stricmp(strType,pSet->m_strType.GetString()) == 0)
			{
				pFind =  pSet;
				break;
			}
		}		
	}

	return pFind;
}

void CRtSets::CreateMultiAttrSets(const CString &strAttrID)
{
	//创建定值高值
	CreateSetHighByAttrID(strAttrID);

	//创建定值低值
	CreateSetLowByAttrID(strAttrID);

	//创建定值突变值
	CreateSetMutationByAttrID(strAttrID);
}

//创建定值高值
void CRtSets::CreateSetHighByAttrID(const CString &strAttrID)
{
	CRtSet *pNew = NULL;
	CString str;
    str.Format("%s%s", strAttrID.GetString(), CRtSet::g_pszKeyHigh);
	pNew = new CRtSet();
	
	if (pNew != NULL)
	{
		pNew->m_strType = CRtSet::g_pszKeyHigh;
		pNew->m_strID = str;
		pNew->m_strUnit = "";
		pNew->m_nUse = 0;
		pNew->m_dValue = 100.0;

		pNew->SetParent(this);
		AddTail(pNew);
	}
}

//创建定值低值
void CRtSets::CreateSetLowByAttrID(const CString &strAttrID)
{
	CRtSet *pNew = NULL;
	CString str;
    str.Format("%s%s", strAttrID.GetString(), CRtSet::g_pszKeyLow);
	pNew = new CRtSet();
	
	if (pNew != NULL)
	{
		pNew->m_strType = CRtSet::g_pszKeyLow;
		pNew->m_strID = str;
		pNew->m_strUnit = "";
		pNew->m_nUse = 0;
		pNew->m_dValue = 0.0;
		
		pNew->SetParent(this);
		AddTail(pNew);
	}
}

//创建定值突变值
void CRtSets::CreateSetMutationByAttrID(const CString &strAttrID)
{
	CRtSet *pNew = NULL;
	CString str;
    str.Format("%s%s", strAttrID.GetString(), CRtSet::g_pszKeyMutation);
	pNew = new CRtSet();
	
	if (pNew != NULL)
	{
		pNew->m_strType = CRtSet::g_pszKeyMutation;
		pNew->m_strID = str;
		pNew->m_strUnit = "";
		pNew->m_nUse = 0;
		pNew->m_dValue = 100.0;
		
		pNew->SetParent(this);
		AddTail(pNew);
	}
}
