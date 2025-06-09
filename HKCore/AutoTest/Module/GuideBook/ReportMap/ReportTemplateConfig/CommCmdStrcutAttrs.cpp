//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CommCmdStrcutAttrs.cpp  CCommCmdStrcutAttrs


#include "stdafx.h"
#include "CommCmdStrcutAttrs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCommCmdStrcutAttrs::CCommCmdStrcutAttrs()
{
	//初始化属性

	//初始化成员变量
}

CCommCmdStrcutAttrs::~CCommCmdStrcutAttrs()
{
}

long CCommCmdStrcutAttrs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CReportTemplateConfigXmlRWKeys *pXmlKeys = (CReportTemplateConfigXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CCommCmdStrcutAttrs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CReportTemplateConfigXmlRWKeys *pXmlKeys = (CReportTemplateConfigXmlRWKeys*)pXmlRWKeys;

	return 0;
}

BOOL CCommCmdStrcutAttrs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CCommCmdStrcutAttrs *p = (CCommCmdStrcutAttrs*)pObj;

	return TRUE;
}

BOOL CCommCmdStrcutAttrs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CCommCmdStrcutAttrs *p = (CCommCmdStrcutAttrs*)pDest;

	return TRUE;
}

CBaseObject* CCommCmdStrcutAttrs::Clone()
{
	CCommCmdStrcutAttrs *p = new CCommCmdStrcutAttrs();
	Copy(p);
	return p;
}

CExBaseObject* CCommCmdStrcutAttrs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CReportTemplateConfigXmlRWKeys *pXmlKeys = (CReportTemplateConfigXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCCommCmdStrcutAttrKey)
	{
		pNew = new CCommCmdStrcutAttr();
	}

	return pNew;
}

CExBaseObject* CCommCmdStrcutAttrs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == RPTCFGCLASSID_CCOMMCMDSTRCUTATTR)
	{
		pNew = new CCommCmdStrcutAttr();
	}

	return pNew;
}
