//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IotPpDataList.cpp  CIotPpDataList


#include "stdafx.h"
#include "IotPpDataList.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIotPpDataList::CIotPpDataList()
{
	//初始化属性

	//初始化成员变量
}

CIotPpDataList::~CIotPpDataList()
{
}

long CIotPpDataList::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIOTPPXmlRWKeys *pXmlKeys = (CIOTPPXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIotPpDataList::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIOTPPXmlRWKeys *pXmlKeys = (CIOTPPXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIotPpDataList::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CIotPpDataList::InitAfterRead()
{
}

BOOL CIotPpDataList::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIotPpDataList *p = (CIotPpDataList*)pObj;

	return TRUE;
}

BOOL CIotPpDataList::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIotPpDataList *p = (CIotPpDataList*)pDest;

	return TRUE;
}

CBaseObject* CIotPpDataList::Clone()
{
	CIotPpDataList *p = new CIotPpDataList();
	Copy(p);
	return p;
}

CBaseObject* CIotPpDataList::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIotPpDataList *p = new CIotPpDataList();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIotPpDataList::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOTPPVALUE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIotPpDataList::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIOTPPXmlRWKeys *pXmlKeys = (CIOTPPXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIotPpValueKey)
	{
		pNew = new CIotPpValue();
	}

	return pNew;
}

CExBaseObject* CIotPpDataList::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOTPPVALUE)
	{
		pNew = new CIotPpValue();
	}

	return pNew;
}
