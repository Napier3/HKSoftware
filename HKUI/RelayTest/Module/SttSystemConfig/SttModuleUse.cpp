//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttModuleUse.cpp  CSttModuleUse


#include "stdafx.h"
#include "SttModuleUse.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttModuleUse::CSttModuleUse()
{
	//初始化属性

	//初始化成员变量
}

CSttModuleUse::~CSttModuleUse()
{
}

long CSttModuleUse::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttSystemConfigXmlRWKeys *pXmlKeys = (CSttSystemConfigXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttModuleUse::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttSystemConfigXmlRWKeys *pXmlKeys = (CSttSystemConfigXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttModuleUse::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
	}
	else if(oBinaryBuffer.IsReadMode())
	{
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
	}
	return 0;
}

void CSttModuleUse::InitAfterRead()
{
}

BOOL CSttModuleUse::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSttModuleUse *p = (CSttModuleUse*)pObj;

	return TRUE;
}

BOOL CSttModuleUse::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttModuleUse *p = (CSttModuleUse*)pDest;

	return TRUE;
}

CBaseObject* CSttModuleUse::Clone()
{
	CSttModuleUse *p = new CSttModuleUse();
	Copy(p);
	return p;
}

CBaseObject* CSttModuleUse::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttModuleUse *p = new CSttModuleUse();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttModuleUse::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CSTTMODULE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttModuleUse::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttSystemConfigXmlRWKeys *pXmlKeys = (CSttSystemConfigXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttModuleKey)
	{
		pNew = new CSttModule();
	}

	return pNew;
}

CExBaseObject* CSttModuleUse::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CSTTMODULE)
	{
		pNew = new CSttModule();
	}

	return pNew;
}
