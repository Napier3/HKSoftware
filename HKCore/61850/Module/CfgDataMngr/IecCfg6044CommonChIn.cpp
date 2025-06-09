//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfg6044Ch.cpp  CIecCfg6044Ch


#include "stdafx.h"
#include "IecCfg6044CommonChIn.h"

CIecCfg6044CommonChIn::CIecCfg6044CommonChIn()
{
	m_nAccuratyLevel = 0;
}

CIecCfg6044CommonChIn::~CIecCfg6044CommonChIn()
{
}

long CIecCfg6044CommonChIn::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfg6044CommonCh::XmlReadOwn(oNode, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;
	xml_GetAttibuteValue(pXmlKeys->m_strCIecCfgAccuracyLevelKey, oNode, m_nAccuratyLevel);

	return 0;
}

long CIecCfg6044CommonChIn::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfg6044CommonCh::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strCIecCfgAccuracyLevelKey, oElement, m_nAccuratyLevel);
	return 0;
}

BOOL CIecCfg6044CommonChIn::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CIecCfg6044CommonCh::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIecCfg6044CommonChIn *p = (CIecCfg6044CommonChIn*)pObj;

	if(m_nAccuratyLevel != p->m_nAccuratyLevel)
	{
		return FALSE;
	}


	return TRUE;
}

BOOL CIecCfg6044CommonChIn::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecCfg6044CommonCh::CopyOwn(pDest);

	CIecCfg6044CommonChIn *p = (CIecCfg6044CommonChIn*)pDest;
	p->m_nAccuratyLevel = m_nAccuratyLevel;

	return TRUE;
}

CBaseObject* CIecCfg6044CommonChIn::Clone()
{
	CIecCfg6044CommonChIn *p = new CIecCfg6044CommonChIn();
	Copy(p);
	return p;
}

