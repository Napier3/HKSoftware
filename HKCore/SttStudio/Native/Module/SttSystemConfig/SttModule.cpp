//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttModule.cpp  CSttModule


#include "stdafx.h"
#include "SttModule.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttModule::CSttModule()
{
	//初始化属性

	//初始化成员变量
}

CSttModule::~CSttModule()
{
}

long CSttModule::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSttSystemConfigXmlRWKeys *pXmlKeys = (CSttSystemConfigXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttModule::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttSystemConfigXmlRWKeys *pXmlKeys = (CSttSystemConfigXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttModule::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

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

void CSttModule::InitAfterRead()
{
}

BOOL CSttModule::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttModule *p = (CSttModule*)pObj;

	return TRUE;
}

BOOL CSttModule::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSttModule *p = (CSttModule*)pDest;

	return TRUE;
}

CBaseObject* CSttModule::Clone()
{
	CSttModule *p = new CSttModule();
	Copy(p);
	return p;
}

CBaseObject* CSttModule::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttModule *p = new CSttModule();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

