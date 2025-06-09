//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfg91StatusDataSet.cpp  CIecCfg91StatusDataSet


#include "stdafx.h"
#include "IecCfg91StatusDataSet.h"

CIecCfg91StatusDataSet::CIecCfg91StatusDataSet()
{
	//初始化属性
	m_nOldData = 0;
	m_nFailure = 0;
	m_nOscillatory = 0;
	m_nInconsistent = 0;
	m_nLeapSecond = 0;
	m_nClockFailure = 0;
	m_nClockNotSynchronized = 0;

// 	m_dwLDName = 0;
// 	m_dwLNName = 0;
// 	m_dwDataSetName = 0;
//	m_dwSmprate = 0;
// 	m_dwVersion = 0;
	m_nValid = 0;

	//初始化成员变量
}

CIecCfg91StatusDataSet::~CIecCfg91StatusDataSet()
{
}

long CIecCfg91StatusDataSet::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

// 	xml_GetAttibuteValue(pXmlKeys->m_strLDNameKey, oNode, m_dwLDName);
// 	xml_GetAttibuteValue(pXmlKeys->m_strLNNameKey, oNode, m_dwLNName);
// 	xml_GetAttibuteValue(pXmlKeys->m_strDataSetNameKey, oNode, m_dwDataSetName);
// 	xml_GetAttibuteValue(pXmlKeys->m_strSmprateKey, oNode, m_dwSmprate);
// 	xml_GetAttibuteValue(pXmlKeys->m_strVersionKey, oNode, m_dwVersion);
	xml_GetAttibuteValue(pXmlKeys->m_strValidKey, oNode, m_nValid);
	xml_GetAttibuteValue(pXmlKeys->m_strObsoleteDataKey, oNode, m_nOldData);
	xml_GetAttibuteValue(pXmlKeys->m_strFaultKey, oNode, m_nFailure);
	xml_GetAttibuteValue(pXmlKeys->m_strOscillationKey, oNode, m_nOscillatory);
	xml_GetAttibuteValue(pXmlKeys->m_strDiscordKey, oNode, m_nInconsistent);
	xml_GetAttibuteValue(pXmlKeys->m_strLeapSecondKey, oNode, m_nLeapSecond);
	xml_GetAttibuteValue(pXmlKeys->m_strReliableClockKey, oNode, m_nClockFailure);
	xml_GetAttibuteValue(pXmlKeys->m_strReferenceSourceSynKey, oNode, m_nClockNotSynchronized);
	return 0;
}

long CIecCfg91StatusDataSet::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

// 	xml_SetAttributeValue(pXmlKeys->m_strLDNameKey, oElement, m_dwLDName);
// 	xml_SetAttributeValue(pXmlKeys->m_strLNNameKey, oElement, m_dwLNName);
// 	xml_SetAttributeValue(pXmlKeys->m_strDataSetNameKey, oElement, m_dwDataSetName);
// 	xml_SetAttributeValue(pXmlKeys->m_strSmprateKey, oElement, m_dwSmprate);
// 	xml_SetAttributeValue(pXmlKeys->m_strVersionKey, oElement, m_dwVersion);
	xml_SetAttributeValue(pXmlKeys->m_strValidKey, oElement, m_nValid);
	xml_SetAttributeValue(pXmlKeys->m_strObsoleteDataKey, oElement, m_nOldData);
	xml_SetAttributeValue(pXmlKeys->m_strFaultKey, oElement, m_nFailure);
	xml_SetAttributeValue(pXmlKeys->m_strOscillationKey, oElement, m_nOscillatory);
	xml_SetAttributeValue(pXmlKeys->m_strDiscordKey, oElement, m_nInconsistent);
	xml_SetAttributeValue(pXmlKeys->m_strLeapSecondKey, oElement, m_nLeapSecond);
	xml_SetAttributeValue(pXmlKeys->m_strReliableClockKey, oElement, m_nClockFailure);
	xml_SetAttributeValue(pXmlKeys->m_strReferenceSourceSynKey, oElement, m_nClockNotSynchronized);
	return 0;
}

BOOL CIecCfg91StatusDataSet::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIecCfg91StatusDataSet *p = (CIecCfg91StatusDataSet*)pObj;

// 	if(m_dwLDName != p->m_dwLDName)
// 	{
// 		return FALSE;
// 	}
// 
// 	if(m_dwLNName != p->m_dwLNName)
// 	{
// 		return FALSE;
// 	}
// 
// 	if(m_dwDataSetName != p->m_dwDataSetName)
// 	{
// 		return FALSE;
// 	}
// 
// 	if(m_dwSmprate != p->m_dwSmprate)
// 	{
// 		return FALSE;
// 	}
// 
// 	if(m_dwVersion != p->m_dwVersion)
// 	{
// 		return FALSE;
// 	}

	if(m_nValid != p->m_nValid)
	{
		return FALSE;
	}

	if(m_nOldData != p->m_nOldData)
	{
		return FALSE;
	}

	if(m_nFailure != p->m_nFailure)
	{
		return FALSE;
	}

	if(m_nOscillatory != p->m_nOscillatory)
	{
		return FALSE;
	}

	if(m_nInconsistent != p->m_nInconsistent)
	{
		return FALSE;
	}

	if(m_nLeapSecond != p->m_nLeapSecond)
	{
		return FALSE;
	}

	if(m_nClockFailure != p->m_nClockFailure)
	{
		return FALSE;
	}

	if(m_nClockNotSynchronized != p->m_nClockNotSynchronized)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIecCfg91StatusDataSet::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecCfg91StatusDataSet *p = (CIecCfg91StatusDataSet*)pDest;

// 	p->m_dwLDName = m_dwLDName;
// 	p->m_dwLNName = m_dwLNName;
// 	p->m_dwDataSetName = m_dwDataSetName;
// 	p->m_dwSmprate = m_dwSmprate;
// 	p->m_dwVersion = m_dwVersion;
	p->m_nValid = m_nValid;
	p->m_nOldData = m_nOldData;
	p->m_nFailure = m_nFailure;
	p->m_nOscillatory = m_nOscillatory;
	p->m_nInconsistent = m_nInconsistent;
	p->m_nLeapSecond = m_nLeapSecond;
	p->m_nClockFailure = m_nClockFailure;
	p->m_nClockNotSynchronized = m_nClockNotSynchronized;
	return TRUE;
}

CBaseObject* CIecCfg91StatusDataSet::Clone()
{
	CIecCfg91StatusDataSet *p = new CIecCfg91StatusDataSet();
	Copy(p);
	return p;
}

CExBaseObject* CIecCfg91StatusDataSet::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIecCfg91StatusDataSetChKey)
	{
		pNew = new CIecCfg91StatusDataSetCh();
	}

	return pNew;
}

CExBaseObject* CIecCfg91StatusDataSet::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == CFGCLASSID_CIECCFG91STATUSDATASETCH)
	{
		pNew = new CIecCfg91StatusDataSetCh();
	}

	return pNew;
}


void CIecCfg91StatusDataSet::InitAfterRead()
{
	SetChCount(16);
}

void CIecCfg91StatusDataSet::SetChCount(long nCount)
{
	long nCurrCount = GetCount();

	if (nCurrCount == nCount)
	{
		return;
	}

	if (nCount < nCurrCount)
	{
		CExBaseList listRemove;
		RemoveTail(0, nCurrCount - nCurrCount, listRemove);
		listRemove.DeleteAll();
		return;
	}

	nCount -= nCurrCount;
	long nIndex = 0;
	CIecCfg91StatusDataSetCh *pCh = NULL;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		pCh = new CIecCfg91StatusDataSetCh;
		AddNewChild(pCh);
	}
}

DWORD CIecCfg91StatusDataSet::Get_Q()
{
	long nIndex = 0;
	CIecCfg91StatusDataSetCh *pCh = NULL;
	POS pos = GetHeadPosition();
	DWORD dwQ = 0;
	DWORD dwQCh = 1;

	while (pos != NULL)
	{
		pCh = (CIecCfg91StatusDataSetCh*)GetNext(pos);
		
		if (pCh->m_nQValue == 1)
		{
			dwQ += dwQCh;
		}

		dwQCh *= 2;
	}

	return dwQ;
}


DWORD CIecCfg91StatusDataSet::Get_S_SetByUser()
{
	long nIndex = 0;
	CIecCfg91StatusDataSetCh *pCh = NULL;
	POS pos = GetHeadPosition();
	DWORD dwS = 0;
	DWORD dwSCh = 1;

	while (pos != NULL)
	{
		pCh = (CIecCfg91StatusDataSetCh*)GetNext(pos);

		if (pCh->m_nSValue > 0) //== 2)
		{
			dwS += dwSCh;
		}

		dwSCh *= 2;
	}

	return dwS;
}

