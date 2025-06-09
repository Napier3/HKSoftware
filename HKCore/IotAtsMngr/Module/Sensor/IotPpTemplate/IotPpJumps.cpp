//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IotPpJumps.cpp  CIotPpJumps


#include "stdafx.h"
#include "IotPpJumps.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIotPpJumps::CIotPpJumps()
{
	//初始化属性

	//初始化成员变量
}

CIotPpJumps::~CIotPpJumps()
{
}

long CIotPpJumps::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIOTPPXmlRWKeys *pXmlKeys = (CIOTPPXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIotPpJumps::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIOTPPXmlRWKeys *pXmlKeys = (CIOTPPXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIotPpJumps::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CIotPpJumps::InitAfterRead()
{
}

BOOL CIotPpJumps::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIotPpJumps *p = (CIotPpJumps*)pObj;

	return TRUE;
}

BOOL CIotPpJumps::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIotPpJumps *p = (CIotPpJumps*)pDest;

	return TRUE;
}

CBaseObject* CIotPpJumps::Clone()
{
	CIotPpJumps *p = new CIotPpJumps();
	Copy(p);
	return p;
}

CBaseObject* CIotPpJumps::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIotPpJumps *p = new CIotPpJumps();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIotPpJumps::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOTPPJUMP)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIotPpJumps::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIOTPPXmlRWKeys *pXmlKeys = (CIOTPPXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIotPpJumpKey)
	{
		pNew = new CIotPpJump();
	}

	return pNew;
}

CExBaseObject* CIotPpJumps::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOTPPJUMP)
	{
		pNew = new CIotPpJump();
	}

	return pNew;
}
