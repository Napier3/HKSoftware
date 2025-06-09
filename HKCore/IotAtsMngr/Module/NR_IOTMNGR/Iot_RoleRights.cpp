//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_RoleRights.cpp  CIot_RoleRights


#include "stdafx.h"
#include "Iot_RoleRights.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_RoleRights::CIot_RoleRights()
{
	//初始化属性

	//初始化成员变量
}

CIot_RoleRights::~CIot_RoleRights()
{
}

long CIot_RoleRights::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_RoleRights::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_RoleRights::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CIot_RoleRights::InitAfterRead()
{
}

BOOL CIot_RoleRights::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_RoleRights *p = (CIot_RoleRights*)pObj;

	return TRUE;
}

BOOL CIot_RoleRights::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_RoleRights *p = (CIot_RoleRights*)pDest;

	return TRUE;
}

CBaseObject* CIot_RoleRights::Clone()
{
	CIot_RoleRights *p = new CIot_RoleRights();
	Copy(p);
	return p;
}

CBaseObject* CIot_RoleRights::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_RoleRights *p = new CIot_RoleRights();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIot_RoleRights::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOT_ROLERIGHT)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIot_RoleRights::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIot_RoleRightKey)
	{
		pNew = new CIot_RoleRight();
	}

	return pNew;
}

CExBaseObject* CIot_RoleRights::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOT_ROLERIGHT)
	{
		pNew = new CIot_RoleRight();
	}

	return pNew;
}
CExBaseObject* CIot_RoleRights::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CIot_RoleRight();

	return pNew;
}
