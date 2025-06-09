//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_Engines.cpp  CIot_Engines


#include "stdafx.h"
#include "Iot_Engines.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_Engines::CIot_Engines()
{
	//初始化属性

	//初始化成员变量
}

CIot_Engines::~CIot_Engines()
{
}

long CIot_Engines::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_Engines::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_Engines::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CIot_Engines::InitAfterRead()
{
}

BOOL CIot_Engines::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_Engines *p = (CIot_Engines*)pObj;

	return TRUE;
}

BOOL CIot_Engines::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_Engines *p = (CIot_Engines*)pDest;

	return TRUE;
}

CBaseObject* CIot_Engines::Clone()
{
	CIot_Engines *p = new CIot_Engines();
	Copy(p);
	return p;
}

CBaseObject* CIot_Engines::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_Engines *p = new CIot_Engines();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIot_Engines::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOT_ENGINE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIot_Engines::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIot_EngineKey)
	{
		pNew = new CIot_Engine();
	}

	return pNew;
}

CExBaseObject* CIot_Engines::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOT_ENGINE)
	{
		pNew = new CIot_Engine();
	}

	return pNew;
}
CExBaseObject* CIot_Engines::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CIot_Engine();

	return pNew;
}
