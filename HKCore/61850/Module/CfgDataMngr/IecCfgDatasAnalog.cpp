//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgDatasAnalog.cpp  CIecCfgDatasAnalog


#include "stdafx.h"
#include "IecCfgDatasAnalog.h"

CIecCfgDatasAnalog::CIecCfgDatasAnalog()
{
	//初始化属性

	//初始化成员变量
}

CIecCfgDatasAnalog::~CIecCfgDatasAnalog()
{
}

long CIecCfgDatasAnalog::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfgDatasBase::XmlReadOwn(oNode, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIecCfgDatasAnalog::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfgDatasBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

BOOL CIecCfgDatasAnalog::IsEqualOwn(CExBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CIecCfgDatasBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIecCfgDatasAnalog *p = (CIecCfgDatasAnalog*)pObj;

	return TRUE;
}

BOOL CIecCfgDatasAnalog::CopyOwn(CExBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecCfgDatasBase::CopyOwn(pDest);

	CIecCfgDatasAnalog *p = (CIecCfgDatasAnalog*)pDest;

	return TRUE;
}

CExBaseObject* CIecCfgDatasAnalog::Clone()
{
	CIecCfgDatasAnalog *p = new CIecCfgDatasAnalog();
	Copy(p);
	return p;
}

CExBaseObject* CIecCfgDatasAnalog::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIecCfgDataAnalogKey)
	{
		pNew = new CIecCfgDataAnalog();
	}

	return pNew;
}

CIecCfgDataBase* CIecCfgDatasAnalog::CreateIecCfgData()
{
	CIecCfgDataBase *pNew = new CIecCfgDataAnalog();
	return pNew;
}

