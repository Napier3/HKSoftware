//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Sys_Users.cpp  CSys_Users


#include "stdafx.h"
#include "Sys_Users.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSys_Users::CSys_Users()
{
	//初始化属性

	//初始化成员变量
}

CSys_Users::~CSys_Users()
{
}

long CSys_Users::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSys_Users::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSys_Users::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CSys_Users::InitAfterRead()
{
}

BOOL CSys_Users::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSys_Users *p = (CSys_Users*)pObj;

	return TRUE;
}

BOOL CSys_Users::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSys_Users *p = (CSys_Users*)pDest;

	return TRUE;
}

CBaseObject* CSys_Users::Clone()
{
	CSys_Users *p = new CSys_Users();
	Copy(p);
	return p;
}

CBaseObject* CSys_Users::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSys_Users *p = new CSys_Users();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSys_Users::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CSYS_USER)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSys_Users::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSys_UserKey)
	{
		pNew = new CSys_User();
	}

	return pNew;
}

CExBaseObject* CSys_Users::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CSYS_USER)
	{
		pNew = new CSys_User();
	}

	return pNew;
}
CExBaseObject* CSys_Users::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CSys_User();

	return pNew;
}
