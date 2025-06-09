//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttXuiDataBase.cpp  CSttXuiDataBase


#include "stdafx.h"
#include "SttXuiDataBase.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttXuiDataBase::CSttXuiDataBase()
{
	//初始化属性

	//初始化成员变量
}

CSttXuiDataBase::~CSttXuiDataBase()
{
}

long CSttXuiDataBase::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode , pXmlRWKeys);
	CSttXMainConfigXmlRWKeys *pXmlKeys = (CSttXMainConfigXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttXuiDataBase::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc , oElement, pXmlRWKeys);
	CSttXMainConfigXmlRWKeys *pXmlKeys = (CSttXMainConfigXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttXuiDataBase::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CSttXuiDataBase::InitAfterRead()
{
}

BOOL CSttXuiDataBase::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSttXuiDataBase *p = (CSttXuiDataBase*)pObj;

	return TRUE;
}

BOOL CSttXuiDataBase::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttXuiDataBase *p = (CSttXuiDataBase*)pDest;

	return TRUE;
}

CBaseObject* CSttXuiDataBase::Clone()
{
	CSttXuiDataBase *p = new CSttXuiDataBase();
	Copy(p);
	return p;
}

CBaseObject* CSttXuiDataBase::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttXuiDataBase *p = new CSttXuiDataBase();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttXuiDataBase::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CSttXuiDataBase::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttXMainConfigXmlRWKeys *pXmlKeys = (CSttXMainConfigXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CSttXuiDataBase::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
