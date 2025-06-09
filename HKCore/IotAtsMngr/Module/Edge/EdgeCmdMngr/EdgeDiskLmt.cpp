//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgeDiskLmt.cpp  CEdgeDiskLmt


#include "stdafx.h"
#include "EdgeDiskLmt.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEdgeDiskLmt::CEdgeDiskLmt()
{
	//初始化属性

	//初始化成员变量
}

CEdgeDiskLmt::~CEdgeDiskLmt()
{
}

long CEdgeDiskLmt::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeDatas::XmlReadOwn(oNode, pXmlRWKeys);
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEdgeDiskLmt::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeDatas::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEdgeDiskLmt::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CEdgeDatas::SerializeOwn(oBinaryBuffer);
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

void CEdgeDiskLmt::InitAfterRead()
{
}

BOOL CEdgeDiskLmt::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CEdgeDatas::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CEdgeDiskLmt *p = (CEdgeDiskLmt*)pObj;

	return TRUE;
}

BOOL CEdgeDiskLmt::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEdgeDatas::CopyOwn(pDest);

	CEdgeDiskLmt *p = (CEdgeDiskLmt*)pDest;

	return TRUE;
}

CBaseObject* CEdgeDiskLmt::Clone()
{
	CEdgeDiskLmt *p = new CEdgeDiskLmt();
	Copy(p);
	return p;
}

CBaseObject* CEdgeDiskLmt::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CEdgeDiskLmt *p = new CEdgeDiskLmt();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CEdgeDiskLmt::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CEdgeDiskLmt::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CEdgeDiskLmt::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
