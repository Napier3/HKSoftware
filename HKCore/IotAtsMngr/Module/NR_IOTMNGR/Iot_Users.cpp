//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_Users.cpp  CIot_Users


#include "stdafx.h"
#include "Iot_Users.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_Users::CIot_Users()
{
	//初始化属性

	//初始化成员变量
}

CIot_Users::~CIot_Users()
{
}

long CIot_Users::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_Users::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_Users::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CIot_Users::InitAfterRead()
{
}

BOOL CIot_Users::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_Users *p = (CIot_Users*)pObj;

	return TRUE;
}

BOOL CIot_Users::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_Users *p = (CIot_Users*)pDest;

	return TRUE;
}

CBaseObject* CIot_Users::Clone()
{
	CIot_Users *p = new CIot_Users();
	Copy(p);
	return p;
}

CBaseObject* CIot_Users::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_Users *p = new CIot_Users();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIot_Users::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOT_USER)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIot_Users::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIot_UserKey)
	{
		pNew = new CIot_User();
	}

	return pNew;
}

CExBaseObject* CIot_Users::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOT_USER)
	{
		pNew = new CIot_User();
	}

	return pNew;
}
CExBaseObject* CIot_Users::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CIot_User();

	return pNew;
}
