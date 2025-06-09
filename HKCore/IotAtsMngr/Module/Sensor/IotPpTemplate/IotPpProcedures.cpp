//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IotPpProcedures.cpp  CIotPpProcedures


#include "stdafx.h"
#include "IotPpProcedures.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIotPpProcedures::CIotPpProcedures()
{
	//初始化属性

	//初始化成员变量
}

CIotPpProcedures::~CIotPpProcedures()
{
}

long CIotPpProcedures::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIOTPPXmlRWKeys *pXmlKeys = (CIOTPPXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIotPpProcedures::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIOTPPXmlRWKeys *pXmlKeys = (CIOTPPXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIotPpProcedures::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CIotPpProcedures::InitAfterRead()
{
}

BOOL CIotPpProcedures::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIotPpProcedures *p = (CIotPpProcedures*)pObj;

	return TRUE;
}

BOOL CIotPpProcedures::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIotPpProcedures *p = (CIotPpProcedures*)pDest;

	return TRUE;
}

CBaseObject* CIotPpProcedures::Clone()
{
	CIotPpProcedures *p = new CIotPpProcedures();
	Copy(p);
	return p;
}

CBaseObject* CIotPpProcedures::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIotPpProcedures *p = new CIotPpProcedures();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIotPpProcedures::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOTPPPROCEDURE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIotPpProcedures::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIOTPPXmlRWKeys *pXmlKeys = (CIOTPPXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIotPpProcedureKey)
	{
		pNew = new CIotPpProcedure();
	}

	return pNew;
}

CExBaseObject* CIotPpProcedures::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOTPPPROCEDURE)
	{
		pNew = new CIotPpProcedure();
	}

	return pNew;
}
