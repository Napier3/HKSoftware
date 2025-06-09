//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_Logs.cpp  CIot_Logs


#include "stdafx.h"
#include "Iot_Logs.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_Logs::CIot_Logs()
{
	//初始化属性

	//初始化成员变量
}

CIot_Logs::~CIot_Logs()
{
}

long CIot_Logs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_Logs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_Logs::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CIot_Logs::InitAfterRead()
{
}

BOOL CIot_Logs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_Logs *p = (CIot_Logs*)pObj;

	return TRUE;
}

BOOL CIot_Logs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_Logs *p = (CIot_Logs*)pDest;

	return TRUE;
}

CBaseObject* CIot_Logs::Clone()
{
	CIot_Logs *p = new CIot_Logs();
	Copy(p);
	return p;
}

CBaseObject* CIot_Logs::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_Logs *p = new CIot_Logs();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIot_Logs::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOT_LOG)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIot_Logs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIot_LogKey)
	{
		pNew = new CIot_Log();
	}

	return pNew;
}

CExBaseObject* CIot_Logs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOT_LOG)
	{
		pNew = new CIot_Log();
	}

	return pNew;
}
CExBaseObject* CIot_Logs::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CIot_Log();

	return pNew;
}
