//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SmDbConfig.cpp  CSmDbConfig


#include "stdafx.h"
#include "SmDbConfig.h"

CSmDbConfig::CSmDbConfig()
{
	//初始化属性

	//初始化成员变量
}

CSmDbConfig::~CSmDbConfig()
{
}

long CSmDbConfig::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSmDbConfigXmlRWKeys *pXmlKeys = (CSmDbConfigXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSmDbConfig::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSmDbConfigXmlRWKeys *pXmlKeys = (CSmDbConfigXmlRWKeys*)pXmlRWKeys;

	return 0;
}

void CSmDbConfig::InitAfterRead()
{
}

BOOL CSmDbConfig::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSmDbConfig *p = (CSmDbConfig*)pObj;

	return TRUE;
}

BOOL CSmDbConfig::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSmDbConfig *p = (CSmDbConfig*)pDest;

	return TRUE;
}

CBaseObject* CSmDbConfig::Clone()
{
	CSmDbConfig *p = new CSmDbConfig();
	Copy(p);
	return p;
}

BOOL CSmDbConfig::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CEPCAPDBFILECFG)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSmDbConfig::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSmDbConfigXmlRWKeys *pXmlKeys = (CSmDbConfigXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSmDbFileCfgKey)
	{
		pNew = new CSmDbFileCfg();
	}

	return pNew;
}

CExBaseObject* CSmDbConfig::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CEPCAPDBFILECFG)
	{
		pNew = new CSmDbFileCfg();
	}

	return pNew;
}
