//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_Roles.cpp  CIot_Roles


#include "stdafx.h"
#include "Iot_Roles.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_Roles::CIot_Roles()
{
	//初始化属性

	//初始化成员变量
}

CIot_Roles::~CIot_Roles()
{
}

long CIot_Roles::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_Roles::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_Roles::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CIot_Roles::InitAfterRead()
{
}

BOOL CIot_Roles::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_Roles *p = (CIot_Roles*)pObj;

	return TRUE;
}

BOOL CIot_Roles::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_Roles *p = (CIot_Roles*)pDest;

	return TRUE;
}

CBaseObject* CIot_Roles::Clone()
{
	CIot_Roles *p = new CIot_Roles();
	Copy(p);
	return p;
}

CBaseObject* CIot_Roles::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_Roles *p = new CIot_Roles();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIot_Roles::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOT_ROLE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIot_Roles::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIot_RoleKey)
	{
		pNew = new CIot_Role();
	}

	return pNew;
}

CExBaseObject* CIot_Roles::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOT_ROLE)
	{
		pNew = new CIot_Role();
	}

	return pNew;
}
CExBaseObject* CIot_Roles::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CIot_Role();

	return pNew;
}
