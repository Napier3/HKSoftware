//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_Factorys.cpp  CIot_Factorys


#include "stdafx.h"
#include "Iot_Factorys.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_Factorys::CIot_Factorys()
{
	//初始化属性

	//初始化成员变量
}

CIot_Factorys::~CIot_Factorys()
{
}

long CIot_Factorys::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_Factorys::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_Factorys::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CIot_Factorys::InitAfterRead()
{
}

BOOL CIot_Factorys::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_Factorys *p = (CIot_Factorys*)pObj;

	return TRUE;
}

BOOL CIot_Factorys::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_Factorys *p = (CIot_Factorys*)pDest;

	return TRUE;
}

CBaseObject* CIot_Factorys::Clone()
{
	CIot_Factorys *p = new CIot_Factorys();
	Copy(p);
	return p;
}

CBaseObject* CIot_Factorys::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_Factorys *p = new CIot_Factorys();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIot_Factorys::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOT_FACTORY)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIot_Factorys::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIot_FactoryKey)
	{
		pNew = new CIot_Factory();
	}

	return pNew;
}

CExBaseObject* CIot_Factorys::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOT_FACTORY)
	{
		pNew = new CIot_Factory();
	}

	return pNew;
}
CExBaseObject* CIot_Factorys::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CIot_Factory();

	return pNew;
}
