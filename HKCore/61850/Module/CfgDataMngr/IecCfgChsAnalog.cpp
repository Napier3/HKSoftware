//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgChsAnalog.cpp  CIecCfgChsAnalog


#include "stdafx.h"
#include "IecCfgChsAnalog.h"

CIecCfgChsAnalog::CIecCfgChsAnalog()
{
	//初始化属性

	//初始化成员变量
}

CIecCfgChsAnalog::~CIecCfgChsAnalog()
{
}

long CIecCfgChsAnalog::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIecCfgChsAnalog::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

BOOL CIecCfgChsAnalog::IsEqualOwn(CExBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIecCfgChsAnalog *p = (CIecCfgChsAnalog*)pObj;

	return TRUE;
}

BOOL CIecCfgChsAnalog::CopyOwn(CExBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecCfgChsAnalog *p = (CIecCfgChsAnalog*)pDest;

	return TRUE;
}

CExBaseObject* CIecCfgChsAnalog::Clone()
{
	CIecCfgChsAnalog *p = new CIecCfgChsAnalog();
	Copy(p);
	return p;
}

CExBaseObject* CIecCfgChsAnalog::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIecCfgAnalogChKey)
	{
		pNew = new CIecCfgAnalogCh();
	}

	return pNew;
}

CExBaseObject* CIecCfgChsAnalog::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == CFGCLASSID_CIECCFGANALOGCH)
	{
		pNew = new CIecCfgAnalogCh();
	}

	return pNew;
}


CIecCfgDataChBase* CIecCfgChsAnalog::CreateChannel()
{
	CIecCfgDataChBase *pNew = new CIecCfgAnalogCh();
	return pNew;
}