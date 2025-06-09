//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IotPpParses.cpp  CIotPpParses


#include "stdafx.h"
#include "IotPpParses.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIotPpParses::CIotPpParses()
{
	//初始化属性

	//初始化成员变量
}

CIotPpParses::~CIotPpParses()
{
}

long CIotPpParses::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIOTPPXmlRWKeys *pXmlKeys = (CIOTPPXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIotPpParses::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIOTPPXmlRWKeys *pXmlKeys = (CIOTPPXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIotPpParses::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CIotPpParses::InitAfterRead()
{
}

BOOL CIotPpParses::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIotPpParses *p = (CIotPpParses*)pObj;

	return TRUE;
}

BOOL CIotPpParses::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIotPpParses *p = (CIotPpParses*)pDest;

	return TRUE;
}

CBaseObject* CIotPpParses::Clone()
{
	CIotPpParses *p = new CIotPpParses();
	Copy(p);
	return p;
}

CBaseObject* CIotPpParses::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIotPpParses *p = new CIotPpParses();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIotPpParses::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOTPPPARSE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIotPpParses::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIOTPPXmlRWKeys *pXmlKeys = (CIOTPPXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIotPpParseKey)
	{
		pNew = new CIotPpParse();
	}

	return pNew;
}

CExBaseObject* CIotPpParses::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOTPPPARSE)
	{
		pNew = new CIotPpParse();
	}

	return pNew;
}
