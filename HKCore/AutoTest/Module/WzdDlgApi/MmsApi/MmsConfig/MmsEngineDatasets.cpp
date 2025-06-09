//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//MmsEngineDatasets.cpp  CMmsEngineDatasets


#include "stdafx.h"
#include "MmsEngineDatasets.h"

CMmsEngineDatasets::CMmsEngineDatasets()
{
	//初始化属性

	//初始化成员变量
}

CMmsEngineDatasets::~CMmsEngineDatasets()
{
}

long CMmsEngineDatasets::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CMmsEngineConfigXmlRWKeys *pXmlKeys = (CMmsEngineConfigXmlRWKeys*)pXmlRWKeys;


	return 0;
}

long CMmsEngineDatasets::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CMmsEngineConfigXmlRWKeys *pXmlKeys = (CMmsEngineConfigXmlRWKeys*)pXmlRWKeys;

	return 0;
}

CBaseObject* CMmsEngineDatasets::Clone()
{
	CMmsEngineDatasets *p = new CMmsEngineDatasets();
	Copy(p);
	return p;
}

BOOL CMmsEngineDatasets::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CMmsEngineDatasets *p = (CMmsEngineDatasets*)pDest;

	return TRUE;
}

BOOL CMmsEngineDatasets::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CMmsEngineDatasets *p = (CMmsEngineDatasets*)pObj;

	return TRUE;
}

CExBaseObject* CMmsEngineDatasets::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CMmsEngineConfigXmlRWKeys *pXmlKeys = (CMmsEngineConfigXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCMmsEngineDsCfgKey)
	{
		pNew = new CMmsEngineDsCfg();
	}

	return pNew;
}

CExBaseObject* CMmsEngineDatasets::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == MSCFGCLASSID_CMMSENGINEDSCFG)
	{
		pNew = new CMmsEngineDsCfg();
	}

	return pNew;
}

BOOL CMmsEngineDatasets::IsDatasetUse(const CString &strDsName)
{
	CMmsEngineDsCfg *pFind = NULL;
	CMmsEngineDsCfg *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CMmsEngineDsCfg *)GetNext(pos);

		if (strDsName.Find(p->m_strKey) >= 0)
		{
			pFind = p;
			break;
		}
	}

	if (pFind == NULL)
	{
		return FALSE;
	}

	return pFind->m_nRead;
}

BOOL CMmsEngineDatasets::IsDatasetUse(const char *pDsName)
{
	return IsDatasetUse(CString(pDsName));
}

char* CMmsEngineDatasets::mms_GetDatasetKey(const CString &strDatasetID)
{
	POS pos = GetHeadPosition();
	CMmsEngineDsCfg *p = NULL;
	CMmsEngineDsCfg *pFind = NULL;

	while (pos != NULL)
	{
		p = (CMmsEngineDsCfg*)GetNext(pos);

		if (strDatasetID.Find(p->m_strKey) >= 0)
		{
			pFind = p;
			break;
		}
	}

	if (pFind != NULL)
	{
		const char *pString = pFind->m_strKey.GetString();
		return (char*)pString;
	}
	else
	{
		return NULL;
	}
}

