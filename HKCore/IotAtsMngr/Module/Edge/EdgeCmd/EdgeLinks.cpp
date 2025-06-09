//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgeLink.cpp  CEdgeLinks


#include "stdafx.h"
#include "EdgeLinks.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEdgeLinks::CEdgeLinks()
{
	//初始化属性

	//初始化成员变量
}

CEdgeLinks::~CEdgeLinks()
{
}

long CEdgeLinks::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEdgeLinks::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEdgeLinks::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CEdgeLinks::InitAfterRead()
{
	m_strID = GetXmlElementKey();
}

BOOL CEdgeLinks::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	return TRUE;
}

BOOL CEdgeLinks::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	return TRUE;
}

CBaseObject* CEdgeLinks::Clone()
{
	CEdgeLinks *p = new CEdgeLinks();
	Copy(p);
	return p;
}

CBaseObject* CEdgeLinks::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CEdgeLinks *p = new CEdgeLinks();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CEdgeLinks::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CEdgeLinks::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	return pNew;
}

CExBaseObject* CEdgeLinks::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	return pNew;
}