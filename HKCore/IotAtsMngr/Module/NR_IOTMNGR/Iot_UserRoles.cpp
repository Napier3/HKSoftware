//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_UserRoles.cpp  CIot_UserRoles


#include "stdafx.h"
#include "Iot_UserRoles.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_UserRoles::CIot_UserRoles()
{
	//初始化属性

	//初始化成员变量
}

CIot_UserRoles::~CIot_UserRoles()
{
}

long CIot_UserRoles::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_UserRoles::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_UserRoles::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CIot_UserRoles::InitAfterRead()
{
}

BOOL CIot_UserRoles::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_UserRoles *p = (CIot_UserRoles*)pObj;

	return TRUE;
}

BOOL CIot_UserRoles::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_UserRoles *p = (CIot_UserRoles*)pDest;

	return TRUE;
}

CBaseObject* CIot_UserRoles::Clone()
{
	CIot_UserRoles *p = new CIot_UserRoles();
	Copy(p);
	return p;
}

CBaseObject* CIot_UserRoles::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_UserRoles *p = new CIot_UserRoles();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIot_UserRoles::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOT_ROLERIGHT)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIot_UserRoles::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIot_RoleRightKey)
	{
		pNew = new CIot_RoleRight();
	}

	return pNew;
}

CExBaseObject* CIot_UserRoles::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOT_ROLERIGHT)
	{
		pNew = new CIot_RoleRight();
	}

	return pNew;
}
CExBaseObject* CIot_UserRoles::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CIot_RoleRight();

	return pNew;
}
