//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpCapDbConfig.cpp  CEpCapDbConfig


#include "stdafx.h"
#include "EpCapDbConfig.h"

CEpCapDbConfig::CEpCapDbConfig()
{
	//初始化属性

	//初始化成员变量
}

CEpCapDbConfig::~CEpCapDbConfig()
{
}

long CEpCapDbConfig::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEpCapDbConfigXmlRWKeys *pXmlKeys = (CEpCapDbConfigXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEpCapDbConfig::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEpCapDbConfigXmlRWKeys *pXmlKeys = (CEpCapDbConfigXmlRWKeys*)pXmlRWKeys;

	return 0;
}

void CEpCapDbConfig::InitAfterRead()
{
}

BOOL CEpCapDbConfig::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEpCapDbConfig *p = (CEpCapDbConfig*)pObj;

	return TRUE;
}

BOOL CEpCapDbConfig::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEpCapDbConfig *p = (CEpCapDbConfig*)pDest;

	return TRUE;
}

CBaseObject* CEpCapDbConfig::Clone()
{
	CEpCapDbConfig *p = new CEpCapDbConfig();
	Copy(p);
	return p;
}

BOOL CEpCapDbConfig::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CEPCAPDBFILECFG)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CEpCapDbConfig::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEpCapDbConfigXmlRWKeys *pXmlKeys = (CEpCapDbConfigXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEpCapDbFileCfgKey)
	{
		pNew = new CEpCapDbFileCfg();
	}

	return pNew;
}

CExBaseObject* CEpCapDbConfig::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CEPCAPDBFILECFG)
	{
		pNew = new CEpCapDbFileCfg();
	}

	return pNew;
}
